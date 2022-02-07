namespace AdventOfCode;

internal static class Day01
{
    public static void Run(string inputFile)
    {
        if (!File.Exists(inputFile))
        {
            Console.Error.WriteLine($"{inputFile} could not be found.");
            Environment.Exit(1);
        }

        var input = File.ReadAllText(inputFile);

        var floor = 0;

        foreach (var c in input)
        {
            switch (c)
            {
                case '(':
                    floor -= 1;
                    break;
                case ')':
                    floor += 1;
                    break;
            }
        }

        Console.WriteLine($"Part 1: floor {floor}");
    }
}
