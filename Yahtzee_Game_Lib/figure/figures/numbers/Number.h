#pragma once
#include "Figure.h"

template<short ID>
class Number : public Figure {
public:
    Number() = delete;
    Number(unsigned int number) : m_number(number) {}

    int calculateScore(const std::vector<int>& diceValues) {
        int score = 0;
        for (int value : diceValues) {
            if (value == m_number) {
                score += value;
            }
        }
        return score;
    }

    std::string getName() const {
        return "Number " + std::to_string(m_number);
    }

    short getId() const {
        return ID;
    }

private:
    const unsigned int m_number;
};


