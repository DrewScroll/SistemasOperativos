#include "PhilosophersStack.h"

PhilosophersStack::PhilosophersStack(std::list<Philosopher>& list): OPList(list)
{
  for (auto it = list.begin(); it != list.end(); ++it)
  {
    if (it->isPhilosopher)
    {
      philosopherList.push_back(&*it);
    }
    else
    {
      apprenticeList.push_back(&*it);
    }
  }
}

PhilosophersStack::~PhilosophersStack()
{
}

void PhilosophersStack::run()
{
  int i;
  do
  {
    i = 0;
    for (auto it = philosopherList.begin(); it != philosopherList.end(); ++it)
    {
      if ((*it)->m_State == State::FULL)
      {
        i++;
        continue;
      }

      auto OPit = std::find(OPList.begin(), OPList.end(), (*it));
      if ((*it)->m_State == State::HUNGRY)
      {
        auto pNext = CircularNext(OPList, OPit);
        if (!pNext->isPhilosopher && pNext->m_State == State::EATING)
        {
          pNext->Suspend();
        }

        auto pPrev = CircularPrev(OPList, OPit);
        if (!pPrev->isPhilosopher && pPrev->m_State == State::EATING)
        {
          pPrev->Suspend();
        }
      }
    }

    for ( auto it = apprenticeList.begin(); it != apprenticeList.end(); ++it)
    {
      std::find(OPList.begin(), OPList.end(), (*it));
    }
  } while (i < philosopherList.size());
}
