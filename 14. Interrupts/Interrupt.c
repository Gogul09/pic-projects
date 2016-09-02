void main() {
        TRISD = 0;
        TRISB = 0XFF;
        OPTION_REG.INTEDG = 1;
        INTCON.GIE = 1;
        INTCON.INTE = 1;
        while(1) {
                PORTD = 0xFF;
        }
}

void interrupt(){
  INTCON.INTF = 0;
  while(1){
    PORTD = 0X00;
  }
}