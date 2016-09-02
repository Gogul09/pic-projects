////////////////////////////////////////////////////////////////////////////////
//  Engineer - I.Gogul
//  College  - Madras Institute of Technology, Chennai
//  University - Anna University
//  Design   - A timer with 60% duty cycle having a time period of 5.1 seconds
////////////////////////////////////////////////////////////////////////////////

void create_on_pulse();
void create_off_pulse();
unsigned int count;
void main() {
    TRISC = 0;         // PORTC as outputs
    while(1){
      create_on_pulse();
      create_on_pulse();
      create_on_pulse();
      create_off_pulse();
      create_off_pulse();
    }
}

void interrupt(){
    INTCON = 0X00;     // Reset the interrupt control register
    count++;           // Increment the count value
    TMR0 = 96;         // Timer TMR0 is returned to its initial value
    INTCON = 0XA0;     // Global interrupt enable and Timer 0 Overflow Interrupt enable
}
void create_on_pulse(){
     OPTION_REG = 0X84; // PORTB pull ups disabled; Prescalar value chosen as 1:32
     TMR0  = 96;        // Counts from 96 to 255 (8 bit timer - 256 is the limit)
     INTCON = 0XA0;     // Global interrupt enable and Timer 0 Overflow Interrupt enable
     count = 0;
     do{
        if(count == 400){
          PORTC.F0 = 1;
          delay_ms(40);
          count = 0; 
          break;
        }
     }while(1);
}
void create_off_pulse(){
     OPTION_REG = 0X84; // PORTB pull ups disabled; Prescalar value chosen as 1:32
     TMR0  = 96;        // Counts from 96 to 255 (8 bit timer - 256 is the limit)
     INTCON = 0XA0;     // Global interrupt enable and Timer 0 Overflow Interrupt enable
     count = 0;
     do{
        if(count == 400){
          PORTC.F0 = 0;
          delay_ms(40);
          count = 0; 
          break;
        }
     }while(1);
}