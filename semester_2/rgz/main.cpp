#include <iostream>
#include <list>
#include <string>
#include <iomanip>
#include <limits>
#include <memory>
#include "OfficeEquipment.h"
#include "Printer.h"
#include "Fax.h"

#define STAGE_4

int main() {
    
        Printer printer1{"LaserJet Pro", "HP", 2022, 299.99, PrinterColorType::Color, true, PaperFormat::A4, Interface::WiFi, ApplicationArea::Office, 35, 1200, "Toner"};
        Printer printer2{};
        Fax fax1{"SuperG3", "Brother", 2021, 199.50, 14400, 600, 150, true, AutoFeederType::SingleSided, Interface::RJ11, ApplicationArea::Office};
        Fax fax2{};

    #ifdef STAGE_1
        std::cout << printer1 << "\n\n";
        std::cout << printer2 << "\n\n";
        std::cout << fax1 << "\n\n";
        std::cout << fax2 << "\n\n";
        
        printer1.setPrintSpeedPPM(40);
        printer2.setPrice(249.99);
        fax1.setMemoryCapacityPages(200);
        fax2.setTransmissionSpeedBPS(33600);
        
        std::cout << "\n=== ПОСЛЕ МОДИФИКАЦИИ ===\n";
        std::cout << printer1 << "\n\n";
        std::cout << printer2 << "\n\n";
        std::cout << fax1 << "\n\n";
        std::cout << fax2 << "\n\n";
    #endif
    #ifdef STAGE_2
        // ПУНКТ 2.4
        OfficeEquipment basic1("BasicDevice", "Generic", 2020, 99.99);
        OfficeEquipment basic2("OfficeMate", "Standard", 2023, 149.95);
        
        std::cout << basic1 << "\n\n";
        std::cout << basic2 << "\n\n";
        
        OfficeEquipment* basePtr = &printer1;
        OfficeEquipment& baseRef = fax1;
        
        std::cout << basePtr->toString() << "\n\n";
        std::cout << baseRef.toString() << "\n\n";
        
        OfficeEquipment* basePtr2 = &basic1;
        std::cout << basePtr2->toString() << "\n\n";
    #endif
    #ifdef STAGE_4 // Скорректированный пункт 3.3 (ВЕРСИЯ C++14)
        std::list<std::unique_ptr<OfficeEquipment>> equipmentList;
        int choice;
        system("cls");
        do {
            std::cout << "\n=== МЕНЮ ===\n";
            std::cout << "1. Добавить оборудование\n";
            std::cout << "2. Добавить принтер\n";
            std::cout << "3. Добавить факс\n";
            std::cout << "4. Показать список\n";
            std::cout << "5. Выход\n";
            std::cout << "\nВыбор: ";
            std::cin >> choice;
            
            std::string model, manufacturer, consumable;
            int year, speedPPM, resolutionDPI, transmissionSpeed, scanResolution, memoryPages;
            double price;
            int colorChoice, paperChoice, interfaceChoice, areaChoice, autoFeederChoice, duplexChoice;
            bool autoFeeder;
            
            switch(choice) {
                case 1: {
                    std::cout << "Модель: "; std::cin >> model;
                    std::cout << "Производитель: "; std::cin >> manufacturer;
                    std::cout << "Год выпуска: "; std::cin >> year;
                    std::cout << "Цена: "; std::cin >> price;
                    equipmentList.push_back(std::make_unique<OfficeEquipment>(model, manufacturer, year, price));
                    system("cls");
                    std::cout << "Оборудование \"" << model << "\" успешно добавлено!\n";
                    break;
                }
                    
                case 2: {
                    std::cout << "Модель: "; std::cin >> model;
                    std::cout << "Производитель: "; std::cin >> manufacturer;
                    std::cout << "Год выпуска: "; std::cin >> year;
                    std::cout << "Цена: "; std::cin >> price;
                    
                    std::cout << "Тип печати (0 - черно-белый, 1 - цветной): "; 
                    std::cin >> colorChoice;
                    PrinterColorType colorType = (colorChoice == 1) ? PrinterColorType::Color : PrinterColorType::BlackWhite;
                    
                    std::cout << "Двусторонняя печать (0 - нет, 1 - да): "; 
                    std::cin >> duplexChoice;
                    bool duplexPrint = (duplexChoice == 1);
                    
                    std::cout << "Максимальный формат (0 - A2, 1 - A3, 2 - A4, 3 - A5): "; 
                    std::cin >> paperChoice;
                    PaperFormat maxPaperFormat = static_cast<PaperFormat>(paperChoice);
                    
                    std::cout << "Интерфейс (0 - Bluetooth, 1 - Ethernet, 2 - NFC, 3 - RJ-11, 4 - USB, 5 - USB Type-B, 6 - USB хост, 7 - Wi-Fi): "; 
                    std::cin >> interfaceChoice;
                    Interface interfaces = static_cast<Interface>(interfaceChoice);
                    
                    std::cout << "Область применения (0 - для дома, 1 - для офиса): "; 
                    std::cin >> areaChoice;
                    ApplicationArea applicationArea = static_cast<ApplicationArea>(areaChoice);
                    
                    std::cout << "Скорость печати (стр/мин): "; std::cin >> speedPPM;
                    std::cout << "Разрешение печати (DPI): "; std::cin >> resolutionDPI;
                    std::cout << "Тип расходников: "; std::cin >> consumable;
                    
                    equipmentList.push_back(std::make_unique<Printer>(model, manufacturer, year, price,
                                                        colorType, duplexPrint, maxPaperFormat,
                                                        interfaces, applicationArea,
                                                        speedPPM, resolutionDPI, consumable));
                    system("cls");
                    std::cout << "Принтер \"" << model << "\" успешно добавлен!\n";
                    break;
                }
                
                case 3: {
                    std::cout << "Модель: "; std::cin >> model;
                    std::cout << "Производитель: "; std::cin >> manufacturer;
                    std::cout << "Год выпуска: "; std::cin >> year;
                    std::cout << "Цена: "; std::cin >> price;
                    std::cout << "Скорость передачи (бит/с): "; std::cin >> transmissionSpeed;
                    std::cout << "Разрешение сканирования (DPI): "; std::cin >> scanResolution;
                    std::cout << "Объем памяти (страниц): "; std::cin >> memoryPages;
                    std::cout << "Наличие автоподатчика (0 - нет, 1 - да): "; std::cin >> autoFeeder;
                    
                    std::cout << "Тип автоподатчика (0 - двусторонний, 1 - односторонний, 2 - нет): "; 
                    std::cin >> autoFeederChoice;
                    AutoFeederType autoFeederType = static_cast<AutoFeederType>(autoFeederChoice);
                    
                    std::cout << "Интерфейс (0 - Bluetooth, 1 - Ethernet, 2 - NFC, 3 - RJ-11, 4 - USB, 5 - USB Type-B, 6 - USB хост, 7 - Wi-Fi): "; 
                    std::cin >> interfaceChoice;
                    Interface interfaces = static_cast<Interface>(interfaceChoice);
                    
                    std::cout << "Область применения (0 - для дома, 1 - для офиса): "; 
                    std::cin >> areaChoice;
                    ApplicationArea applicationArea = static_cast<ApplicationArea>(areaChoice);
                    
                    equipmentList.push_back(std::make_unique<Fax>(model, manufacturer, year, price,
                                                    transmissionSpeed, scanResolution, memoryPages, autoFeeder,
                                                    autoFeederType, interfaces, applicationArea));
                    system("cls");
                    std::cout << "Факс \"" << model << "\" успешно добавлен!\n";
                    break;
                }
                
                case 4:
                    system("cls");
                    std::cout << "\n=== СПИСОК ОБОРУДОВАНИЯ ===\n";
                    for (const auto& item : equipmentList) {
                        std::cout << item->toString() << "\n\n";
                    }
                    break;
                    
                case 5:
                    system("cls");
                    equipmentList.clear();
                    std::cout << "Программа завершена, память очищена автоматически\n";
                    break;
            }
        } while (choice != 5);
    #endif
    return 0;
}