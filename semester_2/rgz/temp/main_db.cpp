#include "DatabaseManager.h"
#include "DatabaseUI.h"
#include <iostream>

int main() {
    DatabaseManager db("office_equipment.db");
    if (!db.openDatabase()) {
        std::cerr << "Failed to open database.\n";
        return 1;
    }

    if (!db.createTables()) {
        std::cerr << "Failed to create tables.\n";
        return 1;
    }

    DatabaseUI ui(db);
    ui.showMenu();

    db.closeDatabase();
    return 0;
}