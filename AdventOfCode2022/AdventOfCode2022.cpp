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
#include <algorithm>
#include <cmath>

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
        vector<vector<char>> grid;

        int startX = 0;
        int startY = 0;
        int endX = 0;
        int endY = 0;

        int currY = 0;
        string line;
        while (getline(input, line))
        {
            grid.emplace_back();
            
            for (int i = 0; i < line.length(); ++i)
            {
                char chr = line[i];

                if (chr == 'S')
                {
                    startX = i;
                    startY = currY;
                    chr = 'a';
                }
                else if (chr == 'E')
                {
                    endX = i;
                    endY = currY;
                    chr = 'z';
                }

                grid.back().push_back(chr);
            }

            currY++;
        }

        vector<vector<int>> distanceToEnd;

        distanceToEnd.resize(grid.size());
        for (int i = 0; i < distanceToEnd.size(); ++i)
        {
            distanceToEnd[i].resize(grid[0].size(), -1);
        }

        calculateValues(endX, endY, grid, distanceToEnd, 0);

        output << distanceToEnd[startY][startX];
    }

    virtual void questionTwo(istream& input, ostream& output)
    {
        vector<vector<char>> grid;

        int startX = 0;
        int startY = 0;
        int endX = 0;
        int endY = 0;

        int currY = 0;
        string line;
        while (getline(input, line))
        {
            grid.emplace_back();

            for (int i = 0; i < line.length(); ++i)
            {
                char chr = line[i];

                if (chr == 'S')
                {
                    startX = i;
                    startY = currY;
                    chr = 'a';
                }
                else if (chr == 'E')
                {
                    endX = i;
                    endY = currY;
                    chr = 'z';
                }

                grid.back().push_back(chr);
            }

            currY++;
        }

        vector<vector<int>> distanceToEnd;

        distanceToEnd.resize(grid.size());
        for (int i = 0; i < distanceToEnd.size(); ++i)
        {
            distanceToEnd[i].resize(grid[0].size(), -1);
        }

        calculateValues(endX, endY, grid, distanceToEnd, 0);

        int shortest = -1;

        for (int y = 0; y < distanceToEnd.size(); ++y)
        {
            for (int x = 0; x < distanceToEnd[y].size(); ++x)
            {
                if (grid[y][x] == 'a' && distanceToEnd[y][x] != -1 && (shortest == -1 || distanceToEnd[y][x] < shortest))
                {
                    shortest = distanceToEnd[y][x];
                }
            }
        }

        output << shortest;
    }

private:

    int followPath(int x, int y, int endX, int endY, const vector<vector<char>>& grid, set<pair<int, int>>& visited)
    {
        if (x == endX && y == endY)
        {
            return 0;
        }

        visited.insert(pair<int, int>(x, y));

        int bestTotal = -1;
        char current = grid[y][x];
        if (x > 0 && grid[y][x-1] <= current + 1
            && visited.find(pair<int, int>(x - 1, y)) == visited.end())
        {
            bestTotal = followPath(x - 1, y, endX, endY, grid, visited);
        }
        if (x < grid[y].size() - 1 && grid[y][x + 1] <= current + 1
            && visited.find(pair<int, int>(x + 1, y)) == visited.end())
        {
            int total = followPath(x + 1, y, endX, endY, grid, visited);

            if (bestTotal != -1 && total < bestTotal)
            {
                total = bestTotal;
            }
        }
        if (y > 0 && grid[y - 1][x] <= current + 1
            && visited.find(pair<int, int>(x, y - 1)) == visited.end())
        {
            int total = followPath(x, y - 1, endX, endY, grid, visited);

            if (bestTotal != -1 && total < bestTotal)
            {
                total = bestTotal;
            }
        }
        if (y < grid.size() - 1 && grid[y + 1][x] <= current + 1
            && visited.find(pair<int,int>(x, y + 1)) == visited.end())
        {
            int total = followPath(x, y + 1, endX, endY, grid, visited);

            if (bestTotal != -1 && total < bestTotal)
            {
                total = bestTotal;
            }
        }

        if (bestTotal == -1)
        {
            return bestTotal;
        }

        bestTotal += 1;

        visited.erase(pair<int, int>(x, y));

        return bestTotal;
    }
    
    void calculateValues(int x, int y, const vector<vector<char>>& grid, vector<vector<int>>& distanceToEnd, int currDistance)
    {
        distanceToEnd[y][x] = currDistance;

        currDistance++;

        char current = grid[y][x];

        if (x > 0 && grid[y][x - 1] >= current - 1
            && (distanceToEnd[y][x - 1] == -1 || distanceToEnd[y][x - 1] > currDistance))
        {
            calculateValues(x-1, y, grid, distanceToEnd, currDistance);
        }

        if (x < grid[y].size() - 1 && grid[y][x + 1] >= current - 1
            && (distanceToEnd[y][x + 1] == -1 || distanceToEnd[y][x + 1] > currDistance))
        {
            calculateValues(x + 1, y, grid, distanceToEnd, currDistance);
        }

        if (y > 0 && grid[y - 1][x] >= current - 1
            && (distanceToEnd[y - 1][x] == -1 || distanceToEnd[y - 1][x] > currDistance))
        {
            calculateValues(x, y - 1, grid, distanceToEnd, currDistance);
        }

        if (y < grid.size() - 1 && grid[y + 1][x] >= current - 1
            && (distanceToEnd[y + 1][x] == -1 || distanceToEnd[y + 1][x] > currDistance))
        {
            calculateValues(x, y + 1, grid, distanceToEnd, currDistance);
        }
    }
};

/*
 *Day 13
 */
class DayThirteen : public DayBase
{
public:
    DayThirteen() : DayBase("Thirteen", "input\\Day13_Input.txt") {}
protected:
    virtual void questionOne(istream& input, ostream& output)
    {
        string line1;
        string line2;
        
        int current = 1;
        int total = 0;

        while (getline(input, line1) && getline(input, line2))
        {

            ListItem line1Item(nullptr);
            ListItem line2Item(nullptr);

            parseLine(line1, line1Item);
            parseLine(line2, line2Item);

            VALUE ret = compare(line1Item, line2Item);

            if (ret == TRUE || ret == UNSURE)
            {
                total += current;
            }

            string skip;
            getline(input, skip);

            current++;
        }

        output << total;
    }

    virtual void questionTwo(istream& input, ostream& output)
    {
        string line1;
        string line2;

        vector<ListItem> items;

        items.emplace_back(nullptr);
        ListItem& item2 = items.back();
        item2.isDecoder = true;
        item2.elements.emplace_back(item2);
        item2.elements[0].elements.emplace_back(item2.elements[0]);
        item2.elements[0].elements[0].value = 2;

        items.emplace_back(nullptr);
        ListItem& item6 = items.back();
        item6.isDecoder = true;
        item6.elements.emplace_back(item6);
        item6.elements[0].elements.emplace_back(item6.elements[0]);
        item6.elements[0].elements[0].value = 6;

        while (getline(input, line1) && getline(input, line2))
        {
            items.emplace_back(nullptr);
            ListItem& line1Item = items.back();
            parseLine(line1, line1Item);

            items.emplace_back(nullptr);
            ListItem& line2Item = items.back();
            parseLine(line2, line2Item);

            string skip;
            getline(input, skip);
        }

        sort(items.begin(), items.end(), DayThirteen::vectorCompare);

        int total = 1;

        for (int i = 0; i < items.size(); ++i)
        {
            if (items[i].isDecoder)
            {
                total *= i + 1;
            }
        }

        output << total;
    }

private:

    class ListItem
    {
    public:
        vector<ListItem> elements;

        int value = -1;

        bool isDecoder = false;

        ListItem* parent;

        ListItem(ListItem* aParent) : parent(aParent) {}
    };

    void parseLine(string line, ListItem& root)
    {
        ListItem* currentItem = &root;
        stringstream ss;
        for (int i = 1; i < line.length(); ++i)
        {
            if (line[i] == '[')
            {
                currentItem->elements.emplace_back(currentItem);
                currentItem = &currentItem->elements.back();
            }
            else if (line[i] == ']')
            {
                if (ss.str().length() > 0)
                {
                    currentItem->elements.emplace_back(currentItem);
                    currentItem->elements.back().value = atoi(ss.str().c_str());

                    ss.str("");
                }

                currentItem = currentItem->parent;
            }
            else if (line[i] == ',')
            {
                if (ss.str().length() > 0)
                {
                    currentItem->elements.emplace_back(currentItem);
                    currentItem->elements.back().value = atoi(ss.str().c_str());

                    ss.str("");
                }
            }
            else
            {
                ss << line[i];
            }
        }
    }

    enum VALUE
    {
        TRUE,
        FALSE,
        UNSURE
    };

    static VALUE compare(const ListItem& left, const ListItem& right)
    {
        if (left.value != -1 && right.value != -1)
        {
            if (left.value < right.value)
            {
                return TRUE;
            }
            else if (left.value == right.value)
            {
                return UNSURE;
            }
            else
            {
                return FALSE;
            }

        }
        else if (left.value != -1)
        {
            if (right.elements.size() == 0)
            {
                return FALSE;
            }

            VALUE ret = compare(left, right.elements[0]);

            if (ret != UNSURE)
            {
                return ret;
            }

            if (right.elements.size() > 1)
            {
                return TRUE;
            }

            return UNSURE;
        }
        else if (right.value != -1)
        {
            if (left.elements.size() == 0)
            {
                return TRUE;
            }

            VALUE ret = compare(left.elements[0], right);

            if (ret != UNSURE)
            {
                return ret;
            }

            if (left.elements.size() > 1)
            {
                return FALSE;
            }

            return UNSURE;
        }

        for (int i = 0; i < left.elements.size(); ++i)
        {
            if (right.elements.size() <= i)
            {
                return FALSE;
            }

            VALUE ret = compare(left.elements[i], right.elements[i]);

            if (ret != UNSURE)
            {
                return ret;
            }
        }

        if (left.elements.size() == right.elements.size())
        {
            return UNSURE;
        }

        return TRUE;
    }

    static bool vectorCompare(const ListItem& left, const ListItem& right)
    {
        return compare(left, right) != FALSE;
    }

};

/*
 *Day 14
 */
class DayFourteen : public DayBase
{
public:
    DayFourteen() : DayBase("Fourteen", "input\\Day14_Input.txt") {}
protected:
    virtual void questionOne(istream& input, ostream& output)
    {
        vector<vector<char>> grid;

        string line;
        while (getline(input, line))
        {
            vector<string> coordinates = splitString(line, " -> ");

            for (int i = 0; i < coordinates.size() - 1; ++i)
            {
                insertLine(coordinates[i], coordinates[i + 1], grid);
            }
        }

        //printGrid(grid);

        int count = 0;

        while (dropSand(grid))
        {
            count++;

            //printGrid(grid);
        }

        output << count;
    }

    virtual void questionTwo(istream& input, ostream& output)
    {
        vector<vector<char>> grid;

        string line;
        while (getline(input, line))
        {
            vector<string> coordinates = splitString(line, " -> ");

            for (int i = 0; i < coordinates.size() - 1; ++i)
            {
                insertLine(coordinates[i], coordinates[i + 1], grid);
            }
        }

        resizeGrid(grid[0].size(), grid.size() + 2, grid);

        for (int i = 0; i < grid[grid.size() - 1].size(); ++i)
        {
            grid[grid.size() - 1][i] = '#';
        }

        //printGrid(grid);

        int count = 0;

        while (dropSandV2(grid))
        {
            count++;

            //printGrid(grid);
        }

        output << count;
    }

private:
    int startX = 500;

    void insertLine(string a, string b, vector<vector<char>>& grid)
    {
        vector<string> aCoords = splitString(a, ",");
        vector<string> bCoords = splitString(b, ",");

        int aX = atoi(aCoords[0].c_str());
        int aY = atoi(aCoords[1].c_str());

        int bX = atoi(bCoords[0].c_str());
        int bY = atoi(bCoords[1].c_str());

        if (aX < startX)
        {
            startX = aX;
        }
        if (bX < startX)
        {
            startX = bX;
        }

        resizeGrid((aX > bX ? aX : bX) + 1, (aY > bY ? aY : bY) + 1, grid);

        if (aX == bX)
        {
            int startY = aY < bY ? aY : bY;
            int endY = aY < bY ? bY : aY;

            for (int y = startY; y <= endY; ++y)
            {
                grid[y][aX] = '#';
            }
        }
        else
        {
            int startX = aX < bX ? aX : bX;
            int endX = aX < bX ? bX : aX;

            for (int x = startX; x <= endX; ++x)
            {
                grid[aY][x] = '#';
            }
        }
    }

    void resizeGrid(size_t width, size_t height, vector<vector<char>>& grid, bool addFloor = false)
    {
        if (grid.size() < height)
        {
            grid.resize(height);
        }

        size_t newWidth = grid[0].size() < width ? width : grid[0].size();

        if (grid[grid.size()-1].size() < newWidth)
        {
            for (int i = 0; i < grid.size(); ++i)
            {
                grid[i].resize(newWidth, (addFloor && i == grid.size() -1) ? '#' : '.');
            }
        }
    }

    void printGrid(vector<vector<char>> grid)
    {
        for (int y = 0; y < grid.size(); ++y)
        {
            for (int x = startX; x < grid[y].size(); ++x)
            {
                cout << grid[y][x];
            }

            cout << endl;
        }
        
        cout << endl;
    }

    bool dropSand(vector<vector<char>>& grid)
    {
        int currX = 500;
        int currY = 0;

        if (grid[currY][currX] == '#')
        {
            return false;
        }

        while (true)
        {
            if (grid.size() <= currY + 1)
            {
                return false;
            }
            else if (grid[currY+1][currX] == '.')
            {
                currY++;
            }
            else if (currX - 1 < 0)
            {
                return false;
            }
            else if (grid[currY+1][currX-1] == '.')
            {
                currY++;
                currX--;
            }
            else if (currX + 1 >= grid[currY].size())
            {
                return false;
            }
            else if (grid[currY + 1][currX + 1] == '.')
            {
                currY++;
                currX++;
            }
            else
            {
                grid[currY][currX] = '#';
                return true;
            }
        }
    }

    bool dropSandV2(vector<vector<char>>& grid)
    {
        int currX = 500;
        int currY = 0;

        if (grid[currY][currX] == '#')
        {
            return false;
        }

        while (true)
        {
            if (grid.size() <= currY + 1)
            {
                return false;
            }
            else if (grid[currY + 1][currX] == '.')
            {
                currY++;
            }
            else if (currX - 1 < 0)
            {
                return false;
            }
            else if (grid[currY + 1][currX - 1] == '.')
            {
                currY++;
                currX--;
            }
            else
            {
                if (currX + 1 >= grid[currY].size())
                {
                    resizeGrid(currX + 2, grid.size(), grid, true);
                }

                if (grid[currY + 1][currX + 1] == '.')
                {
                    currY++;
                    currX++;
                }
                else
                {
                    grid[currY][currX] = '#';
                    return true;
                }
            }
        }
    }
};

/*
 *Day 15
 */
class DayFifteen : public DayBase
{
public:
    DayFifteen() : DayBase("Fifteen", "input\\Day15_Input.txt") {}
protected:
    virtual void questionOne(istream& input, ostream& output)
    {
        string line;
        vector<pair<int, int>> sensors;
        vector<pair<int, int>> closestBeacons;
        vector<int> distances;

        //int minX = -1;
        //int minY = -1;
        //int maxX = -1;
        //int maxY = -1;

        int maxDistance = -1;

        while (getline(input, line))
        {
            vector<string> words = splitString(line, " ");

            int sensorX = atoi(words[2].substr(2, words[2].length() - 3).c_str());
            int sensorY = atoi(words[3].substr(2, words[3].length() - 3).c_str());

            int beaconX = atoi(words[8].substr(2, words[8].length() - 3).c_str());
            int beaconY = atoi(words[9].substr(2).c_str());

            //if (minX == -1)
            //{
            //    minX = sensorX;
            //    maxX = sensorX;
            //    minY = sensorY;
            //    maxY = sensorY;
            //}

            //if (sensorX < minX)
            //{
            //    minX = sensorX;
            //}
            //if (sensorX > maxX)
            //{
            //    maxX = sensorX;
            //}
            //if (sensorY < minY)
            //{
            //    minY = sensorY;
            //}
            //if (sensorY > maxY)
            //{
            //    maxY = sensorY;
            //}

            //if (beaconX < minX)
            //{
            //    minX = beaconX;
            //}
            //if (beaconX > maxX)
            //{
            //    maxX = beaconX;
            //}
            //if (beaconY < minY)
            //{
            //    minY = beaconY;
            //}
            //if (beaconY > maxY)
            //{
            //    maxY = beaconY;
            //}

            int distance = abs(sensorX - beaconX) + abs(sensorY - beaconY);

            //if (maxDistance < distance)
            //{
            //    maxDistance = distance;
            //}

            distances.push_back(distance);

            sensors.emplace_back(pair<int, int>(sensorX, sensorY));
            closestBeacons.emplace_back(pair<int, int>(beaconX, beaconY));
        }

        //Grid grid(minX - maxDistance, maxX + maxDistance, minY - maxDistance, maxY + maxDistance);

        //for (int i = 0; i < sensors.size(); ++i)
        //{
        //    for (int y = 0; y <= distances[i]; ++y)
        //    {
        //        for (int x = 0; x <= distances[i] - y; ++x)
        //        {
        //            grid.addChar(sensors[i].first + x, sensors[i].second + y, '#');

        //            if (x != 0)
        //            {
        //                grid.addChar(sensors[i].first - x, sensors[i].second + y, '#');
        //            }

        //            if (y != 0)
        //            {
        //                grid.addChar(sensors[i].first + x, sensors[i].second - y, '#');

        //                if (x != 0)
        //                {
        //                    grid.addChar(sensors[i].first - x, sensors[i].second - y, '#');
        //                }
        //            }
        //        }
        //    }

        //    grid.addChar(sensors[i].first, sensors[i].second, 'S');
        //    grid.addChar(closestBeacons[i].first, closestBeacons[i].second, 'B');
        //}

        //int total = grid.getFilledCount(2000000);


        int testRow = 2000000;
        //int testRow = 10;

        vector<int> sensorIndexes;
        int minX = -1;
        int maxX = -1;

        for (int i = 0; i < sensors.size(); ++i)
        {
            if (sensors[i].second + distances[i] < testRow)
            {
                continue;
            }
            else if (sensors[i].second - distances[i] > testRow)
            {
                continue;
            }

            sensorIndexes.push_back(i);

            int lowX = sensors[i].first - distances[i];
            int highX = sensors[i].first + distances[i];

            if (minX == -1)
            {
                minX = lowX;
                maxX = highX;
            }

            if (lowX < minX)
            {
                minX = lowX;
            }
            if (highX > maxX)
            {
                maxX = highX;
            }
        }

        vector<char> row;
        row.resize(maxX - minX + 1, '.');

        for (int i = 0; i < sensorIndexes.size(); ++i)
        {
            int sI = sensorIndexes[i];

            int sensorY = abs(testRow - sensors[sI].second);

            for (int x = 0; x <= distances[sI] - sensorY; ++x)
            {
                row[sensors[sI].first + x - minX] = '#';

                if (x != 0)
                {
                    row[sensors[sI].first - x - minX] = '#';
                }
            }

            if (closestBeacons[sI].second == testRow)
            {
                row[closestBeacons[sI].first - minX] = 'B';
            }
        }


        int total = 0;

        for (int x = 0; x < row.size(); ++x)
        {
            if (row[x] != '.' && row[x] != 'B')
            {
                total++;
            }
        }

        output << total;
    }

    virtual void questionTwo(istream& input, ostream& output)
    {
        string line;
        vector<pair<int, int>> sensors;
        vector<pair<int, int>> closestBeacons;
        vector<int> distances;

        while (getline(input, line))
        {
            vector<string> words = splitString(line, " ");

            int sensorX = atoi(words[2].substr(2, words[2].length() - 3).c_str());
            int sensorY = atoi(words[3].substr(2, words[3].length() - 3).c_str());

            int beaconX = atoi(words[8].substr(2, words[8].length() - 3).c_str());
            int beaconY = atoi(words[9].substr(2).c_str());

            int distance = abs(sensorX - beaconX) + abs(sensorY - beaconY);
            distances.push_back(distance);

            sensors.emplace_back(pair<int, int>(sensorX, sensorY));
            closestBeacons.emplace_back(pair<int, int>(beaconX, beaconY));
        }

        int maxCoord = 4000000;
        //int maxCoord = 20;

        bool found = true;
        long long foundX = 0;
        long long foundY = 0;

        for (int y = 0; y < maxCoord; ++y)
        {
            for (int x = 0; x < maxCoord; ++x)
            {
                found = true;

                for (int i = 0; i < sensors.size(); ++i)
                {
                    int sX = sensors[i].first;
                    int sY = sensors[i].second;
                    int dist = distances[i];

                    int distToPoint = abs(sX - x) + abs(sY - y);

                    if (distToPoint <= dist)
                    {
                        found = false;
                        x = sX + dist - abs(sY - y);

                        break;
                    }
                }

                if (found)
                {
                    foundX = x;
                    break;
                }
            }

            if (found)
            {
                foundY = y;
                break;
            }
        }

        long long total = foundX * 4000000 + foundY;

        output << total;
    }
private:
    //class Grid
    //{
    //public:
    //    vector<vector<char>> values;
    //    int startX = 0;
    //    int startY = 0;
    //    int endX = 0;
    //    int endY = 0;

    //    Grid(int minX, int maxX, int minY, int maxY)
    //    {
    //        startX = minX;
    //        startY = minY;
    //        endX = maxX;
    //        endY = maxY;

    //        int width = maxX - minX + 1;
    //        int height = maxY - minY + 1;

    //        values.resize(height);
    //        for (int i = 0; i < height; ++i)
    //        {
    //            values[i].resize(width, '.');
    //        }
    //    }

    //    void addChar(int x, int y, char value)
    //    {
    //        values[y - startY][x - startX] = value;
    //    }

    //    char getChar(int x, int y)
    //    {
    //        return values[y - startY][x - startX];
    //    }

    //    int getFilledCount(int y)
    //    {
    //        int count = 0;
    //        vector<char>& row = values[y - startY];
    //        for (int x = 0; x < row.size(); ++x)
    //        {
    //            if (row[x] != '.' && row[x] != 'B')
    //            {
    //                count++;
    //            }
    //        }

    //        return count;
    //    }
    //};
};


/*
 *Day 15 Harry
 */

using point = pair<int, int>;

int taxi_dist(const point& a, const point& b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

point operator*(const point& a, int scale) {
    return { a.first * scale, a.second * scale };
}

point operator-(const point& a, const point& b) {
    return { a.first - b.first, a.second - b.second };
}
point operator+(const point& a, const point& b) {
    return a - (b * -1);
}

class DayFifteenHarry : public DayBase
{
public:
    DayFifteenHarry() : DayBase("Fifteen Harry", "input\\Day15_Input.txt") {}
protected:
    virtual void questionOne(istream& input, ostream& output)
    {
    }

    virtual void questionTwo(istream& input, ostream& output)
    {
        parse(input);
        for (const auto& line : inputPoints) {
            const auto& source = line.first;
            const auto dist = taxi_dist(line.first, line.second) + 1;
            for (int i = 0; i < 4 * dist; ++i) {
                const auto p = from_iter(source, dist, i);
                if (min(p.first, p.second) >= 0 && max(p.first, p.second) <= 4000000) {
                    bool valid = true;
                    if (all_of(inputPoints.begin(), inputPoints.end(), [&p](const auto& s) {
                        return taxi_dist(p, s.first) > taxi_dist(s.first, s.second);
                        })) {
                        output << (uint64_t)(p.first) * 4000000 + (uint64_t)p.second << endl;
                        return;
                    }
                }
            }
        }

    }

private:
    vector<pair<point, point>> inputPoints;

    int minx, maxx;

    void parse(istream& input) {
        string s;
        bool start = true;
        while (getline(input, s)) {
            inputPoints.emplace_back();
            auto& data = inputPoints.back();
            sscanf_s(s.c_str(), "Sensor at x=%i, y=%i: closest beacon is at x=%i, y=%i",
                &data.first.first, &data.first.second, &data.second.first,
                &data.second.second);
            if (start) {
                start = false;
                minx = maxx = data.first.first;
            }
            minx = min(minx, data.first.first - taxi_dist(data.first, data.second));
            maxx = max(maxx, data.first.first + taxi_dist(data.first, data.second));
            //cerr << data.first << ", " << data.second << endl;
        }
        //cerr << minx << ' ' << maxx << endl;
    }

    point from_iter(const point& source, const int dist, const int iter) {
        point out;

        if (iter < 2 * dist) {
            out.first = iter - dist;
        }
        else {
            out.first = 3 * dist - iter;
        }

        if (iter <= dist) {
            out.second = iter;
        }
        else if (iter <= 3 * dist) {
            out.second = 2 * dist - iter;
        }
        else {
            out.second = iter - (4 * dist);
        }
        return out + source;
    }

};


class DaySixteen : public DayBase
{
public:
    DaySixteen() : DayBase("Sixteen", "input\\Day16_Input.txt") {}
protected:
    virtual void questionOne(istream& input, ostream& output)
    {
        State state;
        vector<Valve>& valves = state.valves;
        parse(input, valves);

        size_t valveCount = valves.size();

        Valve* currentValve = nullptr;
        for (int i = 0; i < valveCount; ++i)
        {
            if (valves[i].name.compare("AA") == 0)
            {
                currentValve = &valves[i];
            }

            valves[i].index = i;
        }

        int total = getBestPressure(30, currentValve, state);

        output << total;
    }

    virtual void questionTwo(istream& input, ostream& output)
    {
        State state;
        vector<Valve>& valves = state.valves;
        parse(input, valves);

        size_t valveCount = valves.size();

        Valve* currentValve = nullptr;
        for (int i = 0; i < valveCount; ++i)
        {
            if (valves[i].name.compare("AA") == 0)
            {
                currentValve = &valves[i];
            }

            valves[i].index = i;
        }

        Input funcInput;

        funcInput.currPlayer = currentValve;
        funcInput.currElephant = currentValve;

        int total = getBestPressureV2(26, state, funcInput);

        output << total;
    }
private:
    class Valve
    {
    public:
        string name;
        int pressure;
        int index;

        bool open = false;

        vector<string> pipeNames;
        vector<Valve*> pipes;
    };

    struct State
    {
        vector<Valve> valves;
    };

    struct Input
    {
        Valve* currPlayer = nullptr;
        Valve* currElephant = nullptr;

        int etaPlayer = 0;
        int etaElephant = 0;
    };

    void parse(istream& input, vector<Valve>& valves)
    {
        string line;
        while (getline(input, line))
        {
            valves.emplace_back();

            Valve& currentValve = valves.back();

            vector<string> strings = splitString(line, " ");

            currentValve.name = strings[1];

            currentValve.pressure = atoi(strings[4].substr(5, strings[4].length() - 6).c_str());

            for (int i = 9; i < strings.size(); ++i)
            {
                currentValve.pipeNames.emplace_back(strings[i].substr(0, 2));
            }
        }

        for (int v = 0; v < valves.size(); ++v)
        {
            Valve& currentValve = valves[v];

            for (int i = 0; i < currentValve.pipeNames.size(); ++i)
            {
                for (int oV = 0; oV < valves.size(); ++oV)
                {
                    if (oV != v)
                    {
                        if (currentValve.pipeNames[i].compare(valves[oV].name) == 0)
                        {
                            currentValve.pipes.push_back(&valves[oV]);
                            break;
                        }
                    }
                }
            }
        }
    }

    int getBestPressure(int turn, Valve* currentValve, State& state)
    {
        size_t valveCount = state.valves.size();

        int currIndex = currentValve->index;

        vector<int> dist;
        vector<bool> visited;
        dist.resize(valveCount, INT_MAX);
        visited.resize(valveCount, false);

        dist[currIndex] = 0;

        deque<pair<Valve*, int>> toCheck;
        toCheck.push_back(pair<Valve*, int>(currentValve, 0));
        while (!toCheck.empty())
        {
            Valve* valve = toCheck.front().first;
            int nextDepth = toCheck.front().second + 1;

            for (int i = 0; i < valve->pipes.size(); ++i)
            {
                Valve* next = valve->pipes[i];
                if (!visited[next->index])
                {
                    visited[next->index] = true;
                    dist[next->index] = nextDepth;

                    toCheck.push_back(pair<Valve*, int>(next, nextDepth));
                }
            }

            toCheck.pop_front();
        }

        int bestPressure = 0;

        for (int i = 0; i < valveCount; ++i)
        {
            Valve& toCheck = state.valves[i];
            if (!toCheck.open && toCheck.pressure != 0)
            {
                int nextTurn = turn - dist[i] - 1;

                if (nextTurn <= 0)
                    continue;

                toCheck.open = true;

                int newPressure = (nextTurn * toCheck.pressure) + getBestPressure(nextTurn, &toCheck, state);

                if (newPressure > bestPressure)
                {
                    bestPressure = newPressure;
                }

                toCheck.open = false;
            }
        }

        return bestPressure;
    }

    int getBestPressureV2(int turn, State& state, Input& input)
    {
        if (turn <= 0)
            return 0;

        size_t valveCount = state.valves.size();

        vector<int> distPlayer;
        vector<int> distElephant;

        if (input.etaPlayer == 0)
        {
            distPlayer.resize(valveCount, INT_MAX);
            getShortestDistances(input.currPlayer, distPlayer);
        }

        if (input.etaElephant == 0)
        {
            distElephant.resize(valveCount, INT_MAX);
            getShortestDistances(input.currElephant, distElephant);
        }

        int bestPressure = 0;

        vector<Valve*> openValves;

        for (int i = 0; i < valveCount; ++i)
        {
            Valve& toCheck = state.valves[i];
            if (!toCheck.open && toCheck.pressure != 0)
            {
                openValves.push_back(&toCheck);
            }
        }

        if (input.etaPlayer == 0 && input.etaElephant == 0)
        {
            for (int p = 0; p < openValves.size(); ++p)
            {
                for (int e = 0; e < openValves.size(); ++e)
                {
                    if (p != e)
                    {
                        Input newInput(input);

                        int pI = openValves[p]->index;
                        int eI = openValves[e]->index;

                        int playerNextTurn = turn - distPlayer[pI] - 1;
                        int elephantNextTurn = turn - distElephant[eI] - 1;

                        int playerPressure = 0;
                        if (playerNextTurn > 0)
                        {
                            openValves[p]->open = true;
                            playerPressure = playerNextTurn * openValves[p]->pressure;
                            newInput.currPlayer = openValves[p];
                        }
                        else
                        {
                            newInput.etaPlayer = turn;
                        }

                        int elephantPressure = 0;
                        if (elephantNextTurn > 0)
                        {
                            openValves[e]->open = true;
                            elephantPressure = elephantNextTurn * openValves[e]->pressure;
                            newInput.currElephant = openValves[e];
                        }
                        else
                        {
                            newInput.etaElephant = turn;
                        }

                        int nextTurn = playerNextTurn;

                        if (playerNextTurn < elephantNextTurn)
                        {
                            nextTurn = elephantNextTurn;
                            newInput.etaPlayer = elephantNextTurn - playerNextTurn;
                        }
                        else if (playerNextTurn > elephantNextTurn)
                        {
                            newInput.etaElephant = playerNextTurn - elephantNextTurn;
                        }

                        int newPressure = playerPressure + elephantPressure + getBestPressureV2(nextTurn, state, newInput);

                        if (newPressure > bestPressure)
                        {
                            bestPressure = newPressure;
                        }

                        if (elephantNextTurn > 0)
                        {
                            openValves[e]->open = false;
                        }

                        if (playerNextTurn > 0)
                        {
                            openValves[p]->open = false;
                        }
                    }
                }
            }
        }
        else if (input.etaPlayer == 0)
        {
            for (int v = 0; v < openValves.size(); ++v)
            {
                Input newInput(input);
                Valve* curr = openValves[v];

                int nextTurn = turn - distPlayer[curr->index] - 1;
                int pressure = nextTurn * curr->pressure;

                curr->open = true;
                newInput.currPlayer = curr;

                if (input.etaElephant < (turn - nextTurn))
                {
                    newInput.etaPlayer = turn - newInput.etaElephant - nextTurn;

                    nextTurn = turn - newInput.etaElephant;
                    newInput.etaElephant = 0;
                }
                else
                {
                    newInput.etaPlayer = 0;
                    newInput.etaElephant -= (turn - nextTurn);
                }

                int newPressure = pressure + getBestPressureV2(nextTurn, state, newInput);

                if (newPressure > bestPressure)
                {
                    bestPressure = newPressure;
                }

                curr->open = false;
            }
        }
        else // state.etaElephant == 0
        {
            for (int v = 0; v < openValves.size(); ++v)
            {
                Input newInput(input);
                Valve* curr = openValves[v];
                int nextTurn = turn - distElephant[curr->index] - 1;
                int pressure = nextTurn * curr->pressure;

                curr->open = true;
                newInput.currElephant = curr;

                if (newInput.etaPlayer < (turn - nextTurn))
                {
                    newInput.etaElephant = turn - newInput.etaPlayer - nextTurn;

                    nextTurn = turn - newInput.etaPlayer;
                    newInput.etaPlayer = 0;
                }
                else
                {
                    newInput.etaElephant = 0;
                    newInput.etaPlayer -= (turn - nextTurn);
                }

                int newPressure = pressure + getBestPressureV2(nextTurn, state, newInput);

                if (newPressure > bestPressure)
                {
                    bestPressure = newPressure;
                }

                curr->open = false;
            }
        }

        return bestPressure;
    }

    void getShortestDistances(Valve* start, vector<int>& dist)
    {
        vector<bool> visited;
        visited.resize(dist.size(), false);

        dist[start->index] = 0;

        deque<pair<Valve*, int>> toCheck;
        toCheck.push_back(pair<Valve*, int>(start, 0));
        while (!toCheck.empty())
        {
            Valve* valve = toCheck.front().first;
            int nextDepth = toCheck.front().second + 1;

            for (int i = 0; i < valve->pipes.size(); ++i)
            {
                Valve* next = valve->pipes[i];
                if (!visited[next->index])
                {
                    visited[next->index] = true;
                    dist[next->index] = nextDepth;

                    toCheck.push_back(pair<Valve*, int>(next, nextDepth));
                }
            }

            toCheck.pop_front();
        }
    }
};

/*
 * Day 17
 */
class DaySeventeen : public DayBase
{
public:
    DaySeventeen() : DayBase("Seventeen", "input\\Day17_Input.txt") {}
protected:
    virtual void questionOne(istream& input, ostream& output)
    { 
        initRockShapes();

        string line;
        getline(input, line);

        int currLineIndex = 0;

        const long long NUM_ROCKS = 2022;

        for (int i = 0; i < NUM_ROCKS; ++i)
        {
            Rock rock;
            spawnRock(rock);

            bool isDone = false;
            while (!isDone)
            {
                moveRock(rock, line[currLineIndex] == '<' ? -1 : 1, 0);
                ++currLineIndex;
                if (currLineIndex >= line.length())
                    currLineIndex = 0;

                isDone = !moveRock(rock, 0, -1);

                if (isDone)
                {
                    settleRock(rock);
                }
            }

            //print();
            //cout << endl;
        }

        output << getTowerHeight();
    }

    virtual void questionTwo(istream& input, ostream& output)
    {
        CurrentRock = 0;
        grid.resize(0);
        yOffset = 0;

        vector<long long> towerHeights;

        string line;
        getline(input, line);

        int currLineIndex = 0;

        const long long NUM_ROCKS = 100000;

        int patternCount = 0;
        int testPatternCount = 5;

        for (long long i = 0; i < NUM_ROCKS; ++i)
        {
            Rock rock;
            spawnRock(rock);

            bool isDone = false;
            while (!isDone)
            {
                moveRock(rock, line[currLineIndex] == '<' ? -1 : 1, 0);
                ++currLineIndex;
                if (currLineIndex >= line.length())
                    currLineIndex = 0;

                isDone = !moveRock(rock, 0, -1);

                if (isDone)
                {
                    settleRock(rock);
                }
            }

            towerHeights.emplace_back(getTowerHeight());

            patternCount = getPatternCount(towerHeights, i, testPatternCount);

            if (patternCount != 0)
                break;
        }

        long long countAt = 1000000000000;
        long long diff = towerHeights[towerHeights.size() - 1] - towerHeights[towerHeights.size() - 1 - patternCount];

        long long total = towerHeights[countAt % patternCount - 1] + (countAt / patternCount) * diff;
        output << total;
    }
private:
    const int TOWER_WIDTH = 7;

    long long yOffset = 0;

    enum RockShape
    {
        Flat = 0,
        Cross,
        L,
        Tall,
        Block
    };
    
    int CurrentRock = Flat;

    typedef deque<vector<char>> Grid;
    Grid grid;

    void addRow()
    {
        grid.emplace_back();
        grid.back().resize(TOWER_WIDTH, '.');

        const int ADJUST = 1000;

        if (grid.size() > ADJUST*2)
        {
            for (int i = 0; i < ADJUST; ++i)
            {
                grid.pop_front();
            }

            yOffset += ADJUST;
        }
    }

    static vector<vector<char>>* FlatShape;
    static vector<vector<char>>* CrossShape;
    static vector<vector<char>>* LShape;
    static vector<vector<char>>* TallShape;
    static vector<vector<char>>* BlockShape;

    struct Rock
    {
        RockShape shape;
        int x; // Left
        long long y; // Bottom

        int width;
        int height;

        const vector<vector<char>>& pixels()
        {
            switch (shape)
            {
            case Flat:
                return *FlatShape;
            case Cross:
                return *CrossShape;
            case L:
                return *LShape;
            case Tall:
                return *TallShape;
            case Block:
                return *BlockShape;
            default:
                return *FlatShape;
            }
        }
    };

    static void initRockShapes()
    {
        FlatShape = new vector<vector<char>>();
        FlatShape->emplace_back();
        FlatShape->back().resize(4, '#');

        CrossShape = new vector<vector<char>>();
        CrossShape->emplace_back();
        CrossShape->back().resize(3, '.');
        CrossShape->back()[1] = '#';
        CrossShape->emplace_back();
        CrossShape->back().resize(3, '#');
        CrossShape->emplace_back();
        CrossShape->back().resize(3, '.');
        CrossShape->back()[1] = '#';

        LShape = new vector<vector<char>>();
        LShape->emplace_back();
        LShape->back().resize(3, '#');
        LShape->emplace_back();
        LShape->back().resize(3, '.');
        LShape->back()[2] = '#';
        LShape->emplace_back();
        LShape->back().resize(3, '.');
        LShape->back()[2] = '#';

        TallShape = new vector<vector<char>>();
        TallShape->emplace_back();
        TallShape->back().emplace_back('#');
        TallShape->emplace_back();
        TallShape->back().emplace_back('#');
        TallShape->emplace_back();
        TallShape->back().emplace_back('#');
        TallShape->emplace_back();
        TallShape->back().emplace_back('#');

        BlockShape = new vector<vector<char>>();
        BlockShape->emplace_back();
        BlockShape->back().resize(2, '#');
        BlockShape->emplace_back();
        BlockShape->back().resize(2, '#');
    }

    void spawnRock(Rock& rock)
    {
        rock.shape = (RockShape)CurrentRock;
        rock.x = 2;
        rock.y = getTowerHeight() + 3;

        switch (rock.shape)
        {
        case Flat:
            rock.width = 4;
            rock.height = 1;
            break;
        case Cross:
            rock.width = 3;
            rock.height = 3;
            break;
        case L:
            rock.width = 3;
            rock.height = 3;
            break;
        case Tall:
            rock.width = 1;
            rock.height = 4;
            break;
        case Block:
            rock.width = 2;
            rock.height = 2;
            break;
        }

        if (++CurrentRock > Block)
        {
            CurrentRock = Flat;
        }

        long long addedHeight = (rock.y + rock.height + 3) - (grid.size() + yOffset);
        for (int i = 0; i < addedHeight; ++i)
            addRow();
    }

    long long getTowerHeight()
    {
        for (int y = grid.size() - 1; y >= 0; --y)
        {
            for (int x = 0; x < TOWER_WIDTH; ++x)
            {
                if (grid[y][x] != '.')
                {
                    return y + 1 + yOffset;
                }
            }
        }

        return 0;
    }

    bool moveRock(Rock& rock, int xDir, int yDir)
    {
        int newX = rock.x + xDir;
        long long newY = rock.y + yDir;

        if (newX < 0 || newX + rock.width > TOWER_WIDTH)
        {
            return false;
        }
        if (newY < 0)
        {
            return false;
        }

        for (int y = 0; y < rock.height; ++y)
        {
            for(int x = 0; x < rock.width; ++x)
            {
                if (grid[y + newY - yOffset][x + newX] != '.' && rock.pixels()[y][x] != '.')
                {
                    return false;
                }
            }
        }

        rock.x = newX;
        rock.y = newY;

        return true;
    }

    void settleRock(Rock& rock)
    {
        long long yAdjust = 0;
        for (int y = 0; y < rock.height; ++y)
        {
            for (int x = 0; x < rock.width; ++x)
            {
                if (rock.pixels()[y][x] != '.')
                {
                    grid[y + rock.y - yOffset][x + rock.x] = '#';
                }
            }
        }
    }

    int getPatternCount(vector<long long> values, long long maxValue, int& currentPatternCount)
    {
        if (maxValue < 15)
            return 0;

        int numToCheck = 5;

        bool matched = false;
        while (!matched && currentPatternCount * 4 < maxValue)
        {
            matched = true;
            for (int i = 0; i < currentPatternCount; ++i)
            {
                int diffOne = values[i + 2 * currentPatternCount] - values[i + currentPatternCount];
                int diffTwo = values[i + 3 * currentPatternCount] - values[i + 2 * currentPatternCount];

                if (diffOne != diffTwo)
                    matched = false;
            }

            if (!matched)
            {
                currentPatternCount++;
            }
            else
            {
                return currentPatternCount;
            }
        }

        return 0;
    }

    void print()
    {
        for (int y = (int)grid.size() - 1; y >= 0; --y)
        {
            for (int x = 0; x < TOWER_WIDTH; ++x)
            {
                cout << grid[y][x];
            }
            cout << endl;
        }
    }
};

vector<vector<char>>* DaySeventeen::FlatShape = nullptr;
vector<vector<char>>* DaySeventeen::CrossShape = nullptr;
vector<vector<char>>* DaySeventeen::LShape = nullptr;
vector<vector<char>>* DaySeventeen::TallShape = nullptr;
vector<vector<char>>* DaySeventeen::BlockShape = nullptr;

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
    days.push_back(new DayThirteen());
    days.push_back(new DayFourteen());
    days.push_back(new DayFifteen());
    days.push_back(new DaySixteen());
    days.push_back(new DaySeventeen());


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
        DaySeventeen test;
        test.runTest("input\\Day17_TestInput.txt");

        days[days.size() - 1]->run();
    }

    for (int i = 0; i < days.size(); ++i)
    {
        delete days[i];
    }

    days.clear();

    return 0;
}
