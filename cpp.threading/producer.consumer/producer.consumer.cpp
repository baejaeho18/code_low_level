#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>

using namespace std;

void producer(queue<string>* downloaded_pages, mutex* m, int index, condition_variable* cv) 
{
  for (int i = 0; i < 5; i++) 
  {
    // 웹사이트를 다운로드 하는데 걸리는 시간이라 생각하면 된다.
    // 각 쓰레드 별로 다운로드 하는데 걸리는 시간이 다르다.
    this_thread::sleep_for(chrono::milliseconds(100 * index));
    string content = "site : " + to_string(i) + " from thread(" + to_string(index) + ")\n";

    // data 는 쓰레드 사이에서 공유되므로 critical section 에 넣어야 한다.
    m->lock();
    downloaded_pages->push(content);
    m->unlock();

    // consumer 에게 content 가 준비되었음을 알린다.
    cv->notify_one();
  } 
} 

void consumer(queue<string>* downloaded_pages, mutex* m,
              int* num_processed, condition_variable* cv) 
{
  while (*num_processed < 25)  // 25는 탈출조건
  {
    unique_lock<mutex> lk(*m);

    cv->wait(lk, [&] { return !downloaded_pages->empty() || *num_processed == 25; });

    if (*num_processed == 25) 
    {
      lk.unlock();
      return;
    }

    // 맨 앞의 페이지를 읽고 대기 목록에서 제거한다.
    string content = downloaded_pages->front();
    downloaded_pages->pop();

    (*num_processed)++;
    lk.unlock();

    cout << content; // content 를 처리한다.
    this_thread::sleep_for(chrono::milliseconds(80));
  }
}

int main() 
{
  queue<string> downloaded_pages;
  mutex m;
  condition_variable cv;

  vector<thread> producers;
  for (int i = 0; i < 5; i++)
    producers.push_back(thread(producer, &downloaded_pages, &m, i + 1, &cv));

  int num_processed = 0;
  vector<thread> consumers;
  for (int i = 0; i < 3; i++)
    consumers.push_back(thread(consumer, &downloaded_pages, &m, &num_processed, &cv));

  for (int i = 0; i < 5; i++)
    producers[i].join();

  cv.notify_all(); // wakeup all the sleeping threads

  for (int i = 0; i < 3; i++)
    consumers[i].join();
}