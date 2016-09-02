void main() {
    TRISD = 0x00;
    while(1){
       PORTD = 0X55;
       delay_ms(1000);
       PORTD = 0XAA;
       delay_ms(1000);
}
}
