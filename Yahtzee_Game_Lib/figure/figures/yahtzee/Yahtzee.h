#pragma once
#include "Figure.h"

template<short ID>
class Yahtzee : public Figure {
public:
    int calculateScore(const std::vector<int>& diceValues) {
        for (unsigned int i = 1; i <= 6; ++i) {
            int count = static_cast<int>(std::count(diceValues.begin(), diceValues.end(), i));
            if (count >= 5) {
                return 50;
            }
        }
        return 0;
    }

    std::string getName() const {
        return "Yahtzee";
    }

    short getId() const {
        return m_id;
    }

private:
    static const int m_id = ID;
};
