#include <Arduino.h>
#include <map>
#include <string>

class DataSmoother{
  public:
    static double alpha;
    double smoothe(int identifier, double val);
    static double lastVal[30];
  private:
};
