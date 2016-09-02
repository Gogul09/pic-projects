void stepper_clock();
void stepper_anti_clock();

void main() {
     TRISC = 0X00;
     while(1){
         stepper_clock();
         delay_ms(2000);
         stepper_anti_clock();
     }
}

void stepper_clock(){
     PORTC = 0x06;     //0
     delay_ms(1000);
     PORTC = 0x03;    //90
     delay_ms(1000);
     PORTC = 0x09;    //180
     delay_ms(1000);
     PORTC = 0x0C;    //270
     delay_ms(1000);
     PORTC = 0x06;    //0
     delay_ms(1000);
}

void stepper_anti_clock(){
     PORTC = 0x06;     //0
     delay_ms(1000);
     PORTC = 0x0C;    //270
     delay_ms(1000);
     PORTC = 0x09;    //180
     delay_ms(1000);
     PORTC = 0x03;    //90
     delay_ms(1000);
     PORTC = 0x06;    //0
     delay_ms(1000);
}