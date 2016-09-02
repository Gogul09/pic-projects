///////////////////////////////////////////////////////////////////////////////////////////
//  Engineer   - I.Gogul
//  College    - Madras Institute of Technology, Chennai
//  University - Anna University
//  Design     - A counter that counts using external clock
///////////////////////////////////////////////////////////////////////////////////////////

void counter();
unsigned int count;
void main() {
    TRISC = 0;         // PORTC as outputs
    TRISB = 0;         // PORTB as outputs
    TRISA.F4 = 1;      // External Clock connected to pin 4
    while(1){
      counter();       // Call the counter function
    }
}

void interrupt(){
    INTCON = 0X00;     // Reset the interrupt control register
    count++;           // Increment the count value
    TMR0 = 96;         // Timer TMR0 is returned to its initial value
    INTCON = 0XA0;     // Global interrupt enable and Timer 0 Overflow Interrupt enable
}
void counter(){
     OPTION_REG = 0XA0; // PORTB pull ups disabled; Prescalar value chosen as default
     TMR0  = 96;        // Counts from 96 to 255 (8 bit timer - 256 is the limit)
     INTCON = 0XA0;     // Global interrupt enable and Timer 0 Overflow Interrupt enable
     PORTB = 0;         // Initially PORTB is zero
     count = 0;
     do{
        if(count == 400){
          PORTC.F0 = 1;
          delay_ms(100);
          count = 0;
          PORTB++;
        }
        else{
          PORTC.F0 = 0;
        }
     }while(1);
}