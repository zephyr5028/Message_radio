/***********************************
  JlmRadio433.h
  prototype de la classe JlmRadio433
  radio 433MHz
***********************************/

#ifndef DEF_JlmRadio433
#define DEF_JlmRadio433

/*-----virtualWire pour la liaison RF 433Mhz-----*/
#include <VirtualWire.h>
#include <VirtualWire_Config.h>
#include <Arduino.h>

class JlmRadio433
{
  public:

    JlmRadio433(boolean radio = false , boolean debug = false );// constructeur avec debug, radio
    ~JlmRadio433(); // destructeur

    void assemblageMessage(char chaine1[]);//routine envoi message radio
    void finMessage();//chaine radio fin de ligne avant transmission
    void envoiMessageRadio(char chaine1[]);  // envoi message Radio

  private:

    boolean m_debug ; // pour affichage console si nécessaire
    boolean m_radio; // pour envoi radio si necessaire
    int const m_taille; // taille du tableau
    char m_chaine[]; // tableau de la chaine avant envoi

};

#endif

