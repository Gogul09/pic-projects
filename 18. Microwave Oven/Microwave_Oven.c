////////////////////////////////////////////////////////////////////////////////
// Engineer   - I.Gogul
// College    - Madras Institute of Technology
// University - Anna University
// Design     - Microwave Oven
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// LCD INITIALIZATION
////////////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////////
// FUNCTION DECLARATIONS
////////////////////////////////////////////////////////////////////////////////
void set_initial_timer();
void stepper_clock();

////////////////////////////////////////////////////////////////////////////////
// GLOBAL VARIABLES
////////////////////////////////////////////////////////////////////////////////
unsigned int counter;
unsigned int count;
char *timer = "00";
unsigned int endTime;

////////////////////////////////////////////////////////////////////////////////
// MAIN FUNCTION
////////////////////////////////////////////////////////////////////////////////
void main() {
     // Initialize ports for stepper motor and LED indicator
     // PIN 0,1,2,3 - Stepper Motor
     // PIN 4 - LED indicator
     
     TRISC = 0X00;
     TRISB = 0XFF;
     OPTION_REG.INTEDG = 1;
     INTCON.GIE = 1;
     INTCON.INTE = 1;
     
     Lcd_Init();
     Lcd_Cmd(_LCD_CLEAR);
     Lcd_Cmd(_LCD_CURSOR_OFF);
     
     counter = 10;                             // Initially counter value is 10
     endTime = 0;                              // Default EndTime is 0 second
     
     while(1){
        if(counter != endTime){
          PORTC.F4 = 1;
          set_initial_timer();
          timer[0] = (counter/10)%10 + 48;    // Extract tens digit
          timer[1] =  counter%10     + 48;    // Extract ones digit
          Lcd_Out(1, 2, "Time Remaining");
          Lcd_Out(2, 7, timer);
          Lcd_Out(2, 10, "sec");
          stepper_clock();
        }

        if(counter == endTime){              // Process completed
          PORTC = 0;                         // Reset PortB to zero
          Lcd_Out(2, 5, "Completed");        // Show as "Completed"
        }
        
        Lcd_Cmd(_LCD_CLEAR);
     }
}
////////////////////////////////////////////////////////////////////////////////
// TIMER FOR 1 SECOND DELAY
////////////////////////////////////////////////////////////////////////////////
void set_initial_timer(){
     OPTION_REG = 0X84;    // PORTB pull ups disabled; Prescalar value chosen as 1:32
     TMR0  = 96;           // Counts from 96 to 255 (8 bit timer - 256 is the limit)
     INTCON = 0XB0;        // Global interrupt enable and Timer 0 Overflow Interrupt enable
     count = 0;
     do{
        if(count == 400){
          PORTC.F0 = 1;
          delay_ms(20);
          count = 0;
          counter--;       // Increment the counter variable here
          break;
        }
        else{
          PORTC.F0 = 0;
        }
     }while(1);
}
////////////////////////////////////////////////////////////////////////////////
// STEPPER MOTOR CLOCKWISE ROTATION
////////////////////////////////////////////////////////////////////////////////
void stepper_clock(){
     PORTC = 0x06;     //0 degree
     delay_ms(200);
     PORTC = 0x03;    //90 degree
     delay_ms(200);
     PORTC = 0x09;    //180 degree
     delay_ms(200);
     PORTC = 0x0C;    //270 degree
     delay_ms(200);
     PORTC = 0x06;    //0 degree
     delay_ms(200);
}
////////////////////////////////////////////////////////////////////////////////
// INTERRUPT SERVICE ROUTINE
////////////////////////////////////////////////////////////////////////////////
void interrupt(){
    if(INTCON.INTF == 1){
      counter = counter + 10;        // Increment by 10
    }
    INTCON = 0X00;
    count++;             // Increment the count value
    TMR0 = 96;           // Timer TMR0 is returned to its initial value
    INTCON = 0XB0;

}