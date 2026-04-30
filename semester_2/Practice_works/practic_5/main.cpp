#include "study_group.h"

#include <exception>
#include <iostream>

int main() {
    try {
        StudentGroup group1;
        StudentGroup group2("AP-526", StudyDirection::PI, 2025, EducationLevel::Bachelor);
        StudentGroup group3("AB-420", StudyDirection::IS, 2024, EducationLevel::Bachelor);

        group1.print();
        group2.print();
        group3.print();

        StudentGroup group4(group2); // group4 - копия group2
        group4.print();

        group2.rename("AP-527");
        group2.print();

        // Динамическая память
        StudentGroup* dynamicA = createGroup("AI-226", StudyDirection::AI, 2022, EducationLevel::Bachelor);
        StudentGroup* dynamicB = createGroup("VT-525", StudyDirection::VT, 2025, EducationLevel::Master);

        if (dynamicA != nullptr) dynamicA->print();
        else std::cout << "Объект A не создан\n";
        
        if (dynamicB != nullptr) dynamicB->print();
        else std::cout << "Объект B не создан\n";

        delete dynamicA;
        delete dynamicB;
        
    } catch (const std::exception& ex) {
        std::cout << "Неизвестная ошибка: " << ex.what() << '\n';
        return 1;
    }

    return 0;
}