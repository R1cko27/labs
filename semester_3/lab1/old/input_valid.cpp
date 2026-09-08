#include "input_valid.h"
#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string inputModel() {
    std::string model;
    while (true) {
        std::getline(std::cin, model);
        if (OfficeEquipment::validateModel(model)) break;
        std::cout << "ОШИБКА: Модель должна содержать от 3 до 100 символов!\n";
        std::cout << "Модель: ";
    }
    return model;
}

int inputYear() {
    int year;
    while (true) {
        std::cout << "Год выпуска: ";
        std::cin >> year;
        if (std::cin.fail()) {
            clearInput();
            std::cout << "ОШИБКА: Введите число!\n";
            std::cout << "Год выпуска: ";
            continue;
        }
        if (OfficeEquipment::validateYear(year)) {
            clearInput();
            break;
        }
        clearInput();
        std::cout << "ОШИБКА: Год должен быть в пределах от 1980 до 2026!\n";
    }
    return year;
}

double inputPrice() {
    double price;
    while (true) {
        std::cout << "Цена: ";
        std::cin >> price;
        if (std::cin.fail()) {
            clearInput();
            std::cout << "ОШИБКА: Введите число!\n";
            std::cout << "Цена: ";
            continue;
        }
        if (OfficeEquipment::validatePrice(price)) {
            clearInput();
            break;
        }
        clearInput();
        std::cout << "ОШИБКА: Цена должна быть в пределах от 3000 до 200000 RUB!\n";
    }
    return price;
}

int inputPrintSpeed() {
    int speed;
    while (true) {
        std::cout << "Скорость печати (стр/мин): ";
        std::cin >> speed;
        if (std::cin.fail()) {
            clearInput();
            std::cout << "ОШИБКА: Введите число!\n";
            std::cout << "Скорость печати (стр/мин): ";
            continue;
        }
        if (Printer::validatePrintSpeed(speed)) {
            clearInput();
            break;
        }
        clearInput();
        std::cout << "ОШИБКА: Скорость печати должна быть в пределах от 3 до 100 стр/мин!\n";
    }
    return speed;
}

int inputResolution() {
    int resolution;
    while (true) {
        std::cout << "Разрешение печати (DPI): ";
        std::cin >> resolution;
        if (std::cin.fail()) {
            clearInput();
            std::cout << "ОШИБКА: Введите число!\n";
            std::cout << "Разрешение печати (DPI): ";
            continue;
        }
        if (Printer::validatePrintResolution(resolution)) {
            clearInput();
            break;
        }
        clearInput();
        std::cout << "ОШИБКА: Разрешение должно быть в пределах от 1200 до 8000 DPI и нацело делиться на 10!\n";
    }
    return resolution;
}

int inputTransmissionSpeed() {
    int speed;
    while (true) {
        std::cout << "Скорость передачи (бит/с): ";
        std::cin >> speed;
        if (std::cin.fail()) {
            clearInput();
            std::cout << "ОШИБКА: Введите число!\n";
            std::cout << "Скорость передачи (бит/с): ";
            continue;
        }
        if (Fax::validateTransmissionSpeed(speed)) {
            clearInput();
            break;
        }
        clearInput();
        std::cout << "ОШИБКА: Скорость должна быть от 2400 до 33600 бит/с и соответствовать стандартным значениям!\n";
        std::cout << "Стандартные значения: 2400, 4800, 7200, 9600, 12000, 14400, 16800, 19200, 21600, 24000, 26400, 28800, 31200, 33600\n";
    }
    return speed;
}

int inputScanResolution() {
    int resolution;
    while (true) {
        std::cout << "Разрешение сканирования (DPI): ";
        std::cin >> resolution;
        if (std::cin.fail()) {
            clearInput();
            std::cout << "ОШИБКА: Введите число!\n";
            std::cout << "Разрешение сканирования (DPI): ";
            continue;
        }
        if (Fax::validateScanResolution(resolution)) {
            clearInput();
            break;
        }
        clearInput();
        std::cout << "ОШИБКА: Разрешение сканирования должно быть в пределах от 100 до 600 DPI!\n";
    }
    return resolution;
}

int inputMemoryPages() {
    int pages;
    while (true) {
        std::cout << "Объем памяти (страниц): ";
        std::cin >> pages;
        if (std::cin.fail()) {
            clearInput();
            std::cout << "ОШИБКА: Введите число!\n";
            std::cout << "Объем памяти (страниц): ";
            continue;
        }
        if (Fax::validateMemoryCapacity(pages)) {
            clearInput();
            break;
        }
        clearInput();
        std::cout << "ОШИБКА: Объем памяти должен быть в пределах от 1 до 500 страниц!\n";
    }
    return pages;
}

Manufacturer inputManufacturer() {
    int manufacturerChoice;
    while (true) {
        std::cout << "Производитель (0-Brother,1-Canon,2-DELI,3-Epson,4-HP,5-Xiaomi,6-Samsung,7-Sharp,8-Panasonic): "; 
        std::cin >> manufacturerChoice;
        
        if (std::cin.fail()) {
            clearInput();
            std::cout << "ОШИБКА: Введите число!\n";
            continue;
        }
        
        if (manufacturerChoice >= 0 && manufacturerChoice <= 8) {
            clearInput();
            return static_cast<Manufacturer>(manufacturerChoice);
        }
        
        clearInput();
        std::cout << "ОШИБКА: Введите число от 0 до 8!\n";
    }
}

Interface inputInterfaces() {
    Interface interfaces = static_cast<Interface>(0);
    int interfaceChoice;
    
    std::cout << "Выберите интерфейсы (вводите номера через пробел, 999 для завершения):\n";
    std::cout << "0 - Bluetooth, 1 - Ethernet, 2 - NFC, 3 - RJ-11, 4 - USB, 5 - USB Type-B, 6 - USB хост, 7 - Wi-Fi\n";

    while (true) {
        std::cin >> interfaceChoice;
        if (std::cin.fail()) {
            clearInput();
            std::cout << "ОШИБКА: Введите число!\n";
            continue;
        }
        if (interfaceChoice == 999) {
            clearInput();
            break;
        }
        if (interfaceChoice >= 0 && interfaceChoice <= 7) {
            interfaces = interfaces | static_cast<Interface>(1 << interfaceChoice);
        } else {
            std::cout << "ОШИБКА: Введите число от 0 до 7 или 999 для завершения!\n";
        }
    }
    return interfaces;
}

ApplicationArea inputApplicationArea() {
    int areaChoice;
    while (true) {
        std::cout << "Область применения (0 - для дома, 1 - для офиса): "; 
        std::cin >> areaChoice;
        
        if (std::cin.fail()) {
            clearInput();
            std::cout << "ОШИБКА: Введите число!\n";
            continue;
        }
        
        if (areaChoice == 0 || areaChoice == 1) {
            clearInput();
            return static_cast<ApplicationArea>(areaChoice);
        }
        
        clearInput();
        std::cout << "ОШИБКА: Введите 0 или 1!\n";
    }
}

PrinterColorType inputColorType() {
    int colorChoice;
    while (true) {
        std::cout << "Тип печати (0 - черно-белый, 1 - цветной): "; 
        std::cin >> colorChoice;
        
        if (std::cin.fail()) {
            clearInput();
            std::cout << "ОШИБКА: Введите число!\n";
            continue;
        }
        
        if (colorChoice == 0 || colorChoice == 1) {
            clearInput();
            return (colorChoice == 1) ? PrinterColorType::Color : PrinterColorType::BlackWhite;
        }
        
        clearInput();
        std::cout << "ОШИБКА: Введите 0 или 1!\n";
    }
}

PaperFormat inputPaperFormat() {
    int paperChoice;
    while (true) {
        std::cout << "Максимальный формат (0 - A2, 1 - A3, 2 - A4, 3 - A5): "; 
        std::cin >> paperChoice;
        
        if (std::cin.fail()) {
            clearInput();
            std::cout << "ОШИБКА: Введите число!\n";
            continue;
        }
        
        if (paperChoice >= 0 && paperChoice <= 3) {
            clearInput();
            return static_cast<PaperFormat>(paperChoice);
        }
        
        clearInput();
        std::cout << "ОШИБКА: Введите число от 0 до 3!\n";
    }
}

ConsumableType inputConsumableType() {
    int consumableChoice;
    while (true) {
        std::cout << "Тип расходников (0 - Toner, 1 - Ink, 2 - Ribbon, 3 - Wax, 4 - SolidInk): ";
        std::cin >> consumableChoice;
        
        if (std::cin.fail()) {
            clearInput();
            std::cout << "ОШИБКА: Введите число!\n";
            continue;
        }
        
        if (consumableChoice >= 0 && consumableChoice <= 4) {
            clearInput();
            return static_cast<ConsumableType>(consumableChoice);
        }
        
        clearInput();
        std::cout << "ОШИБКА: Введите число от 0 до 4!\n";
    }
}

AutoFeederType inputAutoFeederType() {
    int autoFeederChoice;
    while (true) {
        std::cout << "Тип автоподатчика (0 - двусторонний, 1 - односторонний, 2 - нет): "; 
        std::cin >> autoFeederChoice;
        
        if (std::cin.fail()) {
            clearInput();
            std::cout << "ОШИБКА: Введите число!\n";
            continue;
        }
        
        if (autoFeederChoice >= 0 && autoFeederChoice <= 2) {
            clearInput();
            return static_cast<AutoFeederType>(autoFeederChoice);
        }
        
        clearInput();
        std::cout << "ОШИБКА: Введите число от 0 до 2!\n";
    }
}
