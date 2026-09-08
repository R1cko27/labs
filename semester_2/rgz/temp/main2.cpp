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

auto getTypePriority(const OfficeEquipment* obj) -> int {
    if (dynamic_cast<const Printer*>(obj)) return 2;
    if (dynamic_cast<const Fax*>(obj)) return 3;
    return 1;
}

void displayEquipmentList(const std::list<std::unique_ptr<OfficeEquipment>>& equipmentList) { 
    std::cout << "\n=== СПИСОК ОБОРУДОВАНИЯ ===\n";
    
    if (equipmentList.empty()) {
        std::cout << "Список пуст!\n";
        return;
    }
    
    std::vector<const OfficeEquipment*> items;
    for (const auto& item : equipmentList) {
        items.push_back(item.get());
    }
    
    std::sort(items.begin(), items.end(), [](const OfficeEquipment* a, const OfficeEquipment* b) {
        
        int priorityA = getTypePriority(a);
        int priorityB = getTypePriority(b);
        
        if (priorityA != priorityB) {
            return priorityA < priorityB;
        }
        
        return a->getPrice() < b->getPrice();
    });
    
    for (const auto* item : items) {
        std::cout << item->toString() << "\n\n";
    }
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
