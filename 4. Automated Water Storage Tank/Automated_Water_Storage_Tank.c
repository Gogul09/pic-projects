void motor_state1();
void motor_state2();
void motor_state3();

int check = 0;

void main() {
      TRISD = 0x00;
      TRISB = 0x03;
      while(1){
        if(PORTB.F0 == 0 && PORTB.F1 == 0){
            motor_state1();
        }
        if(PORTB.F0 == 0 && PORTB.F1 == 1){
            if(check == 0){
               motor_state2();
            }
            else if (check == 1){
               motor_state1();
            }
        }
        if(PORTB.F0 == 1 && PORTB.F1 == 1){
            motor_state3();
        }
      }
}

void motor_state1(){
     // Motor 1 ON
     PORTD.F0 = 1;
     PORTD.F1 = 0;
     // Motor 2 OFF
     PORTD.F2 = 0;
     PORTD.F3 = 0;
     // Clear flag
     check = 0;
}
void motor_state2(){
    // Motor 1 ON
    PORTD.F0 = 1;
    PORTD.F1 = 0;
    // Motor 2 OFF
    PORTD.F2 = 0;
    PORTD.F3 = 0;
    // Set flag
    check = 1;
}
void motor_state3(){
    // Motor 1 OFF
    PORTD.F0 = 0;
    PORTD.F1 = 0;
    // Motor 2 ON
    PORTD.F2 = 1;
    PORTD.F3 = 0;
}