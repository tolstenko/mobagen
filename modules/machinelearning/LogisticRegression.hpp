#pragma once
#include <vector>

namespace machinelearning {
  class LogisticRegression {
  public:
    static double LossFunction(double expected, double found);
    static double Sigma(double value);
  };
}
