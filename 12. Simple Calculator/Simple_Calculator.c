////////////////////////////////////////////////////////////////////////////////
// Engineer    - I.Gogul
// College     - Madras Institute of Technology, Chennai
// Design      - Simple Calculator
// Description - * Maximum two digit input; Maximum four digit output
//               * Minimum one digit input; Minimum one digit output
//               * Enter number1 and press enter
//               * Enter number2 and press enter
//               * Enter the operation and the result will be displayed
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Concatenate two integers
////////////////////////////////////////////////////////////////////////////////
unsigned int concatenate(unsigned int x, unsigned int y) {
    unsigned pow = 10;
    while(y >= pow)
        pow *= 10;
    return x * pow + y;
}
////////////////////////////////////////////////////////////////////////////////
// LCD Module connections
////////////////////////////////////////////////////////////////////////////////
sbit LCD_RS at RB2_bit;
sbit LCD_EN at RB3_bit;

sbit LCD_D7 at RB7_bit;
sbit LCD_D6 at RB6_bit;
sbit LCD_D5 at RB5_bit;
sbit LCD_D4 at RB4_bit;

sbit LCD_RS_Direction at TRISB2_bit;
sbit LCD_EN_Direction at TRISB3_bit;

sbit LCD_D7_Direction at TRISB7_bit;
sbit LCD_D6_Direction at TRISB6_bit;
sbit LCD_D5_Direction at TRISB5_bit;
sbit LCD_D4_Direction at TRISB4_bit;
////////////////////////////////////////////////////////////////////////////////
// Function Declarations
////////////////////////////////////////////////////////////////////////////////
char keypadPort at PORTD;
unsigned int keypadScan();
////////////////////////////////////////////////////////////////////////////////
// Global Variables
////////////////////////////////////////////////////////////////////////////////
unsigned char operationChar;
unsigned char key;
unsigned char strResult[3];
unsigned int keyInt;
unsigned int num1Digit1;
unsigned int num1Digit2;
unsigned int twoDigit1;
unsigned int num2Digit1;
unsigned int num2Digit2;
unsigned int twoDigit2;
unsigned int operation;
unsigned int result;
////////////////////////////////////////////////////////////////////////////////
// Main Function
////////////////////////////////////////////////////////////////////////////////
void main() {
  // Set PORTD as input port
  TRISD = 0XFF;

  // Initialize the LCD
  Lcd_Init();
  Lcd_Cmd(_LCD_CLEAR);
  Lcd_Cmd(_LCD_CURSOR_OFF);
  while(1){
    // Display calculator
    Lcd_Out(1,3,"Gogul's Calci");
    delay_ms(2000);
    Lcd_Cmd(_LCD_CLEAR);

    // Get Number 1
    while(1){
      int flag = 0;
      Lcd_Out(1,3,"No1: ");
      num1Digit1 = 0;
      num1Digit2 = 0;
      num1Digit1  = keypadScan();
      if(num1Digit1 + '0' == '=') break;
      if(num1Digit1 + '0' == '*' || num1Digit1 + '0' == '/' || num1Digit1 + '0' == '-'|| num1Digit1 + '0' == '+') {
         Lcd_out(1,11,"Error");
         delay_ms(1000);
         Lcd_out(1,11,"     ");
         num1Digit1 = keypadScan();
      }
      Lcd_chr(1,10,num1Digit1 + '0');
      
      num1Digit2 = keypadScan();
      if(num1Digit2 + '0' == '=') {
         flag = 1;
      }
      else {
         flag = 0;
      }
      if(num1Digit2 + '0' == '*' || num1Digit2 + '0' == '/' || num1Digit2 + '0' == '-'|| num1Digit2 + '0' == '+') {
         Lcd_out(1,11,"Error");
         delay_ms(1000);
         Lcd_out(1,11,"     ");
         num1Digit2 = keypadScan();
      }
      if(flag == 1){
           twoDigit1 = num1Digit1;
           break;
      }
      else {
           twoDigit1 = concatenate(num1Digit1, num1Digit2);
      }
      Lcd_chr(1,11,num1Digit2 + '0');
    }

    // Get Number 2
    while(1){
      int flag = 0;
      Lcd_Out(2,3,"No2: ");
      num2Digit1 = 0;
      num2Digit2 = 0;
      num2Digit1  = keypadScan();
      if(num2Digit1 + '0' == '=') break;
      if(num2Digit1 + '0' == '*' || num2Digit1 + '0' == '/' || num2Digit1 + '0' == '-'|| num2Digit1 + '0' == '+') {
         Lcd_out(2,11,"Error");
         delay_ms(1000);
         Lcd_out(2,11,"     ");
         num2Digit1 = keypadScan();
      }
      Lcd_chr(2,10,num2Digit1 + '0');
      num2Digit2 = keypadScan();
      if(num2Digit2 + '0' == '=') {
         flag = 1;
      }
      else {
         flag = 0;
      }
      if(num2Digit2 + '0' == '*' || num2Digit2 + '0' == '/' || num2Digit2 + '0' == '-'|| num2Digit2 + '0' == '+') {
         Lcd_out(2,11,"Error");
         delay_ms(1000);
         Lcd_out(2,11,"     ");
         num2Digit2 = keypadScan();
      }
      if(flag == 1){
           twoDigit2 = num2Digit1;
           break;
      }
      else {
           twoDigit2 = concatenate(num2Digit1, num2Digit2);
      }
      Lcd_chr(2,11,num2Digit2 + '0');
    }
    // Clear the LCD
    Lcd_Cmd(_LCD_CLEAR);

    // Get the operation
    Lcd_Out(1,3,"Operation ");
    operation  = keypadScan();
    operationChar  = operation + '0';
    delay_ms(50);

    // Types of operation
    switch(operationChar){
       case '+': result = twoDigit1 + twoDigit2; break;
       case '-': {
            if(twoDigit1 > twoDigit2){
               result = twoDigit1 - twoDigit2; break;
            }
            else if(twoDigit2 > twoDigit1){
               result = twoDigit2 - twoDigit1; break;
            }
            else if(twoDigit1 == twoDigit2){
               result = 0; break;
            }
       }
       case '*': result = twoDigit1 * twoDigit2; break;
       case '/': result = twoDigit1 / twoDigit2; break;
    }
    Lcd_Cmd(_LCD_CLEAR);

    // Print the result
    Lcd_Out(1,3,"Result");
    IntToStr(result,strResult);
    Lcd_Out(2,5,strResult);

    // Show the result for 5 seconds and clear the screen
    delay_ms(5000);
    Lcd_Cmd(_LCD_CLEAR);
  }
}
////////////////////////////////////////////////////////////////////////////////
//Scanning algorithm for Keypad
////////////////////////////////////////////////////////////////////////////////
unsigned int keypadScan(){
    Keypad_Init();
    do{
       key = '0';
       do{
          key = keypad_key_click();
       }
       while(!key);
       switch(key){
          case 1:  key = '7'; break; // 7   - 55
          case 2:  key = '4'; break; // 4   - 52
          case 3:  key = '1'; break; // 1   - 49
          case 4:  key = '?'; break; // ?   - 63
          case 5:  key = '8'; break; // 8   - 56
          case 6:  key = '5'; break; // 5   - 53
          case 7:  key = '2'; break; // 2   - 50
          case 8:  key = '0'; break; // 0   - 48
          case 9:  key = '9'; break; // 9   - 57
          case 10: key = '6'; break; // 6   - 54
          case 11: key = '3'; break; // 3   - 51
          case 12: key = '='; break; // =   - 61
          case 13: key = '/'; break; // /   - 47
          case 14: key = '*'; break; // *   - 42
          case 15: key = '-'; break; // -   - 45
          case 16: key = '+'; break; // +   - 43
       }
       delay_ms(100);
       // Convert char to int
       keyInt = key - '0';
       // return int
       return keyInt;
       }
    while(1);
}