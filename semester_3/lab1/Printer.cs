// Printer.cs
using System;

namespace OfficeEquipmentLibrary
{
    public enum PrinterColorType
    {
        Color,
        BlackWhite
    }

    public enum PaperFormat
    {
        A2,
        A3,
        A4,
        A5
    }

    public enum ConsumableType // Расходники
    {
        Toner,
        Ink,
        Ribbon,
        Wax,
        SolidInk
    }

    public class Printer : OfficeEquipment
    {
        private PrinterColorType colorType;     // Тип печати
        private bool duplexPrint;               // Наличие двусторонней печати
        private PaperFormat maxPaperFormat;     // Максимальный формат бумаги
        private Interface interfaces;           // Тип подключения
        private ApplicationArea applicationArea; // Область применения
        private int printSpeedPPM;              // Скорость печати в страницах в минуту
        private int printResolutionDPI;         // Разрешение печати
        private ConsumableType consumableType;  // Тип расходников

        public Printer()
            : base()
        {
            colorType = PrinterColorType.BlackWhite;
            duplexPrint = false;
            maxPaperFormat = PaperFormat.A4;
            interfaces = Interface.USB;
            applicationArea = ApplicationArea.Home;
            printSpeedPPM = 20;
            printResolutionDPI = 3000;
            consumableType = ConsumableType.Toner;
        }

        public Printer(string model, Manufacturer manufacturer, int year, double price,
                       PrinterColorType colorType, bool duplexPrint, PaperFormat maxPaperFormat,
                       Interface interfaces, ApplicationArea applicationArea,
                       int speedPPM, int resolutionDPI, ConsumableType consumable)
            : base(model, manufacturer, year, price)
        {
            this.colorType = colorType;
            this.duplexPrint = duplexPrint;
            this.maxPaperFormat = maxPaperFormat;
            this.interfaces = interfaces;
            this.applicationArea = applicationArea;
            this.consumableType = consumable;

            // Валидация специфичных для принтера полей
            if (!ValidatePrintSpeed(speedPPM))
                this.printSpeedPPM = 20;
            else
                this.printSpeedPPM = speedPPM;

            if (!ValidatePrintResolution(resolutionDPI))
                this.printResolutionDPI = 1200;
            else
                this.printResolutionDPI = resolutionDPI;
        }

        // Свойства
        public PrinterColorType ColorType
        {
            get { return colorType; }
            set { colorType = value; }
        }

        public bool DuplexPrint
        {
            get { return duplexPrint; }
            set { duplexPrint = value; }
        }

        public PaperFormat MaxPaperFormat
        {
            get { return maxPaperFormat; }
            set { maxPaperFormat = value; }
        }

        public Interface Interfaces
        {
            get { return interfaces; }
            set { interfaces = value; }
        }

        public ApplicationArea ApplicationArea
        {
            get { return applicationArea; }
            set { applicationArea = value; }
        }

        public int PrintSpeedPPM
        {
            get { return printSpeedPPM; }
            set
            {
                if (ValidatePrintSpeed(value))
                    printSpeedPPM = value;
            }
        }

        public int PrintResolutionDPI
        {
            get { return printResolutionDPI; }
            set
            {
                if (ValidatePrintResolution(value))
                    printResolutionDPI = value;
            }
        }

        public ConsumableType ConsumableType
        {
            get { return consumableType; }
            set { consumableType = value; }
        }

        // Статические методы валидации
        public static bool ValidatePrintSpeed(int speed)
        {
            return speed >= 3 && speed <= 100;
        }

        public static bool ValidatePrintResolution(int resolution)
        {
            return resolution >= 1200 && resolution <= 8000 && resolution % 10 == 0;
        }

        public override string ToStringOverride()
        {
            string paperFormatStr = maxPaperFormat switch
            {
                PaperFormat.A2 => "A2",
                PaperFormat.A3 => "A3",
                PaperFormat.A4 => "A4",
                PaperFormat.A5 => "A5",
                _ => "Неизвестно"
            };

            string interfaceStr = GetInterfaceString(interfaces);
            if (string.IsNullOrEmpty(interfaceStr))
                interfaceStr = "Не указаны";

            string areaStr = applicationArea == ApplicationArea.Home ? "для дома" : "для офиса";

            string consumableStr = consumableType switch
            {
                ConsumableType.Toner => "Тонер",
                ConsumableType.Ink => "Чернила",
                ConsumableType.Ribbon => "Лента",
                ConsumableType.Wax => "Воск",
                ConsumableType.SolidInk => "Твердые чернила",
                _ => "Неизвестно"
            };

            string colorTypeStr = colorType == PrinterColorType.Color ? "цветная" : "черно-белая";

            return $"Модель: {Model}\n" +
                   $"Производитель: {ManufacturerName}\n" +
                   $"Год выпуска: {YearOfManufacture}\n" +
                   $"Цена: {Price} RUB\n" +
                   $"Тип печати: {colorTypeStr}\n" +
                   $"Двусторонняя печать: {(duplexPrint ? "Да" : "Нет")}\n" +
                   $"Максимальный формат: {paperFormatStr}\n" +
                   $"Скорость печати: {printSpeedPPM} стр/мин\n" +
                   $"Разрешение печати: {printResolutionDPI} DPI\n" +
                   $"Тип расходников: {consumableStr}\n" +
                   $"Интерфейс: {interfaceStr}\n" +
                   $"Область применения: {areaStr}";
        }

        // Вспомогательный метод для форматирования интерфейсов
        private string GetInterfaceString(Interface iface)
        {
            var interfaces = new System.Collections.Generic.List<string>();

            if (HasInterface(iface, Interface.Bluetooth)) interfaces.Add("Bluetooth");
            if (HasInterface(iface, Interface.EthernetRJ45)) interfaces.Add("Ethernet (RJ-45)");
            if (HasInterface(iface, Interface.NFC)) interfaces.Add("NFC");
            if (HasInterface(iface, Interface.RJ11)) interfaces.Add("RJ-11");
            if (HasInterface(iface, Interface.USB)) interfaces.Add("USB");
            if (HasInterface(iface, Interface.USBTypeB)) interfaces.Add("USB Type-B");
            if (HasInterface(iface, Interface.USBHost)) interfaces.Add("USB хост");
            if (HasInterface(iface, Interface.WiFi)) interfaces.Add("Wi-Fi");

            return string.Join(", ", interfaces);
        }

        private new bool HasInterface(Interface value, Interface check)
        {
            return (value & check) == check;
        }
    }
}