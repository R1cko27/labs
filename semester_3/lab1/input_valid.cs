// InputValidator.cs
using System;
using System.Collections.Generic;
using System.Linq;
using System.Diagnostics.CodeAnalysis;


namespace OfficeEquipmentLibrary
{
    [ExcludeFromCodeCoverage]
    public static class InputValidator
    {
        public static void ClearInput()
        {
            while (Console.KeyAvailable)
                Console.ReadKey(true);
        }

        public static string InputModel()
        {
            while (true)
            {
                string model = Console.ReadLine()?.Trim() ?? "";
                if (OfficeEquipment.ValidateModel(model))
                    return model;
                
                Console.WriteLine("ОШИБКА: Модель должна содержать от 3 до 100 символов!");
                Console.Write("Модель: ");
            }
        }

        public static int InputYear()
        {
            while (true)
            {
                Console.Write("Год выпуска: ");
                string input = Console.ReadLine()?.Trim() ?? "";
                
                if (!int.TryParse(input, out int year))
                {
                    Console.WriteLine("ОШИБКА: Введите число!");
                    continue;
                }
                
                if (OfficeEquipment.ValidateYear(year))
                    return year;
                
                Console.WriteLine("ОШИБКА: Год должен быть в пределах от 1980 до 2026!");
            }
        }

        public static double InputPrice()
        {
            while (true)
            {
                Console.Write("Цена: ");
                string input = Console.ReadLine()?.Trim() ?? "";
                
                if (!double.TryParse(input, out double price))
                {
                    Console.WriteLine("ОШИБКА: Введите число!");
                    continue;
                }
                
                if (OfficeEquipment.ValidatePrice(price))
                    return price;
                
                Console.WriteLine("ОШИБКА: Цена должна быть в пределах от 3000 до 200000 RUB!");
            }
        }

        public static int InputPrintSpeed()
        {
            while (true)
            {
                Console.Write("Скорость печати (стр/мин): ");
                string input = Console.ReadLine()?.Trim() ?? "";
                
                if (!int.TryParse(input, out int speed))
                {
                    Console.WriteLine("ОШИБКА: Введите число!");
                    continue;
                }
                
                if (Printer.ValidatePrintSpeed(speed))
                    return speed;
                
                Console.WriteLine("ОШИБКА: Скорость печати должна быть в пределах от 3 до 100 стр/мин!");
            }
        }

        public static int InputResolution()
        {
            while (true)
            {
                Console.Write("Разрешение печати (DPI): ");
                string input = Console.ReadLine()?.Trim() ?? "";
                
                if (!int.TryParse(input, out int resolution))
                {
                    Console.WriteLine("ОШИБКА: Введите число!");
                    continue;
                }
                
                if (Printer.ValidatePrintResolution(resolution))
                    return resolution;
                
                Console.WriteLine("ОШИБКА: Разрешение должно быть в пределах от 1200 до 8000 DPI и нацело делиться на 10!");
            }
        }

        public static int InputTransmissionSpeed()
        {
            while (true)
            {
                Console.Write("Скорость передачи (бит/с): ");
                string input = Console.ReadLine()?.Trim() ?? "";
                
                if (!int.TryParse(input, out int speed))
                {
                    Console.WriteLine("ОШИБКА: Введите число!");
                    continue;
                }
                
                if (Fax.ValidateTransmissionSpeed(speed))
                    return speed;
                
                Console.WriteLine("ОШИБКА: Скорость должна быть от 2400 до 33600 бит/с и соответствовать стандартным значениям!");
                Console.WriteLine("Стандартные значения: 2400, 4800, 7200, 9600, 12000, 14400, 16800, 19200, 21600, 24000, 26400, 28800, 31200, 33600");
            }
        }

        public static int InputScanResolution()
        {
            while (true)
            {
                Console.Write("Разрешение сканирования (DPI): ");
                string input = Console.ReadLine()?.Trim() ?? "";
                
                if (!int.TryParse(input, out int resolution))
                {
                    Console.WriteLine("ОШИБКА: Введите число!");
                    continue;
                }
                
                if (Fax.ValidateScanResolution(resolution))
                    return resolution;
                
                Console.WriteLine("ОШИБКА: Разрешение сканирования должно быть в пределах от 100 до 600 DPI!");
            }
        }

        public static int InputMemoryPages()
        {
            while (true)
            {
                Console.Write("Объем памяти (страниц): ");
                string input = Console.ReadLine()?.Trim() ?? "";
                
                if (!int.TryParse(input, out int pages))
                {
                    Console.WriteLine("ОШИБКА: Введите число!");
                    continue;
                }
                
                if (Fax.ValidateMemoryCapacity(pages))
                    return pages;
                
                Console.WriteLine("ОШИБКА: Объем памяти должен быть в пределах от 1 до 500 страниц!");
            }
        }

        public static Manufacturer InputManufacturer()
        {
            while (true)
            {
                Console.Write("Производитель (0-Brother,1-Canon,2-DELI,3-Epson,4-HP,5-Xiaomi,6-Samsung,7-Sharp,8-Panasonic): ");
                string input = Console.ReadLine()?.Trim() ?? "";
                
                if (!int.TryParse(input, out int choice))
                {
                    Console.WriteLine("ОШИБКА: Введите число!");
                    continue;
                }
                
                if (choice >= 0 && choice <= 8)
                    return (Manufacturer)choice;
                
                Console.WriteLine("ОШИБКА: Введите число от 0 до 8!");
            }
        }

        public static Interface InputInterfaces()
        {
            Interface interfaces = 0;
            
            Console.WriteLine("Выберите интерфейсы (вводите номера через пробел, 999 для завершения):");
            Console.WriteLine("0 - Bluetooth, 1 - Ethernet, 2 - NFC, 3 - RJ-11, 4 - USB, 5 - USB Type-B, 6 - USB хост, 7 - Wi-Fi");

            while (true)
            {
                string input = Console.ReadLine()?.Trim() ?? "";
                
                // Разбиваем строку на части по пробелам
                string[] parts = input.Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
                
                foreach (string part in parts)
                {
                    if (!int.TryParse(part, out int choice))
                    {
                        Console.WriteLine($"ОШИБКА: '{part}' не является числом!");
                        continue;
                    }
                    
                    if (choice == 999)
                        return interfaces;
                    
                    if (choice >= 0 && choice <= 7)
                        interfaces |= (Interface)(1 << choice);
                    else
                        Console.WriteLine($"ОШИБКА: {choice} - недопустимый номер! Введите число от 0 до 7 или 999 для завершения!");
                }
                
                // Если введено несколько чисел без 999, продолжаем ввод
                Console.WriteLine("Введите следующие интерфейсы или 999 для завершения:");
            }
        }

        public static ApplicationArea InputApplicationArea()
        {
            while (true)
            {
                Console.Write("Область применения (0 - для дома, 1 - для офиса): ");
                string input = Console.ReadLine()?.Trim() ?? "";
                
                if (!int.TryParse(input, out int choice))
                {
                    Console.WriteLine("ОШИБКА: Введите число!");
                    continue;
                }
                
                if (choice == 0 || choice == 1)
                    return (ApplicationArea)choice;
                
                Console.WriteLine("ОШИБКА: Введите 0 или 1!");
            }
        }

        public static PrinterColorType InputColorType()
        {
            while (true)
            {
                Console.Write("Тип печати (0 - черно-белый, 1 - цветной): ");
                string input = Console.ReadLine()?.Trim() ?? "";
                
                if (!int.TryParse(input, out int choice))
                {
                    Console.WriteLine("ОШИБКА: Введите число!");
                    continue;
                }
                
                if (choice == 0 || choice == 1)
                    return choice == 1 ? PrinterColorType.Color : PrinterColorType.BlackWhite;
                
                Console.WriteLine("ОШИБКА: Введите 0 или 1!");
            }
        }

        public static PaperFormat InputPaperFormat()
        {
            while (true)
            {
                Console.Write("Максимальный формат (0 - A2, 1 - A3, 2 - A4, 3 - A5): ");
                string input = Console.ReadLine()?.Trim() ?? "";
                
                if (!int.TryParse(input, out int choice))
                {
                    Console.WriteLine("ОШИБКА: Введите число!");
                    continue;
                }
                
                if (choice >= 0 && choice <= 3)
                    return (PaperFormat)choice;
                
                Console.WriteLine("ОШИБКА: Введите число от 0 до 3!");
            }
        }

        public static ConsumableType InputConsumableType()
        {
            while (true)
            {
                Console.Write("Тип расходников (0 - Toner, 1 - Ink, 2 - Ribbon, 3 - Wax, 4 - SolidInk): ");
                string input = Console.ReadLine()?.Trim() ?? "";
                
                if (!int.TryParse(input, out int choice))
                {
                    Console.WriteLine("ОШИБКА: Введите число!");
                    continue;
                }
                
                if (choice >= 0 && choice <= 4)
                    return (ConsumableType)choice;
                
                Console.WriteLine("ОШИБКА: Введите число от 0 до 4!");
            }
        }

        public static AutoFeederType InputAutoFeederType()
        {
            while (true)
            {
                Console.Write("Тип автоподатчика (0 - двусторонний, 1 - односторонний, 2 - нет): ");
                string input = Console.ReadLine()?.Trim() ?? "";
                
                if (!int.TryParse(input, out int choice))
                {
                    Console.WriteLine("ОШИБКА: Введите число!");
                    continue;
                }
                
                if (choice >= 0 && choice <= 2)
                    return (AutoFeederType)choice;
                
                Console.WriteLine("ОШИБКА: Введите число от 0 до 2!");
            }
        }

        // Метод для отображения списка оборудования
        public static void DisplayEquipmentList(List<OfficeEquipment> equipmentList)
        {
            Console.WriteLine("\n=== СПИСОК ОБОРУДОВАНИЯ ===");
            
            if (equipmentList == null || equipmentList.Count == 0)
            {
                Console.WriteLine("Список пуст!");
                return;
            }
            
            var baseItems = new List<OfficeEquipment>();
            var printerItems = new List<Printer>();
            var faxItems = new List<Fax>();

            foreach (var item in equipmentList)
            {
                if (item is Printer printer)
                    printerItems.Add(printer);
                else if (item is Fax fax)
                    faxItems.Add(fax);
                else
                    baseItems.Add(item);
            }

            // Сортировка по цене
            baseItems = baseItems.OrderBy(x => x.Price).ToList();
            printerItems = printerItems.OrderBy(x => x.Price).ToList();
            faxItems = faxItems.OrderBy(x => x.Price).ToList();

            foreach (var item in baseItems)
                Console.WriteLine(item.ToString() + "\n");
            
            foreach (var item in printerItems)
                Console.WriteLine(item.ToString() + "\n");
            
            foreach (var item in faxItems)
                Console.WriteLine(item.ToString() + "\n");
        }
    }
}