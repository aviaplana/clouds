#ifndef Stripe_h
#define Stripe_h
#include <Arduino.h>

class Stripe {
  public:
    Stripe(int);
    void nextAction();
    void assignSequence(char **, unsigned int *);
    unsigned long getTimeNext() const { return _time_next; }
    boolean isActive() const { return _is_active; }

  private:
    boolean _is_active;
    boolean _fade;
    boolean _increasing;
    
    uint8_t _pin;
    uint8_t _value_reach;
    uint8_t _current_value;
    int _sequence_position;
    uint8_t _sequence_size;
    
    char **_sequence;
    unsigned int *_delays;
    unsigned int _delay_step;
    
    unsigned long _time_next;
    
    void calculateLenght();
    void setNextValues();
    uint8_t getLenght(char*);
    uint8_t mapLight(uint8_t);
    int getIndex(char, char*);
    uint8_t getSequenceSize();

};

#endif
