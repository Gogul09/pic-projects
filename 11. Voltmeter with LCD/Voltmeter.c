// LCD Module connections
sbit LCD_RS at RD2_bit;
sbit LCD_EN at RD3_bit;

sbit LCD_D7 at RD7_bit;
sbit LCD_D6 at RD6_bit;
sbit LCD_D5 at RD5_bit;
sbit LCD_D4 at RD4_bit;
// End of LCD Module connections

// LCD Pin direction
sbit LCD_RS_Direction at TRISD2_bit;
sbit LCD_EN_Direction at TRISD3_bit;

sbit LCD_D7_Direction at TRISD7_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D4_Direction at TRISD4_bit;
// End of LCD Pin direction

unsigned int adcValue;
unsigned int value;
char *temp1 = "0000";

void main() {

     // ADCON0 = 0b00001000;
     TRISA = 0xff;
     TRISB  = 0X00;
     TRISC  = 0X00;
     PORTB = 0;
     PORTC = 0;
     Lcd_Init();
     Lcd_Cmd(_LCD_CLEAR);
     Lcd_Cmd(_LCD_CURSOR_OFF);
     while(1){
       adcValue = ADC_Read(2);          
       value = adcValue * 4.88;         
       
       temp1[0] = value/1000 + 48;
       temp1[1] = (value/100)%10 + 48;
       temp1[2] = (value/10)%10 + 48;
       temp1[3] = value%10 + 48;
       
       Lcd_Out(1,5,"ADC Value");
       Lcd_Out(2,6,temp1);
       Lcd_Out(2,10," mV");
       delay_ms(2000);
       Lcd_Cmd(_LCD_CLEAR);
    }
}