////////////////////////////////////////////////////////////////////////////////
// Engineer    - I.Gogul
// College     - Madras Institute of Technology, Chennai
// Design      - Voltmeter with LCD and Seven Segment Display
// Description - Voltmeter uses ADC and interfaces LCD and Seven Segment Display
////////////////////////////////////////////////////////////////////////////////

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
char *temp = "0000";
char *binary1 = "0000";
char *binary2 = "0000";
char *binary3 = "0000";
char *binary4 = "0000";

void main() {
     // Define the input and output ports
     ADCON0 = 0b00001000;
     TRISA = 0b00001100;
     TRISB  = 0X00;
     TRISC  = 0X00;
     PORTB = 0;
     PORTC = 0;
     
     // Initialize the LCD
     Lcd_Init();
     Lcd_Cmd(_LCD_CLEAR);
     Lcd_Cmd(_LCD_CURSOR_OFF);
     
     // A to D conversion
     while(1){
       int i;
       adcValue = ADC_Read(2);          
       value = adcValue * 4.88;         
       
       temp[0] = value/1000 + 48;
       temp[1] = (value/100)%10 + 48;
       temp[2] = (value/10)%10 + 48;
       temp[3] = value%10 + 48;
       
       Lcd_Out(1,5,"ADC Value");
       Lcd_Out(2,6,temp);
       Lcd_Out(2,10," mV");
       delay_ms(2000);
       Lcd_Cmd(_LCD_CLEAR);
       
       // Seven segment conversion
       for(i = 0; i<=3; i++){
            binary1[i]=temp[0]%2;
            temp[0] = temp[0]/2;
       }
       for(i = 0; i<=3; i++){
            binary2[i]=temp[1]%2;
            temp[1] = temp[1]/2;
       }
       for(i = 0; i<=3; i++){
            binary3[i]=temp[2]%2;
            temp[2] = temp[2]/2;
       }
       for(i = 0; i<=3; i++){
            binary4[i]=temp[3]%2;
            temp[3] = temp[3]/2;
       }
       // 1st digit
       PORTB.F0 = binary1[0];
       PORTB.F1 = binary1[1];
       PORTB.F2 = binary1[2];
       PORTB.F3 = binary1[3];
       
       // 2nd digit
       PORTB.F4 = binary2[0];
       PORTB.F5 = binary2[1];
       PORTB.F6 = binary2[2];
       PORTB.F7 = binary2[3];
       
       // 3rd digit
       PORTC.F0 = binary3[0];
       PORTC.F1 = binary3[1];
       PORTC.F2 = binary3[2];
       PORTC.F3 = binary3[3];
       
       // 4th digit
       PORTC.F4 = binary4[0];
       PORTC.F5 = binary4[1];
       PORTC.F6 = binary4[2];
       PORTC.F7 = binary4[3];
    }
}