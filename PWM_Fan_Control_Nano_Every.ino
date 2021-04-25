#ifdef ARDUINO_ARCH_MEGAAVR
#define Timer1 TimerB2 // use TimerB2 as a drop in replacement for Timer1
#else // assume architecture supported by TimerOne .... (For Example on an Arduino Uno)
#error "Architecutre not supported."
#endif

#include "Arduino-Nano-Every-Timer-Controller-B/EveryTimerB/EveryTimerB.h"

#define POT_PIN A7
const int FAN_PWM_PIN = 3;  
const int LED_PIN     = 2;  

//const unsigned long CPU_FEQ      = 1000000;             // 1MHz
//const unsigned long PWM_FREQ_HZ  = 1;                   // Adjust this value to adjust the pwm frequency
//const unsigned long COUNTER_TOP  = 16000000/(2*PWM_FREQ_HZ);
//const unsigned long TIMER_PERIOD = CPU_FEQ/PWM_FREQ_HZ;

EveryTimerB TimerB0;

void setup() {
  // put your setup code here, to run once:
  pinMode(POT_PIN, INPUT);
  pinMode(FAN_PWM_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(LED_PIN, HIGH);

  TimerB0.initialize(&TCB1);
  TimerB0.setClockSource(TCB_CLKSEL_CLKTCA_gc); // 256kHz clock source

  Serial.begin(9600);
}

void loop() {
  int pot_val = map(analogRead(POT_PIN), 0, 1023, 0, 128);
  Serial.print("Analog Read: "); Serial.print(analogRead(POT_PIN));
  Serial.print(" Pot_Val: "); Serial.println(pot_val);
  TimerB0.setPwmMode(10, pot_val); 
  delay(200);
}