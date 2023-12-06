#include <util/delay.h>
#include "Lcd.h"
#include "Adc.h"
#include <stdlib.h>
#include "Uart.h"
#include "PWM.h"
#include<EEPROM.h>
//#include "DC_Motor.h"
#if !defined(__AVR_ATmega328P__)
#include <avr/iom328p.h>
#endif

int main() {

 int target; //creating a variable templimit as the limit of 30
 int address=0;
 Adc_Init();  // initializing ADC
 //DC_Init();
 PWM_Init(); 
 Uart_Init();
 unsigned char buffer[4]; //creating a variable buffer of type char
 unsigned char buffer2[4];//creating a variable buffer2 of type char
 unsigned short adc_reading; // setting a variable to store the reading as an integer of 4 bits 

while(1){
  //Uart_SendString("lo", 2);
 target=EEPROM.read(address);
 adc_reading = Adc_ReadChannel(1); //storing the analogue reading in variable adc_reading
 float _voltage = (adc_reading/1024.0) * 5;// converting the analogue reading to voltage using step size
 float temp = (_voltage - 0.5) * 100; //converting  the voltage to a temperature
 int button1=(( PINC >> 2) & 1); // creating a variable to store the input reading of pin A2
 int button2=(( PINC >> 3) & 1); //creating a variable to store the input reading of pin A3
 int button3=(( PINB >> 4) & 1); //creating a variable to store the input reading of pin B4
 int button4=(( PINB >> 5) & 1); //creating a variable to store the input reading of pin B5
 int cold= temp-target;
 int hot= target-temp;
 int flag;
  conv(temp, buffer, 10); //calling the function that implememts itoa to convert the integer value into a string and store it in buffer
  conv(target, buffer2, 10);//calling the function that implememts itoa to convert the integer value into a string and store it in buffer2
  if(button3==HIGH){
       flag=1;
        Uart_SendString(flag,2);
        Uart_SendString("\n",2);
  }
  else if (button4==HIGH){
   flag=2;

  }
  if(flag==1){
  Uart_SendString("on",2);
  Uart_SendString("\n",2);
 LCD_Init();// Initialize LCD 
 LCD_String("Temprature:");	//write string on 1st line of LCD
 LCD_String(buffer);     // printing the temperature value stored in buffer
 LCD_Command(0xC0);		            //Go to 2nd line
 LCD_String("Target:");	        // Write string on 2nd line
 LCD_String(buffer2);  // printing the temperature value stored in buffer2
 
if(button1== HIGH){  //if button1 reading is a high input
 ++ target; //increment the temperature limit by one
EEPROM.write(address,target);
Uart_SendString("Targetincreased", 15);
Uart_SendString("\n",2);

 
}
else if(button2== HIGH){//if button2 reading is a high input
 --target; //decrement the temperature limit by one
 EEPROM.write(address,target);
 Uart_SendString("TargetDecreased", 15);
 Uart_SendString("\n",2);
}
if (temp>target){
  // motor_start(1);
  DIO_SetPinState('c', 5 , 'h');
  DIO_SetPinState('c', 4 , 'l');
  if(cold>=5)
  {
    Set_DutyCycle(255,3); 
    Set_DutyCycle(0,11);
  }
  
  else {
  Set_DutyCycle(190,3);
  Set_DutyCycle(0,11);
  }

}
else if (temp<target) {
  //motor_start(2);
  Set_DutyCycle(0,3);
  Set_DutyCycle(255,11);
  DIO_SetPinState('c', 4 , 'h');
  DIO_SetPinState('c', 5 , 'l');
 if(hot>=5){
  Set_DutyCycle(0,3);
  Set_DutyCycle(255,11); 
  }
  else {
  Set_DutyCycle(0,3);
  Set_DutyCycle(190,11); 
  }

}
else {
Set_DutyCycle(0,3);
Set_DutyCycle(0,11);
DIO_SetPinState('c', 4 , 'l');
DIO_SetPinState('c', 5 , 'l');
}

  }

if(flag==2){
  LCD_Init();// Initialize LCD 
  LCD_String("System off");	//write string on 1st line of LCD
  Uart_SendString("off", 3);
  Uart_SendString("\n",2);
  DIO_SetPinState('c', 4 , 'l');
  DIO_SetPinState('c', 5 , 'l');
  Set_DutyCycle(0,3);
  Set_DutyCycle(0,11);
}
}
	return 0;
}
