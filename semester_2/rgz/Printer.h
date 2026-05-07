#ifndef PRINTER_H
#define PRINTER_H

#include "OfficeEquipment.h"

enum class PrinterColorType { Color, BlackWhite };
enum class PaperFormat { A2, A3, A4, A5 };


class Printer : public OfficeEquipment {
private:
    PrinterColorType colorType;
    bool duplexPrint;
    PaperFormat maxPaperFormat;
    Interface interfaces; 
    ApplicationArea applicationArea;
    int printSpeedPPM;           // Страниц в минуту
    int printResolutionDPI;      // Разрешение
    std::string consumableType;  // Тип расходников

public:
    Printer();
    Printer(const std::string& model, const std::string& manufacturer, int year, double price,
            PrinterColorType colorType, bool duplexPrint, PaperFormat maxPaperFormat,
            Interface interfaces, ApplicationArea applicationArea,
            int speedPPM, int resolutionDPI, const std::string& consumable);
    ~Printer();

    PrinterColorType getColorType() const;
    bool getDuplexPrint() const;
    PaperFormat getMaxPaperFormat() const;
    Interface getInterfaces() const;
    ApplicationArea getApplicationArea() const;
    int getPrintSpeedPPM() const;
    int getPrintResolutionDPI() const;
    std::string getConsumableType() const;
    
    
    
    void setColorType(PrinterColorType type);
    void setDuplexPrint(bool duplex);
    void setMaxPaperFormat(PaperFormat format);
    void setInterfaces(Interface iface);
    void setApplicationArea(ApplicationArea area);
    void setPrintSpeedPPM(int speedPPM);
    void setPrintResolutionDPI(int resolutionDPI);  
    void setConsumableType(const std::string& consumable);

    std::string toString() const override;

    friend std::ostream& operator<<(std::ostream& os, const Printer& printer);
};

#endif
