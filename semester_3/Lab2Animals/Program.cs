using System;
using System.Text;

namespace Lab2_Part2
{
    internal class Program
    {
        private static void Main()
        {
            Console.OutputEncoding = Encoding.UTF8;

            Habitat savanna = new Habitat("African savanna", HabitatType.Land, 30);
            Habitat taiga = new Habitat("Taiga", HabitatType.Land, 10);
            Habitat hollow = new Habitat("Tree hollow in forest", HabitatType.Land, 15);
            Habitat jungle = new Habitat("Tropical jungle", HabitatType.Land, 28);
            Habitat ocean = new Habitat("Open ocean", HabitatType.Water, 18);
            Habitat river = new Habitat("River backwater", HabitatType.Mixed, 22);

            Animal[] animals = new Animal[]
            {
                new Lion("Simba", 5, savanna, true),
                new Tiger("Shere Khan", 7, taiga, 120),
                new Owl("Athena", 3, hollow, 270),
                new Parrot("Kesha", 4, jungle, 50),
                new Shark("Jaws", 10, ocean, 300),
                new Crocodile("Croc", 12, river, 4.5)
            };

            Console.WriteLine("=== Polymorphism demo ===");

            foreach (Animal animal in animals)
            {
                Console.WriteLine(new string('-', 70));

                Console.WriteLine(animal.ToString());
                Console.WriteLine(animal.MakeSound());
                Console.WriteLine(animal.Move());

                if (animal is IFlyable flyable)
                {
                    Console.WriteLine(flyable.Fly());
                }

                if (animal is ISwimmable swimmable)
                {
                    Console.WriteLine(swimmable.Swim());
                }

                if (animal is IPredator predator)
                {
                    Console.WriteLine(predator.Hunt());
                }
            }

            Console.WriteLine();
            Console.WriteLine("=== Object methods overridden in Lion ===");

            Lion lion1 = new Lion(
                "Simba",
                5,
                new Habitat("African savanna", HabitatType.Land, 30),
                true
            );

            Lion lion2 = new Lion(
                "Simba",
                5,
                new Habitat("African savanna", HabitatType.Land, 30),
                true
            );

            Lion lion3 = new Lion(
                "Nala",
                4,
                new Habitat("African savanna", HabitatType.Land, 30),
                false
            );

            Console.WriteLine(lion1.ToString());
            Console.WriteLine(lion2.ToString());
            Console.WriteLine(lion3.ToString());

            Console.WriteLine();
            Console.WriteLine($"ReferenceEquals(lion1, lion2) = {ReferenceEquals(lion1, lion2)}");
            Console.WriteLine($"lion1.Equals(lion2) = {lion1.Equals(lion2)}");
            Console.WriteLine($"lion1.Equals(lion3) = {lion1.Equals(lion3)}");
            Console.WriteLine($"lion1.Equals(null) = {lion1.Equals(null)}");

            Console.WriteLine();
            Console.WriteLine($"lion1.GetHashCode() = {lion1.GetHashCode()}");
            Console.WriteLine($"lion2.GetHashCode() = {lion2.GetHashCode()}");
            Console.WriteLine($"lion3.GetHashCode() = {lion3.GetHashCode()}");

            Console.WriteLine();
            Console.WriteLine("=== Sterile class ===");
            Console.WriteLine("Parrot is sealed, so it cannot have descendants.");
        }
    }
}