#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>
#include "LowPower.h"

RF24 radio(8, 7);
const uint64_t pipe = 0xe8e8e8e8e7LL;

void setup(void) {
  Serial.begin(115200);
  pinMode(10, OUTPUT);

  radio.begin();                        
  radio.setPayloadSize(32);
  radio.setChannel(0x76);
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_1MBPS);
  radio.setAutoAck(1);                
  radio.enableDynamicPayloads();
  radio.enableAckPayload();

  radio.openReadingPipe(1, pipe);
  radio.startListening();
}

void loop(void) {
  char msg[32] = {0};
  char msg2[32]={0};
  if (radio.available()) {
    radio.read(msg, sizeof(msg));
    
    String stringMsg(msg);

    if (stringMsg == "GETSTRING") {
      digitalWrite(10, 1);
      delay(500);
      digitalWrite(10, 0);
      delay(500);
      Serial.println(stringMsg);

    }
    
	      	
    
  } else {
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
    
    digitalWrite(10, 1);
    delay(2000);
    digitalWrite(10, 0);
    delay(2000);
  }
}