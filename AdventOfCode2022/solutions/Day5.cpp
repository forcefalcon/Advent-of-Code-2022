#include <Helpers.h>
#include <DayBase.h>

/**
* DayFive
*
* This is a the solution for Day Five of Advent of Code 2022.
* https://adventofcode.com/2022/day/5
*
*/
class DayFive : public DayBase
{
public:
    DayFive()
        : DayBase(5)
    {}

protected:
    virtual void questionOne(istream& input, ostream& output)
    {
        string line;

        vector<string> inputStacks;
        while (getline(input, line))
        {
            if (line.empty())
            {
                break;
            }

            inputStacks.emplace_back(line);
        }

        size_t totalStacks = (inputStacks.back().length() + 1) / 4;
        inputStacks.pop_back();

        vector<stack<char>> stacks;
        stacks.resize(totalStacks);

        while (!inputStacks.empty())
        {
            string inputStack = inputStacks.back();

            int charPos = 1;
            for (int i = 0; i < totalStacks; ++i)
            {
                char box = inputStack[charPos];

                if (box != ' ')
                    stacks[i].push(box);

                charPos += 4;
            }

            inputStacks.pop_back();
        }

        while (getline(input, line))
        {
            size_t startOffset = 5;
            size_t endOffset = line.find(' ', startOffset);
            int moveNum = atoi(line.substr(startOffset, endOffset - startOffset).c_str());

            startOffset = endOffset + 6;
            endOffset = line.find(' ', startOffset);
            int startStack = atoi(line.substr(startOffset, endOffset - startOffset).c_str()) - 1;

            startOffset = endOffset + 4;
            int endStack = atoi(line.substr(startOffset).c_str()) - 1;

            //cout << moveNum << ":" << startStack << "->" << endStack << '\n';

            for (int i = 0; i < moveNum; ++i)
            {
                if (stacks[startStack].empty())
                {
                    cerr << "Empty Stack!" << '\n';
                    break;
                }

                stacks[endStack].push(stacks[startStack].top());
                stacks[startStack].pop();
            }
        }

        for (int i = 0; i < totalStacks; ++i)
        {
            output << stacks[i].top();
        }
    }

    virtual void questionTwo(istream& input, ostream& output)
    {
        string line;

        vector<string> inputStacks;
        while (getline(input, line))
        {
            if (line.empty())
            {
                break;
            }

            inputStacks.emplace_back(line);
        }

        size_t totalStacks = (inputStacks.back().length() + 1) / 4;
        inputStacks.pop_back();

        vector<stack<char>> stacks;
        stacks.resize(totalStacks);

        while (!inputStacks.empty())
        {
            string inputStack = inputStacks.back();

            int charPos = 1;
            for (int i = 0; i < totalStacks; ++i)
            {
                char box = inputStack[charPos];

                if (box != ' ')
                    stacks[i].push(box);

                charPos += 4;
            }

            inputStacks.pop_back();
        }

        while (getline(input, line))
        {
            size_t startOffset = 5;
            size_t endOffset = line.find(' ', startOffset);
            int moveNum = atoi(line.substr(startOffset, endOffset - startOffset).c_str());

            startOffset = endOffset + 6;
            endOffset = line.find(' ', startOffset);
            int startStack = atoi(line.substr(startOffset, endOffset - startOffset).c_str()) - 1;

            startOffset = endOffset + 4;
            int endStack = atoi(line.substr(startOffset).c_str()) - 1;

            //cout << moveNum << ":" << startStack << "->" << endStack << '\n';

            stack<int> tempStack;
            for (int i = 0; i < moveNum; ++i)
            {
                if (stacks[startStack].empty())
                {
                    cerr << "Empty Stack!" << '\n';
                    break;
                }

                tempStack.push(stacks[startStack].top());
                stacks[startStack].pop();
            }

            for (int i = 0; i < moveNum; ++i)
            {
                stacks[endStack].push(tempStack.top());
                tempStack.pop();
            }
        }

        for (int i = 0; i < totalStacks; ++i)
        {
            output << stacks[i].top();
        }
    }
};

DayFive g_dayFive = DayFive();
