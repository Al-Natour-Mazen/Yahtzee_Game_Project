#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include "Figure.h"
#include "Brelan.h"
#include "Carre.h"
#include "Full.h"
#include "Chance.h"
#include "GrandeSuite.h"
#include "PetiteSuite.h"
#include "Yahtzee.h"
#include "Number.h"

class Joueur {
public:
    Joueur(int number);
    virtual ~Joueur();

    virtual void createAllFigures();
    void createMinorFigures();
    void createMajorFigures();
    void createHardcoreFigures();

    virtual void resetFigures();
    virtual void handleYahtzeeBonus();

    void displayUsedFiguresAndScores(const int& numplayer) const;

    void chooseFigureFacileAndPlusModes();
    void chooseFigureDifficileAndPlusModes(const int& NombreMaxOfFigureTopick);


    int getTotalScore() const;
    bool isFiguresEmpty() const;

    const std::string& getJoueurName() const;

    void calculateFiguresScore(const std::vector<int>& diceValues) const;


    void serialize(std::ostream& out) const;
    void deserialize(std::istream& in);

protected:
    std::vector<std::shared_ptr<Figure>> m_figures;
    std::vector<std::shared_ptr<Figure>> m_figuresUsed;
   
    bool m_firstYahtzee;
    bool m_yahtzeeBonus;
    int m_minorScore;
    int m_totalScore;
    std::string m_name;


    bool aleardyHardFigureCreated;
    std::vector<int> ordreCreationFiguresHardcore;

    virtual bool isFigureUsed(Figure* figure) const;

    std::shared_ptr<Figure> createNumberFigure(unsigned int id) const;
    std::shared_ptr<Figure> createFigures(unsigned int id) const;


    void updateScores(int scoreForFigure, std::shared_ptr<Figure> selectedFigure);
    void displayFigureAndScores() const;
    void chooseFigureHelper(const int& maxFigures);
};
