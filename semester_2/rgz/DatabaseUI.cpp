#include "DatabaseUI.h"
#include <iostream>

DatabaseUI::DatabaseUI(DatabaseManager& db) : dbManager(db) {}

void DatabaseUI::showMenu() {
    std::cout << "Console interface is not fully implemented in this version.\n";
    std::cout << "Please use graphical interface.\n";
}

void DatabaseUI::addOfficeEquipment() {}
void DatabaseUI::addPrinter() {}
void DatabaseUI::addFax() {}
void DatabaseUI::displayAllOfficeEquipment() {}
void DatabaseUI::displayAllPrinters() {}
void DatabaseUI::displayAllFaxes() {}
void DatabaseUI::editOfficeEquipment() {}
void DatabaseUI::editPrinter() {}
void DatabaseUI::editFax() {}