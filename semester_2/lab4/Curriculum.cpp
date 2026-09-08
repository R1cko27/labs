#include "Curriculum.h"
#include <stdexcept>
#include <iostream>
#include <regex>
#include <string>
#include <sstream>
<<<<<<< HEAD
#include <algorithm>
#include <iomanip>
=======
>>>>>>> 958e5f4cc1a1402d8ed9df90272f22de110ca885

bool isValidCodeFormat(const std::string& code) {
    std::regex format(R"(^([0-9]{1,2})\.([0-9]{1,2})\.([0-9]{1,2})$)");
    std::smatch match;

    if (!std::regex_match(code, match, format)) return false;

    int area = std::stoi(match[1].str());
    int group = std::stoi(match[2].str());
    int specialty = std::stoi(match[3].str());

<<<<<<< HEAD
    if (area < Curriculum::MIN_CODE_AREA || area > Curriculum::MAX_CODE_AREA) return false;
    if (group < Curriculum::MIN_CODE_GROUP || group > Curriculum::MAX_CODE_GROUP) return false;
    if (specialty < Curriculum::MIN_CODE_SPECIALTY || specialty > Curriculum::MAX_CODE_SPECIALTY) return false;
=======
    if (area < 1 || area > 40) return false;
    if (group < 1 || group > 9) return false;
    if (specialty < 1 || specialty > 9) return false;
>>>>>>> 958e5f4cc1a1402d8ed9df90272f22de110ca885

    return true;
}

bool isValidTitle(const std::string& title) {
<<<<<<< HEAD
    if (title.length() < Curriculum::MIN_TITLE_LENGTH || title.length() > Curriculum::MAX_TITLE_LENGTH) return false;
=======
    if (title.length() < 5 || title.length() > 100) return false;
>>>>>>> 958e5f4cc1a1402d8ed9df90272f22de110ca885
    for (char c : title) {
        if (c == '!' || c == '@' || c == '#' || c == '$' || c == '%' ||
            c == '^' || c == '&' || c == '*' || c == '+' || c == '=' ||
            c == '/' || c == '\\' || c == '|' || c == '?' || c == ';' ||
            c == ':' || c == '`' || c == '~') {
            return false;
        }
    }
    return true;
}

static std::string responsiblePersonToString(Curriculum::ResponsiblePerson person) {
    switch (person) {
        case Curriculum::ResponsiblePerson::TOMILOV_IN: return "Томилов И. Н.";
        case Curriculum::ResponsiblePerson::BAKAEV_MA: return "Бакаев М. А.";
        case Curriculum::ResponsiblePerson::PAVLOV_AV: return "Павлов А. В.";
        case Curriculum::ResponsiblePerson::GRIF_MG: return "Гриф М. Г.";
        case Curriculum::ResponsiblePerson::IVANOV_AV: return "Иванов А. В.";
        case Curriculum::ResponsiblePerson::GUZHOV_VI: return "Гужов В. И.";
        case Curriculum::ResponsiblePerson::TRUSHIN_VA: return "Трушин В. А.";
        case Curriculum::ResponsiblePerson::ROMANOV_EL: return "Романов Е. Л.";
        case Curriculum::ResponsiblePerson::HUDYAKOV_DS: return "Худяков Д. С.";
        case Curriculum::ResponsiblePerson::NOT_ASSIGNED: return "Не назначен";
        default: return "Не назначен";
    }
}

void Curriculum::validateSemester(int semester) const {
<<<<<<< HEAD
    if (semester < MIN_SEMESTER_COUNT || semester > semesterCount) {
=======
    if (semester < 1 || semester > semesterCount) {
>>>>>>> 958e5f4cc1a1402d8ed9df90272f22de110ca885
        throw std::out_of_range("Номер семестра находится вне диапазона.");
    }
}

void Curriculum::validateInstance(std::string errors[], int& errorCount) const {
    errorCount = 0;

    if (!isValidCodeFormat(code)) {
        errors[errorCount] = "Недопустимый формат кода учебной программы. Ожидаемый шаблон: XX.XX.XXX";
        errorCount++;
    }

    if (!isValidTitle(title)) {
        errors[errorCount] = "Название учебной программы должно содержать только русские буквы, "
<<<<<<< HEAD
                             "пробелы и знаки препинания (.,()\"-). Длина: от " + 
                             std::to_string(MIN_TITLE_LENGTH) + " до " + std::to_string(MAX_TITLE_LENGTH) + " символов.";
=======
                             "пробелы и знаки препинания (.,()\"-). Длина: от 5 до 100 символов.";
>>>>>>> 958e5f4cc1a1402d8ed9df90272f22de110ca885
        errorCount++;
    }

    if (responsiblePerson == ResponsiblePerson::NOT_ASSIGNED) {
        errors[errorCount] = "ФИО ответственного должно быть выбрано из допустимого списка.";
        errorCount++;
    }

<<<<<<< HEAD
    if ((targetCredits > MAX_TARGET_CREDITS) && targetCredits != 0) {
        errors[errorCount] = "Зачетные единицы могут быть в промежутке [" + 
                             std::to_string(MIN_TARGET_CREDITS) + "; " + std::to_string(MAX_TARGET_CREDITS) + "]";
        errorCount++;
    }

    if ((semesterCount < MIN_SEMESTER_COUNT) || (semesterCount > MAX_SEMESTER_COUNT)){
        errors[errorCount] = "Количество семестров должно быть от " + 
                             std::to_string(MIN_SEMESTER_COUNT) + " до " + std::to_string(MAX_SEMESTER_COUNT);
=======
    if ((targetCredits < 240 || targetCredits > 250) && targetCredits != 0) {
        errors[errorCount] = "Зачетные единицы могут быть в промежутке [240; 250]";
        errorCount++;
    }

    if ((semesterCount < 1) || (semesterCount > 10)){
        errors[errorCount] = "Количество семестров должно быть меньше 1 и больше 10";
>>>>>>> 958e5f4cc1a1402d8ed9df90272f22de110ca885
        errorCount++;
    }
}

Curriculum::Curriculum()
    : code("00.00.00"),
      title("Новый учебный план"),
      responsiblePerson(ResponsiblePerson::NOT_ASSIGNED),
      targetCredits(0),
      level(DegreeLevel::BACHELOR),
<<<<<<< HEAD
      semesterCount(MIN_SEMESTER_COUNT),
=======
      semesterCount(1),
>>>>>>> 958e5f4cc1a1402d8ed9df90272f22de110ca885
      semesters(semesterCount),
      currentState(State::EDITING)
{}

Curriculum::Curriculum(const std::string& code,
                       const std::string& title,
                       ResponsiblePerson responsiblePerson,
                       int targetCredits,
                       DegreeLevel level,
                       int semesterCount)
    : code(code), title(title), responsiblePerson(responsiblePerson),
      targetCredits(targetCredits), level(level),
      semesterCount(semesterCount), semesters(semesterCount), currentState(State::EDITING)
{
    std::string errors[5];
    int errorCount;
    validateInstance(errors, errorCount);

    if (errorCount > 0) {
        std::ostringstream oss;
        oss << "Ошибки валидации:\n";
        for (int i = 0; i < errorCount; ++i) {
            oss << (i + 1) << ". " << errors[i] << "\n";
        }
        throw std::invalid_argument(oss.str());
    }
}

Curriculum::Curriculum(const Curriculum& other)
    : code(other.code),
      title(other.title),
      responsiblePerson(other.responsiblePerson),
      targetCredits(other.targetCredits),
      level(other.level),
      semesterCount(other.semesterCount),
      semesters(other.semesters),
      currentState(other.currentState)
{
    std::cout << "Конструктор копирования вызван для: " << title << std::endl;
}

Curriculum::~Curriculum() {}

Curriculum& Curriculum::operator=(const Curriculum& other) {
    std::cout << "Оператор присваивания копированием вызван для: " << title
              << " (присваивается: " << other.title << ")" << std::endl;

    if (this != &other) {
        code = other.code;
        title = other.title;
        responsiblePerson = other.responsiblePerson;
        targetCredits = other.targetCredits;
        level = other.level;
        semesterCount = other.semesterCount;
        semesters = other.semesters;
        currentState = other.currentState;
    }
    return *this;
}

void Curriculum::print() const {
    std::cout << "\nШифр: " << code << std::endl;
    std::cout << "Название: " << title << std::endl;
    std::cout << "Ответственный: " << getResponsiblePerson() << std::endl;
    std::cout << "Целевое количество ЗЕ: " << targetCredits << std::endl;
    std::cout << "Ступень образования: " << getDegreeLevelString() << std::endl;
    std::cout << "Количество семестров: " << semesterCount << std::endl;
    std::cout << "Общее количество дисциплин: " << getDisciplineCount() << std::endl;
    std::cout << "Суммарное количество ЗЕ: " << getTotalDisciplineCredits() << std::endl;
    std::cout << "Состояние: " << getStateString() << std::endl;

    for (int i = 0; i < semesterCount; ++i) {
        std::cout << "  Семестр " << (i + 1) << ": "
                  << getDisciplineCountInSemester(i + 1)
                  << " дисциплин, "
                  << getTotalDisciplineCreditsInSemester(i + 1)
                  << " ЗЕ." << std::endl;
        for (const auto& pair : semesters[i]) {
            const Discipline& discipline = pair.second;
            std::cout << "    - " << discipline.getName()
                      << " (" << discipline.getCredits() << " ЗЕ, "
<<<<<<< HEAD
                      << discipline.getTotalHours() << " ч., "
                      << "Лек:" << discipline.getLectures()
                      << " Лаб:" << discipline.getLaboratories()
                      << " Пр:" << discipline.getPractices()
                      << " Инд:" << discipline.getIndividual()
                      << ", " << discipline.getAttestationString() << ")" << std::endl;
=======
                      << discipline.getDegreeLevelString() << ")" << std::endl;
>>>>>>> 958e5f4cc1a1402d8ed9df90272f22de110ca885
        }
    }
}

<<<<<<< HEAD
void Curriculum::printSemesterDetails(int semester) const {
    validateSemester(semester);
    
    const auto& semesterDisciplines = semesters[semester - 1];
    
    if (semesterDisciplines.empty()) {
        std::cout << "\nSemester " << semester << " does not contain disciplines." << std::endl;
        return;
    }
    
    std::vector<std::pair<std::string, Discipline>> sortedDisciplines(
        semesterDisciplines.begin(), semesterDisciplines.end()
    );
    
    std::sort(sortedDisciplines.begin(), sortedDisciplines.end(),
              [](const auto& a, const auto& b) {
                  return a.first < b.first;
              });
    
    std::cout << std::string(91, '=') << std::endl;
    std::cout << "Group: " << title << std::endl;
    std::cout << "Responsible Person: " << getResponsiblePerson() << std::endl;
    std::cout << "Semester: " << semester << "\n" << std::endl;
    
    std::cout << std::left;
    std::cout << std::setw(35) << "Discipline"
              << std::setw(6) << "CU"
              << std::setw(8) << "Hours"
              << std::setw(8) << "Lect"
              << std::setw(8) << "Lab"
              << std::setw(8) << "Prac"
              << std::setw(8) << "Ind"
              << std::setw(10) << "Attestation" << std::endl;
    std::cout << std::string(91, '-') << std::endl;
    
    int semesterTotalCredits = 0;
    
    for (const auto& [name, discipline] : sortedDisciplines) {
        int hoursBy36 = discipline.getCredits() * 36;
        semesterTotalCredits += discipline.getCredits();
        
        std::cout << std::setw(35) << discipline.getName()
                  << std::setw(6) << discipline.getCredits()
                  << std::setw(8) << hoursBy36
                  << std::setw(8) << discipline.getLectures()
                  << std::setw(8) << discipline.getLaboratories()
                  << std::setw(8) << discipline.getPractices()
                  << std::setw(8) << discipline.getIndividual()
                  << std::setw(10) << discipline.getAttestationString() << std::endl;
    }
    
    std::cout << std::string(91, '-') << "\n" << std::endl;
    std::cout << "Total for semester: " << semesterTotalCredits << " CU" << std::endl;
    std::cout << std::string(91, '=') << "\n" << std::endl;
}

=======
>>>>>>> 958e5f4cc1a1402d8ed9df90272f22de110ca885
void Curriculum::validateState() const {
    if (currentState == State::ACTIVE) {
        throw std::logic_error("Невозможно изменить учебную программу: она уже активна.");
    }
}

std::string Curriculum::getCode() const { return code; }

void Curriculum::setCode(const std::string& newCode) {
    validateState();
    std::regex codePattern(R"(^\d{1,2}\.\d{1,2}\.\d{2,3}$)");
    if (!std::regex_match(newCode, codePattern)) {
        throw std::invalid_argument("Недопустимый формат кода учебной программы. Ожидаемый шаблон: XX.XX.XXX");
    }
    code = newCode;
}

std::string Curriculum::getTitle() const { return title; }

void Curriculum::setTitle(const std::string& newTitle) {
    validateState();
<<<<<<< HEAD
    if (!isValidTitle(newTitle)) {
        throw std::invalid_argument("Название учебной программы должно содержать только русские буквы, "
                                    "пробелы и знаки препинания (.,()\"-). Длина: от " + 
                                    std::to_string(MIN_TITLE_LENGTH) + " до " + std::to_string(MAX_TITLE_LENGTH) + " символов.");
=======
    if (newTitle.empty()) {
        throw std::invalid_argument("Название учебной программы не может быть пустым.");
>>>>>>> 958e5f4cc1a1402d8ed9df90272f22de110ca885
    }
    title = newTitle;
}

std::string Curriculum::getResponsiblePerson() const {
    return responsiblePersonToString(responsiblePerson);
}

void Curriculum::setResponsiblePerson(ResponsiblePerson newPerson) {
    validateState();
    responsiblePerson = newPerson;
}

int Curriculum::getTargetCredits() const { return targetCredits; }

void Curriculum::setTargetCredits(int newTarget) {
    validateState();
<<<<<<< HEAD
    if (newTarget < MIN_TARGET_CREDITS && newTarget != 0) {
        throw std::invalid_argument("Зачетные единицы не могут быть меньше " + std::to_string(MIN_TARGET_CREDITS) + ".");
    }
    if (newTarget > MAX_TARGET_CREDITS) {
        throw std::invalid_argument("Целевые зачётные единицы превышают " + std::to_string(MAX_TARGET_CREDITS) + ".");
=======
    if (newTarget < 240 && newTarget != 0) {
        throw std::invalid_argument("Зачетные единицы не могут быть меньше 240.");
    }
    if (newTarget > 250) {
        throw std::invalid_argument("Целевые зачётные единицы превышают 250.");
>>>>>>> 958e5f4cc1a1402d8ed9df90272f22de110ca885
    }
    targetCredits = newTarget;
}

Curriculum::DegreeLevel Curriculum::getDegreeLevel() const { return level; }

void Curriculum::setDegreeLevel(DegreeLevel newLevel) {
    validateState();
    level = newLevel;
}

std::string Curriculum::getDegreeLevelString() const {
    return degreeLevelToString(level);
}

int Curriculum::getSemesterCount() const { return semesterCount; }

void Curriculum::setSemesterCount(int newCount) {
    validateState();
<<<<<<< HEAD
    if (newCount < MIN_SEMESTER_COUNT) {
        throw std::invalid_argument("Количество семестров должно быть не менее " + std::to_string(MIN_SEMESTER_COUNT) + ".");
    }
    if (newCount > MAX_SEMESTER_COUNT) {
        throw std::invalid_argument("Количество семестров не может превышать " + std::to_string(MAX_SEMESTER_COUNT) + ".");
=======
    if (newCount < 1) {
        throw std::invalid_argument("Количество семестров должно быть не менее 1.");
>>>>>>> 958e5f4cc1a1402d8ed9df90272f22de110ca885
    }
    if (newCount < semesterCount) {
        for (int semester = newCount + 1; semester <= semesterCount; ++semester) {
            if (!semesters[semester - 1].empty()) {
                throw std::invalid_argument("Невозможно уменьшить количество семестров: в удаляемых семестрах есть дисциплины.");
            }
        }
    }
    semesters.resize(newCount);
    semesterCount = newCount;
}

<<<<<<< HEAD
=======
// Основной метод добавления дисциплины (с исключениями)
>>>>>>> 958e5f4cc1a1402d8ed9df90272f22de110ca885
void Curriculum::addDiscipline(int semester, const Discipline& discipline) {
    validateState();
    validateSemester(semester);
    
<<<<<<< HEAD
=======
    if (discipline.getDegreeLevel() != level) {
        throw std::invalid_argument("Дисциплина должна соответствовать ступени образования учебного плана.");
    }
    
>>>>>>> 958e5f4cc1a1402d8ed9df90272f22de110ca885
    auto& semesterDisciplines = semesters[semester - 1];
    if (semesterDisciplines.find(discipline.getName()) != semesterDisciplines.end()) {
        throw std::invalid_argument("Дисциплина с таким названием уже существует в этом семестре.");
    }
    
    semesterDisciplines.emplace(discipline.getName(), discipline);
}

<<<<<<< HEAD
=======
// Безопасная версия добавления дисциплины
bool Curriculum::safeAddDiscipline(int semester, const Discipline& discipline, std::string& errorMessage) {
    try {
        addDiscipline(semester, discipline);
        errorMessage.clear();
        return true;
    } catch (const std::exception& e) {
        errorMessage = e.what();
        return false;
    }
}

// Основной метод удаления дисциплины (с исключениями)
>>>>>>> 958e5f4cc1a1402d8ed9df90272f22de110ca885
void Curriculum::removeDiscipline(int semester, const std::string& disciplineName) {
    validateState();
    validateSemester(semester);
    
    auto& semesterDisciplines = semesters[semester - 1];
    auto it = semesterDisciplines.find(disciplineName);
    if (it == semesterDisciplines.end()) {
        throw std::invalid_argument("Дисциплина не найдена в указанном семестре.");
    }
    semesterDisciplines.erase(it);
}

<<<<<<< HEAD
=======
// Безопасная версия удаления дисциплины
bool Curriculum::safeRemoveDiscipline(int semester, const std::string& disciplineName, std::string& errorMessage) {
    try {
        removeDiscipline(semester, disciplineName);
        errorMessage.clear();
        return true;
    } catch (const std::exception& e) {
        errorMessage = e.what();
        return false;
    }
}

// Безопасная версия установки количества семестров
bool Curriculum::safeSetSemesterCount(int newCount, std::string& errorMessage) {
    try {
        setSemesterCount(newCount);
        errorMessage.clear();
        return true;
    } catch (const std::exception& e) {
        errorMessage = e.what();
        return false;
    }
}

>>>>>>> 958e5f4cc1a1402d8ed9df90272f22de110ca885
int Curriculum::getDisciplineCountInSemester(int semester) const {
    validateSemester(semester);
    return static_cast<int>(semesters[semester - 1].size());
}

int Curriculum::getTotalDisciplineCreditsInSemester(int semester) const {
    validateSemester(semester);
    int total = 0;
    for (const auto& pair : semesters[semester - 1]) {
        total += pair.second.getCredits();
    }
    return total;
}

int Curriculum::getDisciplineCount() const {
    int count = 0;
    for (const auto& semester : semesters) {
        count += static_cast<int>(semester.size());
    }
    return count;
}

int Curriculum::getTotalDisciplineCredits() const {
    int total = 0;
    for (const auto& semester : semesters) {
        for (const auto& pair : semester) {
            total += pair.second.getCredits();
        }
    }
    return total;
}

Curriculum::State Curriculum::getState() const { return currentState; }

std::string Curriculum::getStateString() const {
    return (currentState == State::EDITING) ? "Редактирование" : "Активен";
}

bool Curriculum::activate() {
    validateState();

    std::string errors[5];
    int errorCount = 0;

    if (getDisciplineCount() == 0) {
        errors[errorCount] = "Нельзя активировать план без дисциплин.";
        errorCount++;
    }

    if (targetCredits == 0 && getDisciplineCount() > 0) {
        errors[errorCount] = "Целевые зачётные единицы должны быть заданы для плана с дисциплинами.";
        errorCount++;
    }

    if (targetCredits > 0 && getTotalDisciplineCredits() != targetCredits) {
        errors[errorCount] = "Сумма ЗЕ дисциплин (" + std::to_string(getTotalDisciplineCredits()) +
                             ") не равна целевым ЗЕ (" + std::to_string(targetCredits) + ")";
        errorCount++;
    }

<<<<<<< HEAD
    for (int semester = MIN_SEMESTER_COUNT; semester <= semesterCount; ++semester) {
=======
    for (int semester = 1; semester <= semesterCount; ++semester) {
>>>>>>> 958e5f4cc1a1402d8ed9df90272f22de110ca885
        if (getDisciplineCountInSemester(semester) == 0) {
            errors[errorCount] = "Учебный план нельзя подписать: семестр " + std::to_string(semester) + " пуст.";
            errorCount++;
        }
    }

    if (errorCount > 0) {
        std::cout << "\nОшибка активации учебного плана:\n";
        for (int i = 0; i < errorCount; ++i) {
            std::cout << (i + 1) << ". " << errors[i] << std::endl;
        }
        return false;
    }

    currentState = State::ACTIVE;
    return true;
<<<<<<< HEAD
=======
}

// Безопасная версия активации
bool Curriculum::safeActivate(std::string& errorMessage) {
    try {
        if (activate()) {
            errorMessage.clear();
            return true;
        } else {
            errorMessage = "Активация не удалась. Проверьте консоль для деталей.";
            return false;
        }
    } catch (const std::exception& e) {
        errorMessage = e.what();
        return false;
    }
>>>>>>> 958e5f4cc1a1402d8ed9df90272f22de110ca885
}