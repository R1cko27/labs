#include "DatabaseManager.h"
#include "DatabaseGUI.h"
#include <iostream>

int main() {
    DatabaseManager dbManager("office_equipment.db");
    
    if (!dbManager.openDatabase()) {
        std::cerr << "Failed to open database!" << std::endl;
        return 1;
    }
    
    if (!dbManager.createTables()) {
        std::cerr << "Failed to create tables!" << std::endl;
        dbManager.closeDatabase();
        return 1;
    }
    
    // Запускаем графический интерфейс
    DatabaseGUI gui(dbManager);
    gui.Run();
    
    dbManager.closeDatabase();
    return 0;
}