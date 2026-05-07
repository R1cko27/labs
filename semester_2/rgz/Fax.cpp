#include "Fax.h"
#include <sstream>

Fax::Fax()
    : OfficeEquipment(), transmissionSpeedBPS(14400), scanResolutionDPI(203),
      memoryCapacityPages(100), hasAutomaticFeeder(true),
      autoFeederType(AutoFeederType::SingleSided), interfaces(Interface::RJ11),
      applicationArea(ApplicationArea::Office) {}

Fax::Fax(const std::string& model, const std::string& manufacturer, int year, double price,
         int transmissionSpeed, int scanResolution, int memoryPages, bool autoFeeder,
         AutoFeederType autoFeederType, Interface interfaces, ApplicationArea applicationArea)
    : OfficeEquipment(model, manufacturer, year, price), transmissionSpeedBPS(transmissionSpeed),
      scanResolutionDPI(scanResolution), memoryCapacityPages(memoryPages),
      hasAutomaticFeeder(autoFeeder), autoFeederType(autoFeederType),
      interfaces(interfaces), applicationArea(applicationArea) {}

      
Fax::~Fax(){}

AutoFeederType Fax::getAutoFeederType() const { return autoFeederType; }
Interface Fax::getInterfaces() const { return interfaces; }
ApplicationArea Fax::getApplicationArea() const { return applicationArea; }
int Fax::getTransmissionSpeedBPS() const { return transmissionSpeedBPS; }
int Fax::getScanResolutionDPI() const { return scanResolutionDPI; }
int Fax::getMemoryCapacityPages() const {return memoryCapacityPages; }
bool Fax::getHasAutomaticFeeder() const { return hasAutomaticFeeder; }
void Fax::setTransmissionSpeedBPS(int speedBPS){
    if (speedBPS > 0) this->transmissionSpeedBPS = speedBPS; 
}
void Fax::setScanResolutionDPI(int resolutionDPI){
    if (resolutionDPI > 0) this->scanResolutionDPI = resolutionDPI;
}
void Fax::setMemoryCapacityPages(int pages){
    if (pages > 0) this->memoryCapacityPages = pages;
}
void Fax::setHasAutomaticFeeder(bool autoFeeder){
    this->hasAutomaticFeeder = autoFeeder;
}

std::string Fax::toString() const {
    std::ostringstream oss;
    
    // Преобразование enum AutoFeederType в строку
    std::string feederStr;
    switch (autoFeederType) {
        case AutoFeederType::DoubleSided: feederStr = "двустороннее"; break;
        case AutoFeederType::SingleSided: feederStr = "одностороннее"; break;
        case AutoFeederType::None: feederStr = "нет"; break;
    }
    
    // Преобразование enum Interface в строку
    std::string interfaceStr;
    switch (interfaces) {
        case Interface::Bluetooth: interfaceStr = "Bluetooth"; break;
        case Interface::EthernetRJ45: interfaceStr = "Ethernet (RJ-45)"; break;
        case Interface::NFC: interfaceStr = "NFC"; break;
        case Interface::RJ11: interfaceStr = "RJ-11"; break;
        case Interface::USB: interfaceStr = "USB"; break;
        case Interface::USBTypeB: interfaceStr = "USB Type-B"; break;
        case Interface::USBHost: interfaceStr = "USB хост"; break;
        case Interface::WiFi: interfaceStr = "Wi-Fi"; break;
    }
    
    // Преобразование enum ApplicationArea в строку
    std::string areaStr;
    switch (applicationArea) {
        case ApplicationArea::Home: areaStr = "для дома"; break;
        case ApplicationArea::Office: areaStr = "для офиса"; break;
    }
    
    oss << "Модель: " << getModel() << "\n"
        << "Производитель: " << getManufacturer() << "\n"
        << "Год выпуска: " << getYearOfManufacture() << "\n"
        << "Цена: $" << getPrice() << "\n"
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
