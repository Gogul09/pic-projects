void ServoActivate();

void main() {
    TRISB = 0x00;
    while(1){
      ServoActivate();
      delay_ms(1000);
    }
}
void ServoActivate()
{
  unsigned int i;
  for(i=0;i<100;i++)
  {
    PORTB.F0=1;
    delay_us(2000);
    PORTB.F0=0;
    delay_us(20000);
  }
  
}