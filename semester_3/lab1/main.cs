// Program.cs
// #define STAGE_1
// #define STAGE_2
// #define STAGE_3

using System;
using System.Collections.Generic;
using System.Linq;
using System.Diagnostics.CodeAnalysis;

namespace OfficeEquipmentLibrary
{
    [ExcludeFromCodeCoverage]
    class Program
    {
        static void Main(string[] args)
        {
            Console.OutputEncoding = System.Text.Encoding.UTF8;
            Console.InputEncoding = System.Text.Encoding.UTF8;

            #if STAGE_1
                        RunStage1();
            #elif STAGE_2
                        RunStage2();
            #elif STAGE_3
                        RunStage3();
            #endif
        }

#if STAGE_1
        static void RunStage1()
        {
            // Создание объектов с различными интерфейсами
            Interface printerIfaces = Interface.WiFi | Interface.USB | Interface.Bluetooth;

            OfficeEquipment office = new OfficeEquipment();
            Console.WriteLine(office.ToString() + "\n\n");
            
            Printer printer1 = new Printer("LaserJet Pro", Manufacturer.HP, 2022, 299.99,
                                          PrinterColorType.Color, true, PaperFormat.A4,
                                          printerIfaces,
                                          ApplicationArea.Office, 35, 1200, ConsumableType.Toner);
            
            Printer printer2 = new Printer();
            
            Fax fax1 = new Fax("SuperG3", Manufacturer.Brother, 2021, 199.50,
                              14400, 600, 150, true, AutoFeederType.SingleSided, 
                              Interface.RJ11, ApplicationArea.Office);
            
            Fax fax2 = new Fax();

            Console.WriteLine(printer1.ToString() + "\n\n");
            Console.WriteLine(printer2.ToString() + "\n\n");
            Console.WriteLine(fax1.ToString() + "\n\n");
            Console.WriteLine(fax2.ToString() + "\n\n");

            // Модификация объектов
            printer1.PrintSpeedPPM = 40;
            printer2.Price = 249.99;
            fax1.MemoryCapacityPages = 200;
            fax2.TransmissionSpeedBPS = 33600;

            Console.WriteLine("\n=== ПОСЛЕ МОДИФИКАЦИИ ===\n");
            Console.WriteLine(printer1.ToString() + "\n\n");
            Console.WriteLine(printer2.ToString() + "\n\n");
            Console.WriteLine(fax1.ToString() + "\n\n");
            Console.WriteLine(fax2.ToString() + "\n\n");
        }
#endif

#if STAGE_2
        static void RunStage2()
        {
            // ПУНКТ 2.4
            OfficeEquipment basic1 = new OfficeEquipment("LaserJet Pro", Manufacturer.HP, 2020, 6500);
            OfficeEquipment basic2 = new OfficeEquipment("SuperG3", Manufacturer.Brother, 2023, 5500);

            Console.WriteLine(basic1.ToString() + "\n\n");
            Console.WriteLine(basic2.ToString() + "\n\n");

            // Демонстрация полиморфизма
            Printer printer1 = new Printer("LaserJet Pro", Manufacturer.HP, 2022, 299.99,
                                          PrinterColorType.Color, true, PaperFormat.A4,
                                          Interface.WiFi | Interface.USB, 
                                          ApplicationArea.Office, 35, 1200, ConsumableType.Toner);
            
            Fax fax1 = new Fax("SuperG3", Manufacturer.Brother, 2021, 199.50,
                              14400, 600, 150, true, AutoFeederType.SingleSided, 
                              Interface.RJ11, ApplicationArea.Office);

            OfficeEquipment basePtr = printer1;
            OfficeEquipment baseRef = fax1;

            Console.WriteLine(basePtr.ToString() + "\n\n");
            Console.WriteLine(baseRef.ToString() + "\n\n");

            OfficeEquipment basePtr2 = basic1;
            Console.WriteLine(basePtr2.ToString() + "\n\n");
        }
#endif

#if STAGE_3
        static void RunStage3()
        {
            List<OfficeEquipment> equipmentList = new List<OfficeEquipment>(); // объявление и создание динамического списка
            int choice;

            do
            {
                Console.WriteLine("\n=== МЕНЮ ===");
                Console.WriteLine("1. Добавить оборудование");
                Console.WriteLine("2. Добавить принтер");
                Console.WriteLine("3. Добавить факс");
                Console.WriteLine("4. Показать список");
                Console.WriteLine("5. Выход");
                Console.Write("\nВыбор: ");

                string input = Console.ReadLine()?.Trim() ?? "";
                
                if (!int.TryParse(input, out choice))
                {
                    Console.WriteLine("ОШИБКА: Введите число от 1 до 5!");
                    continue;
                }

                switch (choice)
                {
                    case 1:
                        AddOfficeEquipment(equipmentList);
                        break;

                    case 2:
                        AddPrinter(equipmentList);
                        break;

                    case 3:
                        AddFax(equipmentList);
                        break;

                    case 4:
                        InputValidator.DisplayEquipmentList(equipmentList);
                        break;

                    case 5:
                        equipmentList.Clear();
                        Console.WriteLine("Программа завершена, память очищена");
                        break;

                    default:
                        Console.WriteLine("ОШИБКА: Введите число от 1 до 5!");
                        break;
                }
            } while (choice != 5);
        }

        static void AddOfficeEquipment(List<OfficeEquipment> equipmentList)
        {
            Console.Write("Модель: ");
            string model = InputValidator.InputModel();

            Manufacturer manufacturer = InputValidator.InputManufacturer();
            int year = InputValidator.InputYear();
            double price = InputValidator.InputPrice();

            equipmentList.Add(new OfficeEquipment(model, manufacturer, year, price));
            Console.WriteLine($"Оборудование \"{model}\" успешно добавлено!");
        }

        static void AddPrinter(List<OfficeEquipment> equipmentList)
        {
            Console.Write("Модель: ");
            string model = InputValidator.InputModel();

            Manufacturer manufacturer = InputValidator.InputManufacturer();
            int year = InputValidator.InputYear();
            double price = InputValidator.InputPrice();

            PrinterColorType colorType = InputValidator.InputColorType();

            Console.Write("Двусторонняя печать (0 - нет, 1 - да): ");
            int duplexChoice;
            while (true)
            {
                string input = Console.ReadLine()?.Trim() ?? "";
                if (!int.TryParse(input, out duplexChoice) || (duplexChoice != 0 && duplexChoice != 1))
                {
                    Console.Write("ОШИБКА: Введите 0 или 1!\nДвусторонняя печать (0 - нет, 1 - да): ");
                    continue;
                }
                break;
            }
            bool duplexPrint = duplexChoice == 1;

            PaperFormat maxPaperFormat = InputValidator.InputPaperFormat();
            Interface interfaces = InputValidator.InputInterfaces();
            ApplicationArea applicationArea = InputValidator.InputApplicationArea();

            Console.Write("Скорость печати (стр/мин): ");
            int speedPPM = InputValidator.InputPrintSpeed();

            Console.Write("Разрешение печати (DPI): ");
            int resolutionDPI = InputValidator.InputResolution();

            ConsumableType consumable = InputValidator.InputConsumableType();

            equipmentList.Add(new Printer(model, manufacturer, year, price,
                                        colorType, duplexPrint, maxPaperFormat,
                                        interfaces, applicationArea,
                                        speedPPM, resolutionDPI, consumable));
            Console.WriteLine($"Принтер \"{model}\" успешно добавлен!");
        }

        static void AddFax(List<OfficeEquipment> equipmentList)
        {
            Console.Write("Модель: ");
            string model = InputValidator.InputModel();

            Manufacturer manufacturer = InputValidator.InputManufacturer();
            int year = InputValidator.InputYear();
            double price = InputValidator.InputPrice();

            Console.Write("Скорость передачи (бит/с): ");
            int transmissionSpeed = InputValidator.InputTransmissionSpeed();

            Console.Write("Разрешение сканирования (DPI): ");
            int scanResolution = InputValidator.InputScanResolution();

            Console.Write("Объем памяти (страниц): ");
            int memoryPages = InputValidator.InputMemoryPages();

            Console.Write("Наличие автоподатчика (0 - нет, 1 - да): ");
            int autoFeeder;
            while (true)
            {
                string input = Console.ReadLine()?.Trim() ?? "";
                if (!int.TryParse(input, out autoFeeder) || (autoFeeder != 0 && autoFeeder != 1))
                {
                    Console.Write("ОШИБКА: Введите 0 или 1!\nНаличие автоподатчика (0 - нет, 1 - да): ");
                    continue;
                }
                break;
            }
            bool hasAutoFeeder = autoFeeder == 1;

            AutoFeederType autoFeederType = InputValidator.InputAutoFeederType();
            Interface interfaces = InputValidator.InputInterfaces();
            ApplicationArea applicationArea = InputValidator.InputApplicationArea();

            equipmentList.Add(new Fax(model, manufacturer, year, price,
                                    transmissionSpeed, scanResolution, memoryPages,
                                    hasAutoFeeder, autoFeederType, interfaces, applicationArea));
            Console.WriteLine($"Факс \"{model}\" успешно добавлен!");
        }
#endif
    }
}