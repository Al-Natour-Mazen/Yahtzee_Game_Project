#pragma once
#include "Figure.h"

template<short ID>
class Carre : public Figure {
public:
    int calculateScore(const std::vector<int>& diceValues) {
        for (unsigned short i = 1; i <= 6; ++i) {
            int count = static_cast<int>(std::count(diceValues.begin(), diceValues.end(), i));
            if (count >= 4) {
                m_value = i;
                return count * i;
            }
        }
        return 0;
    }

    std::string getName() const {
        return "Carr� de " + std::to_string(m_value);
    }

    short getId() const {
        return m_id;
    }

private:
    static const short m_id = ID;
    short m_value = 0;
};


