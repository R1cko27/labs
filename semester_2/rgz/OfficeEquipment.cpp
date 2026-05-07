#include "OfficeEquipment.h"
#include <sstream>

OfficeEquipment::OfficeEquipment() : model("Unknown"), manufacturer("Unknown"), yearOfManufacture(2000), price(0.0) {}

OfficeEquipment::OfficeEquipment(const std::string& model, const std::string& manufacturer,
                                 int year, double price)
    : model(model), manufacturer(manufacturer), yearOfManufacture(year), price(price){}

OfficeEquipment::~OfficeEquipment(){}

std::string OfficeEquipment::getModel() const { return model; }
std::string OfficeEquipment::getManufacturer() const { return manufacturer; }
int OfficeEquipment::getYearOfManufacture() const { return yearOfManufacture; }
double OfficeEquipment::getPrice() const { return price; }

void OfficeEquipment::setModel(const std::string& model) { this->model = model; }
void OfficeEquipment::setManufacturer(const std::string& manufacturer){
    this->manufacturer = manufacturer;
}
void OfficeEquipment::setPrice(double price){
    if (price >= 0.0) this->price = price;
}
void OfficeEquipment::setYearOfManufacture(int year){
    if (year > 1900 && year <= 2026) this->yearOfManufacture = year;
    

}

std::string OfficeEquipment::toString() const{
    std::ostringstream oss;
    oss << "Model: " << model << "\n"
        << "Manufacturer: " << manufacturer << "\n"
        << "Year of Manufacture: " << yearOfManufacture << "\n"
        << "Price: $" << price;
    return oss.str();
}

std::ostream& operator<<(std::ostream& os, const OfficeEquipment& equipment){
    os << equipment.toString();
    return os;
}