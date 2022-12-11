// AdventOfCode2022.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <deque>
#include <map>
#include <set>
#include <chrono>
#include <sstream>

using namespace std;

/*
 * Helpers
 */
int sign(int x) {
    return (x > 0) - (x < 0);
}

vector<string> splitString(const string& input, const string& delimeter)
{
    vector<string> result;
    size_t start = 0;
    size_t end = input.find(delimeter, start);
    size_t delimeterLength = delimeter.length();

    while (end != -1)
    {
        result.push_back(input.substr(start, end-start));
        start = end+delimeterLength;
        end = input.find(delimeter, start);
    }

    result.push_back(input.substr(start));

    return result;
}

long long runQuestion(void(*function)(istream& input), const char* inputFile)
{
    ifstream input;
    input.open(inputFile);

    auto start = chrono::high_resolution_clock::now();

    function(input);

    auto elapsed = chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<chrono::microseconds>(elapsed).count();
    cout << "Time: " << microseconds << "us" << "\n\n";

    input.close();

    return microseconds;
}

class DayBase
{
public:
    DayBase(string day, string inputFile) 
        : day(day) 
    {
        input.open(inputFile);
    }

    virtual ~DayBase()
    {
        input.close();
    }

    void run()
    {
        stringstream output;
        output << "Day " << day << "\n";
        output << "----------\n";
        output << "Question 1\n";
        output << "Answer: ";
        questionOne(input, output);
        output << "\n\n";

        resetInput(input);

        output << "Question 2\n";
        output << "Answer: ";
        questionTwo(input, output);
        output << "\n\n";

        cout << output.str();
    }

    void runTest(string testFileOne, string testFileTwo = "")
    {
        ifstream testInput;
        testInput.open(testFileOne);

        stringstream output;
        output << "Day " << day << " Test\n";
        output << "----------\n";
        output << "Question 1\n";
        output << "Answer: ";
        questionOne(testInput, output);
        output << "\n\n";

        if (testFileTwo.empty())
        {
            resetInput(testInput);
        }
        else
        {
            testInput.close();
            testInput.open(testFileTwo);
        }

        output << "Question 2\n";
        output << "Answer: ";
        questionTwo(testInput, output);
        output << "\n\n";

        cout << output.str();

        testInput.close();
    }

    long long testPerformance()
    {
        const int RUN_COUNT = 100;

        stringstream output;
        long long total = 0;

        cout << "Day " << day << "\n";
        cout << "----------\n";
        cout << "Question 1\n";

        auto start = chrono::high_resolution_clock::now();

        for (int i = 0; i < RUN_COUNT; ++i)
        {
            questionOne(input, output);
            resetInput(input);
        }

        auto elapsed = chrono::high_resolution_clock::now() - start;
        long long microseconds = std::chrono::duration_cast<chrono::microseconds>(elapsed).count() / RUN_COUNT;
        cout << "Avg Time: " << microseconds << "us" << "\n";

        total += microseconds;

        cout << "Question 2\n";

        start = chrono::high_resolution_clock::now();

        for (int i = 0; i < RUN_COUNT; ++i)
        {
            questionTwo(input, output);
            resetInput(input);
        }

        elapsed = chrono::high_resolution_clock::now() - start;
        microseconds = std::chrono::duration_cast<chrono::microseconds>(elapsed).count() / RUN_COUNT;
        cout << "Avg Time: " << microseconds << "us" << "\n\n";

        return total;
    }

protected:
    virtual void questionOne(istream& input, ostream& output) = 0;
    virtual void questionTwo(istream& input, ostream& output) = 0;

private:
    string day;
    ifstream input;
    ifstream testInput;

    virtual void resetData() {}

    void resetInput(ifstream& input)
    {
        input.clear();
        input.seekg(0, std::ios::beg);
    }
};

/*
 * Day 1
 */
class DayOne : public DayBase
{
public:
    DayOne()
        : DayBase("One", "input\\Day1_Input.txt")
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

/*
 * Day 2
 */
class DayTwo : public DayBase
{
    enum Hand
    {
        Rock,
        Paper,
        Scissors
    };

public:
    DayTwo()
        : DayBase("Two", "input\\Day2_Input.txt")
    {}

protected:
    virtual void questionOne(istream& input, ostream& output)
    {
        string line;

        int total = 0;

        while (getline(input, line))
        {
            Hand opponent;
            Hand player;

            switch (line[0])
            {
            case 'A':
                opponent = Rock;
                break;
            case 'B':
                opponent = Paper;
                break;
            case 'C':
                opponent = Scissors;
                break;
            default:
                cerr << "Error with Opponent!" << "\n";
                continue;
            }

            switch (line[2])
            {
            case 'X':
                player = Rock;
                total += 1;
                break;
            case 'Y':
                player = Paper;
                total += 2;
                break;
            case 'Z':
                player = Scissors;
                total += 3;
                break;
            default:
                cerr << "Error with Player!" << "\n";
                continue;
            }

            // Points for Game
            if (opponent == Rock && player == Paper ||
                opponent == Paper && player == Scissors ||
                opponent == Scissors && player == Rock)
            {
                total += 6;
            }
            else if (opponent == player)
            {
                total += 3;
            }
        }

        output << (total);
    }

    virtual void questionTwo(istream& input, ostream& output)
    {
        string line;
        int total = 0;
        while (getline(input, line))
        {
            Hand opponent;
            Hand player;

            switch (line[0])
            {
            case 'A':
                opponent = Rock;
                break;
            case 'B':
                opponent = Paper;
                break;
            case 'C':
                opponent = Scissors;
                break;
            default:
                cerr << "Error with Opponent!" << "\n";
                continue;
            }

            switch (line[2])
            {
            case 'X':
                switch (opponent)
                {
                case Rock:
                    player = Scissors;
                    break;
                case Paper:
                    player = Rock;
                    break;
                case Scissors:
                    player = Paper;
                    break;
                }
                break;
            case 'Y':
                switch (opponent)
                {
                case Rock:
                    player = Rock;
                    break;
                case Paper:
                    player = Paper;
                    break;
                case Scissors:
                    player = Scissors;
                    break;
                }
                break;
            case 'Z':
                switch (opponent)
                {
                case Rock:
                    player = Paper;
                    break;
                case Paper:
                    player = Scissors;
                    break;
                case Scissors:
                    player = Rock;
                    break;
                }
                break;
            default:
                cerr << "Error with Player!" << "\n";
                continue;
            }

            // Points for Symbol
            switch (player)
            {
            case Rock:
                total += 1;
                break;
            case Paper:
                total += 2;
                break;
            case Scissors:
                total += 3;
                break;
            }

            // Points for Game
            if (opponent == Rock && player == Paper ||
                opponent == Paper && player == Scissors ||
                opponent == Scissors && player == Rock)
            {
                total += 6;
            }
            else if (opponent == player)
            {
                total += 3;
            }
        }

        output << (total);
    }
};

/*
 * Day 3
 */
class DayThree : public DayBase
{
public:
    DayThree() : DayBase("Three", "input\\Day3_Input.txt") {}

protected:
    virtual void questionOne(istream& input, ostream& output)
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

    void questionTwo(istream& input, ostream& output)
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

private:
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
};

/*
 * Day 4
 */
class DayFour : public DayBase
{
public:
    DayFour() : DayBase("Four", "input\\Day4_Input.txt") {}
protected:
    virtual void questionOne(istream& input, ostream& output)
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

    virtual void questionTwo(istream& input, ostream& output)
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
};

/*
 * Day 5
 */
class DayFive : public DayBase
{
public:
    DayFive() : DayBase("Five", "input\\Day5_Input.txt") {}
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

/*
 * Day 6
 */
class DaySix : public DayBase
{
public:
    DaySix() : DayBase("Six", "input\\Day6_Input.txt") {}
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

/*
 * Day 7
 */
class DaySeven : public DayBase
{
public:
    DaySeven() : DayBase("Seven", "input\\Day7_Input.txt") {}
protected:
    virtual void questionOne(istream& input, ostream& output)
    {
        string line;

        Directory root("root", nullptr);
        Directory* current = &root;
        while (getline(input, line))
        {
            if (line[0] == '$')
            {
                size_t separator = line.find(' ', 2);
                string command = line.substr(2, separator - 2);

                if (command.compare("cd") == 0)
                {
                    string argument = line.substr(separator + 1);

                    if (argument.compare("/") == 0)
                    {
                        current = &root;
                    }
                    else if (argument.compare("..") == 0)
                    {
                        current = current->parent;
                    }
                    else
                    {
                        current = current->getDirectory(argument);
                    }
                }
                else //ls
                {
                    //Do nothing
                }
            }
            else
            {
                size_t separator = line.find(' ');
                string first = line.substr(0, separator);
                string name = line.substr(separator + 1);

                if (first.compare("dir") == 0)
                {
                    current->directories.emplace_back(name, current);
                }
                else
                {
                    current->files.emplace_back(name, atoi(first.c_str()));
                }
            }
        }

        int total = traverseDirectories(&root);

        output << total;
    }

    virtual void questionTwo(istream& input, ostream& output)
    {
        string line;

        Directory root("root", nullptr);
        Directory* current = &root;
        while (getline(input, line))
        {
            if (line[0] == '$')
            {
                size_t separator = line.find(' ', 2);
                string command = line.substr(2, separator - 2);

                if (command.compare("cd") == 0)
                {
                    string argument = line.substr(separator + 1);

                    if (argument.compare("/") == 0)
                    {
                        current = &root;
                    }
                    else if (argument.compare("..") == 0)
                    {
                        current = current->parent;
                    }
                    else
                    {
                        current = current->getDirectory(argument);
                    }
                }
                else //ls
                {
                    //Do nothing
                }
            }
            else
            {
                size_t separator = line.find(' ');
                string first = line.substr(0, separator);
                string name = line.substr(separator + 1);

                if (first.compare("dir") == 0)
                {
                    current->directories.emplace_back(name, current);
                }
                else
                {
                    current->files.emplace_back(name, atoi(first.c_str()));
                }
            }
        }

        int freeSpace = 70000000 - root.getTotalSize();
        int neededSpace = 30000000 - freeSpace;

        int total = findSmallest(&root, 70000000, neededSpace);

        output << total;
    }

private:
    struct File
    {
        string name;
        int size;

        File(string aName, int aSize) : name(aName), size(aSize) {}
    };

    struct Directory
    {
        string name;

        Directory* parent = nullptr;

        vector<Directory> directories;
        vector<File> files;

        Directory(string aName, Directory* aParent) : name(aName), parent(aParent) {}

        Directory* getDirectory(string name)
        {
            for (int d = 0; d < directories.size(); ++d)
            {
                Directory* current = &directories[d];
                if (current->name.compare(name) == 0)
                {
                    return current;
                }
            }

            return nullptr;
        }

        int getTotalSize()
        {
            int total = 0;
            for (int d = 0; d < directories.size(); ++d)
            {
                total += directories[d].getTotalSize();
            }

            for (int f = 0; f < files.size(); ++f)
            {
                total += files[f].size;
            }

            return total;
        }
    };

    int traverseDirectories(Directory* current)
    {
        int total = 0;
        if (current->getTotalSize() <= 100000)
        {
            total += current->getTotalSize();
        }

        for (int d = 0; d < current->directories.size(); ++d)
        {
            total += traverseDirectories(&current->directories[d]);
        }

        return total;
    }

    int findSmallest(Directory* current, int smallest, int freeSpace)
    {
        int currentSmallest = smallest;
        int currentSize = current->getTotalSize();
        if (currentSize >= freeSpace && currentSize < currentSmallest)
        {
            currentSmallest = currentSize;
        }

        for (int d = 0; d < current->directories.size(); ++d)
        {
            int newSmallest = findSmallest(&current->directories[d], currentSmallest, freeSpace);
            if (newSmallest < currentSmallest)
            {
                currentSmallest = newSmallest;
            }
        }

        return currentSmallest;
    }
};

/*
 * Day 8
 */
class DayEight : public DayBase
{
public:
    DayEight() : DayBase("Eight", "input\\Day8_Input.txt") {}
protected:
    virtual void questionOne(istream& input, ostream& output)
    {
        vector<vector<int>> grid;
        string line;

        while (getline(input, line))
        {
            grid.emplace_back();
            vector<int>& row = grid.back();

            for (int c = 0; c < line.length(); ++c)
            {
                row.emplace_back(line[c] - 48);
            }
        }

        size_t height = grid.size();
        size_t width = grid.front().size();
        size_t visibleCount = height * 2 + (width - 2) * 2;

        for (int y = 1; y < height - 1; ++y)
        {
            for (int x = 1; x < width - 1; ++x)
            {
                if (search(x, y, grid))
                {
                    ++visibleCount;
                }
            }
        }

        output << visibleCount;
    }

    virtual void questionTwo(istream& input, ostream& output)
    {
        vector<vector<int>> grid;
        string line;

        while (getline(input, line))
        {
            grid.emplace_back();
            vector<int>& row = grid.back();

            for (int c = 0; c < line.length(); ++c)
            {
                row.emplace_back(line[c] - 48);
            }
        }

        size_t height = grid.size();
        size_t width = grid.front().size();
        int bestScore = 0;

        for (int y = 1; y < height - 1; ++y)
        {
            for (int x = 1; x < width - 1; ++x)
            {
                int score = calculateScenicScore(x, y, grid);
                if (score > bestScore)
                {
                    bestScore = score;
                }
            }
        }

        output << bestScore;
    }

private:
    bool search(int x, int y, vector<vector<int>>& grid)
    {
        size_t height = grid.size();
        size_t width = grid.front().size();
        int value = grid[y][x];

        bool visibleTop = true;
        bool visibleBottom = true;
        bool visibleLeft = true;
        bool visibleRight = true;

        for (int j = 0; j < height; ++j)
        {
            if (j < y)
            {
                if (grid[j][x] >= value)
                {
                    visibleTop = false;
                    j = y;
                }
            }
            else if (j > y)
            {
                if (grid[j][x] >= value)
                {
                    visibleBottom = false;
                    break;
                }
            }
        }

        for (int k = 0; k < width; ++k)
        {
            if (k < x)
            {
                if (grid[y][k] >= value)
                {
                    visibleLeft = false;
                    k = x;
                }
            }
            else if (k > x)
            {
                if (grid[y][k] >= value)
                {
                    visibleRight = false;
                    break;
                }
            }
        }

        return visibleTop || visibleBottom || visibleLeft || visibleRight;
    }

    int calculateScenicScore(int x, int y, vector<vector<int>>& grid)
    {
        size_t height = grid.size();
        size_t width = grid.front().size();
        int value = grid[y][x];

        int scoreMinX = 0;
        int scoreMaxX = 0;
        int scoreMinY = 0;
        int scoreMaxY = 0;

        int minX = x - 1;
        while (minX >= 0)
        {
            scoreMinX++;
            if (grid[y][minX] >= value)
            {
                break;
            }
            minX--;
        }

        int maxX = x + 1;
        while (maxX < width)
        {
            scoreMaxX++;
            if (grid[y][maxX] >= value)
            {
                break;
            }
            maxX++;
        }

        int minY = y - 1;
        while (minY >= 0)
        {
            scoreMinY++;
            if (grid[minY][x] >= value)
            {
                break;
            }
            minY--;
        }


        int maxY = y + 1;
        while (maxY < height)
        {
            scoreMaxY++;
            if (grid[maxY][x] >= value)
            {
                break;
            }
            maxY++;
        }

        return scoreMinX * scoreMaxX * scoreMinY * scoreMaxY;
    }
};

/*
 * Day 9
 */
class DayNine : public DayBase
{
public:
    DayNine() : DayBase("Nine", "input\\Day9_Input.txt") {}
protected:
    virtual void questionOne(istream& input, ostream& output)
    {
        string line;

        int totalCount = 0;
        set<string> moves;

        int headX = 0; int headY = 0; int tailX = 0; int tailY = 0;
        moves.insert("0,0");

        stringstream ss;
        while (getline(input, line))
        {
            int moveCount = atoi(line.substr(2).c_str());

            for (int i = 0; i < moveCount; ++i)
            {
                switch (line[0])
                {
                case 'R':
                    headX++;
                    break;
                case 'L':
                    headX--;
                    break;
                case 'U':
                    headY++;
                    break;
                case 'D':
                    headY--;
                    break;
                }

                calculateTail(headX, headY, tailX, tailY);
                ss << tailX << "," << tailY;
                moves.insert(ss.str());
                ss.str(string());
            }
        }

        output << moves.size();
    }

    virtual void questionTwo(istream& input, ostream& output)
    {
        string line;

        int totalCount = 0;
        set<string> moves;

        const int NUM_KNOTS = 10;
        int X[NUM_KNOTS];
        int Y[NUM_KNOTS];
        moves.insert("0,0");

        for (int i = 0; i < NUM_KNOTS; ++i)
        {
            X[i] = 0;
            Y[i] = 0;
        }

        stringstream ss;
        while (getline(input, line))
        {
            int moveCount = atoi(line.substr(2).c_str());

            for (int i = 0; i < moveCount; ++i)
            {
                switch (line[0])
                {
                case 'R':
                    X[0]++;
                    break;
                case 'L':
                    X[0]--;
                    break;
                case 'U':
                    Y[0]++;
                    break;
                case 'D':
                    Y[0]--;
                    break;
                }

                for (int i = 0; i < NUM_KNOTS - 1; ++i)
                {
                    calculateTail(X[i], Y[i], X[i + 1], Y[i + 1]);
                }
                ss << X[9] << "," << Y[9];
                moves.insert(ss.str());
                ss.str(string());
            }
        }

        output << moves.size();
    }

private:
    void calculateTail(const int headX, const int headY, int& tailX, int& tailY)
    {
        if (headY > tailY + 1)
        {
            tailY = headY - 1;
            if (headX != tailX)
            {
                int diff = headX - tailX;

                tailX += sign(diff);
            }
        }
        else if (headY < tailY - 1)
        {
            tailY = headY + 1;
            if (headX != tailX)
            {
                int diff = headX - tailX;

                tailX += sign(diff);
            }
        }
        else if (headX > tailX + 1)
        {
            tailX = headX - 1;
            if (headY != tailY)
            {
                int diff = headY - tailY;

                tailY += sign(diff);
            }
        }
        else if (headX < tailX - 1)
        {
            tailX = headX + 1;
            if (headY != tailY)
            {
                int diff = headY - tailY;

                tailY += sign(diff);
            }
        }
    }

    void calculateTailTake2(const int headX, const int headY, int& tailX, int& tailY)
    {
        int diffX = headX - tailX;
        int diffY = headY - tailY;

        if (abs(diffY) >= 2)
        {
            tailY += sign(diffY);

            if (headX != tailX)
            {
                tailX += sign(diffX);
            }
        }

        if (abs(diffX) >= 2)
        {
            tailX += sign(diffX);

            if (headY != tailY)
            {
                tailY += sign(diffY);
            }
        }
    }
};

//void Day9Q1Take2(istream& input)
//{
//    string line;
//
//    int totalCount = 0;
//    set<pair<int, int>> moves;
//
//    int headX = 0; int headY = 0; int tailX = 0; int tailY = 0;
//    moves.insert(pair<int,int>(0,0));
//
//    while (getline(input, line))
//    {
//        int moveCount = atoi(line.substr(2).c_str());
//
//        char dir = line[0];
//
//        for (int i = 0; i < moveCount; ++i)
//        {
//            switch (dir)
//            {
//            case 'R':
//                headX++;
//                break;
//            case 'L':
//                headX--;
//                break;
//            case 'U':
//                headY++;
//                break;
//            case 'D':
//                headY--;
//                break;
//            }
//
//            calculateTailTake2(headX, headY, tailX, tailY);
//            moves.insert(pair<int,int>(tailX, tailY));
//        }
//    }
//
//    cout << "Answer: " << moves.size() << endl;
//}
//
//void Day9Q2Take2(istream& input)
//{
//    string line;
//
//    int totalCount = 0;
//    set<pair<int, int>> moves;
//
//    const int NUM_KNOTS = 10;
//    int X[NUM_KNOTS];
//    int Y[NUM_KNOTS];
//    moves.insert(pair<int, int>(0, 0));
//
//    for (int i = 0; i < NUM_KNOTS; ++i)
//    {
//        X[i] = 0;
//        Y[i] = 0;
//    }
//
//    while (getline(input, line))
//    {
//        int moveCount = atoi(line.substr(2).c_str());
//
//        char dir = line[0];
//        for (int i = 0; i < moveCount; ++i)
//        {
//            switch (dir)
//            {
//            case 'R':
//                X[0]++;
//                break;
//            case 'L':
//                X[0]--;
//                break;
//            case 'U':
//                Y[0]++;
//                break;
//            case 'D':
//                Y[0]--;
//                break;
//            }
//
//            for (int i = 0; i < NUM_KNOTS - 1; ++i)
//            {
//                calculateTail(X[i], Y[i], X[i + 1], Y[i + 1]);
//            }
//            moves.insert(pair<int, int>(X[9], Y[9]));
//        }
//    }
//
//    cout << "Answer: " << moves.size() << endl;
//}

/*
 * Day 10
 */
class DayTen : public DayBase
{
public:
    DayTen() : DayBase("Ten", "input\\Day10_Input.txt") {}
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
        cycle++;

        int horizontalPos = (cycle % 40);

        if (horizontalPos >= currentX && horizontalPos <= currentX + 2)
        {
            stream << "#";
        }
        else
        {
            stream << ".";
        }

        if (horizontalPos == 0)
        {
            stream << "\n";
        }
    }
};

/*
 *Day 11
 */
class DayEleven : public DayBase
{
public:
    DayEleven() : DayBase("Eleven", "input\\Day11_Input.txt") {}
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


            if (round == 0)
            {
                cout << "Test" << endl;
            }
            else if (round == 19)
            {
                cout << "Test" << endl;
            }
            else if (round == 999)
            {
                cout << "Test" << endl;
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

/*
 *Day 12
 */
class DayTwelve : public DayBase
{
public:
    DayTwelve() : DayBase("Twelve", "input\\Day12_Input.txt") {}
protected:
    virtual void questionOne(istream& input, ostream& output)
    {
    }

    virtual void questionTwo(istream& input, ostream& output)
    {
    }

private:

};

/*
 * Main
 */

int main()
{
    const bool TEST_PERFORMANCE = false;
    const bool RUN_ALL = false;

    vector<DayBase*> days;
    days.push_back(new DayOne());
    days.push_back(new DayTwo());
    days.push_back(new DayThree());
    days.push_back(new DayFour());
    days.push_back(new DayFive());
    days.push_back(new DaySix());
    days.push_back(new DaySeven());
    days.push_back(new DayEight());
    days.push_back(new DayNine());
    days.push_back(new DayTen());
    days.push_back(new DayEleven());
    days.push_back(new DayTwelve());

    if (TEST_PERFORMANCE)
    {
        long long total = 0;
        for (int i = 0; i < days.size(); ++i)
        {
            total += days[i]->testPerformance();
        }

        cout << "Total Time:" << total / 1000.0f << "ms" << endl;
    }
    else if (RUN_ALL)
    {
        for(int i = 0; i < days.size(); ++ i)
        {
            days[i]->run();
        }
    }
    else
    {
        DayTwelve test;
        test.runTest("input\\Day12_TestInput.txt");

        days[days.size() - 1]->run();
    }

    for (int i = 0; i < days.size(); ++i)
    {
        delete days[i];
    }

    days.clear();

    return 0;
}
