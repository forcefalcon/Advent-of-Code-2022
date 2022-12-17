#include "Day3.h"

int getValueForCharacter(char input)
{
    if (input >= 'A' && input <= 'Z')
    {
        return input - 'A' + 27;
    }
    else
    {
        return input - 'a' + 1;
    }
}

void DayThree::questionOne(istream& input, ostream& output)
{
    string line;

    int total = 0;

    while (getline(input, line))
    {
        bool found = false;
        size_t halfLength = line.length() / 2;
        for (size_t i = 0; i < halfLength; ++i)
        {
            char first = line[i];
            for (size_t j = halfLength; j < line.length(); ++j)
            {
                char second = line[j];
                if (first == second)
                {
                    total += getValueForCharacter(first);
                    found = true;
                    break;
                }
            }
            if (found)
                break;
        }
    }

    output << total;
}

void DayThree::questionTwo(istream& input, ostream& output)
{
    string line1, line2, line3;

    int total = 0;

    while (getline(input, line1) && getline(input, line2) && getline(input, line3))
    {
        bool found = false;
        for (size_t i = 0; i < line1.length(); ++i)
        {
            char first = line1[i];
            for (size_t j = 0; j < line2.length(); ++j)
            {
                char second = line2[j];
                for (size_t k = 0; k < line3.length(); ++k)
                {
                    char third = line3[k];
                    if (first == second && first == third)
                    {
                        total += getValueForCharacter(first);
                        found = true;
                        break;
                    }
                }
                if (found)
                    break;
            }
            if (found)
                break;
        }
    }

    output << total;
}
