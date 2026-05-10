#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include <limits>
#include <memory>

#include "OfficeEquipment.h"
#include "Printer.h"
#include "Fax.h"
#include "input_valid.h"

#define STAGE_1


void clearEquipmentList(std::list<OfficeEquipment*>& equipmentList) {
    for (auto* item : equipmentList) {
        delete item;
    }
    equipmentList.clear();
}

void displayEquipmentList(std::list<OfficeEquipment*>& equipmentList) {
    //system("cls");
    std::cout << "\n=== СПИСОК ОБОРУДОВАНИЯ ===\n";
    
    if (equipmentList.empty()) {
        std::cout << "Список пуст!\n";
        return;
    }
    
    std::vector<OfficeEquipment*> baseItems;
    std::vector<OfficeEquipment*> printerItems;
    std::vector<OfficeEquipment*> faxItems;

    for (auto* item : equipmentList) {
        if (dynamic_cast<Printer*>(item)) {
            printerItems.push_back(item);
        } else if (dynamic_cast<Fax*>(item)) {
            faxItems.push_back(item);
        } else {
            baseItems.push_back(item);
        }
    }

    auto cmpPrice = [](const OfficeEquipment* a, const OfficeEquipment* b) {
        return a->getPrice() < b->getPrice();
    };

    std::sort(baseItems.begin(), baseItems.end(), cmpPrice);
    std::sort(printerItems.begin(), printerItems.end(), cmpPrice);
    std::sort(faxItems.begin(), faxItems.end(), cmpPrice);

    for (const auto* it : baseItems) std::cout << it->toString() << "\n\n";
    for (const auto* it : printerItems) std::cout << it->toString() << "\n\n";
    for (const auto* it : faxItems) std::cout << it->toString() << "\n\n";
}

int main() {
    Interface printerIfaces = Interface::WiFi | Interface::USB | Interface::Bluetooth;
    Printer printer1{"LaserJet Pro", Manufacturer::HP, 2022, 299.99, 
                    PrinterColorType::Color, true, PaperFormat::A4, 
                    printerIfaces,
                    ApplicationArea::Office, 35, 1200, ConsumableType::Toner};
    Printer printer2{};
    Fax fax1{"SuperG3", Manufacturer::Brother, 2021, 199.50, 14400, 600, 150, true, AutoFeederType::SingleSided, Interface::RJ11, ApplicationArea::Office};
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
        OfficeEquipment basic1("LaserJet Pro", Manufacturer::HP, 2020, 6500);
        OfficeEquipment basic2("SuperG3", Manufacturer::Brother, 2023, 5500);
        
        std::cout << basic1 << "\n\n";
        std::cout << basic2 << "\n\n";
        
        OfficeEquipment* basePtr = &printer1;
        OfficeEquipment& baseRef = fax1;
        
        std::cout << basePtr->toString() << "\n\n";
        std::cout << baseRef.toString() << "\n\n";
        
        OfficeEquipment* basePtr2 = &basic1;
        std::cout << basePtr2->toString() << "\n\n";
    #endif
    #ifdef STAGE_3
        std::list<OfficeEquipment*> equipmentList;
        int choice;
        //system("cls");

        do {
            std::cout << "\n=== МЕНЮ ===\n";
            std::cout << "1. Добавить оборудование\n";
            std::cout << "2. Добавить принтер\n";
            std::cout << "3. Добавить факс\n";
            std::cout << "4. Показать список\n";
            std::cout << "5. Выход\n";
            std::cout << "\nВыбор: ";
            std::cin >> choice;
            
            if (std::cin.fail()) {
                clearInput();
                std::cout << "ОШИБКА: Введите число от 1 до 5!\n";
                continue;
            }
            
            switch (choice) {
                case 1: {
                    std::cout << "Модель: ";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::string model = inputModel();
                    
                    Manufacturer manufacturer = inputManufacturer();
                    int year = inputYear();
                    double price = inputPrice();
                    
                    equipmentList.push_back(new OfficeEquipment(model, manufacturer, year, price));
                    //system("cls");
                    std::cout << "Оборудование \"" << model << "\" успешно добавлено!\n";
                    break;
                }
                    
                case 2: {
                    std::cout << "Модель: ";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::string model = inputModel();
                    
                    Manufacturer manufacturer = inputManufacturer();
                    int year = inputYear();
                    double price = inputPrice();
                    
                    PrinterColorType colorType = inputColorType();
                    
                    int duplexChoice;
                    std::cout << "Двусторонняя печать (0 - нет, 1 - да): "; 
                    std::cin >> duplexChoice;
                    while (std::cin.fail() || (duplexChoice != 0 && duplexChoice != 1)) {
                        clearInput();
                        std::cout << "ОШИБКА: Введите 0 или 1!\n";
                        std::cout << "Двусторонняя печать (0 - нет, 1 - да): ";
                        std::cin >> duplexChoice;
                    }
                    bool duplexPrint = (duplexChoice == 1);
                    clearInput();
                    
                    PaperFormat maxPaperFormat = inputPaperFormat();
                    Interface interfaces = inputInterfaces();
                    ApplicationArea applicationArea = inputApplicationArea();
                    
                    std::cout << "Скорость печати (стр/мин): ";
                    int speedPPM = inputPrintSpeed();
                    
                    std::cout << "Разрешение печати (DPI): ";
                    int resolutionDPI = inputResolution();
                    
                    ConsumableType consumable = inputConsumableType();
                    
                    equipmentList.push_back(new Printer(model, manufacturer, year, price,
                                                        colorType, duplexPrint, maxPaperFormat,
                                                        interfaces, applicationArea,
                                                        speedPPM, resolutionDPI, consumable));
                    //system("cls");
                    std::cout << "Принтер \"" << model << "\" успешно добавлен!\n";
                    break;
                }
                
                case 3: {
                    std::cout << "Модель: ";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::string model = inputModel();
                    
                    Manufacturer manufacturer = inputManufacturer();
                    int year = inputYear();
                    double price = inputPrice();
                    
                    std::cout << "Скорость передачи (бит/с): ";
                    int transmissionSpeed = inputTransmissionSpeed();
                    
                    std::cout << "Разрешение сканирования (DPI): ";
                    int scanResolution = inputScanResolution();
                    
                    std::cout << "Объем памяти (страниц): ";
                    int memoryPages = inputMemoryPages();
                    
                    int autoFeeder;
                    std::cout << "Наличие автоподатчика (0 - нет, 1 - да): "; 
                    std::cin >> autoFeeder;
                    while (std::cin.fail() || (autoFeeder != 0 && autoFeeder != 1)) {
                        clearInput();
                        std::cout << "ОШИБКА: Введите 0 или 1!\n";
                        std::cout << "Наличие автоподатчика (0 - нет, 1 - да): ";
                        std::cin >> autoFeeder;
                    }
                    bool hasAutoFeeder = (autoFeeder == 1);
                    clearInput();
                    
                    AutoFeederType autoFeederType = inputAutoFeederType();
                    Interface interfaces = inputInterfaces();
                    ApplicationArea applicationArea = inputApplicationArea();
                    
                    equipmentList.push_back(new Fax(model, manufacturer, year, price,
                                                    transmissionSpeed, scanResolution, memoryPages, 
                                                    hasAutoFeeder, autoFeederType, interfaces, applicationArea));
                    //system("cls");
                    std::cout << "Факс \"" << model << "\" успешно добавлен!\n";
                    break;
                }
                
                case 4: {
                    displayEquipmentList(equipmentList);
                    break;
                }
                    
                case 5:
                    //system("cls");
                    clearEquipmentList(equipmentList);
                    std::cout << "Программа завершена, память очищена\n";
                    break;
                    
                default:
                    std::cout << "ОШИБКА: Введите число от 1 до 5!\n";
                    clearInput();
                    break;
            }
        } while (choice != 5);
    #endif
    return 0;
}