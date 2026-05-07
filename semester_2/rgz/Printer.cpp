#include "Printer.h"
#include <sstream>

Printer::Printer()
    : OfficeEquipment(), colorType(PrinterColorType::BlackWhite), duplexPrint(false),
      maxPaperFormat(PaperFormat::A4), interfaces(Interface::USB), 
      applicationArea(ApplicationArea::Home), printSpeedPPM(20), 
      printResolutionDPI(300), consumableType("Toner") {}

Printer::Printer(const std::string& model, const std::string& manufacturer, int year, double price,
                 PrinterColorType colorType, bool duplexPrint, PaperFormat maxPaperFormat,
                 Interface interfaces, ApplicationArea applicationArea,
                 int speedPPM, int resolutionDPI, const std::string& consumable)
    : OfficeEquipment(model, manufacturer, year, price), colorType(colorType),
      duplexPrint(duplexPrint), maxPaperFormat(maxPaperFormat), interfaces(interfaces),
      applicationArea(applicationArea), printSpeedPPM(speedPPM), 
      printResolutionDPI(resolutionDPI), consumableType(consumable) {}

Printer::~Printer() {}

PrinterColorType Printer::getColorType() const { return colorType; }
bool Printer::getDuplexPrint() const { return duplexPrint; }
PaperFormat Printer::getMaxPaperFormat() const { return maxPaperFormat; }
Interface Printer::getInterfaces() const { return interfaces; }
ApplicationArea Printer::getApplicationArea() const { return applicationArea; }
int Printer::getPrintSpeedPPM() const { return printSpeedPPM; }
int Printer::getPrintResolutionDPI() const { return printResolutionDPI; }
std::string Printer::getConsumableType() const { return consumableType; }

void Printer::setColorType(PrinterColorType type) { colorType = type; }
void Printer::setDuplexPrint(bool duplex) { duplexPrint = duplex; }
void Printer::setMaxPaperFormat(PaperFormat format) { maxPaperFormat = format; }
void Printer::setInterfaces(Interface iface) { interfaces = iface; }
void Printer::setApplicationArea(ApplicationArea area) { applicationArea = area; }
void Printer::setPrintSpeedPPM(int speedPPM) {
    if (speedPPM > 0) this->printSpeedPPM = speedPPM;
}
void Printer::setPrintResolutionDPI(int resolutionDPI) {
    if (resolutionDPI > 0) this->printResolutionDPI = resolutionDPI;
}
void Printer::setConsumableType(const std::string& consumable) {
    this->consumableType = consumable;
}

std::string Printer::toString() const {
    std::ostringstream oss;
    
    std::string paperFormatStr;
    switch (maxPaperFormat) {
        case PaperFormat::A2: paperFormatStr = "A2"; break;
        case PaperFormat::A3: paperFormatStr = "A3"; break;
        case PaperFormat::A4: paperFormatStr = "A4"; break;
        case PaperFormat::A5: paperFormatStr = "A5"; break;
    }
    
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
    
    std::string areaStr;
    switch (applicationArea) {
        case ApplicationArea::Home: areaStr = "для дома"; break;
        case ApplicationArea::Office: areaStr = "для офиса"; break;
    }
    
    oss << "Модель: " << getModel() << "\n"
        << "Производитель: " << getManufacturer() << "\n"
        << "Год выпуска: " << getYearOfManufacture() << "\n"
        << "Цена: $" << getPrice() << "\n"
        << "Тип печати: " << (colorType == PrinterColorType::Color ? "цветная" : "черно-белая") << "\n"
        << "Двусторонняя печать: " << (duplexPrint ? "Да" : "Нет") << "\n"
        << "Максимальный формат: " << paperFormatStr << "\n"
        << "Скорость печати: " << printSpeedPPM << " стр/мин\n"
        << "Разрешение печати: " << printResolutionDPI << " DPI\n"
        << "Тип расходников: " << consumableType << "\n"
        << "Интерфейс: " << interfaceStr << "\n"
        << "Область применения: " << areaStr;
    
    return oss.str();
}

std::ostream& operator<<(std::ostream& os, const Printer& printer) {
    os << printer.toString();
    return os;
}
