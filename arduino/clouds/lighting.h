#ifndef Lighting_h
#define Lighting_h
#include <Arduino.h>
#include "stripe.h"

class Lighting {
  public:
    Lighting();
    void assignLighting(uint8_t, uint8_t);
    void processRutine();
    
  private:
    /*
    In order to be able to get the number of elements in the array, we MUST end the delay arrays with a 0!!
    */
    PROGMEM unsigned int _light1_t[7] = {100, 150, 400, 100, 200, 50, 0};
    PROGMEM char *_light1_v[6] = {"0-50", "50-10", "0", "100", "0", "100"};
    
    PROGMEM unsigned int _light2_t[9] = {100, 150, 400, 100, 200, 50, 200, 100, 0};
    PROGMEM char *_light2_v[8] = {"0-60", "60-20", "20", "100", "0", "100", "0", "10"};
    
    PROGMEM unsigned int _light3_t[8] = {400, 200, 100, 200, 50, 400, 600, 0};
    PROGMEM char *_light3_v[7] = {"0-30", "30", "100", "60-20", "20-90", "90-30", "30-10"};
    
    Stripe _stripes[2] = {Stripe(6), Stripe(2)};
    uint8_t _num_stripes = 2;
};

#endif
