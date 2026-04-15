#include "Curriculum.h"
#include <stdexcept>
#include <iostream>
#include <regex>
#include <cctype>

void checkNonNegative(int value, const std::string& fieldName) {
    if (value < 0) {
        throw std::invalid_argument(fieldName + " cannot be negative.");
    }
}

Curriculum::Curriculum(const std::string& code, 
                       const std::string& title, 
                       const std::string& responsiblePerson, 
                       int targetCredits, 
                       DegreeLevel level)
    : code(code), title(title), responsiblePerson(responsiblePerson), 
      targetCredits(targetCredits), level(level), 
      disciplineCount(0), totalDisciplineCredits(0), currentState(State::EDITING) 
{
    // Проверка шифра
    std::regex codePattern(R"(^\d{1,2}\.\d{1,2}\.\d{2,3}$)");
    if (!std::regex_match(code, codePattern)) {
        throw std::invalid_argument(
            "Недопустимый формат кода учебной программы. Ожидаемый шаблон: XX.XX.XXX\n");
    }

    // Проверка названия
    if (title.empty()) {
        throw std::invalid_argument("Название учебной программы не может быть пустым.");
    }

    // Проверка целевого количества зачётных единиц
    if (targetCredits < 0) {
        throw std::invalid_argument("Зачетные еденицы не могут быть отрицательными.");
    }
    
    // Проверка на нулевое значение
    if (targetCredits == 0) {
        throw std::invalid_argument("Целевое количество зачётных единиц не может быть нулевым. ");
    }

    // Проверка на разумный максимум
    if (targetCredits > 500) {
        throw std::invalid_argument("Целевые зачётные единицы превышают разумный максимум (500).");
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
    if (newCode.empty()) throw std::invalid_argument("Код не может быть пустым.");
    code = newCode;
}

std::string Curriculum::getTitle() const { return title; }
void Curriculum::setTitle(const std::string& newTitle) {
    validateState();
    if (newTitle.empty()) throw std::invalid_argument("Название не может быть пустым.");
    title = newTitle;
}

std::string Curriculum::getResponsiblePerson() const { return responsiblePerson; }
void Curriculum::setResponsiblePerson(const std::string& newPerson) {
    validateState();
    if (newPerson.empty()) throw std::invalid_argument("ФИО ответственного не может быть пустым.");
    responsiblePerson = newPerson;
}

int Curriculum::getTargetCredits() const { return targetCredits; }
void Curriculum::setTargetCredits(int newTarget) {
    validateState();
    checkNonNegative(newTarget, "Target credits");
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
    checkNonNegative(count, "Количество дисциплин");
    checkNonNegative(totalCredits, "Суммарное количество зачётных единиц");
    
    // "Количество дисциплин и суммарное количество зачётных единиц за них могут быть равны 0 только одновременно."
    if ((count == 0 && totalCredits != 0) || (count != 0 && totalCredits == 0)) {
        throw std::invalid_argument("Количество дисциплин и суммарное количество зачётных единиц за них должны быть равны 0 одновременно.");
    }
    
    disciplineCount = count;
    totalDisciplineCredits = totalCredits;
}

int Curriculum::getDisciplineCount() const { return disciplineCount; }
int Curriculum::getTotalDisciplineCredits() const { return totalDisciplineCredits; }

Curriculum::State Curriculum::getState() const { return currentState; }
std::string Curriculum::getStateString() const {
    return (currentState == State::EDITING) ? "Редактирование" : "Активен";
}

// Ввести план в действие
bool Curriculum::activate() {
    if (currentState == State::ACTIVE) return true;

    if (code.empty() || title.empty() || responsiblePerson.empty()) return false;

    if (totalDisciplineCredits != targetCredits) return false;
    
    currentState = State::ACTIVE;
    return true;
}