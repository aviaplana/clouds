#include "stripe.h"

Stripe::Stripe(int new_pin)
{
  _pin = new_pin;
  _is_active = false;
}

void Stripe::assignSequence(char **new_sequence, unsigned int *new_delays)
{
  _sequence = new_sequence;
  _delays = new_delays;
  
  _sequence_position = -1;
  
  _sequence_size = getSequenceSize() - 1;
  _is_active = true;
  _fade = false;
  nextAction();
}

uint8_t Stripe::getSequenceSize()
{
   uint8_t i = 0;
   
   while (_delays[i] != 0) {
     i++;
   }
   
   return i;
}

void Stripe::nextAction()
{
  if ((_fade && _increasing && _current_value < _value_reach) || (_fade && !_increasing && _current_value > _value_reach)) {
    
    if (_increasing) {
      _current_value += 5;
      
      if (_current_value > _value_reach) {
        _current_value = _value_reach;
      } 
      
    } else {
      _current_value -= 5;
      
      if (_current_value < _value_reach) {
        _current_value = _value_reach;
      }
    } 
   _time_next = millis() + _delay_step;    
   
  } else {
    _sequence_position += 1;
    
    if (_sequence_position > _sequence_size) {
      _is_active = false;
      digitalWrite(_pin, LOW);
      return;
    }
   
    setNextValues();
    Serial.println(_current_value);
  }
  
  analogWrite(_pin, mapLight(_current_value));
  
}

void Stripe::setNextValues()
{
  int delimiter = 0;
  delimiter = getIndex('-', _sequence[_sequence_position]);
 
  if (delimiter >= 0) {
   int elements = getLenght(_sequence[_sequence_position]);
   char sub[delimiter];
   
   strncpy(sub, _sequence[_sequence_position], delimiter);
   uint8_t from = atoi(sub);
   
   delimiter++;
   strncpy(sub, _sequence[_sequence_position] + delimiter, elements - delimiter);
   uint8_t to = atoi(sub);
   
   _current_value = from;
   _value_reach = to;
   _fade = true;
   _increasing = from < to;
   
   _delay_step = _delays[_sequence_position] / (abs(to - from) / 5);
   _time_next = millis() + _delay_step;  
   
   } else {
     _fade = false;
    _time_next = millis() + _delays[_sequence_position];
    _current_value = atoi(_sequence[_sequence_position]);
  }  
}

uint8_t Stripe::getLenght(char* tocheck)
{
  uint8_t i = 0;

  while (tocheck[i] != '\0') {
    i++; 
  }
  
  return i;
}

int Stripe::getIndex(char token, char* tosearch)
{
  uint8_t i = 0;
  
  while (tosearch[i] != '\0') {
    if (tosearch[i] == token) {
      return i;
    }  
    i++;
  }
  
  return -1;
}

uint8_t Stripe::mapLight(uint8_t val)
{
  return map(val, 0, 100, 0, 255); 
}
