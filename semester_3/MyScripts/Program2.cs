using System;

namespace Practic2
{
    class Program
    {
        static void Main()
        {
            // ---- Задача 1 ----
            MatrixTasks.Title("Задача 1: массив 1..N и обратный вывод (N = 10)");
            MatrixTasks.PrintReversed(MatrixTasks.BuildAscending(10));

            // ---- Задача 2 ----
            MatrixTasks.Title("Задача 2: квадратный массив по образцу (N = 5)");
            MatrixTasks.PrintMatrix(MatrixTasks.FillPattern(5));

            // ---- Задача 3 ----
            MatrixTasks.Title("Задача 3: спираль, квадрат N*N (N = 5)");
            MatrixTasks.PrintMatrix(MatrixTasks.FillSpiral(5, 5));

            // ---- Задача 4 ----
            MatrixTasks.Title("Задача 4: спираль, прямоугольник M*N (M = 4, N = 6)");
            MatrixTasks.PrintMatrix(MatrixTasks.FillSpiral(4, 6));
        }
    }
}