using System;

namespace CalculatorApp
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Title = "КАЛЬКУЛЯТОР";
            Console.BackgroundColor = ConsoleColor.Magenta;
            Console.ForegroundColor = ConsoleColor.White;
            Console.Clear();

            Console.CancelKeyPress += (sender, e) =>
            {
                e.Cancel = true;
                Console.Clear();
                Console.ForegroundColor = ConsoleColor.Red;
                Console.WriteLine("Программа завершена пользователем (CTRL + C)");
                Console.ResetColor();
                Environment.Exit(0);
            };

            // Создаём экземпляр класса Calculator
            Calculator calc = new Calculator();
            ConsoleKeyInfo keyInfo;

            do
            {
                Console.Clear();
                Console.WriteLine("1. Сложение");
                Console.WriteLine("2. Вычитание");
                Console.WriteLine("3. Умножение");
                Console.WriteLine("4. Деление");
                Console.WriteLine("5. Остаток от деления");
                Console.WriteLine("ESC. Выход");
                Console.Write("\nВыберите операцию: ");

                keyInfo = Console.ReadKey(false);
                Console.WriteLine();

                if (keyInfo.Key == ConsoleKey.Escape)
                {
                    break;
                }

                string choice = keyInfo.KeyChar.ToString();

                try
                {
                    switch (choice)
                    {
                        case "1":
                            Console.Write("\nВведите первое число: ");
                            int a1 = int.Parse(Console.ReadLine()!);
                            Console.Write("Введите второе число: ");
                            int b1 = int.Parse(Console.ReadLine()!);
                            calc.Add(a1, b1);
                            break;

                        case "2":
                            Console.Write("\nВведите первое число: ");
                            int a2 = int.Parse(Console.ReadLine()!);
                            Console.Write("Введите второе число: ");
                            int b2 = int.Parse(Console.ReadLine()!);
                            calc.Subtract(a2, b2);
                            break;

                        case "3":
                            Console.Write("\nВведите первое число: ");
                            int a3 = int.Parse(Console.ReadLine()!);
                            Console.Write("Введите второе число: ");
                            int b3 = int.Parse(Console.ReadLine()!);
                            calc.Multiply(a3, b3);
                            break;

                        case "4":
                            Console.Write("\nВведите делимое: ");
                            int a4 = int.Parse(Console.ReadLine()!);
                            Console.Write("Введите делитель: ");
                            int b4 = int.Parse(Console.ReadLine()!);
                            calc.Divide(a4, b4);
                            break;

                        case "5":
                            Console.Write("\nВведите делимое: ");
                            int a5 = int.Parse(Console.ReadLine()!);
                            Console.Write("Введите делитель: ");
                            int b5 = int.Parse(Console.ReadLine()!);
                            calc.Remainder(a5, b5);
                            break;

                        default:
                            Console.WriteLine("\nНеверный выбор! Попробуйте снова.");
                            break;
                    }
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"\nОшибка: {ex.Message}");
                }

                Console.WriteLine("\nНажмите любую клавишу для продолжения...");
                Console.ReadKey();

            } while (keyInfo.Key != ConsoleKey.Escape);

            Console.Clear();
            Console.ForegroundColor = ConsoleColor.Red;
            Console.WriteLine("Программа завершена");
            Console.ResetColor();
        }
    }
}