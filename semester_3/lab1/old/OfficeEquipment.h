#ifndef OFFICE_EQUIPMENT_H
#define OFFICE_EQUIPMENT_H

#include <string>
#include <iostream>

enum class Manufacturer {
    Brother, Canon, DELI,
    Epson, HP, Xiaomi,
    Samsung, Sharp, Panasonic,
    Unknown
};

class OfficeEquipment{
    private:
        std::string model;
        Manufacturer manufacturer;
        int yearOfManufacture;
        double price;

    public:
        OfficeEquipment();
        OfficeEquipment(const std::string& model, Manufacturer manufacturer, int year, double price);
        virtual ~OfficeEquipment();
        friend std::ostream& operator<<(std::ostream& os, const OfficeEquipment& equipment);

        std::string getModel() const;
        std::string getManufacturer() const;
        int getYearOfManufacture() const;
        double getPrice() const;

        void setModel(const std::string& model);
        void setManufacturer(Manufacturer manufacturer);
        void setPrice(double price);
        void setYearOfManufacture(int year);

        virtual std::string toString() const;

        
        static bool validateModel(const std::string& model);
        static bool validateYear(int year);
        static bool validatePrice(double price);
};

enum class Interface { 
    Bluetooth = 1 << 0,    // 1
    EthernetRJ45 = 1 << 1, // 2
    NFC = 1 << 2,          // 4
    RJ11 = 1 << 3,         // 8
    USB = 1 << 4,          // 16
    USBTypeB = 1 << 5,     // 32
    USBHost = 1 << 6,      // 64
    WiFi = 1 << 7          // 128
};

inline Interface operator|(Interface a, Interface b) {
    return static_cast<Interface>(static_cast<int>(a) | static_cast<int>(b));
}

inline Interface operator&(Interface a, Interface b) {
    return static_cast<Interface>(static_cast<int>(a) & static_cast<int>(b));
}

inline Interface& operator|=(Interface& a, Interface b) {
    a = a | b;
    return a;
}

inline bool hasInterface(Interface value, Interface check) {
    return (static_cast<int>(value) & static_cast<int>(check)) != 0;
}

enum class ApplicationArea { Home, Office };

#endif

// Методы класса представлены ниже в отчёте