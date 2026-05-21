#ifndef DEGREE_LEVEL_H
#define DEGREE_LEVEL_H

#include <string>

enum class DegreeLevel {
    BACHELOR,
    MASTER,
    POSTGRADUATE
};

inline std::string degreeLevelToString(DegreeLevel level) {
    switch (level) {
        case DegreeLevel::BACHELOR: return "Бакалавр";
        case DegreeLevel::MASTER: return "Магистратура";
        case DegreeLevel::POSTGRADUATE: return "Аспирантура";
        default: return "Неизвестно";
    }
}

#endif // DEGREE_LEVEL_H
