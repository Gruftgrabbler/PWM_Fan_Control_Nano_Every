#ifdef ARDUINO_ARCH_MEGAAVR
#define Timer1 TimerB2 // use TimerB2 as a drop in replacement for Timer1
#else
#error "Architecutre not supported. Please use an Arduino Nano Every."
#endif

#include "Arduino-Nano-Every-Timer-Controller-B/EveryTimerB/EveryTimerB.h"
// More Informations about how to use the Library can be found on https://github.com/Kees-van-der-Oord/Arduino-Nano-Every-Timer-Controller-B
// Especially helpfull is https://github.com/Kees-van-der-Oord/Arduino-Nano-Every-Timer-Controller-B/issues/1

#define DELAY_TIME_MS 100

#define POT_PIN         A7
const int FAN_PWM_PIN   = 3;  
const int LED_PIN       = 2;
const int CLOCK_DIVIDER = 10;  

EveryTimerB TimerB0;

//Smooth the Analog Potentiometer Reading
const int NUM_READINGS  = 3;
int readings[NUM_READINGS];
int readIndex;
int sum;
int avg;

void setup() {
  pinMode(POT_PIN, INPUT);
  pinMode(FAN_PWM_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(LED_PIN, HIGH);                  // Just an Arduino Power LED, but you can do more fancy stuff with it

  TimerB0.initialize(&TCB1);                    // TimerB0 uses Pin 3 as output internally
  TimerB0.setClockSource(TCB_CLKSEL_CLKTCA_gc); // 256kHz clock source. Divided by 10 equals 25.6kHz which is okay for a PWM Fan

  for(int i=0; i<NUM_READINGS; i++){
    readings[i] = 0;                            // Initialize Reading Array
  }

  Serial.begin(9600);
}

void loop() {
  //int pot_val = map(analogRead(POT_PIN), 0, 1023, 0, 128);

  sum -= readings[readIndex];                   // Subtract the last reading
  readings[readIndex] = analogRead(POT_PIN);    // Read Potentiometer and save value
  sum += readings[readIndex];                   //
  readIndex++;
  if(readIndex >= NUM_READINGS) readIndex = 0;  //
  
  avg = sum/NUM_READINGS;                       // Smooth the Potentiometer Readings by average the readings
  Serial.println(map(avg, 0, 1023, 0, 128));
  TimerB0.setPwmMode(CLOCK_DIVIDER, map(avg, 0, 1023, 0, 10)); 
  delay(DELAY_TIME_MS);
}