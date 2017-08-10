/*******************************
  gestion radio 433MHz

  avec

  la classe JlmRadio433

  décembre 2016
*******************************/

/*-----debug-----*/
const boolean DEBUG = false; // positionner debug pour l'utiliser ou pas
const boolean RADIO = true; // positionner radio pour l'utiliser ou pas<

#include <SoftwareSerial.h>
#include "JlmRadio433.h"

/* emetteur 433Mhz */
byte  pinEmission = 10; // pin D10 emetteur radio
int vitesse = 600; // vitesse transmission

JlmRadio433 rad(RADIO, DEBUG); // class Radio avec true pour envoi par radio

#define LED_PIN 13 // led en broche 13

// définition des pin
enum PinAssignments {
};

void setup() {
  pinMode(LED_PIN, OUTPUT); // led
  Serial.begin (9600);
  rad.init(pinEmission, vitesse);// initialisation de la broche emission et de la vitesse de transmission
}

void loop ()
{
  // N.B. La constante VW_MAX_MESSAGE_LEN est fournie par la lib VirtualWire
  do  {
    if (RADIO) {
      char chaine1[VW_MAX_MESSAGE_LEN - 1] = "";
      strcat(chaine1, "A=");
      strcat(chaine1, "14");
      strcat(chaine1, "h");
      strcat(chaine1, "52");
      strcat(chaine1, "m");
      rad.assemblageMessage(chaine1);// on assemble le message
    }
    if (RADIO) {
      char chaine1[VW_MAX_MESSAGE_LEN - 1] = "";
      strcat(chaine1, "I=");
      strcat(chaine1, "930");
      rad.assemblageMessage(chaine1);// on assemble le message
    }
    if (RADIO) {
      char chaine1[VW_MAX_MESSAGE_LEN - 1] = "";
      strcat(chaine1, "K=");
      strcat(chaine1, "290");
      rad.assemblageMessage(chaine1);// on assemble le message

      digitalWrite(LED_PIN, HIGH);
      rad.finMessage(); // fin du message sur une ligne
      digitalWrite(LED_PIN, LOW);
    }
    if (RADIO) { // affichage si la batterie est faible
      char chaine1[VW_MAX_MESSAGE_LEN - 1] = "Batterie faible !!!!";
      digitalWrite(LED_PIN, HIGH);
      rad.envoiMessageRadio(chaine1);// on assemble le message
      digitalWrite(LED_PIN, LOW);
    }
    if (RADIO) {
      char chaine1[VW_MAX_MESSAGE_LEN - 1] = "";
      strcat(chaine1, "123456789");
      strcat(chaine1, "abcdefghijklmnopqrstuvwxyz");
      strcat(chaine1, "123456789");
      strcat(chaine1, "abcdefghijklmnopqrstuvwxyz");
      strcat(chaine1, "12345");
      rad.assemblageMessage(chaine1);//on assemble le message

      digitalWrite(LED_PIN, HIGH);
      rad.finMessage(); // fin du message sur une ligne
      digitalWrite(LED_PIN, LOW);
    }
    if (RADIO) {
      char chaine1[VW_MAX_MESSAGE_LEN - 1] = "";
      strcat(chaine1, "taille maximum du tableau : ");
      char taille_temp[2];
      /* char buffer [50];
        int n, a=5, b=3;
        n=sprintf (buffer, "%d plus %d is %d", a, b, a+b);
        printf ("[%s] is a string %d chars long\n",buffer,n);
      */
      sprintf(taille_temp, "%d",  VW_MAX_MESSAGE_LEN);
      strcat(chaine1, taille_temp);
      rad.assemblageMessage(chaine1);// on assemble le message

      digitalWrite(LED_PIN, HIGH);
      rad.finMessage(); // fin du message sur une ligne
      digitalWrite(LED_PIN, LOW);
    }
    delay(2000);
  }  while (1) ;
}
