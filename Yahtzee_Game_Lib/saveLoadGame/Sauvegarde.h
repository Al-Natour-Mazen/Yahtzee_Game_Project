#pragma once
#include <fstream>

class YahtzeeGame;

class Sauvegarde {
public:
    // M�thode pour sauvegarder l'�tat du jeu
    void sauvegarder(const YahtzeeGame& jeu);

    // M�thode pour charger l'�tat du jeu
    void charger(YahtzeeGame& jeu) const;
};


