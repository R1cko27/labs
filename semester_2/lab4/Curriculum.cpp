#include "Curriculum.h"
#include <stdexcept>
#include <iostream>
#include <regex>
#include <string>
#include <sstream>

bool isValidCodeFormat(const std::string& code) {
    std::regex format(R"(^([0-9]{1,2})\.([0-9]{1,2})\.([0-9]{1,2})$)");
    std::smatch match;

    if (!std::regex_match(code, match, format)) return false;

    int area = std::stoi(match[1].str());
    int group = std::stoi(match[2].str());
    int specialty = std::stoi(match[3].str());

    if (area < 1 || area > 40) return false;
    if (group < 1 || group > 9) return false;
    if (specialty < 1 || specialty > 9) return false;

    return true;
}

bool isValidTitle(const std::string& title) {
    if (title.length() < 5 || title.length() > 100) return false;
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
    if (semester < 1 || semester > semesterCount) {
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
                             "пробелы и знаки препинания (.,()\"-). Длина: от 5 до 100 символов.";
        errorCount++;
    }

    if (responsiblePerson == ResponsiblePerson::NOT_ASSIGNED) {
        errors[errorCount] = "ФИО ответственного должно быть выбрано из допустимого списка.";
        errorCount++;
    }

    if ((targetCredits < 240 || targetCredits > 250) && targetCredits != 0) {
        errors[errorCount] = "Зачетные единицы могут быть в промежутке [240; 250]";
        errorCount++;
    }

    if ((semesterCount < 1) || (semesterCount > 10)){
        errors[errorCount] = "Количество семестров должно быть меньше 1 и больше 10";
        errorCount++;
    }
}

Curriculum::Curriculum()
    : code("00.00.00"),
      title("Новый учебный план"),
      responsiblePerson(ResponsiblePerson::NOT_ASSIGNED),
      targetCredits(0),
      level(DegreeLevel::BACHELOR),
      semesterCount(1),
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
                      << discipline.getDegreeLevelString() << ")" << std::endl;
        }
    }
}

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
    if (newTitle.empty()) {
        throw std::invalid_argument("Название учебной программы не может быть пустым.");
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
    if (newTarget < 240 && newTarget != 0) {
        throw std::invalid_argument("Зачетные единицы не могут быть меньше 240.");
    }
    if (newTarget > 250) {
        throw std::invalid_argument("Целевые зачётные единицы превышают 250.");
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
    if (newCount < 1) {
        throw std::invalid_argument("Количество семестров должно быть не менее 1.");
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

// Основной метод добавления дисциплины (с исключениями)
void Curriculum::addDiscipline(int semester, const Discipline& discipline) {
    validateState();
    validateSemester(semester);
    
    if (discipline.getDegreeLevel() != level) {
        throw std::invalid_argument("Дисциплина должна соответствовать ступени образования учебного плана.");
    }
    
    auto& semesterDisciplines = semesters[semester - 1];
    if (semesterDisciplines.find(discipline.getName()) != semesterDisciplines.end()) {
        throw std::invalid_argument("Дисциплина с таким названием уже существует в этом семестре.");
    }
    
    semesterDisciplines.emplace(discipline.getName(), discipline);
}

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

    for (int semester = 1; semester <= semesterCount; ++semester) {
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
}