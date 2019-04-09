#pragma once
#include "Header.h"
#include "Philosopher.h"
#include "CircularHelper.h"

class PhilosophersStack
{
public:
  PhilosophersStack(std::list<Philosopher>& list);
  ~PhilosophersStack();

  std::list <Philosopher> &OPList;//Lista Original completa de filosofos
  std::list <Philosopher*> philosopherList;//Lista de filosofos
  std::list <Philosopher*> apprenticeList;//Lista de aprendices
  void run();
};

