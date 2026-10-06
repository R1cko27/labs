using System;

namespace CalculatorApp
{
    public class Calculator
    {
        public void Add(int a, int b)
        {
            int z = a + b;
            Console.WriteLine($"Сумма чисел {a} и {b} равна {z}");
        }

        public void Subtract(int a, int b)
        {
            int z = a - b;
            Console.WriteLine($"Разность чисел {a} и {b} равна {z}");
        }

        public void Multiply(int a, int b)
        {
            int z = a * b;
            Console.WriteLine($"Произведение чисел {a} и {b} равно {z}");
        }

        public void Divide(int a, int b)
        {
            if (b == 0)
            {
                Console.WriteLine("Деление на ноль невозможно!");
                return;
            }
            int z = a / b;
            Console.WriteLine($"Частное чисел {a} и {b} равно {z}");
        }

        public void Remainder(int a, int b)
        {
            if (b == 0)
            {
                Console.WriteLine("Деление на ноль невозможно!");
                return;
            }
            int z = a % b;
            Console.WriteLine($"Остаток от деления числа {a} на {b} равен {z}");
        }
    }
}