// OfficeEquipment.cs
using System;

namespace OfficeEquipmentLibrary
{
    public enum Manufacturer // Перечисление производителей
    {
        Brother,
        Canon,
        DELI,
        Epson,
        HP,
        Xiaomi,
        Samsung,
        Sharp,
        Panasonic,
        Unknown
    }

    [Flags] // Используем битовую маску
    public enum Interface // Перечисление интерфейсов 
    {
        Bluetooth = 1 << 0,    // 1 (0000 0001 << 0 = 0000 0001 = 1)
        EthernetRJ45 = 1 << 1, // 2 (0000 0001 << 1 = 0000 0010 = 2)
        NFC = 1 << 2,          // 4
        RJ11 = 1 << 3,         // 8
        USB = 1 << 4,          // 16
        USBTypeB = 1 << 5,     // 32
        USBHost = 1 << 6,      // 64
        WiFi = 1 << 7          // 128
    }

    public enum ApplicationArea // Перечисление областей применения
    {
        Home,
        Office
    }

    public class OfficeEquipment // Базовый класс для офисного оборудования

    {
        private string model;
        private Manufacturer manufacturer;
        private int yearOfManufacture;
        private double price;

        public OfficeEquipment()
        {
            model = "Unknown";
            manufacturer = Manufacturer.Unknown;
            yearOfManufacture = 2000;
            price = 0.0;
        }

        public OfficeEquipment(string model, Manufacturer manufacturer, int year, double price)
        {
            if (!ValidateModel(model))
                this.model = "Unknown";
            else
                this.model = model;

            this.manufacturer = manufacturer;

            if (!ValidateYear(year))
                this.yearOfManufacture = 2000;
            else
                this.yearOfManufacture = year;

            if (!ValidatePrice(price))
                this.price = 3000.0;
            else
                this.price = price;
        }

        // Свойства
        public string Model
        {
            get { return model; }
            set
            {
                if (ValidateModel(value))
                    model = value;
            }
        }

        public Manufacturer Manufacturer
        {
            get { return manufacturer; }
            set { manufacturer = value; }
        }

        public int YearOfManufacture
        {
            get { return yearOfManufacture; }
            set
            {
                if (ValidateYear(value))
                    yearOfManufacture = value;
            }
        }

        public double Price
        {
            get { return price; }
            set
            {
                if (ValidatePrice(value))
                    price = value;
            }
        }

        public string ManufacturerName
        {
            get
            {
                return manufacturer switch
                {
                    Manufacturer.Brother => "Brother",
                    Manufacturer.Canon => "Canon",
                    Manufacturer.DELI => "DELI",
                    Manufacturer.Epson => "Epson",
                    Manufacturer.HP => "HP",
                    Manufacturer.Xiaomi => "Xiaomi",
                    Manufacturer.Samsung => "Samsung",
                    Manufacturer.Sharp => "Sharp",
                    Manufacturer.Panasonic => "Panasonic",
                    Manufacturer.Unknown => "Unknown",
                    _ => "Unknown"
                };
            }
        }

        // Методы валидации
        public static bool ValidateModel(string model)
        {
            return !string.IsNullOrEmpty(model) && model.Length >= 3 && model.Length <= 100;
        }

        public static bool ValidateYear(int year)
        {
            return year >= 1980 && year <= 2026;
        }

        public static bool ValidatePrice(double price)
        {
            return price >= 3000.0 && price <= 200000.0;
        }

        // Виртуальный метод для строкового представления
        public virtual string ToStringOverride()
        {
            return $"Model: {model}\n" +
                   $"Manufacturer: {ManufacturerName}\n" +
                   $"Year of Manufacture: {yearOfManufacture}\n" +
                   $"Price: {price} RUB";
        }

        public override string ToString()
        {
            return ToStringOverride();
        }

        // Вспомогательные методы для работы с Interface (Flags)
        public static bool HasInterface(Interface value, Interface check)
        {
            return (value & check) == check;
        }

        public static Interface AddInterface(Interface current, Interface toAdd)
        {
            return current | toAdd;
        }

        public static Interface RemoveInterface(Interface current, Interface toRemove)
        {
            return current & ~toRemove;
        }
    }
}