#include "DayBase.h"

DayBase::DayBase(string day, string inputFile)
    : day(day)
{
    input.open(inputFile);
}

DayBase::~DayBase()
{
    input.close();
}

void DayBase::run()
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

void DayBase::runTest(string testFileOne, string testFileTwo /*= ""*/)
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

long long DayBase::testPerformance()
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