unsigned int overloadValue;
char *temp = "0000";
int liftFloor = 1;
int inputFloor;
int callingFloor;
int doorOpened = 0;
sbit LCD_RS at RD2_bit;
sbit LCD_EN at RD3_bit;
sbit LCD_D7 at RD7_bit;
sbit LCD_D6 at RD6_bit;
sbit LCD_D5 at RD5_bit;
sbit LCD_D4 at RD4_bit;
sbit LCD_RS_Direction at TRISD2_bit;
sbit LCD_EN_Direction at TRISD3_bit;
sbit LCD_D7_Direction at TRISD7_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D4_Direction at TRISD4_bit;
void openDoor();
void closeDoor();
void initLcd();
void display1();
void display2();
void display3();
void move_clock();
void move_anticlock();
void floorNumber1();
void floorNumber2();
void floorNumber3();
void main() {
     TRISD  = 0X00;
     TRISC  = 0X00;
     TRISB  = 0XFF;
     TRISA = 0b00001100;
     ADCON0 = 0b00001000;
     OPTION_REG.F7 = 1;
     while(1){
           overloadValue = ADC_Read(2);
           temp[0] = overloadValue/1000 + 48;
           temp[1] = (overloadValue/100)%10 + 48;
           temp[2] = (overloadValue/10)%10 + 48;
           temp[3] = overloadValue%10 + 48;
           initLcd();
           if (liftFloor == 1){
               display1();
               floorNumber1();
           }
           if (liftFloor == 2){
               display2();
               floorNumber2();
           }
           if (liftFloor == 3){
               display3();
               floorNumber3();
           }
           if(Button(&PORTB, 4, 0, 1)){
             callingFloor = 1;
             if(liftFloor == callingFloor){

             }
             else {
                if(liftFloor == 2){
                  if(doorOpened == 1){
                     closeDoor();
                     doorOpened = 0;
                  }
                  move_clock();
                  delay_ms(3000);
                }
                if(liftFloor == 3){
                  if(doorOpened == 1){
                     closeDoor();
                     doorOpened = 0;
                  }
                  move_clock();
                  delay_ms(3000);
                  move_clock();
                  delay_ms(3000);
                }
                         }
             openDoor();
             doorOpened = 1;
             liftFloor = callingFloor;
             floorNumber1();
             display1();
           }
           if(Button(&PORTB, 5, 0, 1)){
             callingFloor = 2;
             if(liftFloor == callingFloor){

             }
             else {
                if(liftFloor == 1){
                  if(doorOpened == 1){
                     closeDoor();
                     doorOpened = 0;
                  }
                  move_anticlock();
                  delay_ms(3000);
                }
                if(liftFloor == 3){
                  if(doorOpened == 1){
                     closeDoor();
                     doorOpened = 0;
                  }
                  move_clock();
                  delay_ms(3000);
                }
             }
             openDoor();
             doorOpened = 1;
             liftFloor = callingFloor;
             floorNumber2();
             display2();
           }
           if(Button(&PORTB, 6, 0, 1)){
             callingFloor = 3;
             if(liftFloor == callingFloor){

             }
             else {
                if(liftFloor == 1){
                  if(doorOpened == 1){
                     closeDoor();
                     doorOpened = 0;
                  }
                  move_anticlock();
                  delay_ms(3000);
                  move_anticlock();
                  delay_ms(3000);
                }
                if(liftFloor == 2){
                  if(doorOpened == 1){
                     closeDoor();
                     doorOpened = 0;
                  }
                  move_anticlock();
                  delay_ms(3000);
                }
             }
             openDoor();
             doorOpened = 1;
             liftFloor = callingFloor;
             floorNumber3();
             display3();
           }
           delay_ms(2000);
           if(overloadValue > 600){
             initLcd();
             Lcd_Out(1,2,"LIFT OVERLOADED");
             delay_ms(1000);
           }
           else {
              if(Button(&PORTB, 0, 0, 1)){
                 inputFloor = 1;
                 initLcd();
                 if(inputFloor == liftFloor){
                    display1();
                    openDoor();
                    doorOpened = 1;
                 }
                 else {
                    if(liftFloor == 2){
                       if(doorOpened == 1){
                         closeDoor();
                         doorOpened = 0;
                       }
                       move_clock();
                       delay_ms(3000);
                    }
                    if(liftFloor == 3){
                       if(doorOpened == 1){
                         closeDoor();
                         doorOpened = 0;
                       }
                       move_clock();
                       delay_ms(3000);
                       move_clock();
                       delay_ms(3000);
                    }
                    display1();
                    openDoor();
                    doorOpened = 1;
                 }
                 floorNumber1();
                 liftFloor = inputFloor;
              }
              else if(Button(&PORTB, 1, 0, 1)){
                 inputFloor = 2;
                 initLcd();
                 if(inputFloor == liftFloor){
                    display2();
                    openDoor();
                    doorOpened = 1;
                 }
                 else {
                    if(liftFloor == 1){
                       if(doorOpened == 1){
                         closeDoor();
                         doorOpened = 0;
                       }
                       move_anticlock();
                       delay_ms(3000);
                    }
                    if(liftFloor == 3){
                       if(doorOpened == 1){
                         closeDoor();
                         doorOpened = 0;
                       }
                       move_clock();
                       delay_ms(3000);
                    }
                    display2();
                    openDoor();
                    doorOpened = 1;
                 }
                 floorNumber2();
                 liftFloor = inputFloor;
              }
              else if(Button(&PORTB, 2, 0, 1)){
                 inputFloor = 3;
                 initLcd();
                 if(inputFloor == liftFloor){
                    display3();
                    openDoor();
                    doorOpened = 1;
                 }
                 else {
                    if(liftFloor == 1){
                       if(doorOpened == 1){
                         closeDoor();
                         doorOpened = 0;
                       }
                       move_anticlock();
                       delay_ms(3000);
                       move_anticlock();
                       delay_ms(3000);
                    }
                    if(liftFloor == 2){
                       if(doorOpened == 1){
                         closeDoor();
                         doorOpened = 0;
                       }
                       move_anticlock();
                       delay_ms(3000);
                    }
                    display3();
                    openDoor();
                    doorOpened = 1;
                 }
                 floorNumber3();
                 liftFloor = inputFloor;
              }
          }
     }
}
void openDoor(){
   unsigned int i;
   for (i=0; i<20; i++){
       PORTD.F0=1;
       PORTD.F1=1;
       delay_us(600);
       PORTD.F0=0;
       PORTD.F1=0;
       delay_us(20000);
   }
   delay_ms(1000);
}
void closeDoor(){
   unsigned int i;
   for (i=0; i<20; i++){
       PORTD.F0=1;
       PORTD.F1=1;
       delay_us(1500);
       PORTD.F0=0;
       PORTD.F1=0;
       delay_us(20000);
   }
   delay_ms(1000);
}
void move_clock(){
     PORTC.F4 =  0;
     PORTC.F5 =  1;
     PORTC.F6 =  1;
     PORTC.F7 =  0;
     delay_ms(200);
     PORTC.F4 =  1;
     PORTC.F5 =  1;
     PORTC.F6 =  0;
     PORTC.F7 =  0;
     delay_ms(200);
     PORTC.F4 =  1;
     PORTC.F5 =  0;
     PORTC.F6 =  0;
     PORTC.F7 =  1;
     delay_ms(200);
     PORTC.F4 =  0;
     PORTC.F5 =  0;
     PORTC.F6 =  1;
     PORTC.F7 =  1;
     delay_ms(200);
     PORTC.F4 =  0;
     PORTC.F5 =  1;
     PORTC.F6 =  1;
     PORTC.F7 =  0;
     delay_ms(200);
}
void move_anticlock(){
     PORTC.F4 =  0;
     PORTC.F5 =  1;
     PORTC.F6 =  1;
     PORTC.F7 =  0;
     delay_ms(200);
     PORTC.F4 =  0;
     PORTC.F5 =  0;
     PORTC.F6 =  1;
     PORTC.F7 =  1;
     delay_ms(200);
     PORTC.F4 =  1;
     PORTC.F5 =  0;
     PORTC.F6 =  0;
     PORTC.F7 =  1;
     delay_ms(200);
     PORTC.F4 =  1;
     PORTC.F5 =  1;
     PORTC.F6 =  0;
     PORTC.F7 =  0;
     delay_ms(200);
     PORTC.F4 =  0;
     PORTC.F5 =  1;
     PORTC.F6 =  1;
     PORTC.F7 =  0;
     delay_ms(200);
}
void initLcd(){
     Lcd_Init();
     Lcd_Cmd(_LCD_CLEAR);
     Lcd_Cmd(_LCD_CURSOR_OFF);
}
void display1(){
     Lcd_Out(1,4,"You are in");
     Lcd_Out(2,6,"Floor 1");
     delay_ms(1000);
}
void display2(){
     Lcd_Out(1,4,"You are in");
     Lcd_Out(2,6,"Floor 2");
     delay_ms(1000);
}
void display3(){
     Lcd_Out(1,4,"You are in");
     Lcd_Out(2,6,"Floor 3");
     delay_ms(1000);
}
void floorNumber1(){
     PORTC.F0 = 1;
     PORTC.F1 = 0;
     PORTC.F2 = 0;
     PORTC.F3 = 0;
}
void floorNumber2(){
     PORTC.F0 = 0;
     PORTC.F1 = 1;
     PORTC.F2 = 0;
     PORTC.F3 = 0;
}
void floorNumber3(){
     PORTC.F0 = 1;
     PORTC.F1 = 1;
     PORTC.F2 = 0;
     PORTC.F3 = 0;
}