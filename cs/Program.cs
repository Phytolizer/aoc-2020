using AdventOfCode;

using McMaster.Extensions.CommandLineUtils;

public class Program
{
    public static int Main(string[] args) => CommandLineApplication.Execute<Program>(args);

    void RunDay(int day, string inputFile)
    {
        switch (day)
        {
            case 1:
                Day01.Run(inputFile);
                break;
        }
    }

    [Option(ShortName = "d")]
    public int Day { get; } = 0;
    [Option(ShortName = "i")]
    public string? Input { get; private set; }

    private void OnExecute()
    {
        if (Day > 25 || Day < 0)
        {
            Console.Error.WriteLine($"{Day} is not a valid day.");
            Environment.Exit(1);
        }

        Input ??= $"Day{Day:00}/input.txt";

        if (Day == 0)
        {
            foreach (var currentDay in Enumerable.Range(1, 25))
            {
                RunDay(currentDay, Input);
            }
        }
        else
        {
            RunDay(Day, Input);
        }
    }
}
