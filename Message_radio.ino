/*******************************
  gestion d'un radio 433MHz

  avec

  la classe JlmRadio433

  décembre 2016
*******************************/

/*-----debug-----*/
const boolean DEBUG = false; // positionner debug pour l'utiliser ou pas
const boolean RADIO = true; // positionner radio pour l'utiliser ou pas

#include <SoftwareSerial.h>
#include "JlmRadio433.h"

JlmRadio433 rad(RADIO, DEBUG); // class Radio avec true pour envoi par radio

/* emetteur 433Mhz */
const byte pinEmRadio = 10; // pin D10 emetteur radio


// définition des pin
enum PinAssignments {

};

void setup() {
  Serial.begin (9600);
  if (RADIO) {
    vw_set_tx_pin(pinEmRadio); // broche d10 emetteur
    vw_setup(600); // initialisation de la bibliothèque avec la vitesse (vitesse_bps)
  }
}

void loop ()
{
  do  {
    if (RADIO) {
      //char chaine1[VW_MAX_MESSAGE_LEN - 1] = "Time : ";
      char chaine1[11] = "";
      strcat(chaine1, "A=");
      char hour_temp[3];
      char minute_temp[3];
      strcat(chaine1, "14");
      strcat(chaine1, hour_temp);
      strcat(chaine1, "h");
      strcat(chaine1, "52");
      strcat(chaine1, minute_temp);
      strcat(chaine1, "m");
      rad.assemblageMessage(chaine1);// on envoie le message
    }
    if (RADIO) {
      //char chaine1[VW_MAX_MESSAGE_LEN - 1] = "Lum : ";
      char chaine1[12] = "";
      strcat(chaine1, "I=");
      char lumSoir_temp[5];
      strcat(chaine1, "930");
      strcat(chaine1, lumSoir_temp);
      strcat(chaine1, ";");
      char lumValue_temp[5];
      strcat(chaine1, "290");
      strcat(chaine1, lumValue_temp);
      rad.assemblageMessage(chaine1);// on envoie le message
    }
    rad.finMessage();

    if (RADIO) { // affichage si la batterie est faible
      // N.B. La constante VW_MAX_MESSAGE_LEN est fournie par la lib VirtualWire
      //char chaine1[VW_MAX_MESSAGE_LEN - 1] = "Batterie faible !!!!";
      char chaine1[21] = "Batterie faible !!!!";
      rad.envoiMessageRadio(chaine1);// on envoie le message
    }
  }  while (1) ;
}
