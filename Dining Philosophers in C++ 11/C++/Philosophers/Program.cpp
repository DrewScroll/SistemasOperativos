#include "Header.h"
#include "Chopstick.h"
#include "Philosopher.h"
#include "PhilosophersStack.h"

int NextValue(int i, int size)
{
  return (i + 1) % size;
}

int main()
{ 
  char b = 'c';
  do 
  {
    if (b == 'y')
    {
      Philosopher::m_iMeals += 1;
    }

#if (defined(_WIN32) || defined(WIN32))
    std::system("cls");
#elif defined(__unix__)
    std::system("clear");
#endif

    int numPhilosophers = 0;
    while (numPhilosophers <= 1 || numPhilosophers > 10)
    {
      std::cout << "Define numero total de Filosofos.\n";
      std::cin >> numPhilosophers;
      if (numPhilosophers <= 1)
      {
        std::cout << "Numero invalido, escriba un numero mayor a 1 y menor de 10.\n";
      }
    }

  std::list<Philosopher>philosopher;
  std::vector<Chopstick>chopsticks;
  std::vector<std::thread> tasks;
  std::vector<float>eatingTime;

  eatingTime.resize(numPhilosophers);
  float time = 0.0f;

  std::cout << "Desea usar el algoritmo Round Robin?\n y: Si     n:No\n";
  do {
    std::cin >> b;
  } while (b != 'y' && b != 'n');
  Philosopher::RR = b == 'y';

  if (Philosopher::RR)
  {
    std::cout << "Defina el tiempo para el Round Robin.\n";
    std::cin >> Philosopher::m_RRtime;
  }

  for (int i = 0; i < numPhilosophers; ++i)
  {
    time = 0.0f;
    while (time <= 0.0f)
    {
      std::cout << "Define el tiempo de alimentación del filosofo " + std::to_string(i) + ".\n";
      std::cin >> time;
      if (time <= 0.0f)
      {
        std::cout << "Numero invalido, escriba un numero mayor a 0.\n";
      }
    }
    eatingTime[i] = time;
  }

  chopsticks.resize(numPhilosophers);

  for (int i = 0; i < numPhilosophers; ++i)
  {
    philosopher.emplace_back(&chopsticks[i], &chopsticks[NextValue(i, numPhilosophers)], i, i, NextValue(i, numPhilosophers), eatingTime[i]);
  }

  auto it = philosopher.begin();
  while (it != philosopher.end())
  {
    int Aprendiz;
    std::cout << "Philosofo " << it->getName() <<" es Philosofo o Aprendiz?\n";
    std::cout << "0: Philosofo      1:Aprendiz\n";
    std::cin >> Aprendiz;
    if (Aprendiz == 0)
    {
      it->SetBool(true);
      ++it;
    }
    else if (Aprendiz == 1)
    {
      it->SetBool(false);
      ++it;
    }
    else
    {
      std::cout << "Numero invalido, escriba un numero positivo y menor a la cantidad de filosofos.\n";
    }
  }
  
  PhilosophersStack Stack(philosopher);

  tasks.reserve(numPhilosophers + 1);

    for (auto it = philosopher.begin(); it != philosopher.end(); ++it)
      tasks.emplace_back(&Philosopher::run, it);

    tasks.emplace_back(&PhilosophersStack::run, Stack);

    for (int i = 0; i <= numPhilosophers; ++i)
    {
      tasks[i].join();
    }
    
    std::cout << "Desea continuar?" << std::endl;
    std::cin >> b;
  } while (b == 'y');

  std::cout << "Filosofos comieron " << Philosopher::m_iMeals << " veces." << std::endl;

	return 0;
}