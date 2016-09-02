// LCD Module connections
sbit LCD_RS at RB2_bit;
sbit LCD_EN at RB3_bit;

sbit LCD_D7 at RB7_bit;
sbit LCD_D6 at RB6_bit;
sbit LCD_D5 at RB5_bit;
sbit LCD_D4 at RB4_bit;
// End of LCD Module connections

// LCD Pin direction
sbit LCD_RS_Direction at TRISB2_bit;
sbit LCD_EN_Direction at TRISB3_bit;

sbit LCD_D7_Direction at TRISB7_bit;
sbit LCD_D6_Direction at TRISB6_bit;
sbit LCD_D5_Direction at TRISB5_bit;
sbit LCD_D4_Direction at TRISB4_bit;
// End of LCD Pin direction

unsigned int adcValue;
unsigned int temperature;
char *temp = "00";
void main() {
     ADCON0 = 0b00001000;
     TRISA = 0b00001100;
     while(1){
       adcValue = ADC_Read(2);
       temperature = adcValue * 0.4883;
       //temp[0] = temperature/1000 + 48;
       //temp[1] = (temperature/100)%10 + 48;
       temp[0] = (temperature/10)%10 + 48;
       temp[1] = temperature%10 + 48;
       Lcd_Init();
       Lcd_Cmd(_LCD_CLEAR);
       Lcd_Cmd(_LCD_CURSOR_OFF);
       Lcd_Out(1,5,"Temperature");
       Lcd_Out(2,7,temp);
       Lcd_Out(2,11,"C");
       delay_ms(2000);
       Lcd_Cmd(_LCD_CLEAR);
     }
}