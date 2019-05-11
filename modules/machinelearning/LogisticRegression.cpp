#include "LogisticRegression.hpp"
#include <cmath>

double machinelearning::LogisticRegression::LossFunction(double expected, double found) {
  return -(found*log(expected) + (1-found)*log(1-expected));
}

double machinelearning::LogisticRegression::Sigma(double value) {
  return 1/(1+exp(-value));
}