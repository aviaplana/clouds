#include "lighting.h"

Lighting lighting;


void setup() 
{
  Serial.begin(9600);
}

void loop() 
{  
  if (Serial.available() > 0) {
    int action = Serial.parseInt();
    lighting.assignLighting(0, action);
  }
  
  lighting.processRutine();
}
