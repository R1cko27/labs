#ifndef OFFICE_EQUIPMENT_H
#define OFFICE_EQUIPMENT_H

#include <string>
#include <iostream>

class OfficeEquipment{
    private:
        std::string model;
        std::string manufacturer;
        int yearOfManufacture;
        double price;

    public:
        OfficeEquipment();
        OfficeEquipment(const std::string& model, const std::string& manufacturer, int year, double price);
        virtual ~OfficeEquipment();


        std::string getModel() const;
        std::string getManufacturer() const;
        int getYearOfManufacture() const;
        double getPrice() const;

        void setModel(const std::string& model);
        void setManufacturer(const std::string& manufacturer);
        void setPrice(double price);
        void setYearOfManufacture(int year);

        virtual std::string toString() const;

        friend std::ostream& operator<<(std::ostream& os, const OfficeEquipment& equipment);
};

enum class Interface { Bluetooth, EthernetRJ45, NFC, RJ11, USB, USBTypeB, USBHost, WiFi };
enum class ApplicationArea { Home, Office };

#endif
