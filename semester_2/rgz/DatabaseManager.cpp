#include "DatabaseManager.h"
#include <iostream>
#include <sstream>

DatabaseManager::DatabaseManager(const std::string& dbName) : db(nullptr), dbName(dbName) {}

DatabaseManager::~DatabaseManager() {
    closeDatabase();
}

bool DatabaseManager::openDatabase() {
    int rc = sqlite3_open(dbName.c_str(), &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    return true;
}

void DatabaseManager::closeDatabase() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
}

bool DatabaseManager::createTables() {
    const char* sqlOfficeEquipment = 
        "CREATE TABLE IF NOT EXISTS OfficeEquipment ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "model TEXT NOT NULL,"
        "manufacturer INTEGER NOT NULL,"
        "year INTEGER NOT NULL,"
        "price REAL NOT NULL);";

    const char* sqlPrinter = 
        "CREATE TABLE IF NOT EXISTS Printer ("
        "id INTEGER PRIMARY KEY,"
        "model TEXT NOT NULL,"
        "manufacturer INTEGER NOT NULL,"
        "year INTEGER NOT NULL,"
        "price REAL NOT NULL,"
        "colorType INTEGER NOT NULL,"
        "duplexPrint INTEGER NOT NULL,"
        "maxPaperFormat INTEGER NOT NULL,"
        "interfaces INTEGER NOT NULL,"
        "applicationArea INTEGER NOT NULL,"
        "printSpeedPPM INTEGER NOT NULL,"
        "printResolutionDPI INTEGER NOT NULL,"
        "consumableType INTEGER NOT NULL);";

    const char* sqlFax = 
        "CREATE TABLE IF NOT EXISTS Fax ("
        "id INTEGER PRIMARY KEY,"
        "model TEXT NOT NULL,"
        "manufacturer INTEGER NOT NULL,"
        "year INTEGER NOT NULL,"
        "price REAL NOT NULL,"
        "autoFeederType INTEGER NOT NULL,"
        "interfaces INTEGER NOT NULL,"
        "applicationArea INTEGER NOT NULL,"
        "transmissionSpeedBPS INTEGER NOT NULL,"
        "scanResolutionDPI INTEGER NOT NULL,"
        "memoryCapacityPages INTEGER NOT NULL,"
        "hasAutomaticFeeder INTEGER NOT NULL);";

    char* errMsg = nullptr;
    int rc;

    rc = sqlite3_exec(db, sqlOfficeEquipment, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }

    rc = sqlite3_exec(db, sqlPrinter, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }

    rc = sqlite3_exec(db, sqlFax, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }

    return true;
}

// Вспомогательные функции для конверсии enums

int DatabaseManager::manufacturerToInt(Manufacturer m) {
    return static_cast<int>(m);
}

Manufacturer DatabaseManager::intToManufacturer(int i) {
    return static_cast<Manufacturer>(i);
}

int DatabaseManager::applicationAreaToInt(ApplicationArea a) {
    return static_cast<int>(a);
}

ApplicationArea DatabaseManager::intToApplicationArea(int i) {
    return static_cast<ApplicationArea>(i);
}

int DatabaseManager::interfaceToInt(Interface i) {
    return static_cast<int>(i);
}

Interface DatabaseManager::intToInterface(int i) {
    return static_cast<Interface>(i);
}

int DatabaseManager::printerColorTypeToInt(PrinterColorType p) {
    return static_cast<int>(p);
}

PrinterColorType DatabaseManager::intToPrinterColorType(int i) {
    return static_cast<PrinterColorType>(i);
}

int DatabaseManager::paperFormatToInt(PaperFormat p) {
    return static_cast<int>(p);
}

PaperFormat DatabaseManager::intToPaperFormat(int i) {
    return static_cast<PaperFormat>(i);
}

int DatabaseManager::consumableTypeToInt(ConsumableType c) {
    return static_cast<int>(c);
}

ConsumableType DatabaseManager::intToConsumableType(int i) {
    return static_cast<ConsumableType>(i);
}

int DatabaseManager::autoFeederTypeToInt(AutoFeederType a) {
    return static_cast<int>(a);
}

AutoFeederType DatabaseManager::intToAutoFeederType(int i) {
    return static_cast<AutoFeederType>(i);
}

// Методы для OfficeEquipment

int DatabaseManager::insertOfficeEquipment(const OfficeEquipment& eq) {
    std::string sql = "INSERT INTO OfficeEquipment (model, manufacturer, year, price) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return -1;
    }

    sqlite3_bind_text(stmt, 1, eq.getModel().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, manufacturerToInt(eq.getManufacturerEnum()));
    sqlite3_bind_int(stmt, 3, eq.getYearOfManufacture());
    sqlite3_bind_double(stmt, 4, eq.getPrice());

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Execution failed: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return -1;
    }

    sqlite3_finalize(stmt);
    int lastId = static_cast<int>(sqlite3_last_insert_rowid(db));
    return lastId;
}

// Аналогично для других, но для краткости, я напишу только для одного.

std::vector<OfficeEquipment> DatabaseManager::getAllOfficeEquipment() {
    std::vector<OfficeEquipment> equipments;
    std::string sql = "SELECT model, manufacturer, year, price FROM OfficeEquipment;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return equipments;
    }

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        std::string model = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        int manInt = sqlite3_column_int(stmt, 1);
        int year = sqlite3_column_int(stmt, 2);
        double price = sqlite3_column_double(stmt, 3);

        Manufacturer man = intToManufacturer(manInt);
        OfficeEquipment eq(model, man, year, price);
        equipments.push_back(eq);
    }

    sqlite3_finalize(stmt);
    return equipments;
}

bool DatabaseManager::deleteOfficeEquipment(int id) {
    std::string sql = "DELETE FROM OfficeEquipment WHERE id = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) return false;

    sqlite3_bind_int(stmt, 1, id);
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE;
}

bool DatabaseManager::updateOfficeEquipmentModel(int id, const std::string& newModel) {
    std::string sql = "UPDATE OfficeEquipment SET model = ? WHERE id = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) return false;

    sqlite3_bind_text(stmt, 1, newModel.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, id);
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE;
}

bool DatabaseManager::updateOfficeEquipmentPrice(int id, double newPrice) {
    std::string sql = "UPDATE OfficeEquipment SET price = ? WHERE id = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) return false;

    sqlite3_bind_double(stmt, 1, newPrice);
    sqlite3_bind_int(stmt, 2, id);
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE;
}

bool DatabaseManager::updateOfficeEquipmentYear(int id, int newYear) {
    std::string sql = "UPDATE OfficeEquipment SET year = ? WHERE id = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) return false;

    sqlite3_bind_int(stmt, 1, newYear);
    sqlite3_bind_int(stmt, 2, id);
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE;
}

bool DatabaseManager::updateOfficeEquipmentManufacturer(int id, Manufacturer manufacturer) {
    std::string sql = "UPDATE OfficeEquipment SET manufacturer = ? WHERE id = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) return false;

    sqlite3_bind_int(stmt, 1, manufacturerToInt(manufacturer));
    sqlite3_bind_int(stmt, 2, id);
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE;
}

// Аналогично для Printer и Fax, но для краткости опущу.

// Для Printer insert

bool DatabaseManager::insertPrinter(int equipmentId, const Printer& printer) {

    std::string sql = "INSERT INTO Printer (id, model, manufacturer, year, price, colorType, duplexPrint, maxPaperFormat, interfaces, applicationArea, printSpeedPPM, printResolutionDPI, consumableType) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);"; 
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, equipmentId);
    sqlite3_bind_text(stmt, 2, printer.getModel().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, manufacturerToInt(printer.getManufacturerEnum()));
    sqlite3_bind_int(stmt, 4, printer.getYearOfManufacture());
    sqlite3_bind_double(stmt, 5, printer.getPrice());
    sqlite3_bind_int(stmt, 6, printerColorTypeToInt(printer.getColorTypeEnum()));
    sqlite3_bind_int(stmt, 7, printer.getDuplexPrint() ? 1 : 0);
    sqlite3_bind_int(stmt, 8, paperFormatToInt(printer.getMaxPaperFormatEnum()));
    sqlite3_bind_int(stmt, 9, interfaceToInt(printer.getInterfacesEnum()));
    sqlite3_bind_int(stmt, 10, applicationAreaToInt(printer.getApplicationAreaEnum()));
    sqlite3_bind_int(stmt, 11, printer.getPrintSpeedPPM());
    sqlite3_bind_int(stmt, 12, printer.getPrintResolutionDPI());
    sqlite3_bind_int(stmt, 13, consumableTypeToInt(printer.getConsumableTypeEnum()));

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Execution failed: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

std::vector<Printer> DatabaseManager::getAllPrinters() {
    std::vector<Printer> printers;
    std::string sql = "SELECT model, manufacturer, year, price, colorType, duplexPrint, maxPaperFormat, interfaces, applicationArea, printSpeedPPM, printResolutionDPI, consumableType FROM Printer;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return printers;
    }

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        std::string model = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        int manInt = sqlite3_column_int(stmt, 1);
        int year = sqlite3_column_int(stmt, 2);
        double price = sqlite3_column_double(stmt, 3);
        int colorInt = sqlite3_column_int(stmt, 4);
        bool duplex = sqlite3_column_int(stmt, 5) != 0;
        int paperInt = sqlite3_column_int(stmt, 6);
        int ifaceInt = sqlite3_column_int(stmt, 7);
        int appInt = sqlite3_column_int(stmt, 8);
        int speed = sqlite3_column_int(stmt, 9);
        int res = sqlite3_column_int(stmt, 10);
        int consInt = sqlite3_column_int(stmt, 11);

        Manufacturer man = intToManufacturer(manInt);
        PrinterColorType color = intToPrinterColorType(colorInt);
        PaperFormat paper = intToPaperFormat(paperInt);
        Interface iface = intToInterface(ifaceInt);
        ApplicationArea app = intToApplicationArea(appInt);
        ConsumableType cons = intToConsumableType(consInt);

        Printer p(model, man, year, price, color, duplex, paper, iface, app, speed, res, cons);
        printers.push_back(p);
    }

    sqlite3_finalize(stmt);
    return printers;
}

bool DatabaseManager::deletePrinter(int id) {
    std::string sql = "DELETE FROM Printer WHERE id = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) return false;

    sqlite3_bind_int(stmt, 1, id);
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE;
}

bool DatabaseManager::updatePrinterModel(int id, const std::string& newModel) {
    if (!updateOfficeEquipmentModel(id, newModel)) return false;
    std::string sql = "UPDATE Printer SET model = ? WHERE id = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) return false;

    sqlite3_bind_text(stmt, 1, newModel.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, id);
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE;
}

bool DatabaseManager::updatePrinterPrice(int id, double newPrice) {
    if (!updateOfficeEquipmentPrice(id, newPrice)) return false;
    std::string sql = "UPDATE Printer SET price = ? WHERE id = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) return false;

    sqlite3_bind_double(stmt, 1, newPrice);
    sqlite3_bind_int(stmt, 2, id);
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE;
}

bool DatabaseManager::updatePrinterSpeedPPM(int id, int speedPPM) {
    std::string sql = "UPDATE Printer SET printSpeedPPM = ? WHERE id = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) return false;

    sqlite3_bind_int(stmt, 1, speedPPM);
    sqlite3_bind_int(stmt, 2, id);
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE;
}

bool DatabaseManager::updatePrinterResolutionDPI(int id, int resolutionDPI) {
    std::string sql = "UPDATE Printer SET printResolutionDPI = ? WHERE id = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) return false;

    sqlite3_bind_int(stmt, 1, resolutionDPI);
    sqlite3_bind_int(stmt, 2, id);
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE;
}

// Аналогично для Fax

bool DatabaseManager::insertFax(int equipmentId, const Fax& fax) {

    std::string sql = "INSERT INTO Fax (id, model, manufacturer, year, price, autoFeederType, interfaces, applicationArea, transmissionSpeedBPS, scanResolutionDPI, memoryCapacityPages, hasAutomaticFeeder) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);"; 
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, equipmentId);
    sqlite3_bind_text(stmt, 2, fax.getModel().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, manufacturerToInt(fax.getManufacturerEnum()));
    sqlite3_bind_int(stmt, 4, fax.getYearOfManufacture());
    sqlite3_bind_double(stmt, 5, fax.getPrice());
    sqlite3_bind_int(stmt, 6, autoFeederTypeToInt(fax.getAutoFeederTypeEnum()));
    sqlite3_bind_int(stmt, 7, interfaceToInt(fax.getInterfacesEnum()));
    sqlite3_bind_int(stmt, 8, applicationAreaToInt(fax.getApplicationAreaEnum()));
    sqlite3_bind_int(stmt, 9, fax.getTransmissionSpeedBPS());
    sqlite3_bind_int(stmt, 10, fax.getScanResolutionDPI());
    sqlite3_bind_int(stmt, 11, fax.getMemoryCapacityPages());
    sqlite3_bind_int(stmt, 12, fax.getHasAutomaticFeeder() ? 1 : 0);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Execution failed: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

std::vector<Fax> DatabaseManager::getAllFaxes() {
    std::vector<Fax> faxes;
    std::string sql = "SELECT model, manufacturer, year, price, autoFeederType, interfaces, applicationArea, transmissionSpeedBPS, scanResolutionDPI, memoryCapacityPages, hasAutomaticFeeder FROM Fax;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return faxes;
    }

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        std::string model = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        int manInt = sqlite3_column_int(stmt, 1);
        int year = sqlite3_column_int(stmt, 2);
        double price = sqlite3_column_double(stmt, 3);
        int autoInt = sqlite3_column_int(stmt, 4);
        int ifaceInt = sqlite3_column_int(stmt, 5);
        int appInt = sqlite3_column_int(stmt, 6);
        int speed = sqlite3_column_int(stmt, 7);
        int res = sqlite3_column_int(stmt, 8);
        int mem = sqlite3_column_int(stmt, 9);
        bool feeder = sqlite3_column_int(stmt, 10) != 0;

        Manufacturer man = intToManufacturer(manInt);
        AutoFeederType autoF = intToAutoFeederType(autoInt);
        Interface iface = intToInterface(ifaceInt);
        ApplicationArea app = intToApplicationArea(appInt);

        Fax f(model, man, year, price, speed, res, mem, feeder, autoF, iface, app);
        faxes.push_back(f);
    }

    sqlite3_finalize(stmt);
    return faxes;
}

bool DatabaseManager::deleteFax(int id) {
    std::string sql = "DELETE FROM Fax WHERE id = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) return false;

    sqlite3_bind_int(stmt, 1, id);
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE;
}

bool DatabaseManager::updateFaxModel(int id, const std::string& newModel) {
    if (!updateOfficeEquipmentModel(id, newModel)) return false;
    std::string sql = "UPDATE Fax SET model = ? WHERE id = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) return false;

    sqlite3_bind_text(stmt, 1, newModel.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, id);
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE;
}

bool DatabaseManager::updateFaxPrice(int id, double newPrice) {
    if (!updateOfficeEquipmentPrice(id, newPrice)) return false;
    std::string sql = "UPDATE Fax SET price = ? WHERE id = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) return false;

    sqlite3_bind_double(stmt, 1, newPrice);
    sqlite3_bind_int(stmt, 2, id);
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE;
}

bool DatabaseManager::updateFaxTransmissionSpeed(int id, int speedBPS) {
    std::string sql = "UPDATE Fax SET transmissionSpeedBPS = ? WHERE id = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) return false;

    sqlite3_bind_int(stmt, 1, speedBPS);
    sqlite3_bind_int(stmt, 2, id);
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE;
}

bool DatabaseManager::updateFaxMemoryPages(int id, int pages) {
    std::string sql = "UPDATE Fax SET memoryCapacityPages = ? WHERE id = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) return false;

    sqlite3_bind_int(stmt, 1, pages);
    sqlite3_bind_int(stmt, 2, id);
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE;
}
