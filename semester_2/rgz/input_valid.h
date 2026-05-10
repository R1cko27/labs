#ifndef INPUT_VALID_H
#define INPUT_VALID_H

#include <iostream>
#include <memory>
#include <list>
#include "OfficeEquipment.h"
#include "Printer.h"
#include "Fax.h"


void clearInput();
std::string inputModel();
int inputYear();
double inputPrice();
int inputPrintSpeed();
int inputResolution();
int inputTransmissionSpeed();
int inputScanResolution();
int inputMemoryPages();

Manufacturer inputManufacturer();
Interface inputInterfaces();
ApplicationArea inputApplicationArea();
PrinterColorType inputColorType();
PaperFormat inputPaperFormat();
ConsumableType inputConsumableType();
AutoFeederType inputAutoFeederType();

void displayEquipmentList(const std::list<std::unique_ptr<OfficeEquipment>>& equipmentList);

#endif