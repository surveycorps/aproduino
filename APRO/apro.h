/**
* @file apro.h
*
* Pins used for the core to manage nrf24, encoders, and motor drivers
*/

#include <RF24.h>

#define CW LOW
#define CCW HIGH

// E6
#define LED 7

/*** Motors and Encoders ***/
// D2 | C7 | B4
#define ENCODER_L 0
#define PWM_L 13
#define DIR_L 8
#define INT_VECT_L 2

// D1 | C6 | B5
#define ENCODER_R 2
#define PWM_R 5
#define DIR_R 9
#define INT_VECT_R 1

// D0 | D3 | B6 | B7
#define ENCODER_S 3
#define ENCODER_S2 1
#define PWM_S 10
#define DIR_S 11
#define INT_VECT_S 0
#define INT_VECT_S2 3

/*** NRF24L01+ ***/
// D7 | D4
#define CE 6
#define CSN 4

// Wireless Setup
#define WRITE_ADDR 0xe7e7e7e7e7LL
#define READ_ADDR 0xc2c2c2c2c2LL
#define CHANNEL 0x60
#define PAYLOAD_SIZE 6

const uint64_t pipes[2] = {WRITE_ADDR, READ_ADDR};

class APRO
{
public:
   APRO();
   void init_radio(RF24 radio);
   void init_motors();
};
