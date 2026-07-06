// FILE: performanceTest.ino
// AUTHOR: Holman Buenaventura
// PURPOSE: Performance test of quickMap class vs native map()

#include <quickMap.h>

uint32_t start;
uint32_t stop;
uint32_t reference;

volatile long zz = 3000, yy = 20000;
volatile float x;
volatile int z;

quickMap mapper;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.println("QUICKMAP PERFORMANCE TEST");
  Serial.println();
  delay(100);

  //  Get a non optimizable value;
  z = analogRead(A0);

  //  REFERENCE (map nativo de Arduino)
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    x = map(z, 0, 1023, yy, zz);
  }
  stop = micros();
  reference = stop - start;
  Serial.print("MAP NATIVO:\t");
  Serial.println(reference);
  Serial.print(z);
  Serial.print(" -> ");
  Serial.println(x);
  Serial.println();
  delay(100);

  //  QUICKMAP
  mapper.init(0, 1023, yy, zz);
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    x = mapper.map(z);
  }
  stop = micros();
  Serial.print("QUICKMAP:\t");
  Serial.println(stop - start);
  Serial.print(z);
  Serial.print(" -> ");
  Serial.println(x);
  Serial.print("Performance factor: ");
  Serial.println((float)reference / (stop - start));
  Serial.println();
  delay(100);
}

void loop()
{
}
