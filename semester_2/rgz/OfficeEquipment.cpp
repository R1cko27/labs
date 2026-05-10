#include "OfficeEquipment.h"
#include <sstream>

OfficeEquipment::OfficeEquipment() : model("Unknown"), manufacturer(Manufacturer::Unknown), yearOfManufacture(2000), price(0.0) {}

OfficeEquipment::OfficeEquipment(const std::string& model, Manufacturer manufacturer,
                                 int year, double price)
    : model(model), manufacturer(manufacturer), yearOfManufacture(year), price(price){
    // Валидация в конструкторе
    if (!validateModel(model)) {
        this->model = "Unknown";
    }
    if (!validateYear(year)) {
        this->yearOfManufacture = 2000;
    }
    if (!validatePrice(price)) {
        this->price = 3000.0;
    }
}

OfficeEquipment::~OfficeEquipment(){}

std::string OfficeEquipment::getModel() const { return model; }
std::string OfficeEquipment::getManufacturer() const { 
    switch (manufacturer) {
        case Manufacturer::Brother: return "Brother";
        case Manufacturer::Canon: return "Canon";
        case Manufacturer::DELI: return "DELI";
        case Manufacturer::Epson: return "Epson";
        case Manufacturer::HP: return "HP";
        case Manufacturer::Xiaomi: return "Xiaomi";
        case Manufacturer::Samsung: return "Samsung";
        case Manufacturer::Sharp: return "Sharp";
        case Manufacturer::Panasonic: return "Panasonic";
        case Manufacturer::Unknown: return "Unknown";
        default: return "Unknown";
    }
}
int OfficeEquipment::getYearOfManufacture() const { return yearOfManufacture; }
double OfficeEquipment::getPrice() const { return price; }

void OfficeEquipment::setModel(const std::string& model) { 
    if (validateModel(model)) this->model = model;
}
void OfficeEquipment::setManufacturer(Manufacturer manufacturer){
    this->manufacturer = manufacturer;
}
void OfficeEquipment::setPrice(double price){
    if (validatePrice(price)) this->price = price;
}
void OfficeEquipment::setYearOfManufacture(int year){
    if (validateYear(year)) this->yearOfManufacture = year;
}

bool OfficeEquipment::validateModel(const std::string& model) {
    return model.length() >= 3 && model.length() <= 100;
}

bool OfficeEquipment::validateYear(int year) {
    return year >= 1980 && year <= 2026;
}

bool OfficeEquipment::validatePrice(double price) {
    return price >= 3000.0 && price <= 200000.0;
}

std::string OfficeEquipment::toString() const{
    std::string manufacture;
    switch (manufacturer) {
        case Manufacturer::Brother: manufacture =  "Brother"; break;
        case Manufacturer::Canon: manufacture = "Canon"; break;
        case Manufacturer::DELI: manufacture = "DELI"; break;
        case Manufacturer::Epson: manufacture = "Epson"; break;
        case Manufacturer::HP: manufacture = "HP"; break;
        case Manufacturer::Xiaomi: manufacture = "Xiaomi"; break;
        case Manufacturer::Samsung: manufacture = "Samsung"; break;
        case Manufacturer::Sharp: manufacture = "Sharp"; break;
        case Manufacturer::Panasonic: manufacture = "Panasonic"; break;
        case Manufacturer::Unknown: manufacture = "Unknown"; break;
        default: manufacture = "Unknown"; break;
    }

    std::ostringstream oss;
    oss << "Model: " << model << "\n"
        << "Manufacturer: " << manufacture << "\n"
        << "Year of Manufacture: " << yearOfManufacture << "\n"
        << "Price: " << price << " RUB";
    return oss.str();
}

std::ostream& operator<<(std::ostream& os, const OfficeEquipment& equipment){
    os << equipment.toString();
    return os;
}