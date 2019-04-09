#pragma once
#include "Header.h"
#include "Chopstick.h"
#include "Random.h"

enum class State {
  UNDEFINED = 0,
  THINKING,
  EATING,
  HUNGRY,
  FULL,
  SUSPEND
};

class PhilosophersStack;

class Philosopher
{
public:
  Philosopher(Chopstick* leftChopstick, Chopstick* rightChopstick, int philosopherNumber, int leftChopstickNumber, int rightChopstickNumber, float timeMS);
  ~Philosopher();

  static bool RR; //Round Robin
  static float m_RRtime;
  static int m_iMeals;

  void run();
  void Suspend();
  void SetBool(bool b) { isPhilosopher = b; }
  int getName() { return m_philosopherNumber; }
  friend class PhilosophersStack;

  bool operator==(Philosopher* other) const { return m_philosopherNumber == other->m_philosopherNumber; }

private:
  Chopstick* m_leftChopstick;
  Chopstick* m_rightChopstick;
  int m_philosopherNumber;
  int m_leftChopstickNumber;
  int m_rightChopstickNumber;
  float m_timeMilliseconds;
  float m_totalTime;
  State m_State;
  bool isPhilosopher;
  
  void eat();
  void thinking();
};

