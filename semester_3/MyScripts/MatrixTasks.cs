using System;

namespace Practic2
{
    class MatrixTasks
    {
        //  ЗАДАЧА 1 
        // Массив 1..N, вывод в обратном порядке.
        public static int[] BuildAscending(int n)
        {
            var arr = new int[n];
            for (int i = 0; i < n; i++) arr[i] = i + 1;
            return arr;
        }

        public static void PrintReversed(int[] arr)
        {
            Console.Write("Прямой порядок : ");
            foreach (var x in arr) Console.Write(x + " ");
            Console.WriteLine();

            Console.Write("Обратный порядок: ");
            for (int i = arr.Length - 1; i >= 0; i--) Console.Write(arr[i] + " ");
            Console.WriteLine();
        }

        //  ЗАДАЧА 2 
        // Квадратный массив:
        //   1 1 1 1 1
        //   1 1 1 1 1
        //   0 1 1 1 1
        //   0 0 1 1 1
        //   0 0 0 1 1
        public static int[,] FillPattern(int n)
        {
            var m = new int[n, n];
            for (int r = 0; r < n; r++)
                for (int c = 0; c < n; c++)
                    m[r, c] = (r - c <= 1) ? 1 : 0;
            return m;
        }

        //  ЗАДАЧИ 3 и 4 
        public static int[,] FillSpiral(int rows, int cols)
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

        //  служебный вывод 
        public static void PrintMatrix(int[,] m)
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

        public static void Title(string s)
        {
            Console.WriteLine();
            Console.WriteLine(new string('=', 60));
            Console.WriteLine(s);
            Console.WriteLine(new string('=', 60));
        }
    }
}