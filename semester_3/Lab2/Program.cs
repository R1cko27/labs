using System;
using System.Text;

namespace Lab2_Part1
{
    internal class Program
    {
        private static void Main()
        {
            Console.OutputEncoding = Encoding.UTF8;

            MyString s1;
            MyString s2;

            Console.WriteLine("=== Конструкторы ===");

            s1 = new MyString();
            Console.WriteLine($"s1 = new MyString(): \"{s1}\"");

            s1 = new MyString("Привет мир 123");
            Console.WriteLine($"s1 = new MyString(\"Привет мир 123\"): \"{s1}\"");

            s2 = new MyString("Как дела?");
            Console.WriteLine($"s2 = new MyString(\"Как дела?\"): \"{s2}\"");

            s2 = new MyString(s1);
            Console.WriteLine($"s2 = new MyString(s1): \"{s2}\"");


            Console.WriteLine("\n=== Length, ToString ===");

            Console.WriteLine($"s1.Length = {s1.Length}");
            Console.WriteLine($"s2.Length = {s2.Length}");

            Console.WriteLine($"s1.ToString() = \"{s1.ToString()}\"");
            Console.WriteLine($"s2.ToString() = \"{s2.ToString()}\"");


            Console.WriteLine("\n=== Индексатор ===");

            Console.WriteLine($"s1[0] = '{s1[0]}'");

            s1[0] = 'J';
            Console.WriteLine($"s1 после s1[0] = 'J': \"{s1}\"");


            Console.WriteLine("\n=== GetWords, WordCount, TotalWordLength ===");

            Console.WriteLine($"s1.GetWords(): [{string.Join(", ", s1.GetWords())}]");
            Console.WriteLine($"s2.GetWords(): [{string.Join(", ", s2.GetWords())}]");

            Console.WriteLine($"s1.WordCount() = {s1.WordCount()}");
            Console.WriteLine($"s2.WordCount() = {s2.WordCount()}");

            Console.WriteLine($"s1.TotalWordLength() = {s1.TotalWordLength()}");
            Console.WriteLine($"s2.TotalWordLength() = {s2.TotalWordLength()}");


            Console.WriteLine("\n=== Equals, ==, !=, GetHashCode ===");

            Console.WriteLine($"s1.Equals(s2) = {s1.Equals(s2)}");
            Console.WriteLine($"s1.Equals((object)s2) = {s1.Equals((object)s2)}");

            Console.WriteLine($"s1 == s2 = {s1 == s2}");
            Console.WriteLine($"s1 != s2 = {s1 != s2}");

            Console.WriteLine($"s1.GetHashCode() = {s1.GetHashCode()}");
            Console.WriteLine($"s2.GetHashCode() = {s2.GetHashCode()}");


            Console.WriteLine("\n=== CompareTo, <, >, <=, >= ===");

            Console.WriteLine($"s1.CompareTo(s2) = {s1.CompareTo(s2)}");

            Console.WriteLine($"s1 < s2 = {s1 < s2}");
            Console.WriteLine($"s1 > s2 = {s1 > s2}");
            Console.WriteLine($"s1 <= s2 = {s1 <= s2}");
            Console.WriteLine($"s1 >= s2 = {s1 >= s2}");


            Console.WriteLine("\n=== Унарный минус: удаление последнего символа ===");

            s2 = -s2;
            Console.WriteLine($"s2 = -s2: \"{s2}\"");

            Console.WriteLine($"s1 < s2 = {s1 < s2}");
            Console.WriteLine($"s1 > s2 = {s1 > s2}");
            Console.WriteLine($"s1 <= s2 = {s1 <= s2}");
            Console.WriteLine($"s1 >= s2 = {s1 >= s2}");


            Console.WriteLine("\n=== Оператор +: добавление числа ===");

            s1 = s1 + 42;
            Console.WriteLine($"s1 = s1 + 42: \"{s1}\"");

            s1 = 7 + s1;
            Console.WriteLine($"s1 = 7 + s1: \"{s1}\"");


            Console.WriteLine("\n=== Оператор *: замена всех символов ===");

            s1 = s1 * '#';
            Console.WriteLine($"s1 = s1 * '#': \"{s1}\"");

            s1 = '@' * s1;
            Console.WriteLine($"s1 = '@' * s1: \"{s1}\"");


            Console.WriteLine("\n=== Методы расширения ===");

            s1 = new MyString("Hello, world! Это тест... Да?");
            Console.WriteLine($"s1 = \"{s1}\"");

            Console.WriteLine(
                $"s1.ToString().ContainsAny('!', '?') = " +
                $"{s1.ToString().ContainsAny('!', '?')}"
            );

            Console.WriteLine(
                $"s1.ToString().RemovePunctuation() = " +
                $"\"{s1.ToString().RemovePunctuation()}\""
            );

            Console.WriteLine($"s1.ContainsAny('.', ',') = {s1.ContainsAny('.', ',')}");

            s1 = s1.RemovePunctuation();
            Console.WriteLine($"s1 = s1.RemovePunctuation(): \"{s1}\"");
        }
    }
}