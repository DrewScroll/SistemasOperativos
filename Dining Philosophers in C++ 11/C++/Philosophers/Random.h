#pragma once
#include <random>
#include <ctime>

namespace Random
{
  static int randomInt(int min, int max, int salt = 0)
  {
    std::default_random_engine generator;
    generator.seed(static_cast<int>(std::time(0) + salt));

    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
  }
}