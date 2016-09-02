void main()
{
  short duty  = 0; //initial value for duty

  TRISD = 0xFF; //PORTD as input
  TRISC = 0x00; //PORTC as output
  TRISB = 0x00; //PORTB as output
  PORTB = 0x02; //Run motor in anticlock wise

  PWM1_Init(1000);  //Initialize PWM1
  PWM1_Start();  //start PWM1
  PWM1_Set_Duty(duty); //Set current duty for PWM1

  while (1)        // endless loop
  {
     if (!RD0_bit && duty<250) //if button on RD0 pressed
     {
        Delay_ms(40);
        duty = duty + 10;  //increment current_duty
        PWM1_Set_Duty(duty);  //Change the duty cycle
     }
     if (!RD1_bit && duty >0) //button on RD1 pressed
     {
       Delay_ms(40);
       duty = duty - 10;  //decrement duty
       PWM1_Set_Duty(duty);
     }
    Delay_ms(10);      // slow down change pace a little
  }
}