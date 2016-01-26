#include "lighting.h"

Lighting::Lighting()
{
  uint8_t i; 
  
  for (i = 0; i < _num_stripes; i++) {
    pinMode(i, OUTPUT);  
  }
}

void Lighting::assignLighting(uint8_t stripe_number, uint8_t number)
{  
  switch (number) {
    case 1:
      _stripes[stripe_number].assignSequence(_light1_v, _light1_t);
    break;
    
    case 2:
      _stripes[stripe_number].assignSequence(_light2_v, _light2_t);
    break;
    
    case 3:
      _stripes[stripe_number].assignSequence(_light3_v, _light3_t);
    break;
    
    default:
      return;
    break;
  }
}

void Lighting::processRutine() 
{
  uint8_t i;
  
  for (i = 0; i < _num_stripes; i++) {
    if (_stripes[i].isActive() && millis() >= _stripes[i].getTimeNext()) {
      _stripes[i].nextAction(); 
    }
  }  
}

