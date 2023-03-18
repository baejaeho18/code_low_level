// �Ʒ��� �ҽ��� ���� ������ ��������� C �� �ø� ������
// C++ �� ��� ���� ���Դϴ�.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ImeControl.h"

#include <Imm.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CImeControl::CImeControl()
{
}

CImeControl::~CImeControl()
{
}

void CImeControl::Hangul_On(HWND hWnd)
{
	HIMC hIMC;
	DWORD dwConv, dwSent, dwTemp;

	hIMC = ImmGetContext( hWnd );
	ImmGetConversionStatus( hIMC, &dwConv, &dwSent );

	dwTemp = dwConv & ~IME_CMODE_LANGUAGE;
	dwTemp = IME_CMODE_NATIVE;
	dwConv = dwTemp;

	ImmSetConversionStatus( hIMC, dwConv, dwSent );
	ImmReleaseContext( hWnd, hIMC );
}

void CImeControl::Hangul_Off( HWND hWnd )
{
	HIMC hIMC;
	DWORD dwConv, dwSent, dwTemp;

	hIMC = ImmGetContext( hWnd );
	ImmGetConversionStatus( hIMC, &dwConv, &dwSent );

	dwTemp = dwConv & ~IME_CMODE_LANGUAGE;
	dwConv = dwTemp;

	ImmSetConversionStatus( hIMC, dwConv, dwSent );
	ImmReleaseContext( hWnd, hIMC );
}

void CImeControl::IMENormal( HWND hWnd )
{
	HIMC hIMC;
	DWORD dwConv, dwSent, dwTemp;

	hIMC = ImmGetContext( hWnd );
	ImmGetConversionStatus( hIMC, &dwConv, &dwSent );

	dwTemp = dwConv & ~IME_CMODE_LANGUAGE;
	dwConv = dwTemp;
	dwConv &= ~IME_CMODE_FULLSHAPE;

	ImmSetConversionStatus( hIMC, dwConv, dwSent );
	ImmReleaseContext( hWnd, hIMC );
}

void CImeControl::FullMode_On( HWND hWnd )
{
	HIMC hIMC;
	DWORD dwConv, dwSent;
	hIMC = ImmGetContext( hWnd );
	ImmGetConversionStatus( hIMC, &dwConv, &dwSent );

	dwConv = IME_CMODE_FULLSHAPE;

	ImmSetConversionStatus( hIMC, dwConv, dwSent );
	ImmReleaseContext( hWnd, hIMC );
}

void CImeControl::FullMode_Off( HWND hWnd )
{
	HIMC hIMC;
	DWORD dwConv, dwSent;

	hIMC = ImmGetContext( hWnd );

	ImmGetConversionStatus( hIMC, &dwConv, &dwSent );

	dwConv &= ~IME_CMODE_FULLSHAPE;

	ImmSetConversionStatus( hIMC, dwConv, dwSent );
	ImmReleaseContext( hWnd, hIMC );
}

void CImeControl::Hangul_Full(HWND hWnd)
{
	HIMC hIMC;
	DWORD dwConv, dwSent, dwTemp;

	hIMC = ImmGetContext( hWnd );
	ImmGetConversionStatus( hIMC, &dwConv, &dwSent );

	dwTemp = dwConv & ~IME_CMODE_LANGUAGE;
	dwTemp = IME_CMODE_NATIVE;
	dwConv = dwTemp;
	dwConv = IME_CMODE_FULLSHAPE;

	ImmSetConversionStatus(hIMC, dwConv, dwSent);
	ImmReleaseContext(hWnd, hIMC);
}
