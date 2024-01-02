#include "IA.h"

IA::IA() : Joueur() {}

void IA::chooseFigure(const std::vector<int>& diceValues) {
    displayFigureAndScores(diceValues);

    double maxExpectedScore = -1.0;
    std::shared_ptr<Figure> bestFigure = nullptr;

    // Parcourir toutes les figures disponibles
    for (auto& figure : m_figures) {
        // V�rifier si la figure a d�j� �t� utilis�e
        if (isFigureUsed(figure.get())) continue;

        // Calculer le score attendu pour cette figure
        double expectedScore = figure->calculateScore(diceValues);

        // Si le score attendu est plus �lev� que le score maximal actuel, mettre � jour le score maximal et la meilleure figure
        if (expectedScore > maxExpectedScore) {
            maxExpectedScore = expectedScore;
            bestFigure = figure;
        }
    }

    // Mettre � jour les scores et ajouter la meilleure figure � la liste des figures utilis�es
    if (bestFigure != nullptr) {
        int score = bestFigure->calculateScore(diceValues);
        updateScores(score, bestFigure);
        m_figuresUsed.push_back(bestFigure);
    }
}

