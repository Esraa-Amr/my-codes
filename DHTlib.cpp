#include "Arduino.h"
#include "DHTlib.h"

DHT::DHT(byte pin)
{
  Pin=pin;
   RH_int = 0, RH_dec = 0, T_int = 0, T_dec = 0, sum = 0, pulse[80];
   count=0;
}
DHT:: expectPulse(bool lvl)
{
  count=0;
  while(digitalRead(Pin)==lvl) count++;
  return count;
  }
DHT::compute()
{
  pinMode(Pin, OUTPUT);
    digitalWrite(Pin, HIGH);
    delay(1000);
    digitalWrite(Pin, LOW);
    delay(18);
    digitalWrite(Pin, HIGH);
    delayMicroseconds(40);
    pinMode(Pin, INPUT);
    if (digitalRead(Pin) == LOW)
    {
      while (digitalRead(Pin) == LOW)
      {
      }
      while (digitalRead(Pin) == HIGH)
      {
      }
    }
    
            else
            {
                Serial.println("NOT RESPONDING");
                return ;
            }
            for (int i = 0; i < 80; i++)
                pulse[i] = expectPulse(i % 2);
            for (int i = 0; i < 40; i++)
            {
                lowCycle = pulse[i * 2];
                highCycle = pulse[(i * 2) + 1];
                if (i < 8)
                {
                    RH_int <<= 1;
                    if (highCycle > lowCycle) RH_int |= 1;
                }
                if (i < 16)
                {
                    RH_dec <<= 1;
                    if (highCycle > lowCycle) RH_dec |= 1;
                }
                if (i < 24)
                {
                    T_int <<= 1;
                    if (highCycle > lowCycle) T_int |= 1;
                }
                if (i < 32)
                {
                    T_dec <<= 1;
                    if (highCycle > lowCycle) T_dec |= 1;
                }
                if (i < 40)
                {
                    sum <<= 1;
                    if (highCycle > lowCycle) sum |= 1;
                }
            }
            if (sum != RH_int + RH_dec + T_int + T_dec)
            {
                Serial.println("ERROR !!!");
            }
    
}
DHT::getT()
{
  compute();
  Serial.print("T= ");
  Serial.print(T_int); Serial.print(".");
        Serial.println(T_dec);
}
DHT::getRH()
{
  compute();
  Serial.print("RH= ");
  Serial.print(RH_int); Serial.print(".");
        Serial.println(RH_dec);
}
