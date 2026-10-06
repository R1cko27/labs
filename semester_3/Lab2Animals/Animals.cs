using System;

namespace Lab2_Part2
{
    public enum HabitatType
    {
        Land,
        Water,
        Mixed
    }

    public class Habitat
    {
        public string Name { get; }
        public HabitatType Type { get; }
        public int Temperature { get; }

        public Habitat(string? name, HabitatType type, int temperature)
        {
            Name = name ?? throw new ArgumentNullException(nameof(name));
            Type = type;
            Temperature = temperature;
        }

        public override string ToString()
        {
            return $"{Name} ({Type}, {Temperature} C)";
        }
    }

    public interface IFlyable
    {
        string Fly();
    }

    public interface ISwimmable
    {
        string Swim();
    }

    public interface IPredator
    {
        string Hunt();
    }

    public abstract class Animal
    {
        public string Name { get; }
        public int Age { get; }
        public Habitat Habitat { get; }

        protected Animal(string? name, int age, Habitat? habitat)
        {
            Name = name ?? throw new ArgumentNullException(nameof(name));

            if (age < 0)
            {
                throw new ArgumentOutOfRangeException(nameof(age));
            }

            Habitat = habitat ?? throw new ArgumentNullException(nameof(habitat));
        }

        protected string CoreData()
        {
            return $"name={Name}, age={Age}, habitat={Habitat}";
        }

        public virtual string MakeSound()
        {
            return $"{Name} makes a generic animal sound.";
        }

        public virtual string Move()
        {
            return $"{Name} moves in a generic way.";
        }

        public override string ToString()
        {
            return $"{GetType().Name}: {CoreData()}";
        }
    }

    public abstract class Mammal : Animal
    {
        protected Mammal(string? name, int age, Habitat? habitat)
            : base(name, age, habitat)
        {
        }

        public override string MakeSound()
        {
            return $"{Name} is a mammal and makes a characteristic sound.";
        }

        public override string Move()
        {
            return $"{Name} moves on four limbs.";
        }

        public override string ToString()
        {
            return $"Mammal {GetType().Name}: {CoreData()}";
        }
    }

    public abstract class Bird : Animal, IFlyable
    {
        protected Bird(string? name, int age, Habitat? habitat)
            : base(name, age, habitat)
        {
        }

        public virtual string Fly()
        {
            return $"{Name} flies by flapping wings.";
        }

        public override string MakeSound()
        {
            return $"{Name} sings or cries.";
        }

        public override string Move()
        {
            return $"{Name} moves by hopping and flying.";
        }

        public override string ToString()
        {
            return $"Bird {GetType().Name}: {CoreData()}";
        }
    }

    public abstract class Fish : Animal, ISwimmable
    {
        protected Fish(string? name, int age, Habitat? habitat)
            : base(name, age, habitat)
        {
        }

        public virtual string Swim()
        {
            return $"{Name} swims using fins.";
        }

        public override string Move()
        {
            return $"{Name} moves in water.";
        }

        public override string ToString()
        {
            return $"Fish {GetType().Name}: {CoreData()}";
        }
    }

    public class Lion : Mammal, IPredator
    {
        public bool HasMane { get; }

        public Lion(string? name, int age, Habitat? habitat, bool hasMane)
            : base(name, age, habitat)
        {
            HasMane = hasMane;
        }

        public override string MakeSound()
        {
            return $"{Name} roars: R-R-R!";
        }

        public override string Move()
        {
            return $"{Name} stalks and runs across the savanna.";
        }

        public string Hunt()
        {
            return $"{Name} hunts large ungulates in a pride.";
        }

        public override bool Equals(object? obj)
        {
            if (obj is not Lion other)
            {
                return false;
            }

            if (ReferenceEquals(this, other))
            {
                return true;
            }

            return string.Equals(Name, other.Name, StringComparison.Ordinal)
                && Age == other.Age
                && HasMane == other.HasMane
                && string.Equals(Habitat.Name, other.Habitat.Name, StringComparison.Ordinal)
                && Habitat.Type == other.Habitat.Type
                && Habitat.Temperature == other.Habitat.Temperature;
        }

        public override int GetHashCode()
        {
            return HashCode.Combine(
                Name,
                Age,
                HasMane,
                Habitat.Name,
                Habitat.Type,
                Habitat.Temperature);
        }

        public override string ToString()
        {
            return $"Mammal {GetType().Name} (Equals/GetHashCode/ToString overridden): {CoreData()}, hasMane={HasMane}";
        }
    }

    public class Tiger : Mammal, IPredator, ISwimmable
    {
        public int StripeCount { get; }

        public Tiger(string? name, int age, Habitat? habitat, int stripeCount)
            : base(name, age, habitat)
        {
            if (stripeCount < 0)
            {
                throw new ArgumentOutOfRangeException(nameof(stripeCount));
            }

            StripeCount = stripeCount;
        }

        public override string MakeSound()
        {
            return $"{Name} growls and chuffs.";
        }

        public override string Move()
        {
            return $"{Name} moves stealthily through the forest.";
        }

        public string Hunt()
        {
            return $"{Name} hunts alone from an ambush.";
        }

        public string Swim()
        {
            return $"{Name} swims well and crosses rivers.";
        }

        public override string ToString()
        {
            return $"Mammal {GetType().Name}: {CoreData()}, stripeCount={StripeCount}";
        }
    }

    public class Owl : Bird, IPredator
    {
        public double FieldOfViewDegrees { get; }

        public Owl(string? name, int age, Habitat? habitat, double fieldOfViewDegrees)
            : base(name, age, habitat)
        {
            if (fieldOfViewDegrees < 0 || fieldOfViewDegrees > 360)
            {
                throw new ArgumentOutOfRangeException(nameof(fieldOfViewDegrees));
            }

            FieldOfViewDegrees = fieldOfViewDegrees;
        }

        public override string Fly()
        {
            return $"{Name} flies silently thanks to soft feathers.";
        }

        public override string MakeSound()
        {
            return $"{Name} hoots: Hoo-hoo!";
        }

        public override string Move()
        {
            return $"{Name} is a nocturnal predator: it flies and perches on branches.";
        }

        public string Hunt()
        {
            return $"{Name} hunts small rodents at night.";
        }

        public override string ToString()
        {
            return $"Bird {GetType().Name}: {CoreData()}, fieldOfViewDegrees={FieldOfViewDegrees}";
        }
    }

    public sealed class Parrot : Bird
    {
        public int VocabularySize { get; }

        public Parrot(string? name, int age, Habitat? habitat, int vocabularySize)
            : base(name, age, habitat)
        {
            if (vocabularySize < 0)
            {
                throw new ArgumentOutOfRangeException(nameof(vocabularySize));
            }

            VocabularySize = vocabularySize;
        }

        public override string Fly()
        {
            return $"{Name} flies quickly and maneuverably.";
        }

        public override string MakeSound()
        {
            return $"{Name} repeats words and makes loud cries.";
        }

        public override string Move()
        {
            return $"{Name} moves along branches and flies in a flock.";
        }

        public override string ToString()
        {
            return $"Bird {GetType().Name} (sealed): {CoreData()}, vocabularySize={VocabularySize}";
        }
    }

    public class Shark : Fish, IPredator
    {
        public int ToothCount { get; }

        public Shark(string? name, int age, Habitat? habitat, int toothCount)
            : base(name, age, habitat)
        {
            if (toothCount < 0)
            {
                throw new ArgumentOutOfRangeException(nameof(toothCount));
            }

            ToothCount = toothCount;
        }

        public override string Swim()
        {
            return $"{Name} swims constantly using its caudal fin.";
        }

        public override string Move()
        {
            return $"{Name} glides through the water column.";
        }

        public string Hunt()
        {
            return $"{Name} tracks prey by smell and electric fields.";
        }

        public override string ToString()
        {
            return $"Fish {GetType().Name}: {CoreData()}, toothCount={ToothCount}";
        }
    }

    public class Crocodile : Animal, IPredator, ISwimmable
    {
        public double LengthMeters { get; }

        public Crocodile(string? name, int age, Habitat? habitat, double lengthMeters)
            : base(name, age, habitat)
        {
            if (lengthMeters <= 0)
            {
                throw new ArgumentOutOfRangeException(nameof(lengthMeters));
            }

            LengthMeters = lengthMeters;
        }

        public override string MakeSound()
        {
            return $"{Name} growls and hisses.";
        }

        public override string Move()
        {
            return $"{Name} crawls on land and swims in water.";
        }

        public string Hunt()
        {
            return $"{Name} hunts from an ambush near water.";
        }

        public string Swim()
        {
            return $"{Name} swims by paddling with its tail.";
        }

        public override string ToString()
        {
            return $"{GetType().Name} (direct descendant of Animal): {CoreData()}, lengthMeters={LengthMeters}";
        }
    }
}