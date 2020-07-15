#pragma once
#include <random>
#include <ctime>

namespace mobagen {
  class Random {
  public:
    typedef struct {
    public:
      int s0;
      int s1;
      int s2;
      int s3;
    } State;

//  insideUnitCircle	Returns a random point inside a circle with radius 1 (Read Only).
//  insideUnitSphere	Returns a random point inside a sphere with radius 1 (Read Only).
//  onUnitSphere	Returns a random point on the surface of a sphere with radius 1 (Read Only).
//  rotation	Returns a random rotation (Read Only).
//  rotationUniform	Returns a random rotation with uniform distribution (Read Only).
//  state	Gets/Sets the full internal state of the random number generator.
//  value	Returns a random number between 0.0 [inclusive] and 1.0 [inclusive] (Read Only).

//  ColorHSV	Generates a random color from HSV and alpha ranges.
    /// @brief Initializes the random number generator state with a seed.
    static void InitState(int seed);

    /// @brief Returns a random int number between and min [inclusive] and max [inclusive] (Read Only).
    static int Range(int min, int max);

    /// @brief Returns a random float number between and min [inclusive] and max [inclusive] (Read Only).
    static float Range(float min, float max);

  private:
    // todo: fix this abomination, use pcg pls
    static std::mt19937_64 mt;
  };
}