/**********************************
  JlmRadio433.cpp
  définitions de la classe Radio
  radio 433MHz
**********************************/

#include "JlmRadio433.h"

//constructeur avec debug et radio pour affichage si nécessaire
JlmRadio433::JlmRadio433( boolean radio, boolean debug) : m_radio(radio), m_debug(debug),
  m_taille(VW_MAX_MESSAGE_LEN - 1)
{
  m_chaine[m_taille] = "";
  m_chaine[0] = '\0'; // initialisation du tableau m_chaine
}

JlmRadio433::~JlmRadio433()
{
}

// initialisation de la broche emission et de la vitesse
void JlmRadio433::init(byte pinEmission, int vitesse)
{
  vw_set_tx_pin(pinEmission); // broche d10 emetteur
  vw_setup(vitesse); // initialisation de la bibliothèque avec la vitesse (vitesse_bps)
}


//----routine envoi message radio----
void JlmRadio433::assemblageMessage(char chaine1[]) {
  byte resultat = strcmp(chaine1, "\0");
  if (resultat != 0) { // test de la fin de chaine
    strcat(m_chaine, chaine1);
    strcat(m_chaine, ";");
  } else {
    JlmRadio433::envoiMessageRadio(m_chaine);
    m_chaine[0] = '\0'; // raz de la chaine
  }
}

//----chaine radio fin de ligne avant transmission-----
void JlmRadio433::finMessage() {
  char chaine1[1] = "";
  strcat(chaine1, "\0");
  JlmRadio433::assemblageMessage(chaine1);// on assemble le message
}

//---- envoi message Radio-----
void JlmRadio433::envoiMessageRadio(char chaine1[]) {
  if (m_radio) {
    strcat(chaine1, '\0');
    vw_send((uint8_t *)chaine1, strlen(chaine1) + 1); // On envoie le message
    // strlen : Retourne le nombre de caractères de cs sans tenir compte du caractère de fin de chaîne.
    vw_wait_tx(); // On attend la fin de l'envoi
    delay(10);
  }
}


