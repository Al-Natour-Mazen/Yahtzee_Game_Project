#include "Joueur.h"
#include <algorithm>

//============================================//
//                  PUBLIC                    //
//============================================//

/** Create a player with a total and minor score of 0 and a game grid empty.
**/
Joueur::Joueur() : m_totalScore(0), m_yahtzeeBonus(false), m_minorScore(0), m_firstYahtzee(false) {
    // Already init.
}

/** Destructor for a player, destroy all the vectors with allocated figures.
**/
Joueur::~Joueur() {
    for (Figure* f : m_figures) {
        delete f;
    }
    for (Figure* f : m_figuresUsed) {
        delete f;
    }
}

/** Create all the figures for the minor part if they are not already in the used figures.
**/
void Joueur::createMinorFigures() {
    for (unsigned int i = 1; i <= 6; ++i) {
        Figure* newFigure = createMinorFigure(i);
        if (newFigure && !isFigureUsed(newFigure)) {
            m_figures.push_back(newFigure);
        }
    }
}

/** Create all the figures for the major part if they are not alreadyin the used figures.
**/
void Joueur::createMajorFigures() {
    for (unsigned short i = 0; i < 7; ++i) {
        Figure* newFigure = nullptr;
        switch (i) {
        case 0:
            newFigure = new Brelan<7>();
            break;
        case 1:
            newFigure = new Carre<8>();
            break;
        case 2:
            newFigure = new Full<9>();
            break;
        case 3:
            newFigure = new PetiteSuite<10>();
            break;
        case 4:
            newFigure = new GrandeSuite<11>();
            break;
        case 5:
            !m_firstYahtzee ? newFigure = new Yahtzee<ID_YAHTZEE_FIRST>() : newFigure = new Yahtzee<ID_YAHTZEE_BONUS>();
            break;
        case 6:
            newFigure = new Chance<14>();
            break;
        }
        if (newFigure && !isFigureUsed(newFigure)) {
            handleYahtzeeBonus(newFigure);
        }
    }
}

/** Create the figures for the minor and major part of the game.
**/
void Joueur::createAllFigures() {
    createMinorFigures();
    createMajorFigures();
}

/** Remove all the figures that we don't use anymore. 
**/
void Joueur::resetFigures() {
    m_figures.clear();
}

/** Display the differents figures possible for a set of dice.
*   @param diveValues : vector of 5 dices.
**/
void Joueur::displayFigureAndScores(const std::vector<int>& diceValues) const {
    std::cout << "Scores des figures possibles : " << std::endl;
    for (size_t i = 0; i < m_figures.size(); ++i) {
        std::cout << i + 1 << ". " << m_figures[i]->getName() << ": " << m_figures[i]->calculateScore(diceValues) << " points" << std::endl;
    }
    std::cout << std::endl;
}


/** Display all the figures and get the figure choose by the player.
*   @param diceValues : vector of 5 dices.
**/
void Joueur::chooseFigure(const std::vector<int>& diceValues) {
    int choice;

    std::cout << std::endl << "Choisissez une figure parmi les options suivantes :" << std::endl;
    displayFigureAndScores(diceValues);

    bool correctAnswer = false;

    do {
        if (m_figures.empty()) {
            std::cout << "Il n'y a plus de figures disponibles. Fin de la Partie." << std::endl;
            break;
        }

        std::cout << "Choix (1-" << m_figures.size() << ") : ";
        std::cin >> choice;

        if (choice >= 1 && choice <= static_cast<int>(m_figures.size())) {
            Figure* selectedFigure = m_figures[choice - 1];

            // V�rifier si la figure a d�j� �t� utilis�e
            if (isFigureUsed(selectedFigure)) {
                std::cout << "Vous avez d�j� choisi cette figure. Veuillez choisir une figure diff�rente." << std::endl;
            }
            else {
                int scoreForFigure = selectedFigure->calculateScore(diceValues);
              
                updateScores(scoreForFigure, selectedFigure);

                correctAnswer = true;
            }
        }
        else {
            std::cout << "Choix invalide. Veuillez choisir une figure valide." << std::endl;
        }
    } while (!correctAnswer);
}

/** Give the total score of the game in progress.
*   @return : the total score.
**/
int Joueur::getTotalScore() const
{
    return m_totalScore;
}
// TODO : METTRE UN COM
void Joueur::serialize(std::ostream& out) const {
    out << m_firstYahtzee << "\n";
    out << m_yahtzeeBonus << "\n";
    out << m_minorScore << "\n";
    out << m_totalScore << "\n";

    out << m_figures.size() << "\n";
    for (const auto& figure : m_figures) {
        figure->serialize(out);
    }

    out << m_figuresUsed.size() << "\n";
    for (const auto& figure : m_figuresUsed) {
        figure->serialize(out);
    }
}

// TODO : METTRE UN COM
void Joueur::deserialize(std::istream& in) {
    in >> m_firstYahtzee;
    in >> m_yahtzeeBonus;
    in >> m_minorScore;
    in >> m_totalScore;

    size_t taille;
    in >> taille;
    m_figures.resize(taille);
    for (auto& figure : m_figures) {
        int typeId;
        in >> typeId;
        switch (typeId) {
        case 1:
            //figure = new Brelan<65465>();
            break;
        case 2:
            //figure = new SubFigure2();
            break;
            // Ajoutez pour chaque sous-classe de Figure
        default:
            throw std::runtime_error("Type de figure inconnu");
        }
        figure->deserialize(in);
    }

    // Faites de m�me pour m_figuresUsed
}

//============================================//
//                  PRIVATE                   //
//============================================//

/** Look if the figure pass in parameter is in the used figures.
*   @param figure : the figure that need to be check.
*   @return : true if the figure is in the used figures else false.
*/
bool Joueur::isFigureUsed(Figure* figure) const {
    auto is_figure = [figure](const Figure* usedFigure) {
        return figure->getId() == usedFigure->getId();
        };

    return std::find_if(m_figuresUsed.begin(), m_figuresUsed.end(), is_figure) != std::end(m_figuresUsed);
}

/** Create a figure in the minor part of the game, base on the number on a dice.
*   @param number : the number on a dice (form 1 to 6)
*   @return : the figure associate with it's number.
**/
Figure* Joueur::createMinorFigure(unsigned int number) const {
    switch (number) {
    case 1: return new Number<1>(number);
    case 2: return new Number<2>(number);
    case 3: return new Number<3>(number);
    case 4: return new Number<4>(number);
    case 5: return new Number<5>(number);
    case 6: return new Number<6>(number);
    default: return nullptr;
    }
}

/** For one figure, look if it's the second Yahtzee and if it's the case then add 100 points to the player.
*   @param newFigure : the figure that we want to check for the second Yahtzee.
**/
void Joueur::handleYahtzeeBonus(Figure* newFigure) {
    if (newFigure->getId() == ID_YAHTZEE_BONUS) {
        if (!m_yahtzeeBonus) {
            std::cout << "Yahtzee encore ! +100 points." << std::endl;
            m_totalScore += 100;
            m_yahtzeeBonus = true;
        }
        delete newFigure;
    }
    else {
        m_figures.push_back(newFigure);
    }
}

/** Update the total score base on the points that the selected figure give us.
*   @param scoreForFigure : is the score for the selected figure.
*   @param selectedFigure : the figure selected.
**/
void Joueur::updateScores(int scoreForFigure, Figure* selectedFigure) {
    const short figureId = selectedFigure->getId();

    if (figureId == ID_YAHTZEE_FIRST && scoreForFigure > 0) {
        m_firstYahtzee = true;
    }

    m_totalScore += scoreForFigure;

    if (figureId >= 1 && figureId <= 6) {
        m_minorScore += scoreForFigure;
        if (m_minorScore >= 63) {
            m_totalScore += 35;
        }
    }

    std::cout << "Vous avez choisi " << selectedFigure->getName() << " et vous avez obtenu " << scoreForFigure << " points." << std::endl;

    // Add the selected figure to the list of figures used.
    m_figuresUsed.push_back(selectedFigure);
}

