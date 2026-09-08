#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "Curriculum.h"


Curriculum testfunc(Curriculum c) {
    std::cout << "Вызвана фунция testfunc" << std::endl;
    Curriculum plan("10.03.01", "Информационная безопасность", Curriculum::ResponsiblePerson::TOMILOV_IN, 240, Curriculum::DegreeLevel::BACHELOR);
    return plan;
}


int main() {
    try {
<<<<<<< HEAD
        Curriculum invalidPlan("недействительная_группа", "", Curriculum::ResponsiblePerson::TOMILOV_IN, -1, Curriculum::DegreeLevel::BACHELOR);
=======
        Curriculum invalidPlan("недействительная_группа", "", "Панфилов А.П..", -1, Curriculum::DegreeLevel::BACHELOR);
>>>>>>> 958e5f4cc1a1402d8ed9df90272f22de110ca885
    } catch (const std::invalid_argument& e) {
        std::cout << "Перехваченное исключение:\n" << e.what() << std::endl;
    }
    try {
        Curriculum plan0;
        plan0.print();

<<<<<<< HEAD
        Curriculum plan("10.03.01", "Информационная безопасность", Curriculum::ResponsiblePerson::TOMILOV_IN, 240, Curriculum::DegreeLevel::BACHELOR);
        plan.print();
=======
        Curriculum plan("10.03.01", "Информационная безопасность", "Панфилов А.П.", 240, Curriculum::DegreeLevel::BACHELOR);
        printCurriculumInfo(plan);
>>>>>>> 958e5f4cc1a1402d8ed9df90272f22de110ca885

        plan.setCode("2.22.02");
        plan.setTitle("Сварочное производство");
        plan.setResponsiblePerson(Curriculum::ResponsiblePerson::PAVLOV_AV);
        plan.setDisciplinesInfo(50, 240);

        if (plan.activate()) {
            std::cout << "\nПлан активирован\n" << std::endl;
        } else {
            std::cout << "\nОшибка активации\n" << std::endl;
        }

        plan.print();

<<<<<<< HEAD
        Curriculum plan2("09.03.03", "Прикладная информатика", Curriculum::ResponsiblePerson::IVANOV_AV, 245, Curriculum::DegreeLevel::MASTER);
=======
        Curriculum plan2("09.03.03", "Прикладная информатика", "Имнакулов С.А.", 245, Curriculum::DegreeLevel::MASTER);
>>>>>>> 958e5f4cc1a1402d8ed9df90272f22de110ca885
        plan2.activate();

        // Проверка правила "могут быть равны 0 только одновременно"
        try {
            plan2.setDisciplinesInfo(0, 245);
        } catch (const std::invalid_argument& e) {
            std::cout << "\nПерехваченное исключение при установки дисциплин: " << e.what() << std::endl;
        }   

        plan2.setDisciplinesInfo(30, 245);
        plan2.activate();

        Curriculum* plan3 = new Curriculum("09.03.03", "Прикладная информатика", Curriculum::ResponsiblePerson::IVANOV_AV, 245, Curriculum::DegreeLevel::MASTER);
        plan3->setDisciplinesInfo(30, 245);
        plan3->print();

        std::cout << "\nСтатистический массив\n" << std::endl;
        Curriculum arr[3];
        for (int i = 0; i < 3; ++i) {
            arr[i].print();
        }
        
        std::cout << "\nДинамический массив\n" << std::endl;
        Curriculum* curriculumArray = new Curriculum[3];
        
        for (int i = 0; i < 3; ++i) {
            curriculumArray[i].print();
        }
        
        std::cout << "\nСтатистический массив указателей\n" << std::endl;

        Curriculum* ptrArr[3];  
        for(int i = 0; i < 3; ++i) {
            ptrArr[i] = new Curriculum();
            ptrArr[i]->print();
        }
        for(int i = 0; i < 3; ++i) {
            delete ptrArr[i];
        }


            Curriculum temp("09.03.03", "Прикладная информатика", 
                                                Curriculum::ResponsiblePerson::IVANOV_AV, 245, 
                                                Curriculum::DegreeLevel::MASTER);
            Curriculum result = testfunc(temp); 

            Curriculum main = temp;  // Конструктор копирования
            main.print();

    } catch (const std::exception& e) {
        std::cerr << "Непредвиденная ошибка:\n" << e.what() << std::endl;
        return 1;
    }

    return 0;
}