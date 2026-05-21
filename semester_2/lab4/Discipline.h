#ifndef DISCIPLINE_H
#define DISCIPLINE_H

#include <string>
#include <stdexcept>
#include "DegreeLevel.h"

class Discipline {
public:
    Discipline(const std::string& name, int credits, DegreeLevel level)
        : name(name), credits(credits), level(level) {
        if (name.empty()) {
            throw std::invalid_argument("Название дисциплины не может быть пустым.");
        }
        if (credits < 1) {
            throw std::invalid_argument("Количество зачётных единиц может быть в пределе от 2 до 6");
        }
    }

    std::string getName() const { return name; }
    int getCredits() const { return credits; }
    DegreeLevel getDegreeLevel() const { return level; }
    std::string getDegreeLevelString() const { return degreeLevelToString(level); }

private:
    std::string name;
    int credits;
    DegreeLevel level;
};

#endif // DISCIPLINE_H
