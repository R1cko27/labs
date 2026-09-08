#include "Printer.h"
#include <sstream>
#include <vector> 

Printer::Printer()
    : OfficeEquipment(), colorType(PrinterColorType::BlackWhite), duplexPrint(false),
      maxPaperFormat(PaperFormat::A4), interfaces(Interface::USB), 
      applicationArea(ApplicationArea::Home), printSpeedPPM(20), 
      printResolutionDPI(3000), consumableType(ConsumableType::Toner) {}

Printer::Printer(const std::string& model, Manufacturer manufacturer, int year, double price,
                 PrinterColorType colorType, bool duplexPrint, PaperFormat maxPaperFormat,
                 Interface interfaces, ApplicationArea applicationArea,
                 int speedPPM, int resolutionDPI, ConsumableType consumable)
    : OfficeEquipment(model, manufacturer, year, price), colorType(colorType),
      duplexPrint(duplexPrint), maxPaperFormat(maxPaperFormat), interfaces(interfaces),
      applicationArea(applicationArea), printSpeedPPM(speedPPM), 
      printResolutionDPI(resolutionDPI), consumableType(consumable) {
    // Валидация специфичных для принтера полей
    if (!validatePrintSpeed(speedPPM)) {
        this->printSpeedPPM = 20;
    }
    if (!validatePrintResolution(resolutionDPI)) {
        this->printResolutionDPI = 1200;
    }
}

Printer::~Printer() {}

PrinterColorType Printer::getColorType() const { return colorType; }
bool Printer::getDuplexPrint() const { return duplexPrint; }
PaperFormat Printer::getMaxPaperFormat() const { return maxPaperFormat; }
Interface Printer::getInterfaces() const { return interfaces; }
ApplicationArea Printer::getApplicationArea() const { return applicationArea; }
int Printer::getPrintSpeedPPM() const { return printSpeedPPM; }
int Printer::getPrintResolutionDPI() const { return printResolutionDPI; }
ConsumableType Printer::getConsumableType() const { return consumableType; }

void Printer::setColorType(PrinterColorType type) { colorType = type; }
void Printer::setDuplexPrint(bool duplex) { duplexPrint = duplex; }
void Printer::setMaxPaperFormat(PaperFormat format) { maxPaperFormat = format; }
void Printer::setInterfaces(Interface iface) { interfaces = iface; }
void Printer::setApplicationArea(ApplicationArea area) { applicationArea = area; }
void Printer::setPrintSpeedPPM(int speedPPM) {
    if (validatePrintSpeed(speedPPM)) this->printSpeedPPM = speedPPM;
}
void Printer::setPrintResolutionDPI(int resolutionDPI) {
    if (validatePrintResolution(resolutionDPI)) this->printResolutionDPI = resolutionDPI;
}
void Printer::setConsumableType(ConsumableType consumable) {
    this->consumableType = consumable;
}

bool Printer::validatePrintSpeed(int speed) {
    return speed >= 3 && speed <= 100;
}

bool Printer::validatePrintResolution(int resolution) {
    return resolution >= 1200 && resolution <= 8000 && resolution % 10 == 0;
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
    
    std::string consumableStr;
    switch (consumableType) {
        case ConsumableType::Toner: consumableStr = "Тонер"; break;
        case ConsumableType::Ink: consumableStr = "Чернила"; break;
        case ConsumableType::Ribbon: consumableStr = "Лента"; break;
        case ConsumableType::Wax: consumableStr = "Воск"; break;
        case ConsumableType::SolidInk: consumableStr = "Твердые чернила"; break;
    }

    oss << "Модель: " << getModel() << "\n"
        << "Производитель: " << getManufacturer() << "\n"
        << "Год выпуска: " << getYearOfManufacture() << "\n"
        << "Цена: " << getPrice() << " RUB\n"
        << "Тип печати: " << (colorType == PrinterColorType::Color ? "цветная" : "черно-белая") << "\n"
        << "Двусторонняя печать: " << (duplexPrint ? "Да" : "Нет") << "\n"
        << "Максимальный формат: " << paperFormatStr << "\n"
        << "Скорость печати: " << printSpeedPPM << " стр/мин\n"
        << "Разрешение печати: " << printResolutionDPI << " DPI\n"
        << "Тип расходников: " << consumableStr << "\n"
        << "Интерфейс: " << interfaceStr << "\n"
        << "Область применения: " << areaStr;
    
    return oss.str();
}

std::ostream& operator<<(std::ostream& os, const Printer& printer) {
    os << printer.toString();
    return os;
}