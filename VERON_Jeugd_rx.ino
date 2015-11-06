#include <Manchester.h>

/*
VERON_Jeugd_rx
Gerrit Polder, PA3BYA

Programmatje om met attiny85 en 433MHz zendmodule een signaaltje te ontvangen.
Bij ontvangst van een geldig signaal wordt afwisselend twee ledjes aan en uitgezet.
Ledjes kunnen b.v. de ogen zijn van een van lasdraad gesoldeerd poppetje.

Software voor Jeugd project prijsvraag op de DVRA 2015

*/

#define RX_PIN 0
#define LED_L 1
#define LED_R 2

uint8_t moo = 0;
uint8_t data;
uint8_t id;

void setup() {
  pinMode(LED_L, OUTPUT);  
  digitalWrite(LED_L, moo);
  pinMode(LED_R, OUTPUT);  
  digitalWrite(LED_R, moo);
  man.setupReceive(RX_PIN, MAN_1200);
  man.beginReceive();
}

void loop() {
  if (man.receiveComplete()) { //received something
    uint16_t m = man.getMessage();
    man.beginReceive(); //start listening for next message right after you retrieve the message
    if (man.decodeMessage(m, id, data)) { //extract id and data from message, check if checksum is correct
      //id now contains ID of sender (or receiver(or any other arbitrary 4 bits of data))
      //data now contains one byte of data received from sender
      //both id and data are BELIEVED (not guaranteed) to be transmitted correctly
      moo = ++moo % 4;
      
      switch (moo) {
          case 0:
            digitalWrite(LED_L, 0);
            digitalWrite(LED_R, 0);
            break;
          case 1:
            digitalWrite(LED_L, 1);
            digitalWrite(LED_R, 0);
            break;
          case 2:
            digitalWrite(LED_L, 0);
            digitalWrite(LED_R, 1);
            break;
          case 3:
            digitalWrite(LED_L, 1);
            digitalWrite(LED_R, 1);
            break;      
          default: 
            digitalWrite(LED_L, 0);
            digitalWrite(LED_R, 0);
          break;
        }
    }
  }
}

