#include "Philosopher.h"

using namespace std::chrono_literals;

Philosopher::Philosopher(Chopstick * leftChopstick, Chopstick * rightChopstick, int philosopherNumber, int leftChopstickNumber, int rightChopstickNumber, float timeMS)
{
  m_leftChopstick = leftChopstick;
  m_rightChopstick = rightChopstick;
  m_philosopherNumber = philosopherNumber;
  m_leftChopstickNumber = leftChopstickNumber;
  m_rightChopstickNumber = rightChopstickNumber;
  m_timeMilliseconds = 0;
  m_totalTime = timeMS;
  m_State = State::THINKING;
  m_iMeals = 0;
}

Philosopher::~Philosopher()
{
}

bool Philosopher::RR;

float Philosopher::m_RRtime;

int Philosopher::m_iMeals;

void Philosopher::eat()
{
  if (m_leftChopstick == m_rightChopstick)
    throw std::exception("Palillos izquierdos y derechos no deben ser el mismo");

  m_State = State::HUNGRY;

  if (!m_leftChopstick->getTaken() && !m_rightChopstick->getTaken())
  {
    m_leftChopstick->TakeChopstick();
    m_rightChopstick->TakeChopstick();

    m_State = State::EATING;

    std::cout << "   Filosofo " + std::to_string(m_philosopherNumber) + " recoge palillo " + std::to_string(m_leftChopstickNumber) + ".\n";
    std::cout << "   Filosofo " + std::to_string(m_philosopherNumber) + " recoge palillo " + std::to_string(m_rightChopstickNumber) + ".\n";
    std::cout << "Filosofo " + std::to_string(m_philosopherNumber) + " come.\n";
    std::cout << "Filosofo " + std::to_string(m_philosopherNumber) + " come por " + std::to_string(m_timeMilliseconds / 1000.0f) + ".\n";

    if (RR)
    {
      if (m_totalTime >= m_RRtime)
      {
        m_timeMilliseconds = m_RRtime;
      }
      else
      {
        m_timeMilliseconds = m_totalTime;
      }
    }
    else
    {
      m_timeMilliseconds = m_totalTime;
    }

    while (m_timeMilliseconds > 0)
    {
      if (m_State == State::SUSPEND)
      {
        while (m_leftChopstick->getTaken() || m_rightChopstick->getTaken())
        {
          std::this_thread::sleep_for(1ms);
        }
        m_leftChopstick->TakeChopstick();
        m_rightChopstick->TakeChopstick();

        std::cout << "   Filosofo " + std::to_string(m_philosopherNumber) + " vuelve a recoger palillo " + std::to_string(m_leftChopstickNumber) + ".\n";
        std::cout << "   Filosofo " + std::to_string(m_philosopherNumber) + " vuelve a recoger palillo " + std::to_string(m_rightChopstickNumber) + ".\n";
        std::cout << "Filosofo " + std::to_string(m_philosopherNumber) + " continua comiendo.\n";
        std::cout << "Filosofo " + std::to_string(m_philosopherNumber) + " come por " + std::to_string(m_timeMilliseconds / 1000.0f) + ".\n";
      }
      --m_timeMilliseconds;
      --m_totalTime;
      std::this_thread::sleep_for(1ms);
    }
    m_leftChopstick->DropChopstick();
    m_rightChopstick->DropChopstick();

    std::cout << "   Filosofo " + std::to_string(m_philosopherNumber) + " suelta palillo " + std::to_string(m_leftChopstickNumber) + ".\n";
    std::cout << "   Filosofo " + std::to_string(m_philosopherNumber) + " suelta palillo " + std::to_string(m_rightChopstickNumber) + ".\n";

    m_State = State::THINKING;
  }
}

void Philosopher::thinking()
{
  std::chrono::milliseconds timeout(Random::randomInt(500, 2000, std::rand() % (m_leftChopstickNumber + m_rightChopstickNumber)));
  std::cout << "        Filosofo " + std::to_string(m_philosopherNumber) + " esta pensando durante " + std::to_string(timeout.count() / 1000.0f) + ".\n";
  std::this_thread::sleep_for(timeout);
}

void Philosopher::run()
{
  while (m_totalTime > 0)
  {
    thinking();
    eat();
  }
  m_State = State::FULL;
  std::cout << "Filosofo " + std::to_string(m_philosopherNumber) + " esta lleno.\n";
}
void Philosopher::Suspend()
{
  m_State = State::SUSPEND;
  m_leftChopstick->DropChopstick();
  m_rightChopstick->DropChopstick();
};