#ifndef DATABASE_UI_H
#define DATABASE_UI_H

#include "DatabaseManager.h"

class DatabaseUI {
private:
    DatabaseManager& dbManager;

public:
    DatabaseUI(DatabaseManager& db);
    void showMenu();
    void addOfficeEquipment();
    void addPrinter();
    void addFax();
    void displayAllOfficeEquipment();
    void displayAllPrinters();
    void displayAllFaxes();
    void editOfficeEquipment();
    void editPrinter();
    void editFax();
};

#endif // DATABASE_UI_H