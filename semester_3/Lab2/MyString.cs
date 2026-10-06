using System;
using System.Globalization;
using System.Linq;

namespace Lab2_Part1
{
    public class MyString : IEquatable<MyString>, IComparable<MyString>
    {
        private string text;

        // Конструкторы
        public MyString() : this(string.Empty){}

        public MyString(string value)
        {
            text = value ?? string.Empty;
        }

        public MyString(MyString other)
        {
            text = other?.text ?? string.Empty;
        }

        // Свойство длины строки
        public int Length => text.Length;

        // Индексатор для доступа и изменения символа по индексу
        public char this[int index]
        {
            get
            {
                if (index < 0 || index >= text.Length)
                {
                    throw new ArgumentOutOfRangeException(nameof(index));
                }

                return text[index];
            }

            set
            {
                if (index < 0 || index >= text.Length)
                {
                    throw new ArgumentOutOfRangeException(nameof(index));
                }

                char[] buffer = text.ToCharArray();
                buffer[index] = value;
                text = new string(buffer);
            }
        }

        public override string ToString()
        {
            return text;
        }

        // Реализация интерфейсов IEquatable<MyString> и IComparable<MyString>
        public override bool Equals(object? obj)
        {
            return Equals(obj as MyString);
        }
        
        public bool Equals(MyString? other)
        {
            if (other is null)
            {
                return false;
            }

            if (ReferenceEquals(this, other))
            {
                return true;
            }

            return string.Equals(text, other.text, StringComparison.Ordinal);
        }

        public override int GetHashCode()
        {
            return text.GetHashCode();
        }

        public int CompareTo(MyString? other)
        {
            return Compare(this, other);
        }

        // Возвращает слова строки, разделённые пробельными символами
        public string[] GetWords()
        {
            return text.Split(new char[0], StringSplitOptions.RemoveEmptyEntries);
        }

        // Количество слов
        public int WordCount()
        {
            return GetWords().Length;
        }

        // Суммарная длина всех слов
        public int TotalWordLength()
        {
            return GetWords().Sum(word => word.Length);
        }

        // Вспомогательный метод сравнения
        private static int Compare(MyString? left, MyString? right)
        {
            if (ReferenceEquals(left, right)) return 0;
            if (left is null) return -1;
            if (right is null) return 1;
            
            // Сравнение по суммарной длине слов
            int result = left.TotalWordLength().CompareTo(right.TotalWordLength());
            if (result != 0) return result;
            
            // Если длины слов совпадают, сравниваем по количеству слов
            result = left.WordCount().CompareTo(right.WordCount());
            if (result != 0) return result;
            
            // Если и это совпадает, сравниваем обычным лексикографическим способом
            return string.Compare(left.text, right.text, StringComparison.Ordinal);
        }

        // Перегрузка оператора <
        // Сравнение строк по длине слов
        public static bool operator <(MyString? left, MyString? right)
        {
            return Compare(left, right) < 0;
        }

        // При перегрузке < обязательно нужно перегрузить >
        public static bool operator >(MyString? left, MyString? right)
        {
            return Compare(left, right) > 0;
        }

        // Дополнительные операторы сравнения
        public static bool operator <=(MyString? left, MyString? right)
        {
            return Compare(left, right) <= 0;
        }

        public static bool operator >=(MyString? left, MyString? right)
        {
            return Compare(left, right) >= 0;
        }

        // Перегрузка оператора ==
        public static bool operator ==(MyString? left, MyString? right)
        {
            if (ReferenceEquals(left, right)) return true;
            if (left is null || right is null) return false;
            return left.Equals(right);
        }

        public static bool operator !=(MyString? left, MyString? right)
        {
            return !(left == right);
        }

        // Добавление числа к строке
        public static MyString operator +(MyString? source, int number)
        {
            string leftPart = source?.text ?? string.Empty;

            return new MyString(leftPart + number.ToString(CultureInfo.InvariantCulture));
        }

        // Добавление числа слева от строки
        public static MyString operator +(int number, MyString? source)
        {
            string rightPart = source?.text ?? string.Empty;

            return new MyString(number.ToString(CultureInfo.InvariantCulture) + rightPart);
        }

        // Удаление последнего символа из строки
        public static MyString operator -(MyString? source)
        {
            if (source is null || source.text.Length == 0)
            {
                return new MyString(string.Empty);
            }

            return new MyString(source.text.Substring(0, source.text.Length - 1));
        }

        // Замена всех символов строки на заданный символ
        public static MyString operator *(MyString? source, char replacement)
        {
            if (source is null) return new MyString(string.Empty);

            return new MyString(new string(replacement, source.text.Length));
        }

        // символ * строка
        public static MyString operator *(char replacement, MyString? source)
        {
            return source * replacement;
        }
    }

    // Статический класс с методами расширения
    public static class Extensions
    {
        // Проверка наличия в строке хотя бы одного из заданных символов
        public static bool ContainsAny(this string? source, params char[]? symbols)
        {
            if (source is null || source.Length == 0 || symbols is null || symbols.Length == 0)
                return false;
                
            char[] symbolsArray = symbols;
            return source.Any(ch => symbolsArray.Contains(ch));
        }

        // Удаление знаков препинания
        public static string RemovePunctuation(this string? source)
        {
            if (source is null) return string.Empty;
            return new string(source.Where(ch => !char.IsPunctuation(ch)).ToArray());
        }

        // Метод расширения для класса MyString
        // Проверка наличия в строке хотя бы одного из заданных символов
        public static bool ContainsAny(this MyString? source, params char[]? symbols)
        {
            if (source is null) return false;
            return source.ToString().ContainsAny(symbols);
        }

        // Удаление знаков препинания
        public static MyString RemovePunctuation(this MyString? source)
        {
            if (source is null) return new MyString(string.Empty);
            return new MyString(source.ToString().RemovePunctuation());
        }
    }
}