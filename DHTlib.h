#include "Arduino.h"

class DHT{
public:
  DHT(byte pin);
  compute();
  getT();
  getRH();
  expectPulse(bool lvl);

private:
byte Pin;
int count;
unsigned char RH_int , RH_dec , T_int , T_dec , sum , pulse[80], lowCycle, highCycle;
};
