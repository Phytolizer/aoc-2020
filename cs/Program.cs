using System.Diagnostics;
using AdventOfCode;
using NDesk.Options;

void PrintUsage()
{
    var mainModule = Process.GetCurrentProcess().MainModule;
    var programName = "aoc2020";

    if (mainModule != null)
    {
        programName = mainModule.FileName;
    }
    Console.WriteLine($"Usage: {programName} [OPTIONS]");
    Console.WriteLine("  OPTIONS:");
    Console.WriteLine("    -h,--help            Display this help message");
    Console.WriteLine("    -d,--day=<DAY>       Set the day to run");
    Console.WriteLine("    -i,--input=<INPUT>   Set the input file to use");
}

void RunDay(int day, string inputFile)
{
    switch (day)
    {
        case 1:
            Day01.Run(inputFile);
            break;
    }
}

var help = false;
var day = 0;
var input = "input.txt";

var p = new OptionSet() {
    { "d|day=", v => day = int.Parse(v) },
    { "i|input=", v => input = v },
    { "h|?|help", v => help = v != null },
};

var extra = p.Parse(args);

if (extra.Count > 0)
{
    Console.Error.WriteLine("Unexpected extra arguments.");
    Environment.Exit(1);
}

if (help)
{
    PrintUsage();
    Environment.Exit(0);
}
if (day > 25 || day < 1)
{
    PrintUsage();
    Console.Error.WriteLine($"{day} is not a valid day.");
    Environment.Exit(1);
}

if (day == 0)
{
    foreach (var currentDay in Enumerable.Range(1, 25))
    {
        RunDay(currentDay, input);
    }
}
else
{
    RunDay(day, input);
}
