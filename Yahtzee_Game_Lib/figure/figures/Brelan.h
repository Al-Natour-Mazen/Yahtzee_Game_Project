#pragma once
#include "Figure.h"

template<short ID>
class Brelan : public Figure {
public:
    int calculateScore(const std::vector<int>& diceValues) {
        for (unsigned short i = 1; i <= 6; ++i) {
            int count = static_cast<int>(std::count(diceValues.begin(), diceValues.end(), i));
            if (count >= 3) {
                m_value = i;
                return 3 * i;
            }
        }
        return 0;
    }

    std::string getName() const {
        if (m_value == 0) {
            return "Brelan";
        }
        return "Brelan de " + std::to_string(m_value);
    }

    short getId() const {
        return ID;
    }

    void serialize(std::ostream& out) const {
        out << "id: " << ID << "\n";
    }

private:
    short m_value = 0;
};
