// Fax.cs
using System;

namespace OfficeEquipmentLibrary
{
    public enum AutoFeederType
    {
        DoubleSided,
        SingleSided,
        None
    }

    public class Fax : OfficeEquipment
    {
        private AutoFeederType autoFeederType;
        private Interface interfaces;
        private ApplicationArea applicationArea;
        private int transmissionSpeedBPS;      // Скорость передачи в битах в секунду
        private int scanResolutionDPI;         // Разрешение сканирования в DPI
        private int memoryCapacityPages;       // Количество страниц в памяти
        private bool hasAutomaticFeeder;       // Наличие автоматической подачи

        public Fax()
            : base()
        {
            autoFeederType = AutoFeederType.SingleSided;
            interfaces = Interface.RJ11;
            applicationArea = ApplicationArea.Office;
            transmissionSpeedBPS = 14400;
            scanResolutionDPI = 203;
            memoryCapacityPages = 100;
            hasAutomaticFeeder = true;
        }

        public Fax(string model, Manufacturer manufacturer, int year, double price,
                   int transmissionSpeed, int scanResolution, int memoryPages, bool autoFeeder,
                   AutoFeederType autoFeederType, Interface interfaces, ApplicationArea applicationArea)
            : base(model, manufacturer, year, price)
        {
            // Валидация специфичных для факса полей
            if (!ValidateTransmissionSpeed(transmissionSpeed))
                this.transmissionSpeedBPS = 14400;
            else
                this.transmissionSpeedBPS = transmissionSpeed;

            if (!ValidateScanResolution(scanResolution))
                this.scanResolutionDPI = 200;
            else
                this.scanResolutionDPI = scanResolution;

            if (!ValidateMemoryCapacity(memoryPages))
                this.memoryCapacityPages = 100;
            else
                this.memoryCapacityPages = memoryPages;

            this.hasAutomaticFeeder = autoFeeder;
            this.autoFeederType = autoFeederType;
            this.interfaces = interfaces;
            this.applicationArea = applicationArea;
        }

        // Свойства вместо геттеров и сеттеров
        public AutoFeederType AutoFeederType
        {
            get { return autoFeederType; }
            set { autoFeederType = value; }
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

        public int TransmissionSpeedBPS
        {
            get { return transmissionSpeedBPS; }
            set
            {
                if (ValidateTransmissionSpeed(value))
                    transmissionSpeedBPS = value;
            }
        }

        public int ScanResolutionDPI
        {
            get { return scanResolutionDPI; }
            set
            {
                if (ValidateScanResolution(value))
                    scanResolutionDPI = value;
            }
        }

        public int MemoryCapacityPages
        {
            get { return memoryCapacityPages; }
            set
            {
                if (ValidateMemoryCapacity(value))
                    memoryCapacityPages = value;
            }
        }

        public bool HasAutomaticFeeder
        {
            get { return hasAutomaticFeeder; }
            set { hasAutomaticFeeder = value; }
        }

        public override string ToString()
        {
            return ToStringOverride();
        }

        public override string ToStringOverride()
        {
            string feederStr = autoFeederType switch
            {
                AutoFeederType.DoubleSided => "двустороннее",
                AutoFeederType.SingleSided => "одностороннее",
                AutoFeederType.None => "нет",
                _ => "неизвестно"
            };

            string interfaceStr = GetInterfaceString(interfaces);
            if (string.IsNullOrEmpty(interfaceStr))
                interfaceStr = "Не указаны";

            string areaStr = applicationArea == ApplicationArea.Home ? "для дома" : "для офиса";

            return $"Модель: {Model}\n" +
                   $"Производитель: {Manufacturer}\n" +
                   $"Год выпуска: {YearOfManufacture}\n" +
                   $"Цена: {Price} RUB\n" +
                   $"Скорость передачи: {transmissionSpeedBPS} бит/с\n" +
                   $"Разрешение сканирования: {scanResolutionDPI} DPI\n" +
                   $"Объем памяти: {memoryCapacityPages} страниц\n" +
                   $"Автоподатчик: {(hasAutomaticFeeder ? "Да" : "Нет")}\n" +
                   $"Тип автоподатчика: {feederStr}\n" +
                   $"Интерфейс: {interfaceStr}\n" +
                   $"Область применения: {areaStr}";
        }

        // Статические методы валидации
        public static bool ValidateTransmissionSpeed(int speed)
        {
            return speed >= 2400 && speed <= 33600 && speed % 100 == 0;
        }

        public static bool ValidateScanResolution(int resolution)
        {
            return resolution >= 100 && resolution <= 600;
        }

        public static bool ValidateMemoryCapacity(int pages)
        {
            return pages >= 1 && pages <= 500;
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