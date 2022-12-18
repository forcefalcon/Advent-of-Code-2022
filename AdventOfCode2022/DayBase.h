#pragma once

#include <Helpers.h>

class DayBase
{
public:
    DayBase(string day);
    virtual ~DayBase();

    void run();
    void runTest();
    long long testPerformance(bool test = false);

protected:
    virtual void questionOne(istream& input, ostream& output) = 0;
    virtual void questionTwo(istream& input, ostream& output) = 0;

private:
    string day;
    ifstream input;
    ifstream testInput;
    ifstream testInputTwo;

    virtual void resetData() {}

    inline void resetInput(ifstream& input)
    {
        input.clear();
        input.seekg(0, std::ios::beg);
    }
};