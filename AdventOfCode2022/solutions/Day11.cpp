#include <Helpers.h>
#include <DayBase.h>

/**
* DayEleven
*
* This is a the solution for Day Eleven of Advent of Code 2022.
* https://adventofcode.com/2022/day/11
*
*/
class DayEleven : public DayBase
{
public:
    DayEleven()
        : DayBase(11)
    {}

protected:
    virtual void questionOne(istream& input, ostream& output)
    {
        parseInput(input);

        for (int round = 0; round < 20; ++round)
        {
            for (int m = 0; m < monkeys.size(); ++m)
            {
                Monkey* current = &monkeys[m];

                while (!current->items.empty())
                {
                    unsigned long long currentItem = current->items.front();
                    current->items.pop_front();

                    int next = current->inspect(currentItem);

                    monkeys[next].items.push_back(currentItem);

                    current->inspected++;
                }
            }
        }

        unsigned long long one = 0;
        unsigned long long two = 0;

        for (int i = 0; i < monkeys.size(); ++i)
        {
            if (monkeys[i].inspected > one)
            {
                two = one;
                one = monkeys[i].inspected;
            }
            else if (monkeys[i].inspected > two)
            {
                two = monkeys[i].inspected;
            }
        }

        output << (one * two);

        monkeys.clear();
    }

    virtual void questionTwo(istream& input, ostream& output)
    {
        parseInput(input);

        for (int round = 0; round < 10000; ++round)
        {
            for (int m = 0; m < monkeys.size(); ++m)
            {
                Monkey* current = &monkeys[m];

                while (!current->items.empty())
                {
                    unsigned long long currentItem = current->items.front();
                    current->items.pop_front();

                    int next = current->inspect2(currentItem);

                    currentItem = currentItem % largestDivisor;

                    monkeys[next].items.push_back(currentItem);

                    current->inspected++;
                }
            }
        }

        unsigned long long one = 0;
        unsigned long long two = 0;

        for (int i = 0; i < monkeys.size(); ++i)
        {
            if (monkeys[i].inspected > one)
            {
                two = one;
                one = monkeys[i].inspected;
            }
            else if (monkeys[i].inspected > two)
            {
                two = monkeys[i].inspected;
            }
        }

        output << (one * two);
    }

private:
    class Monkey
    {
    public:
        deque<unsigned long long> items;

        // Operation
        bool isMultiply = false;
        int operationValue = 0;

        // Test
        int divisible = 0;
        int testTrue = 0;
        int testFalse = 0;

        unsigned long long inspected = 0;

        Monkey() {}

        int inspect(unsigned long long& itemValue)
        {
            unsigned long long otherValue = 0;
            if (operationValue == -1)
            {
                otherValue = itemValue;
            }
            else
            {
                otherValue = operationValue;
            }


            if (isMultiply)
            {
                itemValue = itemValue * otherValue;
            }
            else
            {
                itemValue = itemValue + otherValue;
            }

            itemValue /= 3;

            if (itemValue % divisible == 0)
            {
                return testTrue;
            }
            else
            {
                return testFalse;
            }
        }

        int inspect2(unsigned long long& itemValue)
        {
            unsigned long long otherValue = 0;
            if (operationValue == -1)
            {
                otherValue = itemValue;
            }
            else
            {
                otherValue = operationValue;
            }

            if (isMultiply)
            {
                itemValue = itemValue * otherValue;
            }
            else
            {
                itemValue = itemValue + otherValue;
            }

            //itemValue /= 3;

            if (itemValue % divisible == 0)
            {
                return testTrue;
            }
            else
            {
                return testFalse;

            }
        }
    };

    vector<Monkey> monkeys;
    int largestDivisor = 1;

    void parseInput(istream& input)
    {
        largestDivisor = 1;

        Monkey* current = nullptr;
        string line;
        while (getline(input, line))
        {
            vector<string> args = splitString(line, " ");

            if (args.size() == 1)
            {
                // Do nothing
            }
            else if (args[0].compare("Monkey") == 0)
            {
                monkeys.emplace_back();
                current = &monkeys.back();
            }
            else if (args[2].compare("Starting") == 0)
            {
                for (int i = 4; i < args.size(); ++i)
                {
                    if (i < args.size() - 1)
                    {
                        current->items.push_back(atoi(args[i].substr(0, args[i].length() - 1).c_str()));
                    }
                    else
                    {
                        current->items.push_back(atoi(args[i].c_str()));
                    }
                }
            }
            else if (args[2].compare("Operation:") == 0)
            {
                current->isMultiply = args[6].compare("*") == 0;

                if (args[7].compare("old") == 0)
                {
                    current->operationValue = -1;
                }
                else
                {
                    current->operationValue = atoi(args[7].c_str());
                }
            }
            else if (args[2].compare("Test:") == 0)
            {
                current->divisible = atoi(args[5].c_str());

                largestDivisor *= current->divisible;
            }
            else if (args[5].compare("true:") == 0)
            {
                current->testTrue = atoi(args[9].c_str());
            }
            else if (args[5].compare("false:") == 0)
            {
                current->testFalse = atoi(args[9].c_str());
            }
        }
    }
};

DayEleven g_dayEleven = DayEleven();
