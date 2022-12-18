#include <Helpers.h>
#include <DayBase.h>

/**
* DayOne
*
* This is a the solution for Day One of Advent of Code 2022.
* https://adventofcode.com/2022/day/1
*
*/
class DayOne : public DayBase
{
public:
    DayOne()
        : DayBase(1)
    {}

protected:
    virtual void questionOne(istream& input, ostream& output)
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

    virtual void questionTwo(istream& input, ostream& output)
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
};

DayOne g_dayOne = DayOne();
