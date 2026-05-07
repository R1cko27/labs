#ifndef FAX_H
#define FAX_H

#include "OfficeEquipment.h"

enum class AutoFeederType { DoubleSided, SingleSided, None };

class Fax : public OfficeEquipment {
private:
    AutoFeederType autoFeederType;
    Interface interfaces;
    ApplicationArea applicationArea;
    int transmissionSpeedBPS;      // Скорость передачи в битах в секунду
    int scanResolutionDPI;         // Разрешение сканирования в DPI
    int memoryCapacityPages;       // Количество страниц в памяти
    bool hasAutomaticFeeder;       // Наличие автоматической подачи

public:
    Fax();
    Fax(const std::string& model, const std::string& manufacturer, int year, double price,
        int transmissionSpeed, int scanResolution, int memoryPages, bool autoFeeder,
        AutoFeederType autoFeederType, Interface interfaces, ApplicationArea applicationArea);
    ~Fax();
    
    AutoFeederType getAutoFeederType() const;
    Interface getInterfaces() const;
    ApplicationArea getApplicationArea() const;
    int getTransmissionSpeedBPS() const;
    int getScanResolutionDPI() const;
    int getMemoryCapacityPages() const;
    bool getHasAutomaticFeeder() const;
    
    void setAutoFeederType(AutoFeederType type);
    void setInterfaces(Interface iface);
    void setApplicationArea(ApplicationArea area);
    void setTransmissionSpeedBPS(int speedBPS);
    void setScanResolutionDPI(int resolutionDPI);
    void setMemoryCapacityPages(int pages);
    void setHasAutomaticFeeder(bool autoFeeder);

    std::string toString() const override;


    friend std::ostream& operator<<(std::ostream& os, const Fax& fax);
};

#endif
