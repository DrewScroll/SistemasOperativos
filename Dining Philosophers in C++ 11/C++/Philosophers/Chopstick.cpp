#include "Chopstick.h"

Chopstick::Chopstick()
{
  taken = false;
  m = new std::mutex();
  cv = new std::condition_variable();
}

Chopstick::~Chopstick()
{
  delete m;
  delete cv;
}

void Chopstick::TakeChopstick()
{
  std::unique_lock<std::mutex> Lock(*m);
  while (taken)
  {
    cv->wait(Lock);
  }
  taken = true;
}

void Chopstick::DropChopstick()
{
  std::lock_guard<std::mutex> Lock(*m);
  taken = false;
  cv->notify_one();
}
