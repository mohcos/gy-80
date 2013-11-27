#include "DataSmoother.h"
#include <Arduino.h>

double DataSmoother::alpha = 0.2;
double DataSmoother::lastVal[30] = {0};
double DataSmoother::smoothe(int identifier, double val)
{
  double result = val * alpha + (lastVal[identifier]*(1.0-alpha));
  lastVal[identifier] = result;
  return result;
}
