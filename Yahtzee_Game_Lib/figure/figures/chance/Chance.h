#pragma once
#include "Figure.h"

template<short ID>
class Chance : public Figure {
public:
    int calculateScore(const std::vector<int>& diceValues) {
        int sum = 0;
        for (int value : diceValues) {
            sum += value;
        }
        return sum;
    }

    std::string getName() const {
        return "Chance";
    }

    short getId() const {
        return ID;
    }

    void serialize(std::ostream& out) const {
        // La classe Chance n'a pas de membres de donn�es � s�rialiser
    }

    void deserialize(std::istream& in)  {
        // La classe Chance n'a pas de membres de donn�es � d�s�rialiser
    }
};

