#include <Helpers.h>
#include <DayBase.h>

/**
* DayTen
*
* This is a the solution for Day Ten of Advent of Code 2022.
* https://adventofcode.com/2022/day/10
*
*/
class DayTen : public DayBase
{
public:
    DayTen()
        : DayBase(10)
    {}

protected:
    virtual void questionOne(istream& input, ostream& output)
    {
        string line;

        int cycle = 0;
        int currentX = 1;
        int total = 0;

        while (getline(input, line))
        {
            size_t separator = line.find(' ');
            string command = line.substr(0, separator);

            if (command.compare("noop") == 0)
            {
                total += incrementCycle(cycle, currentX);
            }
            else if (command.compare("addx") == 0)
            {
                int amount = atoi(line.substr(separator + 1).c_str());

                for (int i = 0; i < 2; ++i)
                {
                    total += incrementCycle(cycle, currentX);
                }

                currentX += amount;
            }
        }

        output << total;
    }

    virtual void questionTwo(istream& input, ostream& output)
    {
        string line;

        int cycle = 0;
        int currentX = 1;
        int total = 0;

        stringstream ss;
        ss << "\n";
        while (getline(input, line))
        {
            size_t separator = line.find(' ');
            string command = line.substr(0, separator);

            if (command.compare("noop") == 0)
            {
                drawPixel(cycle, currentX, ss);
            }
            else if (command.compare("addx") == 0)
            {
                int amount = atoi(line.substr(separator + 1).c_str());

                for (int i = 0; i < 2; ++i)
                {
                    drawPixel(cycle, currentX, ss);
                }

                currentX += amount;
            }
        }

        output << ss.str();
    }

private:
    int incrementCycle(int& cycle, const int currentX)
    {
        cycle++;

        if (cycle == 20 || cycle == 60 || cycle == 100
            || cycle == 140 || cycle == 180 || cycle == 220)
        {
            return currentX * cycle;
        }

        return 0;
    }

    void drawPixel(int& cycle, const int currentX, ostream& stream)
    {
        int horizontalPos = (cycle % 40);

        if (horizontalPos >= currentX - 1 && horizontalPos <= currentX + 1)
        {
            stream << "#";
        }
        else
        {
            stream << ".";
        }

        if (horizontalPos == 39)
        {
            stream << "\n";
        }

        cycle++;
    }
};

DayTen g_dayTen = DayTen();
