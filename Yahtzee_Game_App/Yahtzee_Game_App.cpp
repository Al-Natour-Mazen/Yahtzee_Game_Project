// Yahtzee_Game_App.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "../Yahtzee_Game_Lib/Joueur.h"
#include "../Yahtzee_Game_Lib/Lancer.h"

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    Joueur joueur;

    for (int round = 0; round < 13; ++round) { // Correction : Il y a 13 tours dans le Yahtzee
        Lancer lancer;
        lancer.rollDice();

        std::cout << "Valeurs des des : ";
        for (int value : lancer.getDiceValues()) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
        joueur.resetFigures();

        joueur.createFigures(lancer.getDiceValues());

        joueur.chooseFigure(lancer.getDiceValues());

        joueur.calculateTotalScore(lancer.getDiceValues());

        std::cout << "Score total du joueur : " << joueur.totalScore << std::endl;
    }

    return 0;
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.