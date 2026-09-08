using Microsoft.VisualStudio.TestTools.UnitTesting;
using OfficeEquipmentLibrary;

namespace OfficeEquipmentTests
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void ValidateModel_Valid_ReturnsTrue()
        {
            bool result = OfficeEquipment.ValidateModel("HP LaserJet");
            Assert.IsTrue(result);
        }

        [TestMethod]
        public void ValidateModel_TooShort_ReturnsFalse()
        {
            bool result = OfficeEquipment.ValidateModel("H");
            Assert.IsFalse(result);
        }

        [TestMethod]
        public void ValidateModel_Empty_ReturnsFalse()
        {
            bool result = OfficeEquipment.ValidateModel("");
            Assert.IsFalse(result);
        }

        [TestMethod]
        public void ValidateYear_Valid_ReturnsTrue()
        {
            bool result = OfficeEquipment.ValidateYear(2022);
            Assert.IsTrue(result);
        }

        [TestMethod]
        public void ValidateYear_TooOld_ReturnsFalse()
        {
            bool result = OfficeEquipment.ValidateYear(1970);
            Assert.IsFalse(result);
        }

        [TestMethod]
        public void ValidatePrice_Valid_ReturnsTrue()
        {
            bool result = OfficeEquipment.ValidatePrice(50000);
            Assert.IsTrue(result);
        }

        [TestMethod]
        public void ValidatePrice_TooLow_ReturnsFalse()
        {
            bool result = OfficeEquipment.ValidatePrice(1000);
            Assert.IsFalse(result);
        }
        
        [TestMethod]
        public void OfficeEquipment_DefaultConstructor_Works()
        {
            OfficeEquipment eq = new OfficeEquipment();
            Assert.IsNotNull(eq);
            Assert.AreEqual("Unknown", eq.Model);
            Assert.AreEqual(2000, eq.YearOfManufacture);
            Assert.AreEqual(0, eq.Price);
        }

        [TestMethod]
        public void OfficeEquipment_ConstructorWithParams_Works()
        {
            OfficeEquipment eq = new OfficeEquipment("TestModel", Manufacturer.HP, 2022, 50000);
            Assert.AreEqual("TestModel", eq.Model);
            Assert.AreEqual(Manufacturer.HP, eq.Manufacturer);
            Assert.AreEqual(2022, eq.YearOfManufacture);
            Assert.AreEqual(50000, eq.Price);
        }

        [TestMethod]
        public void OfficeEquipment_ConstructorWithParams_InvalidModel_UsesDefault()
        {
            OfficeEquipment eq = new OfficeEquipment("A", Manufacturer.HP, 2022, 50000);
            Assert.AreEqual("Unknown", eq.Model);
        }

        [TestMethod]
        public void OfficeEquipment_ConstructorWithParams_InvalidYear_UsesDefault()
        {
            OfficeEquipment eq = new OfficeEquipment("Test", Manufacturer.HP, 1900, 50000);
            Assert.AreEqual(2000, eq.YearOfManufacture);
        }

        [TestMethod]
        public void OfficeEquipment_ConstructorWithParams_InvalidPrice_UsesDefault()
        {
            OfficeEquipment eq = new OfficeEquipment("Test", Manufacturer.HP, 2022, 100);
            Assert.AreEqual(3000, eq.Price);
        }

        [TestMethod]
        public void OfficeEquipment_SetModel_Valid_Works()
        {
            OfficeEquipment eq = new OfficeEquipment();
            eq.Model = "NewModel";
            Assert.AreEqual("NewModel", eq.Model);
        }

        [TestMethod]
        public void OfficeEquipment_SetModel_Invalid_Ignored()
        {
            OfficeEquipment eq = new OfficeEquipment();
            eq.Model = "A";
            Assert.AreEqual("Unknown", eq.Model);
        }

        [TestMethod]
        public void OfficeEquipment_SetYear_Valid_Works()
        {
            OfficeEquipment eq = new OfficeEquipment();
            eq.YearOfManufacture = 2023;
            Assert.AreEqual(2023, eq.YearOfManufacture);
        }

        [TestMethod]
        public void OfficeEquipment_SetYear_Invalid_Ignored()
        {
            OfficeEquipment eq = new OfficeEquipment();
            eq.YearOfManufacture = 1900;
            Assert.AreEqual(2000, eq.YearOfManufacture);
        }

        [TestMethod]
        public void OfficeEquipment_SetPrice_Valid_Works()
        {
            OfficeEquipment eq = new OfficeEquipment();
            eq.Price = 75000;
            Assert.AreEqual(75000, eq.Price);
        }

        [TestMethod]
        public void OfficeEquipment_SetPrice_Invalid_Ignored()
        {
            OfficeEquipment eq = new OfficeEquipment();
            eq.Price = 100;
            Assert.AreEqual(0, eq.Price);
        }

        [TestMethod]
        public void OfficeEquipment_SetManufacturer_Works()
        {
            OfficeEquipment eq = new OfficeEquipment();
            eq.Manufacturer = Manufacturer.Canon;
            Assert.AreEqual(Manufacturer.Canon, eq.Manufacturer);
        }

        [TestMethod]
        public void OfficeEquipment_ToString_ReturnsString()
        {
            OfficeEquipment eq = new OfficeEquipment("TestModel", Manufacturer.HP, 2022, 50000);
            string result = eq.ToString();
            StringAssert.Contains(result, "TestModel");
            StringAssert.Contains(result, "HP");
            StringAssert.Contains(result, "2022");
            StringAssert.Contains(result, "50000");
        }

        [TestMethod]
        public void OfficeEquipment_ManufacturerName_ReturnsCorrectString()
        {
            OfficeEquipment eq = new OfficeEquipment();
            eq.Manufacturer = Manufacturer.Brother;
            Assert.AreEqual("Brother", eq.ManufacturerName);
            
            eq.Manufacturer = Manufacturer.Canon;
            Assert.AreEqual("Canon", eq.ManufacturerName);
            
            eq.Manufacturer = Manufacturer.HP;
            Assert.AreEqual("HP", eq.ManufacturerName);
            
            eq.Manufacturer = Manufacturer.Unknown;
            Assert.AreEqual("Unknown", eq.ManufacturerName);
        }
        // ТЕСТЫ ДЛЯ PRINTER

        [TestMethod]
        public void ValidatePrintSpeed_Valid_ReturnsTrue()
        {
            bool result = Printer.ValidatePrintSpeed(35);
            Assert.IsTrue(result);
        }

        [TestMethod]
        public void ValidatePrintSpeed_TooHigh_ReturnsFalse()
        {
            bool result = Printer.ValidatePrintSpeed(150);
            Assert.IsFalse(result);
        }

        [TestMethod]
        public void ValidatePrintResolution_Valid_ReturnsTrue()
        {
            bool result = Printer.ValidatePrintResolution(2400);
            Assert.IsTrue(result);
        }

        [TestMethod]
        public void ValidatePrintResolution_NotDivisibleBy10_ReturnsFalse()
        {
            bool result = Printer.ValidatePrintResolution(2501);
            Assert.IsFalse(result);
        }

        [TestMethod]
        public void ValidatePrintResolution_TooLow_ReturnsFalse()
        {
            bool result = Printer.ValidatePrintResolution(100);
            Assert.IsFalse(result);
        }

        [TestMethod]
        public void Printer_DefaultConstructor_Works()
        {
            Printer printer = new Printer();
            Assert.IsNotNull(printer);
            Assert.AreEqual("Unknown", printer.Model);
        }

        [TestMethod]
        public void Printer_SetPrintSpeed_Valid_Works()
        {
            Printer printer = new Printer();
            printer.PrintSpeedPPM = 50;
            Assert.AreEqual(50, printer.PrintSpeedPPM);
        }

        [TestMethod]
        public void Printer_SetPrintSpeed_Invalid_Ignored()
        {
            Printer printer = new Printer();
            printer.PrintSpeedPPM = 200;
            Assert.AreEqual(20, printer.PrintSpeedPPM);
        }

        [TestMethod]
        public void Printer_ConstructorWithParams_Works()
        {
            Printer printer = new Printer("HP Laser", Manufacturer.HP, 2022, 50000,
                                        PrinterColorType.Color, true, PaperFormat.A4,
                                        Interface.USB | Interface.WiFi,
                                        ApplicationArea.Office, 35, 2400,
                                        ConsumableType.Toner);
            
            Assert.AreEqual("HP Laser", printer.Model);
            Assert.AreEqual(Manufacturer.HP, printer.Manufacturer);
            Assert.AreEqual(2022, printer.YearOfManufacture);
            Assert.AreEqual(50000, printer.Price);
            Assert.AreEqual(PrinterColorType.Color, printer.ColorType);
            Assert.IsTrue(printer.DuplexPrint);
            Assert.AreEqual(PaperFormat.A4, printer.MaxPaperFormat);
            Assert.AreEqual(ApplicationArea.Office, printer.ApplicationArea);
            Assert.AreEqual(35, printer.PrintSpeedPPM);
            Assert.AreEqual(2400, printer.PrintResolutionDPI);
            Assert.AreEqual(ConsumableType.Toner, printer.ConsumableType);
        }

        [TestMethod]
        public void Printer_ConstructorWithParams_InvalidSpeed_UsesDefault()
        {
            Printer printer = new Printer("HP", Manufacturer.HP, 2022, 50000,
                                        PrinterColorType.Color, true, PaperFormat.A4,
                                        Interface.USB, ApplicationArea.Office,
                                        200, 2400, ConsumableType.Toner);
            Assert.AreEqual(20, printer.PrintSpeedPPM);
        }

        [TestMethod]
        public void Printer_ConstructorWithParams_InvalidResolution_UsesDefault()
        {
            Printer printer = new Printer("HP", Manufacturer.HP, 2022, 50000,
                                        PrinterColorType.Color, true, PaperFormat.A4,
                                        Interface.USB, ApplicationArea.Office,
                                        35, 100, ConsumableType.Toner);
            Assert.AreEqual(1200, printer.PrintResolutionDPI);
        }

        [TestMethod]
        public void Printer_SetColorType_Works()
        {
            Printer printer = new Printer();
            printer.ColorType = PrinterColorType.Color;
            Assert.AreEqual(PrinterColorType.Color, printer.ColorType);
        }

        [TestMethod]
        public void Printer_SetDuplexPrint_Works()
        {
            Printer printer = new Printer();
            printer.DuplexPrint = true;
            Assert.IsTrue(printer.DuplexPrint);
            
            printer.DuplexPrint = false;
            Assert.IsFalse(printer.DuplexPrint);
        }

        [TestMethod]
        public void Printer_SetMaxPaperFormat_Works()
        {
            Printer printer = new Printer();
            printer.MaxPaperFormat = PaperFormat.A3;
            Assert.AreEqual(PaperFormat.A3, printer.MaxPaperFormat);
        }

        [TestMethod]
        public void Printer_SetInterfaces_Works()
        {
            Printer printer = new Printer();
            printer.Interfaces = Interface.USB | Interface.WiFi;
            Assert.AreEqual(Interface.USB | Interface.WiFi, printer.Interfaces);
        }

        [TestMethod]
        public void Printer_SetApplicationArea_Works()
        {
            Printer printer = new Printer();
            printer.ApplicationArea = ApplicationArea.Office;
            Assert.AreEqual(ApplicationArea.Office, printer.ApplicationArea);
        }

        [TestMethod]
        public void Printer_SetPrintResolution_Valid_Works()
        {
            Printer printer = new Printer();
            printer.PrintResolutionDPI = 2400;
            Assert.AreEqual(2400, printer.PrintResolutionDPI);
        }

        [TestMethod]
        public void Printer_SetPrintResolution_Invalid_Ignored()
        {
            Printer printer = new Printer();
            printer.PrintResolutionDPI = 100;
            Assert.AreEqual(3000, printer.PrintResolutionDPI);
        }

        [TestMethod]
        public void Printer_SetConsumableType_Works()
        {
            Printer printer = new Printer();
            printer.ConsumableType = ConsumableType.Ink;
            Assert.AreEqual(ConsumableType.Ink, printer.ConsumableType);
        }

        [TestMethod]
        public void Printer_ToString_ContainsAllFields()
        {
            Printer printer = new Printer("HP Laser", Manufacturer.HP, 2022, 50000,
                                        PrinterColorType.Color, true, PaperFormat.A4,
                                        Interface.USB | Interface.WiFi,
                                        ApplicationArea.Office, 35, 2400,
                                        ConsumableType.Toner);
            
            string result = printer.ToString();
            StringAssert.Contains(result, "HP Laser");
            StringAssert.Contains(result, "HP");
            StringAssert.Contains(result, "2022");
            StringAssert.Contains(result, "50000");
            StringAssert.Contains(result, "цветная");
            StringAssert.Contains(result, "A4");
            StringAssert.Contains(result, "35");
            StringAssert.Contains(result, "2400");
            StringAssert.Contains(result, "Тонер");
            StringAssert.Contains(result, "USB");
        }
        public void Printer_ToStringOverride_Works()
        {
            var printer = new Printer("HP", Manufacturer.HP, 2022, 50000,
                                    PrinterColorType.Color, true, PaperFormat.A4,
                                    Interface.USB, ApplicationArea.Office,
                                    35, 2400, ConsumableType.Toner);
            
            string result = printer.ToStringOverride();
            Assert.IsNotNull(result);
            StringAssert.Contains(result, "HP");
            StringAssert.Contains(result, "35");
        }

        // ===== ТЕСТЫ ДЛЯ FAX =====

        [TestMethod]
        public void ValidateTransmissionSpeed_Valid_ReturnsTrue()
        {
            bool result = Fax.ValidateTransmissionSpeed(14400);
            Assert.IsTrue(result);
        }

        [TestMethod]
        public void ValidateTransmissionSpeed_Invalid_ReturnsFalse()
        {
            bool result = Fax.ValidateTransmissionSpeed(10050);
            Assert.IsFalse(result);
        }

        [TestMethod]
        public void ValidateScanResolution_Valid_ReturnsTrue()
        {
            bool result = Fax.ValidateScanResolution(600);
            Assert.IsTrue(result);
        }

        [TestMethod]
        public void ValidateScanResolution_Invalid_ReturnsFalse()
        {
            bool result = Fax.ValidateScanResolution(50);
            Assert.IsFalse(result);
        }

        [TestMethod]
        public void ValidateMemoryCapacity_Valid_ReturnsTrue()
        {
            bool result = Fax.ValidateMemoryCapacity(150);
            Assert.IsTrue(result);
        }

        [TestMethod]
        public void ValidateMemoryCapacity_Invalid_ReturnsFalse()
        {
            bool result = Fax.ValidateMemoryCapacity(600);
            Assert.IsFalse(result);
        }

        [TestMethod]
        public void Fax_DefaultConstructor_Works()
        {
            Fax fax = new Fax();
            Assert.IsNotNull(fax);
            Assert.AreEqual(14400, fax.TransmissionSpeedBPS);
        }

        [TestMethod]
        public void Fax_SetTransmissionSpeed_Valid_Works()
        {
            Fax fax = new Fax();
            fax.TransmissionSpeedBPS = 33600;
            Assert.AreEqual(33600, fax.TransmissionSpeedBPS);
        }

        [TestMethod]
        public void Fax_SetTransmissionSpeed_Invalid_Ignored()
        {
            Fax fax = new Fax();
            fax.TransmissionSpeedBPS = 10050;
            Assert.AreEqual(14400, fax.TransmissionSpeedBPS);
        }

        [TestMethod]
        public void Fax_ConstructorWithParams_Works()
        {
            Fax fax = new Fax("SuperFax", Manufacturer.Brother, 2021, 15000,
                            14400, 600, 150, true, AutoFeederType.SingleSided,
                            Interface.RJ11 | Interface.USB,
                            ApplicationArea.Office);
            
            Assert.AreEqual("SuperFax", fax.Model);
            Assert.AreEqual(Manufacturer.Brother, fax.Manufacturer);
            Assert.AreEqual(2021, fax.YearOfManufacture);
            Assert.AreEqual(15000, fax.Price);
            Assert.AreEqual(14400, fax.TransmissionSpeedBPS);
            Assert.AreEqual(600, fax.ScanResolutionDPI);
            Assert.AreEqual(150, fax.MemoryCapacityPages);
            Assert.IsTrue(fax.HasAutomaticFeeder);
            Assert.AreEqual(AutoFeederType.SingleSided, fax.AutoFeederType);
            Assert.AreEqual(ApplicationArea.Office, fax.ApplicationArea);
        }

        [TestMethod]
        public void Fax_ConstructorWithParams_InvalidSpeed_UsesDefault()
        {
            Fax fax = new Fax("Fax", Manufacturer.Brother, 2021, 15000,
                            10050, 600, 150, true, AutoFeederType.SingleSided,
                            Interface.RJ11, ApplicationArea.Office);
            Assert.AreEqual(14400, fax.TransmissionSpeedBPS);
        }

        [TestMethod]
        public void Fax_ConstructorWithParams_InvalidResolution_UsesDefault()
        {
            Fax fax = new Fax("Fax", Manufacturer.Brother, 2021, 15000,
                            14400, 50, 150, true, AutoFeederType.SingleSided,
                            Interface.RJ11, ApplicationArea.Office);
            Assert.AreEqual(200, fax.ScanResolutionDPI);
        }

        [TestMethod]
        public void Fax_ConstructorWithParams_InvalidMemory_UsesDefault()
        {
            Fax fax = new Fax("Fax", Manufacturer.Brother, 2021, 15000,
                            14400, 600, 600, true, AutoFeederType.SingleSided,
                            Interface.RJ11, ApplicationArea.Office);
            Assert.AreEqual(100, fax.MemoryCapacityPages);
        }

        [TestMethod]
        public void Fax_SetAutoFeederType_Works()
        {
            Fax fax = new Fax();
            fax.AutoFeederType = AutoFeederType.DoubleSided;
            Assert.AreEqual(AutoFeederType.DoubleSided, fax.AutoFeederType);
            
            fax.AutoFeederType = AutoFeederType.None;
            Assert.AreEqual(AutoFeederType.None, fax.AutoFeederType);
        }

        [TestMethod]
        public void Fax_SetInterfaces_Works()
        {
            Fax fax = new Fax();
            fax.Interfaces = Interface.RJ11 | Interface.USB;
            Assert.AreEqual(Interface.RJ11 | Interface.USB, fax.Interfaces);
        }

        [TestMethod]
        public void Fax_SetApplicationArea_Works()
        {
            Fax fax = new Fax();
            fax.ApplicationArea = ApplicationArea.Home;
            Assert.AreEqual(ApplicationArea.Home, fax.ApplicationArea);
        }

        [TestMethod]
        public void Fax_SetScanResolution_Valid_Works()
        {
            Fax fax = new Fax();
            fax.ScanResolutionDPI = 300;
            Assert.AreEqual(300, fax.ScanResolutionDPI);
        }

        [TestMethod]
        public void Fax_SetScanResolution_Invalid_Ignored()
        {
            Fax fax = new Fax();
            fax.ScanResolutionDPI = 50;
            Assert.AreEqual(203, fax.ScanResolutionDPI);
        }

        [TestMethod]
        public void Fax_SetMemoryCapacity_Valid_Works()
        {
            Fax fax = new Fax();
            fax.MemoryCapacityPages = 200;
            Assert.AreEqual(200, fax.MemoryCapacityPages);
        }

        [TestMethod]
        public void Fax_SetMemoryCapacity_Invalid_Ignored()
        {
            Fax fax = new Fax();
            fax.MemoryCapacityPages = 600;
            Assert.AreEqual(100, fax.MemoryCapacityPages);
        }

        [TestMethod]
        public void Fax_SetHasAutomaticFeeder_Works()
        {
            Fax fax = new Fax();
            fax.HasAutomaticFeeder = false;
            Assert.IsFalse(fax.HasAutomaticFeeder);
            
            fax.HasAutomaticFeeder = true;
            Assert.IsTrue(fax.HasAutomaticFeeder);
        }

        [TestMethod]
        public void Fax_GetInterfaceString_Works()
        {
            // Создаем Fax с USB интерфейсом
            Fax fax = new Fax("TestFax", Manufacturer.Brother, 2022, 15000,
                            14400, 600, 150, true, AutoFeederType.SingleSided,
                            Interface.USB | Interface.WiFi,  // ← Добавляем USB
                            ApplicationArea.Office);
            
            string result = fax.ToString();
            StringAssert.Contains(result, "USB");
            StringAssert.Contains(result, "Wi-Fi");
        }

        [TestMethod]
        public void Fax_ToString_ContainsAllFields()
        {
            Fax fax = new Fax("SuperFax", Manufacturer.Brother, 2021, 15000,
                            14400, 600, 150, true, AutoFeederType.SingleSided,
                            Interface.RJ11, ApplicationArea.Office);
            
            string result = fax.ToString();
            StringAssert.Contains(result, "SuperFax");
            StringAssert.Contains(result, "Brother");
            StringAssert.Contains(result, "2021");
            StringAssert.Contains(result, "15000");
            StringAssert.Contains(result, "14400");
            StringAssert.Contains(result, "600");
            StringAssert.Contains(result, "150");
            StringAssert.Contains(result, "одностороннее");
            StringAssert.Contains(result, "RJ-11");
        }
        // ===== ТЕСТЫ ДЛЯ INTERFACE (ФЛАГИ) =====

        [TestMethod]
        public void Interface_HasInterface_ReturnsTrue()
        {
            Interface iface = Interface.USB | Interface.WiFi;
            bool result = OfficeEquipment.HasInterface(iface, Interface.USB);
            Assert.IsTrue(result);
        }

        [TestMethod]
        public void Interface_HasInterface_ReturnsFalse()
        {
            Interface iface = Interface.USB | Interface.WiFi;
            bool result = OfficeEquipment.HasInterface(iface, Interface.Bluetooth);
            Assert.IsFalse(result);
        }

        [TestMethod]
        public void Interface_AddInterface_Works()
        {
            Interface iface = Interface.USB;
            Interface result = OfficeEquipment.AddInterface(iface, Interface.WiFi);
            Assert.IsTrue(OfficeEquipment.HasInterface(result, Interface.WiFi));
        }

        [TestMethod]
        public void Interface_RemoveInterface_Works()
        {
            Interface iface = Interface.USB | Interface.WiFi;
            Interface result = OfficeEquipment.RemoveInterface(iface, Interface.WiFi);
            Assert.IsFalse(OfficeEquipment.HasInterface(result, Interface.WiFi));
            Assert.IsTrue(OfficeEquipment.HasInterface(result, Interface.USB));
        }
        [TestMethod]
        public void ValidatePrintSpeed_Valid_MinValue_ReturnsTrue()
        {
            bool result = Printer.ValidatePrintSpeed(3);
            Assert.IsTrue(result);
        }

        [TestMethod]
        public void ValidatePrintSpeed_Valid_MaxValue_ReturnsTrue()
        {
            bool result = Printer.ValidatePrintSpeed(100);
            Assert.IsTrue(result);
        }

        [TestMethod]
        public void ValidatePrintSpeed_Invalid_BelowMin_ReturnsFalse()
        {
            bool result = Printer.ValidatePrintSpeed(2);
            Assert.IsFalse(result);
        }

        [TestMethod]
        public void ValidatePrintSpeed_Invalid_AboveMax_ReturnsFalse()
        {
            bool result = Printer.ValidatePrintSpeed(101);
            Assert.IsFalse(result);
        }

        [TestMethod]
        public void ValidatePrintResolution_Valid_MinValue_ReturnsTrue()
        {
            bool result = Printer.ValidatePrintResolution(1200);
            Assert.IsTrue(result);
        }

        [TestMethod]
        public void ValidatePrintResolution_Valid_MaxValue_ReturnsTrue()
        {
            bool result = Printer.ValidatePrintResolution(8000);
            Assert.IsTrue(result);
        }

        [TestMethod]
        public void ValidatePrintResolution_Invalid_BelowMin_ReturnsFalse()
        {
            bool result = Printer.ValidatePrintResolution(1190);
            Assert.IsFalse(result);
        }

        [TestMethod]
        public void ValidatePrintResolution_Invalid_AboveMax_ReturnsFalse()
        {
            bool result = Printer.ValidatePrintResolution(8010);
            Assert.IsFalse(result);
        }

        [TestMethod]
        public void ValidateTransmissionSpeed_Valid_MinValue_ReturnsTrue()
        {
            bool result = Fax.ValidateTransmissionSpeed(2400);
            Assert.IsTrue(result);
        }

        [TestMethod]
        public void ValidateTransmissionSpeed_Valid_MaxValue_ReturnsTrue()
        {
            bool result = Fax.ValidateTransmissionSpeed(33600);
            Assert.IsTrue(result);
        }

        [TestMethod]
        public void ValidateTransmissionSpeed_Invalid_BelowMin_ReturnsFalse()
        {
            bool result = Fax.ValidateTransmissionSpeed(2000);
            Assert.IsFalse(result);
        }

        [TestMethod]
        public void ValidateTransmissionSpeed_Invalid_AboveMax_ReturnsFalse()
        {
            bool result = Fax.ValidateTransmissionSpeed(34000);
            Assert.IsFalse(result);
        }

        [TestMethod]
        public void ValidateScanResolution_Valid_MinValue_ReturnsTrue()
        {
            bool result = Fax.ValidateScanResolution(100);
            Assert.IsTrue(result);
        }

        [TestMethod]
        public void ValidateScanResolution_Valid_MaxValue_ReturnsTrue()
        {
            bool result = Fax.ValidateScanResolution(600);
            Assert.IsTrue(result);
        }

        [TestMethod]
        public void ValidateScanResolution_Invalid_BelowMin_ReturnsFalse()
        {
            bool result = Fax.ValidateScanResolution(99);
            Assert.IsFalse(result);
        }

        [TestMethod]
        public void ValidateScanResolution_Invalid_AboveMax_ReturnsFalse()
        {
            bool result = Fax.ValidateScanResolution(601);
            Assert.IsFalse(result);
        }

        [TestMethod]
        public void ValidateMemoryCapacity_Valid_MinValue_ReturnsTrue()
        {
            bool result = Fax.ValidateMemoryCapacity(1);
            Assert.IsTrue(result);
        }

        [TestMethod]
        public void ValidateMemoryCapacity_Valid_MaxValue_ReturnsTrue()
        {
            bool result = Fax.ValidateMemoryCapacity(500);
            Assert.IsTrue(result);
        }

        [TestMethod]
        public void ValidateMemoryCapacity_Invalid_BelowMin_ReturnsFalse()
        {
            bool result = Fax.ValidateMemoryCapacity(0);
            Assert.IsFalse(result);
        }

        [TestMethod]
        public void ValidateMemoryCapacity_Invalid_AboveMax_ReturnsFalse()
        {
            bool result = Fax.ValidateMemoryCapacity(501);
            Assert.IsFalse(result);
        }

        [TestMethod]
        public void ValidateYear_Valid_MinValue_ReturnsTrue()
        {
            bool result = OfficeEquipment.ValidateYear(1980);
            Assert.IsTrue(result);
        }

        [TestMethod]
        public void ValidateYear_Valid_MaxValue_ReturnsTrue()
        {
            bool result = OfficeEquipment.ValidateYear(2026);
            Assert.IsTrue(result);
        }

        [TestMethod]
        public void ValidateYear_Invalid_BelowMin_ReturnsFalse()
        {
            bool result = OfficeEquipment.ValidateYear(1979);
            Assert.IsFalse(result);
        }

        [TestMethod]
        public void ValidateYear_Invalid_AboveMax_ReturnsFalse()
        {
            bool result = OfficeEquipment.ValidateYear(2027);
            Assert.IsFalse(result);
        }

        [TestMethod]
        public void ValidatePrice_Valid_MinValue_ReturnsTrue()
        {
            bool result = OfficeEquipment.ValidatePrice(3000);
            Assert.IsTrue(result);
        }

        [TestMethod]
        public void ValidatePrice_Valid_MaxValue_ReturnsTrue()
        {
            bool result = OfficeEquipment.ValidatePrice(200000);
            Assert.IsTrue(result);
        }

        [TestMethod]
        public void ValidatePrice_Invalid_BelowMin_ReturnsFalse()
        {
            bool result = OfficeEquipment.ValidatePrice(2999.99);
            Assert.IsFalse(result);
        }

        [TestMethod]
        public void ValidatePrice_Invalid_AboveMax_ReturnsFalse()
        {
            bool result = OfficeEquipment.ValidatePrice(200000.01);
            Assert.IsFalse(result);
        }
    }
}