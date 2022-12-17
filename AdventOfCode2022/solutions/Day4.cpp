#include "Day4.h"

void DayFour::questionOne(istream& input, ostream& output)
{
    string line;

    int totalOverlaps = 0;
    while (getline(input, line))
    {
        // Get Each Set
        size_t comma = line.find(',');
        string first = line.substr(0, comma);
        string second = line.substr(comma + 1);

        size_t dash = first.find('-');
        int start1 = atoi(first.substr(0, dash).c_str());
        int end1 = atoi(first.substr(dash + 1).c_str());

        dash = second.find('-');
        int start2 = atoi(second.substr(0, dash).c_str());
        int end2 = atoi(second.substr(dash + 1).c_str());

        if (start1 == start2)
        {
            totalOverlaps += 1;
        }
        else if (start1 < start2)
        {
            if (end1 >= end2)
            {
                totalOverlaps += 1;
            }
        }
        else if (end2 >= end1)
        {
            totalOverlaps += 1;
        }
    }

    output << totalOverlaps;
}

void DayFour::questionTwo(istream& input, ostream& output)
{
    string line;

    int totalOverlaps = 0;
    while (getline(input, line))
    {
        // Get Each Set
        size_t comma = line.find(',');
        string first = line.substr(0, comma);
        string second = line.substr(comma + 1);

        size_t dash = first.find('-');
        int start1 = atoi(first.substr(0, dash).c_str());
        int end1 = atoi(first.substr(dash + 1).c_str());

        dash = second.find('-');
        int start2 = atoi(second.substr(0, dash).c_str());
        int end2 = atoi(second.substr(dash + 1).c_str());

        if (start1 == start2)
        {
            totalOverlaps += 1;
        }
        else if (start1 < start2)
        {
            if (end1 >= start2)
            {
                totalOverlaps += 1;
            }
        }
        else if (end2 >= start1)
        {
            totalOverlaps += 1;
        }
    }

    output << totalOverlaps;
}