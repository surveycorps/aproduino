/* apro.c
 * This file contains all the helper functions to easily interface the
 * hardware with our robot
 */

#include "apro.h"
#include "RF24.h"

APRO::APRO() {}

void APRO::init_radio(RF24 radio)
{
  radio.begin();
  radio.setPayloadSize(PAYLOAD_SIZE);
  radio.setCRCLength(RF24_CRC_8);
  radio.setRetries(2, 15);
  radio.setDataRate(RF24_2MBPS);
  radio.setPALevel(RF24_PA_MAX);
  radio.setAutoAck(1);
  radio.setChannel(CHANNEL);
  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1, pipes[1]);
  radio.startListening();
  radio.stopListening();
  radio.printDetails();
  radio.startListening();
  radio.powerUp();
}

void APRO::init_motors()
{
  CLKPR = (1<<CLKPCE);
  CLKPR = 0;
  pinMode(LED, OUTPUT);

  pinMode(ENCODER_R, INPUT);
  pinMode(ENCODER_L, INPUT);
  pinMode(ENCODER_S, INPUT);
  pinMode(ENCODER_S2, INPUT);

  pinMode(PWM_R, OUTPUT);
  pinMode(PWM_L, OUTPUT);
  pinMode(PWM_S, OUTPUT);

  pinMode(DIR_R, OUTPUT);
  pinMode(DIR_L, OUTPUT);
  pinMode(DIR_S, OUTPUT);

  analogWrite(PWM_R, 0);
  analogWrite(PWM_L, 0);
  analogWrite(PWM_S, 0);

  digitalWrite(DIR_R, CW);
  digitalWrite(DIR_L, CW);
  digitalWrite(DIR_S, CW);
}
