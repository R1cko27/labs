using System;

namespace LabTasks
{
    class Program
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
        static int DoOperationSwitch(Operation op, int a, int b)
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

        // ===================== ЗАДАЧА 1 =====================
        // Массив 1..N, вывод в обратном порядке.
        static int[] BuildAscending(int n)
        {
            var arr = new int[n];
            for (int i = 0; i < n; i++) arr[i] = i + 1;
            return arr;
        }

        static void PrintReversed(int[] arr)
        {
            Console.Write("Прямой порядок : ");
            foreach (var x in arr) Console.Write(x + " ");
            Console.WriteLine();

            Console.Write("Обратный порядок: ");
            for (int i = arr.Length - 1; i >= 0; i--) Console.Write(arr[i] + " ");
            Console.WriteLine();
        }

        // ===================== ЗАДАЧА 2 =====================
        // Квадратный массив:
        //   1 1 1 1 1
        //   1 1 1 1 1
        //   0 1 1 1 1
        //   0 0 1 1 1
        //   0 0 0 1 1
        static int[,] FillPattern(int n)
        {
            var m = new int[n, n];
            for (int r = 0; r < n; r++)
                for (int c = 0; c < n; c++)
                    m[r, c] = (r - c <= 1) ? 1 : 0;
            return m;
        }

        // ===================== ЗАДАЧИ 3 и 4 =====================
        static int[,] FillSpiral(int rows, int cols)
        {
            var a = new int[rows, cols];
            int top = 0, bottom = rows - 1, left = 0, right = cols - 1, val = 1;
            int total = rows * cols;

            while (val <= total)
            {
                for (int c = left;  c <= right;  c++) a[top,    c] = val++; // → вверх
                top++;
                for (int r = top;   r <= bottom; r++) a[r,      right] = val++; // ↓ право
                right--;
                if (val <= total)
                {
                    for (int c = right; c >= left; c--) a[bottom, c] = val++; // ← низ
                    bottom--;
                }
                if (val <= total)
                {
                    for (int r = bottom; r >= top; r--) a[r,      left] = val++; // ↑ лево
                    left++;
                }
            }
            return a;
        }

        // ===================== служебный вывод =====================
        static void PrintMatrix(int[,] m)
        {
            int rows = m.GetLength(0), cols = m.GetLength(1);
            int max = 0;
            for (int r = 0; r < rows; r++)
                for (int c = 0; c < cols; c++)
                    if (m[r, c] > max) max = m[r, c];
            int w = max.ToString().Length + 1;

            for (int r = 0; r < rows; r++)
            {
                for (int c = 0; c < cols; c++)
                    Console.Write(m[r, c].ToString().PadLeft(w));
                Console.WriteLine();
            }
        }

        static void Title(string s)
        {
            Console.WriteLine();
            Console.WriteLine(new string('=', 60));
            Console.WriteLine(s);
            Console.WriteLine(new string('=', 60));
        }

        // ===================== MAIN =====================
        static void Main()
        {
            // ---- Задача 1 ----
            Title("Задача 1: массив 1..N и обратный вывод (N = 10)");
            PrintReversed(BuildAscending(10));

            // ---- Задача 2 ----
            Title("Задача 2: квадратный массив по образцу (N = 5)");
            PrintMatrix(FillPattern(5));

            // ---- Задача 3 ----
            Title("Задача 3: спираль, квадрат N*N (N = 5)");
            PrintMatrix(FillSpiral(5, 5));

            // ---- Задача 4 ----
            Title("Задача 4: спираль, прямоугольник M*N (M = 4, N = 6)");
            PrintMatrix(FillSpiral(4, 6));

            // ---- Задание: DoOperation с enum ----
            Title("Задание: DoOperation через перечисление (оба стиля)");
            int a = 8, b = 3;
            var ops = new[]
            {
                Operation.Add, Operation.Subtract, Operation.Multiply,
                Operation.Divide, Operation.Power, Operation.Sqrt
            };
            Console.WriteLine($"a = {a}, b = {b}   (для Sqrt используется только a)");
            Console.WriteLine($"{"Операция",-10} {"switch-оператор",-18} {"switch-выражение"}");
            foreach (var op in ops)
            {
                int r1 = DoOperationSwitch(op, a, b);
                int r2 = DoOperationExpression(op, a, b);
                Console.WriteLine($"{op,-10} {r1,-18} {r2}");
            }

            // демонстрация защиты от ошибок
            Console.WriteLine();
            try { DoOperationSwitch(Operation.Divide, 5, 0); }
            catch (DivideByZeroException e) { Console.WriteLine("Divide/0 -> " + e.Message); }

            try { DoOperationExpression(Operation.Sqrt, -4, 0); }
            catch (ArgumentException e) { Console.WriteLine("Sqrt(-4) -> " + e.Message); }
        }
    }
}