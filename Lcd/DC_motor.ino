#include "DC_Motor.h"
#if !defined(__AVR_ATmega328P__)
#include <avr/iom328p.h>
#endif

unsigned char MotorArray[2] = {3, 3} ;

void DC_Init(){
    DDRD |=  (1 << MotorArray[0]);
    DDRB |=  (1 << MotorArray[1]);
}


void motor_start(int direction){

      if (direction == 1)
    {
      PORTD |=  (1 << MotorArray[0]);
      PORTB &=  ~(1 << MotorArray[1]);
    } else {
      PORTD &=  ~(1 << MotorArray[0]);
      PORTB |=  (1 << MotorArray[1]);
    }
}

