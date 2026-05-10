#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <memory>

#include "OfficeEquipment.h"
#include "Printer.h"
#include "Fax.h"
#include "input_valid.h"


void displayEquipmentList(const std::list<std::unique_ptr<OfficeEquipment>>& equipmentList) { 
    std::cout << "\n=== СПИСОК ОБОРУДОВАНИЯ ===\n";
    
    if (equipmentList.empty()) {
        std::cout << "Список пуст!\n";
        return;
    }
    
    std::vector<const OfficeEquipment*> baseItems;
    std::vector<const OfficeEquipment*> printerItems;
    std::vector<const OfficeEquipment*> faxItems;

    for (const auto& item : equipmentList) { 
        const OfficeEquipment* ptr = item.get(); 
        if (dynamic_cast<const Printer*>(ptr)) { 
            printerItems.push_back(ptr);
        } else if (dynamic_cast<const Fax*>(ptr)) {
            faxItems.push_back(ptr);
        } else {
            baseItems.push_back(ptr);
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
    std::list<std::unique_ptr<OfficeEquipment>> equipmentList;
    int choice;

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
                
                equipmentList.push_back(std::make_unique<OfficeEquipment>(model, manufacturer, year, price));
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
                
                equipmentList.push_back(std::make_unique<Printer>(model, manufacturer, year, price,
                                                    colorType, duplexPrint, maxPaperFormat,
                                                    interfaces, applicationArea,
                                                    speedPPM, resolutionDPI, consumable));
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
                
                equipmentList.push_back(std::make_unique<Fax>(model, manufacturer, year, price,
                                                transmissionSpeed, scanResolution, memoryPages, 
                                                hasAutoFeeder, autoFeederType, interfaces, applicationArea));
                std::cout << "Факс \"" << model << "\" успешно добавлен!\n";
                break;
            }
            
            case 4: {
                displayEquipmentList(equipmentList);
                break;
            }
                
            case 5:
                equipmentList.clear();
                std::cout << "Программа завершена, память очищена\n";
                break;
                
            default:
                std::cout << "ОШИБКА: Введите число от 1 до 5!\n";
                clearInput();
                break;
        }
    } while (choice != 5);
    
    return 0;
}