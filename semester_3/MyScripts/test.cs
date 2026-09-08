using System;
using System.Collections.Generic; // ДОБАВЛЕНО!

namespace PersonExample
{
    class School
    {
        private List<Person> studys = new List<Person>();
        
        public void addPerson(Person per)
        {
            studys.Add(per);
            Console.WriteLine($"Человек - {per.Name()} добавлен в список учащихся");
        }
        
        public void ShowAllPerson()
        {
            Console.WriteLine("\nСписок всех учащихся:");
            foreach (var per in studys)
            {
                per.Info();
                Console.WriteLine("-------------------");
            }
        }
    }
    
    class Person
    {
        private string name;
        private string secondname;
        private int age;

        public Person(string name, string secondname, int age)
        {
            this.name = name;
            this.secondname = secondname;
            this.age = age;
        }
        
        public void Info()
        {
            Console.WriteLine($"Name - {name}");
            Console.WriteLine($"Second Name - {secondname}");
            Console.WriteLine($"Age - {age}");
        }
        
        public string Name()
        {
            return $"{name} {secondname}";
        }
    }
    
    class Programm
    {
        static void Main(string[] args)
        {
            School school = new School();
            
            Person person1 = new Person("Artem", "Panfilov", 19);
            Person person2 = new Person("Ivan", "Petrov", 20);
            Person person3 = new Person("Maria", "Ivanova", 18);
            
            school.addPerson(person1);
            school.addPerson(person2);
            school.addPerson(person3);
            
            school.ShowAllPerson();
        }
    }
}