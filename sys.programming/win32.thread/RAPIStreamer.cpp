#include "stdafx.h"
#include "RAPIStreamer.h"
#include <string.h>
#include <stdlib.h>

const int FILE_SIZE_3K  =  3 * 1024;
const int FILE_SIZE_5K  =  5 * 1024;
const int FILE_SIZE_10K = 10 * 1024;

HANDLE g_hFileMap         = NULL; // File mapping object for sharing information with serial app
HANDLE g_hD2PDAEvent      = NULL; // ����ũž���� PDA�� ������ ����Ÿ�� ���� ��� ����ϴ� Event
HANDLE g_hPDA2DEvent      = NULL;    
HANDLE g_hSMClearEvent    = NULL; // Shared Memory�� clear�ϴٴ� ���� ��Ÿ���� Event
HANDLE g_hThreadExitEvent = NULL;
HANDLE g_hThreadExitReady = NULL;

HANDLE g_hMutex = NULL;

struct CThreadContext {
  char        *pSharedMemory;  // assume this info is NULL terminated..
  IRAPIStream *pStream;        //
  HANDLE       hPDA2DEvent;
  HANDLE       hThreadExitEvent;
};


BOOL AttachExistingFileMapping()
{                       
  g_hFileMap = ::CreateFileMapping(INVALID_HANDLE_VALUE, 
      NULL, 
      PAGE_READWRITE, 
      0, 
      FILE_SIZE_3K, 
      TEXT("DirtFileMapping"));

  if (g_hFileMap && GetLastError() == ERROR_ALREADY_EXISTS) 
    return TRUE;      

  ::CloseHandle(g_hFileMap);
  return FALSE;
}

BOOL InitEvents()
{
  // ���������� �����Ǵ� Kernel Object
  //
  g_hD2PDAEvent   = ::CreateEvent(NULL, FALSE, FALSE, TEXT("DirtD2PDAEvent"));
  g_hPDA2DEvent   = ::CreateEvent(NULL, FALSE, FALSE, TEXT("DirtPDA2DEvent"));
  g_hSMClearEvent = ::CreateEvent(NULL, FALSE,  TRUE, TEXT("DirtSMClearEvent"));

  //
  g_hMutex = ::CreateMutex(NULL, FALSE, TEXT("DirtMutex"));

  // �� �����尣 ����ȭ�� ���� ���Ǵ� Event
  g_hThreadExitEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL);
  g_hThreadExitReady = ::CreateEvent(NULL, FALSE, FALSE, NULL);

  return TRUE;
}

DWORD PDAThreadProc(PVOID arg)
{
  CThreadContext* pContext = (CThreadContext*)arg;

  HANDLE h[2] = { pContext->hThreadExitEvent, pContext->hPDA2DEvent };

  while (true) 
  {
    char buffer[FILE_SIZE_10K] = { 0 };
    // 1. PDA�� ���� ����Ÿ�� ��ٸ���.
    DWORD r1 = ::WaitForMultipleObjects(2, h, FALSE, INFINITE);

    // 2. ���� �̺�Ʈ�̸� �����Ѵ�.
    if (r1 != WAIT_OBJECT_0 + 1) break;

    // 3. ����Ÿ�� �б� ���� mutex�� ��´�.
    DWORD r2 = ::WaitForSingleObject(g_hMutex, INFINITE);
    // if (r2 != WAIT_OBJECT_0) { //�ɰ��� ����.  break; }

    // 4. shared memory���� ����Ÿ�� �д´�. (���������� ����Ÿ��
    // NULL-termination�Ǿ��ִٰ� �����Ѵ�)
    strcpy(buffer, pContext->pSharedMemory);

    // 5. PC�� �����Ѵ�.
    DWORD nBytesToSend = strlen(buffer);
    DWORD nBytesWritten; 
    pContext->pStream->Write(buffer, nBytesToSend, &nBytesWritten);
    pContext->pSharedMemory[0] = NULL;

    //
    // 6. PDA�� �ٽ� ����Ÿ�� ������ �� �ִٰ� �ñ׳��� ������.
    ::SetEvent(g_hSMClearEvent);

    // 
    // 7. mutex�� ���´�.
    ::ReleaseMutex(g_hMutex);
  }

  ::SetEvent(g_hThreadExitReady);

  return DWORD(1);
}

// TODO
// ��Ȯ�ϰ� Ż�� ������ ã�Ƴ���.
//
bool shouldOut(char *buffer)
{
  int end = strlen(buffer);
  if (end != 3) false;

  return (buffer[1] == char(7));
}

int ReadString(IRAPIStream* pStream, char *buffer)
{
  char em1 = 3;
  char em2 = 6;
  int  pos = 0;
  while (true) 
  {
    char byte_;
    DWORD dwWritten;
    pStream->Read(&byte_, 1, &dwWritten);
    buffer[pos++] = byte_;
    if (byte_ == em1 || byte_ == em2) 
      break;
  }

  return pos;
}

RAPISTREAMER_API int 
CallRAPIStreamer(DWORD dwInput, BYTE* pInput, DWORD* pcbOutput, BYTE** ppOutput, IRAPIStream* pStream)
{
  // TODO by leech 2003-05-12 �� 
  // �ʱ�ȭ ������ ���⼭ map�ϴ°� ���� �� �𸣰���
  PVOID pView = ::MapViewOfFile(g_hFileMap, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);

  CThreadContext context;
  context.pStream          = pStream;
  context.pSharedMemory    = (char*)pView;
  context.hPDA2DEvent      = g_hPDA2DEvent;
  context.hThreadExitEvent = g_hThreadExitEvent;

  DWORD ThreadID;
  HANDLE hThread = ::CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)PDAThreadProc, &context, NULL, &ThreadID);

  char buffer[FILE_SIZE_3K] = { 0 };
  while (true) 
  {
    // 1. PC���� ����Ÿ�� �д´�.
    memset(buffer, 0x00, FILE_SIZE_3K);

    DWORD nBytesRead = ReadString(pStream, buffer);
    if (shouldOut(buffer)) 
    {
      memset(pView, 0x00, FILE_SIZE_3K);
      break;
    }

    // 2. mutex�� ��´�.
    DWORD r1 = ::WaitForSingleObject(g_hMutex, INFINITE);

    // 3. shared memory�� ����Ÿ�� ����.
    // (����Ÿ�� �������� �ݵ�� NULL-termination �����ش�)
    unsigned i; 
    for (i=0; i<nBytesRead; ++i) context.pSharedMemory[i] = buffer[i];
    context.pSharedMemory[i] = NULL;

    // 4. mutex�� ���´�.
    ::ReleaseMutex(g_hMutex);

    // 5. PDA�� ���� ����Ÿ�� ���������� �˸���.
    ::SetEvent(g_hD2PDAEvent);
  }

  ::SetEvent(g_hThreadExitEvent);
  ::WaitForSingleObject(g_hThreadExitReady, INFINITE);

  ::UnmapViewOfFile(pView);

  ::CloseHandle(g_hFileMap);
  ::CloseHandle(g_hMutex);
  ::CloseHandle(hThread);

  return 1;
}

BOOL 
APIENTRY DllMain(HANDLE hModule, DWORD dwReason, LPVOID lpReserved)
{
  switch (dwReason) 
  {
    case DLL_PROCESS_ATTACH: 

      if (AttachExistingFileMapping())
        return InitEvents();

      ::MessageBox(NULL, L"���� �������α׷��� ���� �ϼ���", L"title", MB_OK);
      return FALSE;

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
      break;
  }
  return TRUE;
}
