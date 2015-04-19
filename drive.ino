#include <SPI.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <printf.h>
#include <apro.h>

/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 Modified by Alain Hernandez and Alfredo Muniz
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
*/

// Set CSN/SS to pin D4 = 6, Set CE to Pin D3 = 5

RF24 radio(CE, CSN); // CE, CSN
APRO robot;

byte payload[PAYLOAD_SIZE];
volatile boolean state_r = 0;
volatile boolean state_l = 0;
volatile boolean state_s = 0;
volatile boolean state_s2 = 0;
volatile boolean dir = 0;
volatile int count = 0;

boolean stop = 0;

void setup(void)
{
  // Print preamble
  //
  //Serial.begin(1000000);
  delay(500);
  //printf_begin();
  //printf("\n\rRF24/examples/pingpair_dyn/\n\r");
  robot.init_motors();
  //robot.init_radio(radio);
  attachInterrupt(INT_VECT_R, count_r, CHANGE);
  attachInterrupt(INT_VECT_L, count_l, CHANGE);
  attachInterrupt(INT_VECT_S, count_s, CHANGE);
  attachInterrupt(INT_VECT_S2, count_s2, CHANGE);
}

void loop(void)
{
  // rising S2 S = low CW
  // falling S2 S = high CW
  // rising S S2 = high CW
  // falling S S2 = low CW
  
  // rising S2 S = high CCW 
  // falling S2 S = low CCW
  // rising S S2 = low CCW
  // falling S S2 = high CCW
  
  digitalWrite(DIR_R, CCW);
  analogWrite(PWM_R, 200);
  digitalWrite(DIR_L, CCW);
  analogWrite(PWM_L, 200);
  //digitalWrite(DIR_S, CCW);
  //analogWrite(PWM_S, 200);
  
  if (count > 40000) {
    count = 0;
  }
  //printf("dir=%d count=%d\n\r", dir, count);
  /*
  if( radio.available((uint8_t *)pipes[1]) )
  {
    printf("Got something\n");
    // Dump the payloads until we've gotten everything
    uint8_t len;
    while (radio.available((uint8_t *)pipes[1]))
    {
      // Fetch the payload, and see if this was the last one.
      radio.read(&payload, PAYLOAD_SIZE);

      // Spew it
      for (int i = 0; i < PAYLOAD_SIZE; i++) {
        printf("value=%d\n\r", payload[i]);
      }
      
      // Move the motors
      digitalWrite(DIR_L, payload[0]);
      analogWrite(PWM_L, payload[1]);
      digitalWrite(DIR_R, payload[2]);
      analogWrite(PWM_R, payload[3]);
      digitalWrite(DIR_S, payload[4]);
      analogWrite(PWM_S, payload[5]);
    }
  }
  */
}

void count_s()
{
  count = count + 1;
}

void count_s2()
{
  count = count + 1;
}

void count_l()
{
  state_l = state_l;
}

void count_r()
{
  state_r = state_r;
}
