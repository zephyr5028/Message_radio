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
  byte message[VW_MAX_MESSAGE_LEN];
  byte taille_message = VW_MAX_MESSAGE_LEN;
  // N.B. La constante VW_MAX_MESSAGE_LEN est fournie par la lib VirtualWire

  /*
    La variable "taille_message" doit impérativement être remise à
    la taille du buffer avant de pouvoir recevoir un message.
    Le plus simple est d'utiliser une variable locale pour ne pas
    avoir à réassigner la valeur à chaque début de loop().
  */
  //Serial.print(VW_MAX_MESSAGE_LEN);
  // On attend de recevoir un message
  vw_wait_rx();

  if (vw_get_message(message, &taille_message)) {
    // On copie le message, qu'il soit corrompu ou non
    digitalWrite(13, true); // Flash a light to show received good message
    Serial.println((char*) message); // Affiche le message
    digitalWrite(13, false);
  }
}
