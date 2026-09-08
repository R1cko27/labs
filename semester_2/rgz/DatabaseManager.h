#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include "lib/sqlite3.h"
#include <string>
#include <vector>
#include "OfficeEquipment.h"
#include "Printer.h"
#include "Fax.h"

class DatabaseManager {
private:
    sqlite3* db;
    std::string dbName;

public:
    DatabaseManager(const std::string& dbName);
    ~DatabaseManager();

    bool openDatabase();
    void closeDatabase();
    bool createTables();

    // Методы для OfficeEquipment
    int insertOfficeEquipment(const OfficeEquipment& eq);
    std::vector<OfficeEquipment> getAllOfficeEquipment();
    bool deleteOfficeEquipment(int id);
    bool updateOfficeEquipmentModel(int id, const std::string& newModel);
    bool updateOfficeEquipmentPrice(int id, double newPrice);
    bool updateOfficeEquipmentYear(int id, int newYear);
    bool updateOfficeEquipmentManufacturer(int id, Manufacturer manufacturer);

    // Методы для Printer
    bool insertPrinter(int equipmentId, const Printer& printer);
    std::vector<Printer> getAllPrinters();
    bool deletePrinter(int id);
    bool updatePrinterModel(int id, const std::string& newModel);
    bool updatePrinterPrice(int id, double newPrice);
    bool updatePrinterSpeedPPM(int id, int speedPPM);
    bool updatePrinterResolutionDPI(int id, int resolutionDPI);

    // Методы для Fax
    bool insertFax(int equipmentId, const Fax& fax);
    std::vector<Fax> getAllFaxes();
    bool deleteFax(int id);
    bool updateFaxModel(int id, const std::string& newModel);
    bool updateFaxPrice(int id, double newPrice);
    bool updateFaxTransmissionSpeed(int id, int speedBPS);
    bool updateFaxMemoryPages(int id, int pages);

    // Вспомогательные методы
    static int manufacturerToInt(Manufacturer m);
    static Manufacturer intToManufacturer(int i);
    static int applicationAreaToInt(ApplicationArea a);
    static ApplicationArea intToApplicationArea(int i);
    static int interfaceToInt(Interface i);
    static Interface intToInterface(int i);
    static int printerColorTypeToInt(PrinterColorType p);
    static PrinterColorType intToPrinterColorType(int i);
    static int paperFormatToInt(PaperFormat p);
    static PaperFormat intToPaperFormat(int i);
    static int consumableTypeToInt(ConsumableType c);
    static ConsumableType intToConsumableType(int i);
    static int autoFeederTypeToInt(AutoFeederType a);
    static AutoFeederType intToAutoFeederType(int i);
};

#endif // DATABASE_MANAGER_H