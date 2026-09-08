#ifndef DEGREE_LEVEL_H
#define DEGREE_LEVEL_H

#include <string>

enum class DegreeLevel {
<<<<<<< HEAD
    BACHELOR,       ///< Бакалавр
    MASTER,         ///< Магистратура
    POSTGRADUATE    ///< Аспирантура
=======
    BACHELOR,
    MASTER,
    POSTGRADUATE
>>>>>>> 958e5f4cc1a1402d8ed9df90272f22de110ca885
};

inline std::string degreeLevelToString(DegreeLevel level) {
    switch (level) {
        case DegreeLevel::BACHELOR: return "Бакалавр";
        case DegreeLevel::MASTER: return "Магистратура";
        case DegreeLevel::POSTGRADUATE: return "Аспирантура";
        default: return "Неизвестно";
    }
}

<<<<<<< HEAD
#endif // DEGREE_LEVEL_H
=======
#endif // DEGREE_LEVEL_H
>>>>>>> 958e5f4cc1a1402d8ed9df90272f22de110ca885
