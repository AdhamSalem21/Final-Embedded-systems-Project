#include <stdio.h>
#include <util/delay.h>
#include "DIO.h"


void DIO_SetPinDirection(unsigned char port,int pin,unsigned char direction){// creating a function pin state that takes parameters port,pin and direction.

if (port=='b' & pin<=7 &pin>=0){ //

if(direction=='o'){//if o is written in the direction parameter
  DDRB= DDRB|(1<<pin); // pin is set as high for output
}
else if (direction='i'){//if i is written in the direction parameter
DDRB= DDRB &!(1<<pin);  //bit cleared to 0 for input
}
}
}
void  DIO_SetPinState(unsigned char port,int pin,unsigned char state){  // creating a function pin state that takes parameters port,pin and state.

if (port=='b'& pin<=7 &pin>=0){  
  if (state=='h'){ //if h is written in the state parameter
    PORTB=PORTB |(1<<pin);// pin is set as high
  }
  else if (state=='l'){//if h is written in the state parameter
    PORTB=PORTB &= ~(1<<pin);// pin is cleared to 0 for low
  }
}

if (port=='c'& pin<=5 &pin>=1){  
  if (state=='h'){ //if h is written in the state parameter
    PORTC=PORTC |(1<<pin);// pin is set as high
  }
  else if (state=='l'){//if h is written in the state parameter
    PORTC=PORTC &= ~(1<<pin);// pin is cleared to 0 for low
  }
}
}






