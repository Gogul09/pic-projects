void main() {
    TRISD = 0x00;
    TRISB = 0x01;
    while(1){
        if(PORTB.F0 == 1){
           PORTD = 0X55;
           delay_ms(1000);
           PORTD = 0XAA;
           delay_ms(1000);
        }
        else{
           PORTD = 0x00;
        }
}
}
