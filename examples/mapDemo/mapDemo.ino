// FILE: mapDemo.ino
// AUTHOR: Holman Buenaventura
// PURPOSE: demo of quickMap.

#include <quickMap.h>

uint32_t start;
uint32_t stop;
uint32_t reference;

volatile long zz = 30000, yy = 20000;
volatile float x;

quickMap mapper;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.println("QUICKMAP_DEMO");
  Serial.println();

  //  Get a non optimizable value;
  int z = analogRead(A0);

  //  REFERENCE (Función nativa map() de Arduino)
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    x = map(z, 0, 1023, yy, zz);
  }
  stop = micros();
  reference = stop - start;
  Serial.print("Tiempo map() nativo: ");
  Serial.println(reference);
  Serial.print(z);
  Serial.print(" -> ");
  Serial.println(x);
  Serial.println();

  //  QUICKMAP (Tu alternativa optimizada)
  //  Ya no requiere usar .f obligatoriamente, acepta números de forma natural
  mapper.init(0, 1023, yy, zz); 
  
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    x = mapper.map(z);
  }
  stop = micros();
  Serial.print("Tiempo quickMap: ");
  Serial.println(stop - start);
  Serial.print(z);
  Serial.print(" -> ");
  Serial.println(x);
  Serial.println();

  //  GAIN
  Serial.print("Performance factor: ");
  Serial.println((float)reference / (stop - start));
}

void loop()
{
}
