#include <iostream>
#include <list>
#include <string>
#include <memory>
#include "OfficeEquipment.h"
#include "Printer.h"
#include "Fax.h"

int main() {
    std::list<std::unique_ptr<OfficeEquipment>> equipmentList;
    int choice;
    
    do {
        std::cout << "\n=== MENU ===\n";
        std::cout << "1. Add OfficeEquipment\n";
        std::cout << "2. Add Printer\n";
        std::cout << "3. Add Fax\n";
        std::cout << "4. Display list\n";
        std::cout << "5. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        
        std::string model, manufacturer, consumable;
        int year, speedPPM, resolutionDPI, transmissionSpeed, scanResolution, memoryPages;
        double price;
        bool isColor, autoFeeder;
        
        switch(choice) {
            case 1:
                std::cout << "Model: "; std::cin >> model;
                std::cout << "Manufacturer: "; std::cin >> manufacturer;
                std::cout << "Year: "; std::cin >> year;
                std::cout << "Price: "; std::cin >> price;
                equipmentList.push_back(std::make_unique<OfficeEquipment>(model, manufacturer, year, price));
                break;
            case 2:
                std::cout << "Model: "; std::cin >> model;
                std::cout << "Manufacturer: "; std::cin >> manufacturer;
                std::cout << "Year: "; std::cin >> year;
                std::cout << "Price: "; std::cin >> price;
                std::cout << "Color (1/0): "; std::cin >> isColor;
                std::cout << "Speed PPM: "; std::cin >> speedPPM;
                std::cout << "Resolution DPI: "; std::cin >> resolutionDPI;
                std::cout << "Consumable type: "; std::cin >> consumable;
                equipmentList.push_back(std::make_unique<Printer>(model, manufacturer, year, price,
                                                                   isColor, speedPPM, resolutionDPI, consumable));
                break;
            case 3:
                std::cout << "Model: "; std::cin >> model;
                std::cout << "Manufacturer: "; std::cin >> manufacturer;
                std::cout << "Year: "; std::cin >> year;
                std::cout << "Price: "; std::cin >> price;
                std::cout << "Transmission speed BPS: "; std::cin >> transmissionSpeed;
                std::cout << "Scan resolution DPI: "; std::cin >> scanResolution;
                std::cout << "Memory pages: "; std::cin >> memoryPages;
                std::cout << "Auto feeder (1/0): "; std::cin >> autoFeeder;
                equipmentList.push_back(std::make_unique<Fax>(model, manufacturer, year, price,
                                                              transmissionSpeed, scanResolution, memoryPages, autoFeeder));
                break;
            case 4:
                std::cout << "\n=== EQUIPMENT LIST ===\n";
                for (const auto& item : equipmentList) {
                    std::cout << item->toString() << "\n\n";
                }
                break;
            case 5:
                equipmentList.clear();
                std::cout << "Goodbye!\n";
                break;
        }
    } while (choice != 5);
    
    return 0;
}