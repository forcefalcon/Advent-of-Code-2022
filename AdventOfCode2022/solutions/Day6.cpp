#include <Helpers.h>
#include <DayBase.h>

/**
* DaySix
*
* This is a the solution for Day Six of Advent of Code 2022.
* https://adventofcode.com/2022/day/6
*
*/
class DaySix : public DayBase
{
public:
    DaySix()
        : DayBase(6)
    {}

protected:
    virtual void questionOne(istream& input, ostream& output)
    {
        deque<char> chars;
        char current;
        int count = 0;
        while (input.get(current))
        {
            count++;

            if (chars.size() < 4)
            {
                chars.push_back(current);
            }
            else
            {
                chars.pop_front();
                chars.push_back(current);
            }

            if (chars.size() == 4)
            {
                if (chars[0] != chars[1]
                    && chars[0] != chars[2]
                    && chars[0] != chars[3]
                    && chars[1] != chars[2]
                    && chars[1] != chars[3]
                    && chars[2] != chars[3])
                {
                    break;
                }
            }
        }

        output << count;
    }

    virtual void questionTwo(istream& input, ostream& output)
    {
        int max_size = 14;

        deque<char> chars;
        char current;
        int count = 0;
        while (input.get(current))
        {
            count++;

            if (chars.size() < max_size)
            {
                chars.push_back(current);
            }
            else
            {
                chars.pop_front();
                chars.push_back(current);
            }

            if (chars.size() == max_size)
            {
                if (isUnique(chars, 0))
                {
                    break;
                }
            }
        }

        output << count;
    }

private:
    bool isUnique(deque<char> chars, int startIndex)
    {
        for (int i = startIndex + 1; i < chars.size(); ++i)
        {
            if (chars[startIndex] == chars[i])
                return false;
        }

        if (startIndex == chars.size())
            return true;

        return isUnique(chars, startIndex + 1);
    }
};

DaySix g_daySix = DaySix();
