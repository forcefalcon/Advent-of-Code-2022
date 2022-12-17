#include "Day1.h"

void DayOne::questionOne(istream& input, ostream& output)
{
    string line;

    int current = 0;
    int highest = 0;

    while (getline(input, line))
    {
        int value = atoi(line.c_str());
        if (value == 0)
        {
            if (highest < current)
                highest = current;

            current = 0;
        }
        else
        {
            current += value;
        }
    }

    output << highest;
}

void DayOne::questionTwo(istream& input, ostream& output)
{
    string line;

    int current = 0;
    int first = 0;
    int second = 0;
    int third = 0;

    while (getline(input, line))
    {
        int value = atoi(line.c_str());
        if (value == 0)
        {
            if (current > first)
            {
                third = second;
                second = first;
                first = current;
            }
            else if (current > second)
            {
                third = second;
                second = current;
            }
            else if (current > third)
            {
                third = current;
            }

            current = 0;
        }
        else
        {
            current += value;
        }
    }

    output << (first + second + third);
}