#include <Manchester.h>

/*
VERON_Jeugd_tx
Gerrit Polder, PA3BYA

Programmatje om met attiny85 en 433MHz zendmodule een signaaltje te zenden.
Bij indrukken van de button wordt 10 keer per seconde het getal 2000 verzonden.

Software voor Jeugd project prijsvraag op de DVRA 2015

*/

#define TX_PIN 0  //pin where your transmitter is connected
#define LED_PIN 1 //pin for blinking LED
#define BUTTON_PIN 2 //pin for button
#define SENDER_ID 5

uint8_t moo = 1; //last led status
uint16_t transmit_data = 2000;
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, moo);
  man.workAround1MhzTinyCore(); //add this in order for transmitter to work with 1Mhz Attiny85/84
  man.setupTransmit(TX_PIN, MAN_1200);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(BUTTON_PIN);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == LOW) {
    // turn LED on:
    digitalWrite(LED_PIN, HIGH);
    man.transmit(man.encodeMessage(SENDER_ID, transmit_data));
    delay(100);
  } else {
    // turn LED off:
    digitalWrite(LED_PIN, LOW);
  }
}
