#include "Curriculum.h"
#include <stdexcept>
#include <iostream>
#include <regex>
#include <cctype>
#include <string>
#include <sstream>

bool isValidCodeFormat(const std::string& code) {
    std::regex format(R"(^(\d{1,2})\.(\d{1,2})\.(\d{1,2})$)");
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

bool isValidPersonName(const std::string& name) {
    if (name.empty() || name.length() > 29) return false;
    int dotCount = 0;
    for (char c : name) if (c == '.') dotCount++;
    
    return (dotCount == 1 || dotCount == 2);
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

    if (!isValidPersonName(responsiblePerson)) {
        errors[errorCount] = "ФИО ответственного должно быть в формате: Фамилия И. или Фамилия И.О.";
        errorCount++;
    }

    if ((targetCredits < 240 || targetCredits > 250) && targetCredits != 0) {
        errors[errorCount] = "Зачетные единицы могут быть в промежутке [240; 250]";
        errorCount++;
    }
}

// Конструктор по умолчанию
Curriculum::Curriculum()
    : code("00.00.00"),
      title("Новый учебный план"),
      responsiblePerson("Не назначен"),
      targetCredits(0),
      level(DegreeLevel::BACHELOR),
      disciplineCount(0),
      totalDisciplineCredits(0),
      currentState(State::EDITING)
{}

// Конструктор с параметрами
Curriculum::Curriculum(const std::string& code,
                       const std::string& title,
                       const std::string& responsiblePerson,
                       int targetCredits,
                       DegreeLevel level)
    : code(code), title(title), responsiblePerson(responsiblePerson),
      targetCredits(targetCredits), level(level),
      disciplineCount(0), totalDisciplineCredits(0), currentState(State::EDITING)
{
    std::string errors[4];
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

void Curriculum::validateState() const {
    if (currentState == State::ACTIVE) throw std::logic_error("Невозможно изменить учебную программу: она уже активна.");
}

std::string Curriculum::getCode() const { return code; }

void Curriculum::setCode(const std::string& newCode) {
    validateState();
    std::regex codePattern(R"(^\d{1,2}\.\d{1,2}\.\d{2,3}$)");
    if (!std::regex_match(newCode, codePattern))
        throw std::invalid_argument("Недопустимый формат кода учебной программы. Ожидаемый шаблон: XX.XX.XXX");
    code = newCode;
}

std::string Curriculum::getTitle() const { return title; }

void Curriculum::setTitle(const std::string& newTitle) {
    validateState();
    if (newTitle.empty()) throw std::invalid_argument("Название учебной программы не может быть пустым.");
    title = newTitle;
}

std::string Curriculum::getResponsiblePerson() const { return responsiblePerson; }

void Curriculum::setResponsiblePerson(const std::string& newPerson) {
    validateState();
    if (newPerson.empty())
        throw std::invalid_argument("ФИО ответственного не может быть пустым.");
    responsiblePerson = newPerson;
}

int Curriculum::getTargetCredits() const { return targetCredits; }

void Curriculum::setTargetCredits(int newTarget) {
    validateState();
    if (newTarget < 240 && newTarget != 0) throw std::invalid_argument("Зачетные единицы не могут быть меньше 240.");
    if (newTarget > 250) throw std::invalid_argument("Целевые зачётные единицы превышают 250.");

    targetCredits = newTarget;
}

Curriculum::DegreeLevel Curriculum::getDegreeLevel() const { return level; }

void Curriculum::setDegreeLevel(DegreeLevel newLevel) {
    validateState();
    level = newLevel;
}

std::string Curriculum::getDegreeLevelString() const {
    switch (level) {
        case DegreeLevel::BACHELOR: return "Бакалавр";
        case DegreeLevel::MASTER: return "Магистратура";
        case DegreeLevel::POSTGRADUATE: return "Аспирантура";
        default: return "Неизвестно";
    }
}

void Curriculum::setDisciplinesInfo(int count, int totalCredits) {
    validateState();
    if ((count < 0) && (count > 80)) throw std::invalid_argument("Количество дисциплин не может быть отрицательным и больше 80");
    if (totalCredits < 0) throw std::invalid_argument("Суммарное количество зачётных единиц не может быть отрицательным.");
    if ((count == 0 && totalCredits != 0) || (count != 0 && totalCredits == 0))
        throw std::invalid_argument("Количество дисциплин и суммарное количество зачётных единиц за них должны быть равны 0 одновременно.");
    disciplineCount = count;
    totalDisciplineCredits = totalCredits;
}

int Curriculum::getDisciplineCount() const { return disciplineCount; }

int Curriculum::getTotalDisciplineCredits() const { return totalDisciplineCredits; }

Curriculum::State Curriculum::getState() const { return currentState; }

std::string Curriculum::getStateString() const {
    return (currentState == State::EDITING) ? "Редактирование" : "Активен";
}

bool Curriculum::activate() {
    validateState();

    std::string errors[3];
    int errorCount = 0;

    if (totalDisciplineCredits != targetCredits) {
        errors[errorCount] = "Сумма ЗЕ дисциплин (" + std::to_string(totalDisciplineCredits) +
                             ") не равна целевым ЗЕ (" + std::to_string(targetCredits) + ")";
        errorCount++;
    }

    if ((disciplineCount == 0 && totalDisciplineCredits != 0) ||
        (disciplineCount != 0 && totalDisciplineCredits == 0)) {
        errors[errorCount] = "Количество дисциплин и суммарное количество ЗЕ должны быть равны 0 одновременно";
        errorCount++;
    }

    if (targetCredits > 0 && disciplineCount == 0) {
        errors[errorCount] = "Нельзя активировать план без дисциплин";
        errorCount++;
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