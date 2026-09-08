using System;
using System.Diagnostics.CodeAnalysis;

namespace CarExample

{    [ExcludeFromCodeCoverage]
    class Car
    {
        private string model;
        private int year;
        private string color;

        public Car(string model, int year, string color)
        {
            this.model = model;
            this.year = year;
            this.color = color;
        }

        public void StartEngine()
        {
            Console.WriteLine($"{model} заводит двигатель... Бррр!");
        }

        public void Drive(int distance)
        {
            Console.WriteLine($"{model} проехал {distance} км.");
        }

        public void ShowInfo()
        {
            Console.WriteLine($"Модель: {model}");
            Console.WriteLine($"Год: {year}");
            Console.WriteLine($"Цвет: {color}");
        }
    }

    // Главный класс программы
    class Program
    {
        static void Main(string[] args)
        {
            // Создаем объект (экземпляр класса Car)
            Car myCar = new Car("Toyota Camry", 2022, "Серебристый");

            // Используем методы объекта
            myCar.ShowInfo();
            Console.WriteLine();
            myCar.StartEngine();
            myCar.Drive(150);

            Console.WriteLine("\nНажмите Enter для выхода...");
            Console.ReadLine();
        }
    }
}