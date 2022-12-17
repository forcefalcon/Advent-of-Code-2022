#pragma once

#include <Helpers.h>

class DayBase
{
public:
    DayBase(string day, string inputFile);
    virtual ~DayBase();

    void run();
    void runTest(string testFileOne, string testFileTwo = "");
    long long testPerformance();

protected:
    virtual void questionOne(istream& input, ostream& output) = 0;
    virtual void questionTwo(istream& input, ostream& output) = 0;

private:
    string day;
    ifstream input;
    ifstream testInput;

    virtual void resetData() {}

    inline void resetInput(ifstream& input)
    {
        input.clear();
        input.seekg(0, std::ios::beg);
    }
};