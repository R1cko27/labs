#include "Fax.h"
#include <sstream>
#include <vector>
#include <set>


Fax::Fax()
    : OfficeEquipment(), transmissionSpeedBPS(14400), scanResolutionDPI(203),
      memoryCapacityPages(100), hasAutomaticFeeder(true),
      autoFeederType(AutoFeederType::SingleSided), interfaces(Interface::RJ11),
      applicationArea(ApplicationArea::Office) {}

Fax::Fax(const std::string& model, Manufacturer manufacturer, int year, double price,
         int transmissionSpeed, int scanResolution, int memoryPages, bool autoFeeder,
         AutoFeederType autoFeederType, Interface interfaces, ApplicationArea applicationArea)
    : OfficeEquipment(model, manufacturer, year, price), transmissionSpeedBPS(transmissionSpeed),
      scanResolutionDPI(scanResolution), memoryCapacityPages(memoryPages),
      hasAutomaticFeeder(autoFeeder), autoFeederType(autoFeederType),
      interfaces(interfaces), applicationArea(applicationArea) {
    if (!validateTransmissionSpeed(transmissionSpeed)) 
        this->transmissionSpeedBPS = 14400;
    
    if (!validateScanResolution(scanResolution)) 
        this->scanResolutionDPI = 200;
    
    if (!validateMemoryCapacity(memoryPages)) 
        this->memoryCapacityPages = 100;
}

Fax::~Fax(){}

AutoFeederType Fax::getAutoFeederType() const { return autoFeederType; }
Interface Fax::getInterfaces() const { return interfaces; }
ApplicationArea Fax::getApplicationArea() const { return applicationArea; }
int Fax::getTransmissionSpeedBPS() const { return transmissionSpeedBPS; }
int Fax::getScanResolutionDPI() const { return scanResolutionDPI; }
int Fax::getMemoryCapacityPages() const {return memoryCapacityPages; }
bool Fax::getHasAutomaticFeeder() const { return hasAutomaticFeeder; }

void Fax::setAutoFeederType(AutoFeederType type) { autoFeederType = type; }
void Fax::setInterfaces(Interface iface) { interfaces = iface; }
void Fax::setApplicationArea(ApplicationArea area) { applicationArea = area; }

void Fax::setTransmissionSpeedBPS(int speedBPS){
    if (validateTransmissionSpeed(speedBPS)) this->transmissionSpeedBPS = speedBPS; 
}

void Fax::setScanResolutionDPI(int resolutionDPI){
    if (validateScanResolution(resolutionDPI)) this->scanResolutionDPI = resolutionDPI;
}

void Fax::setMemoryCapacityPages(int pages){
    if (validateMemoryCapacity(pages)) this->memoryCapacityPages = pages;
}

void Fax::setHasAutomaticFeeder(bool autoFeeder){
    this->hasAutomaticFeeder = autoFeeder;
}

bool Fax::validateTransmissionSpeed(int speed) {
    return speed >= 2400 && speed <= 33600 && speed%100 == 0;
}


bool Fax::validateScanResolution(int resolution) {
    return resolution >= 100 && resolution <= 600;
}

bool Fax::validateMemoryCapacity(int pages) {
    return pages >= 1 && pages <= 500;
}

std::string Fax::toString() const {
    std::ostringstream oss;
    
    std::string feederStr;
    switch (autoFeederType) {
        case AutoFeederType::DoubleSided: feederStr = "двустороннее"; break;
        case AutoFeederType::SingleSided: feederStr = "одностороннее"; break;
        case AutoFeederType::None: feederStr = "нет"; break;
    }
    
    std::string interfaceStr;
    std::vector<std::string> ifaceList;

    if (hasInterface(interfaces, Interface::Bluetooth)) ifaceList.push_back("Bluetooth");
    if (hasInterface(interfaces, Interface::EthernetRJ45)) ifaceList.push_back("Ethernet (RJ-45)");
    if (hasInterface(interfaces, Interface::NFC)) ifaceList.push_back("NFC");
    if (hasInterface(interfaces, Interface::RJ11)) ifaceList.push_back("RJ-11");
    if (hasInterface(interfaces, Interface::USB)) ifaceList.push_back("USB");
    if (hasInterface(interfaces, Interface::USBTypeB)) ifaceList.push_back("USB Type-B");
    if (hasInterface(interfaces, Interface::USBHost)) ifaceList.push_back("USB хост");
    if (hasInterface(interfaces, Interface::WiFi)) ifaceList.push_back("Wi-Fi");

    for (size_t i = 0; i < ifaceList.size(); ++i) {
        if (i > 0) interfaceStr += ", ";
        interfaceStr += ifaceList[i];
    }
    if (ifaceList.empty()) interfaceStr = "Не указаны";
    
    std::string areaStr;
    switch (applicationArea) {
        case ApplicationArea::Home: areaStr = "для дома"; break;
        case ApplicationArea::Office: areaStr = "для офиса"; break;
    }
    
    oss << "Модель: " << getModel() << "\n"
        << "Производитель: " << getManufacturer() << "\n"
        << "Год выпуска: " << getYearOfManufacture() << "\n"
        << "Цена: " << getPrice() << " RUB\n"
        << "Скорость передачи: " << transmissionSpeedBPS << " бит/с\n"
        << "Разрешение сканирования: " << scanResolutionDPI << " DPI\n"
        << "Объем памяти: " << memoryCapacityPages << " страниц\n"
        << "Автоподатчик: " << (hasAutomaticFeeder ? "Да" : "Нет") << "\n"
        << "Тип автоподатчика: " << feederStr << "\n"
        << "Интерфейс: " << interfaceStr << "\n"
        << "Область применения: " << areaStr;
    
    return oss.str();
}

std::ostream& operator<<(std::ostream& os, const Fax& fax){
    os << fax.toString();
    return os;
}