#include "DatabaseUI.h"
#include "input_valid.h"
#include <iostream>
#include <string>
#include <limits>

DatabaseUI::DatabaseUI(DatabaseManager& db) : dbManager(db) {}

void DatabaseUI::showMenu() {
    int choice;
    do {
        std::cout << "\n=== МЕНЮ БД ===\n";
        std::cout << "1. Добавить оборудование\n";
        std::cout << "2. Добавить принтер\n";
        std::cout << "3. Добавить факс\n";
        std::cout << "4. Показать все оборудование\n";
        std::cout << "5. Показать все принтеры\n";
        std::cout << "6. Показать все факсы\n";
        std::cout << "7. Редактировать оборудование\n";
        std::cout << "8. Редактировать принтер\n";
        std::cout << "9. Редактировать факс\n";
        std::cout << "0. Выход\n";
        std::cout << "\nВыбор: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            clearInput();
            std::cout << "ОШИБКА: Введите число от 0 до 9!\n";
            continue;
        }

        switch (choice) {
            case 1: addOfficeEquipment(); break;
            case 2: addPrinter(); break;
            case 3: addFax(); break;
            case 4: displayAllOfficeEquipment(); break;
            case 5: displayAllPrinters(); break;
            case 6: displayAllFaxes(); break;
            case 7: editOfficeEquipment(); break;
            case 8: editPrinter(); break;
            case 9: editFax(); break;
            case 0: std::cout << "До встречи!\n"; break;
            default: std::cout << "ОШИБКА: Введите число от 0 до 9!\n";
        }
    } while (choice != 0);
}

void DatabaseUI::addOfficeEquipment() {
    std::cout << "\n=== ДОБАВЛЕНИЕ ОБОРУДОВАНИЯ ===\n";
    std::cout << "Модель: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string model = inputModel();
    
    Manufacturer man = inputManufacturer();
    int year = inputYear();
    double price = inputPrice();

    OfficeEquipment eq(model, man, year, price);
    int id = dbManager.insertOfficeEquipment(eq);
    if (id > 0) {
        std::cout << "✓ Оборудование \"" << model << "\" успешно добавлено в БД! ID: " << id << "\n";
    } else {
        std::cout << "✗ Ошибка при добавлении оборудования!\n";
    }
}

void DatabaseUI::addPrinter() {
    std::cout << "\n=== ДОБАВЛЕНИЕ ПРИНТЕРА ===\n";
    std::cout << "Модель: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string model = inputModel();
    
    Manufacturer man = inputManufacturer();
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
    
    // Сначала добавляем оборудование и получаем ID
    OfficeEquipment eq(model, man, year, price);
    int equipmentId = dbManager.insertOfficeEquipment(eq);
    
    if (equipmentId <= 0) {
        std::cout << "✗ Ошибка при добавлении базового оборудования!\n";
        return;
    }
    
    Printer p(model, man, year, price, colorType, duplexPrint, maxPaperFormat,
              interfaces, applicationArea, speedPPM, resolutionDPI, consumable);
    
    if (dbManager.insertPrinter(equipmentId, p)) {
        std::cout << "✓ Принтер \"" << model << "\" успешно добавлен в БД! ID: " << equipmentId << "\n";
    } else {
        std::cout << "✗ Ошибка при добавлении принтера!\n";
    }
}

void DatabaseUI::addFax() {
    std::cout << "\n=== ДОБАВЛЕНИЕ ФАКСА ===\n";
    std::cout << "Модель: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string model = inputModel();
    
    Manufacturer man = inputManufacturer();
    int year = inputYear();
    double price = inputPrice();
    
    std::cout << "Скорость передачи (бит/с): ";
    int transmissionSpeed = inputTransmissionSpeed();
    
    std::cout << "Разрешение сканирования (DPI): ";
    int scanResolution = inputScanResolution();
    
    std::cout << "Объем памяти (страниц): ";
    int memoryPages = inputMemoryPages();
    
    int feederChoice;
    std::cout << "Автоматическая подача (0 - нет, 1 - да): ";
    std::cin >> feederChoice;
    while (std::cin.fail() || (feederChoice != 0 && feederChoice != 1)) {
        clearInput();
        std::cout << "ОШИБКА: Введите 0 или 1!\n";
        std::cout << "Автоматическая подача (0 - нет, 1 - да): ";
        std::cin >> feederChoice;
    }
    bool hasFeeder = (feederChoice == 1);
    clearInput();
    
    AutoFeederType autoF = inputAutoFeederType();
    Interface interfaces = inputInterfaces();
    ApplicationArea app = inputApplicationArea();
    
    // Сначала добавляем оборудование и получаем ID
    OfficeEquipment eq(model, man, year, price);
    int equipmentId = dbManager.insertOfficeEquipment(eq);
    
    if (equipmentId <= 0) {
        std::cout << "✗ Ошибка при добавлении базового оборудования!\n";
        return;
    }
    
    Fax f(model, man, year, price, transmissionSpeed, scanResolution, memoryPages, 
          hasFeeder, autoF, interfaces, app);
    
    if (dbManager.insertFax(equipmentId, f)) {
        std::cout << "✓ Факс \"" << model << "\" успешно добавлен в БД! ID: " << equipmentId << "\n";
    } else {
        std::cout << "✗ Ошибка при добавлении факса!\n";
    }
}

void DatabaseUI::displayAllOfficeEquipment() {
    std::cout << "\n=== СПИСОК ОБОРУДОВАНИЯ ===\n";
    auto equipments = dbManager.getAllOfficeEquipment();
    
    if (equipments.empty()) {
        std::cout << "База данных пуста!\n";
        return;
    }
    
    for (const auto& eq : equipments) {
        std::cout << eq << std::endl << std::endl;
    }
}

void DatabaseUI::displayAllPrinters() {
    std::cout << "\n=== СПИСОК ПРИНТЕРОВ ===\n";
    auto printers = dbManager.getAllPrinters();
    
    if (printers.empty()) {
        std::cout << "Принтеры не найдены!\n";
        return;
    }
    
    for (const auto& p : printers) {
        std::cout << p << std::endl << std::endl;
    }
}

void DatabaseUI::displayAllFaxes() {
    std::cout << "\n=== СПИСОК ФАКСОВ ===\n";
    auto faxes = dbManager.getAllFaxes();
    
    if (faxes.empty()) {
        std::cout << "Факсы не найдены!\n";
        return;
    }
    
    for (const auto& f : faxes) {
        std::cout << f << std::endl << std::endl;
    }
}

void DatabaseUI::editOfficeEquipment() {
    std::cout << "\n=== РЕДАКТИРОВАНИЕ ОБОРУДОВАНИЯ ===\n";
    std::cout << "Введите ID оборудования: ";
    int id;
    std::cin >> id;
    
    if (std::cin.fail()) {
        clearInput();
        std::cout << "ОШИБКА: Введите корректный ID!\n";
        return;
    }
    clearInput();
    
    std::cout << "\nВыберите что изменить:\n";
    std::cout << "1. Модель\n";
    std::cout << "2. Цена\n";
    std::cout << "3. Год\n";
    std::cout << "4. Производитель\n";
    std::cout << "0. Отмена\n";
    std::cout << "Выбор: ";
    
    int choice;
    std::cin >> choice;
    
    if (std::cin.fail()) {
        clearInput();
        std::cout << "ОШИБКА: Введите число!\n";
        return;
    }
    clearInput();
    
    switch (choice) {
        case 1: {
            std::cout << "Новая модель: ";
            std::string model = inputModel();
            if (dbManager.updateOfficeEquipmentModel(id, model)) {
                std::cout << "✓ Модель успешно обновлена!\n";
            } else {
                std::cout << "✗ Ошибка при обновлении!\n";
            }
            break;
        }
        case 2: {
            std::cout << "Новая цена: ";
            double price = inputPrice();
            if (dbManager.updateOfficeEquipmentPrice(id, price)) {
                std::cout << "✓ Цена успешно обновлена!\n";
            } else {
                std::cout << "✗ Ошибка при обновлении!\n";
            }
            break;
        }
        case 3: {
            std::cout << "Новый год: ";
            int year = inputYear();
            if (dbManager.updateOfficeEquipmentYear(id, year)) {
                std::cout << "✓ Год успешно обновлен!\n";
            } else {
                std::cout << "✗ Ошибка при обновлении!\n";
            }
            break;
        }
        case 4: {
            Manufacturer man = inputManufacturer();
            if (dbManager.updateOfficeEquipmentManufacturer(id, man)) {
                std::cout << "✓ Производитель успешно обновлен!\n";
            } else {
                std::cout << "✗ Ошибка при обновлении!\n";
            }
            break;
        }
        case 0:
            break;
        default:
            std::cout << "ОШИБКА: Введите число от 0 до 4!\n";
    }
}

void DatabaseUI::editPrinter() {
    std::cout << "\n=== РЕДАКТИРОВАНИЕ ПРИНТЕРА ===\n";
    std::cout << "Введите ID принтера: ";
    int id;
    std::cin >> id;
    
    if (std::cin.fail()) {
        clearInput();
        std::cout << "ОШИБКА: Введите корректный ID!\n";
        return;
    }
    clearInput();
    
    std::cout << "\nВыберите что изменить:\n";
    std::cout << "1. Модель\n";
    std::cout << "2. Цена\n";
    std::cout << "3. Скорость печати (PPM)\n";
    std::cout << "4. Разрешение печати (DPI)\n";
    std::cout << "0. Отмена\n";
    std::cout << "Выбор: ";
    
    int choice;
    std::cin >> choice;
    
    if (std::cin.fail()) {
        clearInput();
        std::cout << "ОШИБКА: Введите число!\n";
        return;
    }
    clearInput();
    
    switch (choice) {
        case 1: {
            std::cout << "Новая модель: ";
            std::string model = inputModel();
            if (dbManager.updatePrinterModel(id, model)) {
                std::cout << "✓ Модель принтера и оборудования успешно обновлены!\n";
            } else {
                std::cout << "✗ Ошибка при обновлении!\n";
            }
            break;
        }
        case 2: {
            std::cout << "Новая цена: ";
            double price = inputPrice();
            if (dbManager.updatePrinterPrice(id, price)) {
                std::cout << "✓ Цена принтера и оборудования успешно обновлены!\n";
            } else {
                std::cout << "✗ Ошибка при обновлении!\n";
            }
            break;
        }
        case 3: {
            std::cout << "Новая скорость печати (стр/мин): ";
            int speed = inputPrintSpeed();
            if (dbManager.updatePrinterSpeedPPM(id, speed)) {
                std::cout << "✓ Скорость печати успешно обновлена!\n";
            } else {
                std::cout << "✗ Ошибка при обновлении!\n";
            }
            break;
        }
        case 4: {
            std::cout << "Новое разрешение печати (DPI): ";
            int res = inputResolution();
            if (dbManager.updatePrinterResolutionDPI(id, res)) {
                std::cout << "✓ Разрешение печати успешно обновлено!\n";
            } else {
                std::cout << "✗ Ошибка при обновлении!\n";
            }
            break;
        }
        case 0:
            break;
        default:
            std::cout << "ОШИБКА: Введите число от 0 до 4!\n";
    }
}

void DatabaseUI::editFax() {
    std::cout << "\n=== РЕДАКТИРОВАНИЕ ФАКСА ===\n";
    std::cout << "Введите ID факса: ";
    int id;
    std::cin >> id;
    
    if (std::cin.fail()) {
        clearInput();
        std::cout << "ОШИБКА: Введите корректный ID!\n";
        return;
    }
    clearInput();
    
    std::cout << "\nВыберите что изменить:\n";
    std::cout << "1. Модель\n";
    std::cout << "2. Цена\n";
    std::cout << "3. Скорость передачи (BPS)\n";
    std::cout << "4. Объем памяти (страниц)\n";
    std::cout << "0. Отмена\n";
    std::cout << "Выбор: ";
    
    int choice;
    std::cin >> choice;
    
    if (std::cin.fail()) {
        clearInput();
        std::cout << "ОШИБКА: Введите число!\n";
        return;
    }
    clearInput();
    
    switch (choice) {
        case 1: {
            std::cout << "Новая модель: ";
            std::string model = inputModel();
            if (dbManager.updateFaxModel(id, model)) {
                std::cout << "✓ Модель факса и оборудования успешно обновлены!\n";
            } else {
                std::cout << "✗ Ошибка при обновлении!\n";
            }
            break;
        }
        case 2: {
            std::cout << "Новая цена: ";
            double price = inputPrice();
            if (dbManager.updateFaxPrice(id, price)) {
                std::cout << "✓ Цена факса и оборудования успешно обновлены!\n";
            } else {
                std::cout << "✗ Ошибка при обновлении!\n";
            }
            break;
        }
        case 3: {
            std::cout << "Новая скорость передачи (бит/с): ";
            int speed = inputTransmissionSpeed();
            if (dbManager.updateFaxTransmissionSpeed(id, speed)) {
                std::cout << "✓ Скорость передачи успешно обновлена!\n";
            } else {
                std::cout << "✗ Ошибка при обновлении!\n";
            }
            break;
        }
        case 4: {
            std::cout << "Новый объем памяти (страниц): ";
            int pages = inputMemoryPages();
            if (dbManager.updateFaxMemoryPages(id, pages)) {
                std::cout << "✓ Объем памяти успешно обновлен!\n";
            } else {
                std::cout << "✗ Ошибка при обновлении!\n";
            }
            break;
        }
        case 0:
            break;
        default:
            std::cout << "ОШИБКА: Введите число от 0 до 4!\n";
    }
}