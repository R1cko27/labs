#ifndef PRINTER_H
#define PRINTER_H

#include "OfficeEquipment.h"

enum class PrinterColorType { Color, BlackWhite };
enum class PaperFormat { A2, A3, A4, A5 };
enum class ConsumableType { Toner, Ink, Ribbon, Wax, SolidInk };

class Printer : public OfficeEquipment {
private:
    PrinterColorType colorType; // Тип печати
    bool duplexPrint;       // Наличие двусторонней печати
    PaperFormat maxPaperFormat; // Максимальный формат бумаги
    Interface interfaces;  // Тип подключенияs
    ApplicationArea applicationArea; // Область применения
    int printSpeedPPM; // Скорость печати в страницах в минуту
    int printResolutionDPI; // Разрешение печати
    ConsumableType consumableType;  // Тип расходников

public:
    Printer();
    Printer(const std::string& model, Manufacturer manufacturer, int year, double price,
            PrinterColorType colorType, bool duplexPrint, PaperFormat maxPaperFormat,
            Interface interfaces, ApplicationArea applicationArea,
            int speedPPM, int resolutionDPI, ConsumableType consumable);
    ~Printer() = default;

    PrinterColorType getColorType() const;
    PrinterColorType getColorTypeEnum() const;
    bool getDuplexPrint() const;
    PaperFormat getMaxPaperFormat() const;
    PaperFormat getMaxPaperFormatEnum() const;
    Interface getInterfaces() const;
    Interface getInterfacesEnum() const;
    ApplicationArea getApplicationArea() const;
    ApplicationArea getApplicationAreaEnum() const;
    int getPrintSpeedPPM() const;
    int getPrintResolutionDPI() const;
    ConsumableType getConsumableType() const;
    ConsumableType getConsumableTypeEnum() const;
    
    void setColorType(PrinterColorType type);
    void setDuplexPrint(bool duplex);
    void setMaxPaperFormat(PaperFormat format);
    void setInterfaces(Interface iface);
    void setApplicationArea(ApplicationArea area);
    void setPrintSpeedPPM(int speedPPM);
    void setPrintResolutionDPI(int resolutionDPI);  
    void setConsumableType(ConsumableType consumable);
    
    std::string toString() const override;

    friend std::ostream& operator<<(std::ostream& os, const Printer& printer);
    
    static bool validatePrintSpeed(int speed);
    static bool validatePrintResolution(int resolution);
};

#endif

