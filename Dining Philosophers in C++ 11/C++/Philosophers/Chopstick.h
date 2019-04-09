#pragma once
#include "Header.h"

class Chopstick
{
public:
  Chopstick();
  ~Chopstick();

  bool getTaken() { return taken; }
  void TakeChopstick();
  void DropChopstick();

private:
  std::mutex* m;
  std::condition_variable* cv;
  bool taken;
};