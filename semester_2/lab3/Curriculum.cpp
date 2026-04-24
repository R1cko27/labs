#include "Curriculum.h"

#include <stdexcept>
#include <iostream>
#include <regex>
#include <cctype>
#include <string>
#include <vector>
#include <sstream>

void checkNonNegative(int value, const std::string& fieldName) {
    if (value < 0) {
        throw std::invalid_argument(fieldName + " cannot be negative.");
    }
}

std::vector<std::string> Curriculum::validateInstance() const {
    std::vector<std::string> errors;
    
    std::regex codePattern(R"(^\d{2}\.\d{2}\.\d{2}$)");
    if (!std::regex_match(code, codePattern)) 
        errors.push_back("Недопустимый формат кода учебной программы. Ожидаемый шаблон: XX.XX.XX");

    if (title.empty()) errors.push_back("Название учебной программы не может быть пустым.");
    
    if (responsiblePerson.empty()) errors.push_back("ФИО ответственного не может быть пустым.");
    
    if (targetCredits < 0) errors.push_back("Зачетные единицы не могут быть отрицательными.");
    
    if (targetCredits == 0) errors.push_back("Целевое количество зачётных единиц не может быть нулевым.");
    
    if (targetCredits > 500) errors.push_back("Целевые зачётные единицы превышают разумный максимум (500).");
    
    return errors;
}

// Конструктор по умолчанию
Curriculum::Curriculum() 
    : code("00.00.00"),
      title("Новый учебный план"), 
      responsiblePerson("Не назначен"), 
      targetCredits(1), 
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
    auto errors = validateInstance();
    if (!errors.empty()) {
        std::ostringstream oss;
        oss << "Ошибки валидации:\n";
        for (size_t i = 0; i < errors.size(); ++i) {
            oss << (i + 1) << ". " << errors[i] << "\n";
        }
        throw std::invalid_argument(oss.str());
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
    std::regex codePattern(R"(^\d{2}\.\d{2}\.\d{2}$)");
    if (!std::regex_match(newCode, codePattern)) 
        throw std::invalid_argument("Недопустимый формат кода учебной программы. Ожидаемый шаблон: XX.XX.XX");
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
    if (newTarget < 0) throw std::invalid_argument("Зачетные единицы не могут быть отрицательными.");
    if (newTarget == 0) throw std::invalid_argument("Целевое количество зачётных единиц не может быть нулевым.");
    if (newTarget > 500) throw std::invalid_argument("Целевые зачётные единицы превышают разумный максимум (500).");
    
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
    if (count < 0) throw std::invalid_argument("Количество дисциплин не может быть отрицательным.");
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
    
    std::vector<std::string> errors;
    
    // Проверка соответствия кредитов
    if (totalDisciplineCredits != targetCredits) 
        errors.push_back("Сумма ЗЕ дисциплин (" + std::to_string(totalDisciplineCredits) + 
                        ") не равна целевым ЗЕ (" + std::to_string(targetCredits) + ")");
    
    if ((disciplineCount == 0 && totalDisciplineCredits != 0) || 
        (disciplineCount != 0 && totalDisciplineCredits == 0)) 
        errors.push_back("Количество дисциплин и суммарное количество ЗЕ должны быть равны 0 одновременно");
    
    if (targetCredits > 0 && disciplineCount == 0) errors.push_back("Нельзя активировать план без дисциплин");
    
    if (!errors.empty()) {
        std::cout << "\nОшибка активации учебного плана:\n";
        for (size_t i = 0; i < errors.size(); ++i) {
            std::cout << (i + 1) << ". " << errors[i] << std::endl;
        }
        return false;
    }
    
    currentState = State::ACTIVE;
    return true;
}