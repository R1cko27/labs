using System;
using System.Collections.Generic;
using System.Linq;

namespace NetworkLab                 // Практика 2, стр. 17 + 22 (вариант: сетевое оборудование)
{
    // ======================================================================
    //  БАЗОВЫЙ ТИП  —  «Сетевое оборудование»
    // ======================================================================
    public class NetworkDevice
    {
        // private: наружу не видны, доступ только через свойства ---
        private string _model = "Undefined";
        private string _manufacturer = "Undefined";
        private decimal _price;

        // protected: видны в этом классе и во ВСЕХ производных ---
        protected string _firmware;          // версию прошивки читают наследники напрямую
        protected string _installPlace;      // место установки

        public string MacAddress { get; set; }

        public string Model
        {
            get => _model;
            set => _model = string.IsNullOrWhiteSpace(value) ? "Undefined" : value.Trim();
        }

        public string Manufacturer
        {
            get => _manufacturer;
            set => _manufacturer = string.IsNullOrWhiteSpace(value) ? "Undefined" : value.Trim();
        }

        public decimal Price
        {
            get => _price;
            set
            {
                if (value < 0)
                    throw new ArgumentException("Цена не может быть отрицательной.");
                _price = value;
            }
        }

        // Виртуальное свойство — переопределяется наследниками.
        public virtual string DeviceType => "Сетевое оборудование";

        public NetworkDevice(string model, string manufacturer, decimal price,
                             string mac, string firmware, string installPlace)
        {
            Model        = model;
            Manufacturer = manufacturer;
            Price        = price;
            MacAddress   = mac;
            _firmware    = firmware;
            _installPlace = installPlace;
        }

        //  виртуальные методы (полиморфизм) 
        public virtual string GetSpecs()
            => $"  MAC: {MacAddress} | прошивка: {_firmware} | установка: {_installPlace}";

        public virtual void Print()
        {
            Console.WriteLine(ToString());
            Console.WriteLine(GetSpecs());
        }

        public override string ToString()
            => $"[{DeviceType}] {Manufacturer} {Model} — {Price:C}";

    }

    //  ПРОИЗВОДНЫЙ ТИП 1  —  «Маршрутизатор Wi‑Fi»
    public class WifiRouter : NetworkDevice
    {
        private int _antennas;
        public string WifiStandard { get; set; }     // напр. "Wi‑Fi 6 (802.11ax)"
        public bool   GuestNetwork { get; set; }

        public int Antennas
        {
            get => _antennas;
            set => _antennas = value < 0 ? throw new ArgumentException("Антенн не может быть < 0.") : value;
        }

        public override string DeviceType => "Маршрутизатор Wi‑Fi";

        public WifiRouter(string model, string manufacturer, decimal price, string mac,
                          string firmware, string installPlace,
                          string wifiStandard, int antennas, bool guestNetwork)
            : base(model, manufacturer, price, mac, firmware, installPlace)
        {
            WifiStandard = wifiStandard;
            Antennas     = antennas;
            GuestNetwork = guestNetwork;
        }

        // Переопределение
        public override string GetSpecs()
            => base.GetSpecs() +
               $"\n  Wi‑Fi: {WifiStandard} | антенн: {Antennas} | гостевая сеть: {(GuestNetwork ? "да" : "нет")}" +
               $"\n  (protected‑поле базы видно здесь: firmware={_firmware})";

        public override string ToString() => base.ToString() + $"  [{WifiStandard}]";
    }

    //  ПРОИЗВОДНЫЙ ТИП 2  —  «Коммутатор (свитч)»
    public class Switch : NetworkDevice
    {
        private int _ports;
        private decimal _portSpeedGbps;

        public bool Managed     { get; set; }   // управляемый / неуправляемый
        public bool VlanSupport { get; set; }

        public int Ports
        {
            get => _ports;
            set => _ports = value <= 0 ? throw new ArgumentException("Портов должно быть > 0.") : value;
        }

        public decimal PortSpeedGbps
        {
            get => _portSpeedGbps;
            set => _portSpeedGbps = value <= 0 ? throw new ArgumentException("Скорость порта > 0.") : value;
        }

        public override string DeviceType => "Коммутатор (свитч)";

        public Switch(string model, string manufacturer, decimal price, string mac,
                      string firmware, string installPlace,
                      int ports, decimal portSpeedGbps, bool managed, bool vlanSupport)
            : base(model, manufacturer, price, mac, firmware, installPlace)
        {
            Ports         = ports;
            PortSpeedGbps = portSpeedGbps;
            Managed       = managed;
            VlanSupport   = vlanSupport;
        }

        public override string GetSpecs()
            => base.GetSpecs() +
               $"\n  Портов: {Ports} | скорость порта: {PortSpeedGbps} Гбит/с | " +
               $"управляемый: {(Managed ? "да" : "нет")} | VLAN: {(VlanSupport ? "да" : "нет")}";

        public override string ToString() => base.ToString() + $"  [{Ports} портов]";
    }
}