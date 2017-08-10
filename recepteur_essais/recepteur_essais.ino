/*******************************
  gestion  radio 433MHz

  recepteur
*******************************/
#include <VirtualWire.h>
void setup() {
  Serial.begin(9600);
  vw_setup(2000); // initialisation de la bibliothèque VirtualWire à 2000
  vw_set_rx_pin(11); // broche d11 recepteur
  vw_setup(600); // initialisation de la bibliothèque avec la vitesse (vitesse_bps)
  vw_rx_start(); // On peut maintenant recevoir des messages
  Serial.println("Go !");
}

void loop() {
  uint8_t taille_message = VW_MAX_MESSAGE_LEN;
  uint8_t message[VW_MAX_MESSAGE_LEN];
  // N.B. La constante VW_MAX_MESSAGE_LEN est fournie par la lib VirtualWire
  /*
    La variable "taille_message" doit impérativement être remise à
    la taille du buffer avant de pouvoir recevoir un message.
    Le plus simple est d'utiliser une variable locale pour ne pas
    avoir à réassigner la valeur à chaque début de loop().
  */
  //Serial.print("taille du message : ");
  //Serial.println(taille_message);
  unsigned long millisecondes = 1000;
  // On attend de recevoir un message
  //vw_wait_rx();
  if (vw_wait_rx_max( millisecondes)) {
    if (vw_get_message(message, &taille_message)) {
      // On copie le message, qu'il soit corrompu ou non
      //    vw_get_message(message, &taille_message);
      int i;
      digitalWrite(13, true); // Flash a light to show received good message
      // Message with a good checksum received, dump it.
      //Serial.print("Got: ");
       Serial.println((char*) message); // Affiche le message
      for (i = 0; i < taille_message; i++)
      {
        //  Serial.print(message[i], BIN);
        Serial.write(message[i]);
      }
      Serial.println("");
      digitalWrite(13, false);
    }
    //  Serial.println((char*) message); // Affiche le message
  }
}
/*
  // receiver.pde
  //
  // Simple example of how to use VirtualWire to receive messages
  // Implements a simplex (one-way) receiver with an Rx-B1 module
  //
  // See VirtualWire.h for detailed API docs
  // Author: Mike McCauley (mikem@airspayce.com)
  // Copyright (C) 2008 Mike McCauley
  // $Id: receiver.pde,v 1.3 2009/03/30 00:07:24 mikem Exp $
  #include <VirtualWire.h>
  void setup()
  {
    Serial.begin(9600); // Debugging only
    Serial.println("setup");
    // Initialise the IO and ISR
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000);      // Bits per sec
    vw_rx_start();       // Start the receiver PLL running
  }
  void loop()
  {
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
        int i;
        digitalWrite(13, true); // Flash a light to show received good message
        // Message with a good checksum received, dump it.
        Serial.print("Got: ");

        for (i = 0; i < buflen; i++)
        {
            Serial.print(buf[i], HEX);
            Serial.print(" ");
        }
        Serial.println("");
        digitalWrite(13, false);
    }
  }
*/

/*
avec rxb6
#include <VirtualWire.h>

const int led_pin = 13;
const int transmit_pin = 12;
const int receive_pin = 11;
const int transmit_en_pin = 3;

void setup()
{
    delay(1000);
    Serial.begin(9600); // Debugging only
    Serial.println("setup");

    // Initialise the IO and ISR
    vw_set_tx_pin(transmit_pin);
    vw_set_rx_pin(receive_pin);
    vw_set_ptt_pin(transmit_en_pin);
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000);  // Bits per sec

    vw_rx_start();       // Start the receiver PLL running

    pinMode(led_pin, OUTPUT);
}

void loop()
{
    // RF 433 MHz Module
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
        int i;
      digitalWrite(led_pin, HIGH); // Flash a light to show received good message
        // Message with a good checksum received, dump it.
        Serial.print("Got: ");
        for (i = 0; i < buflen; i++)
        {
          Serial.print(buf[i], HEX);
          Serial.print(' ');
        }
      Serial.println();
      Serial.println("Got TEXT: ");
      for (i = 0; i < buflen; i++)
      {
        Serial.print((char)buf[i]);
      }
      Serial.println();
      Serial.println();
      digitalWrite(led_pin, LOW);
  }
}*/
