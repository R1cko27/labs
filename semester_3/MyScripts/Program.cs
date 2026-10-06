using System;

namespace Practic2
{
    class Program
    {
        static void Main()
        {
            // ---- Задание: DoOperation с enum ----
            Calculator.Title("Задание: DoOperation через перечисление");
            int a = 8, b = 3;
            var ops = new[]
            {
                Calculator.Operation.Add, Calculator.Operation.Subtract, Calculator.Operation.Multiply,
                Calculator.Operation.Divide, Calculator.Operation.Power, Calculator.Operation.Sqrt
            };
            Console.WriteLine($"a = {a}, b = {b}   (для Sqrt используется только a)");
            Console.WriteLine($"{"Операция",-10} {"switch-оператор",-18}");
            foreach (var op in ops)
            {
                int r1 = Calculator.DoOperationSwitch(op, a, b);
                Console.WriteLine($"{op,-10} {r1,-18}");
            }

            // демонстрация защиты от ошибок
            Console.WriteLine();
            try { Calculator.DoOperationSwitch(Calculator.Operation.Divide, 5, 0); }
            catch (DivideByZeroException e) { Console.WriteLine("Divide/0 -> " + e.Message); }
        }
    }
}