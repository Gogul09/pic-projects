unsigned char i = 1;
unsigned char pattern1,pattern2;
unsigned char DICE[] = {0,0X08,0X22,0X2A,0X55,0X50,0X77};

void main() {
   TRISB  = 0X00;
   TRISD  = 0X00;
   TRISC  = 0XFF;
   
   PORTB  = 0X00;
   PORTD  = 0X00;
   
   while(1){
     if(PORTC.F0 == 1){
        pattern1 = DICE[i];
        pattern2 = DICE[i+1];
        PORTB = pattern1;
        PORTD = pattern2;
        delay_ms(500);
        PORTB = 0;
        PORTD = 0;
        i = 0;
     }
     i++;
     if(i==7) i = 1;
   }
}