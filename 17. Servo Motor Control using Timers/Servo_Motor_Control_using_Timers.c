////////////////////////////////////////////////////////////////////////////////
//  Engineer   - I.Gogul
//  College    - Madras Institute of Technology, Chennai
//  University - Anna University
//  Design     - Servo Motor Control using Timer-0
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Function Initializations
////////////////////////////////////////////////////////////////////////////////
void pulse_on();
void pulse_off();
void servoActivate();
////////////////////////////////////////////////////////////////////////////////
// Global variables
////////////////////////////////////////////////////////////////////////////////
unsigned int count;
////////////////////////////////////////////////////////////////////////////////
// Main Function
////////////////////////////////////////////////////////////////////////////////
void main() {
    TRISC = 0;           // PORTC as output to blink LED
    TRISB = 0;           // PORTB as output to drive servo motor
    while(1){
      servoActivate();   // Activate servo motor
    }
}
////////////////////////////////////////////////////////////////////////////////
// Activate the SERVO Motor
////////////////////////////////////////////////////////////////////////////////
void servoActivate(){
  unsigned int i;
  PORTB.F0=1;
  pulse_on();
  pulse_on();
  PORTB.F0=0;
  pulse_off();
  pulse_off();
  pulse_off();
  pulse_off();
  pulse_off();
  pulse_off();
  pulse_off();
  delay_ms(1000);
}
////////////////////////////////////////////////////////////////////////////////
// ON Pulse - 300 micro second
////////////////////////////////////////////////////////////////////////////////
void pulse_on(){
     OPTION_REG = 0X84;   // PORTB pull ups disabled; Prescalar value chosen as 1:32
     TMR0  = 254;         // Counts from 237 to 255
     INTCON = 0XA0;       // Global interrupt enable and Timer 0 Overflow Interrupt enable
     count = 0;           // Initially count is zero
     do{
        if(count == 19){
          PORTC.F0 = 1;
          delay_ms(20);
          count = 0;
          break;
        }
     }while(1);
}
////////////////////////////////////////////////////////////////////////////////
// OFF Pulse - 20000 micro second
////////////////////////////////////////////////////////////////////////////////
void pulse_off(){
     OPTION_REG = 0X84;     // PORTB pull ups disabled; Prescalar value chosen as 1:32
     TMR0  = 254;           // Counts from 96 to 255
     INTCON = 0XA0;         // Global interrupt enable and Timer 0 Overflow Interrupt enable
     count = 0;             // Initially count is zero
     do{
        if(count == 19){
          PORTC.F0 = 0;
          delay_ms(20);
          count = 0;
          break;
        }
     }while(1);
}
////////////////////////////////////////////////////////////////////////////////
// Interrupt Sub Routine
////////////////////////////////////////////////////////////////////////////////
void interrupt(){
    INTCON = 0X00;         // Reset the interrupt control register
    count++;               // Increment the count value
    TMR0 = 254;            // Timer TMR0 is returned to its initial value
    INTCON = 0XA0;         // Global interrupt enable and Timer 0 Overflow Interrupt enable
}