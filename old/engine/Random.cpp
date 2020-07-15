#include "Random.hpp"

namespace mobagen {
  // todo: improve this
  std::mt19937_64 Random::mt = std::mt19937_64(time(nullptr));

  void Random::InitState(int seed) {
    mt = std::mt19937_64(seed);
  }

  int Random::Range(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(mt);
  }

  float Random::Range(float min, float max) {
    std::uniform_real_distribution<float> dist(min, max);
    return dist(mt);
  }
}