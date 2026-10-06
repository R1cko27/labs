using System;

namespace Practic2
{
    class Calculator
    {
        public enum Operation
        {
            Add      = 1, // сложение
            Subtract = 2, // вычитание
            Multiply = 3, // умножение
            Divide   = 4, // деление          (новое)
            Power    = 5, // возведение в степень (новое)
            Sqrt     = 6  // квадратный корень (новое, унарная — использует a)
        }

        // Вариант 1: switch-ОПЕРАТОР
        public static int DoOperationSwitch(Operation op, int a, int b)
        {
            switch (op)
            {
                case Operation.Add:      return a + b;
                case Operation.Subtract: return a - b;
                case Operation.Multiply: return a * b;
                case Operation.Divide:
                    if (b == 0) throw new DivideByZeroException("Деление на ноль.");
                    return a / b;                       // целочисленное деление
                case Operation.Power:
                    checked { return (int)Math.Pow(a, b); } // бросит OverflowException при переполнении
                case Operation.Sqrt:
                    if (a < 0) throw new ArgumentException("Корень из отрицательного числа.");
                    return (int)Math.Sqrt(a);           // унарная: b игнорируется
                default:
                    throw new ArgumentOutOfRangeException(nameof(op), "Неизвестная операция.");
            }
        }

        public static void Title(string s)
        {
            Console.WriteLine();
            Console.WriteLine(new string('=', 60));
            Console.WriteLine(s);
            Console.WriteLine(new string('=', 60));
        }
    }
}