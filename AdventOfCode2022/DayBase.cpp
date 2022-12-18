#include "DayBase.h"

DayBase::DayBase(string day)
    : day(day)
{
    stringstream ss;
    ss << "input\\Day" << day << "_Input.txt";
    input.open(ss.str());

    ss.str("");

    ss << "input\\Day" << day << "_TestInput.txt";
    testInput.open(ss.str());

    ss.str("");

    ss << "input\\Day" << day << "_TestInput2.txt";
    testInputTwo.open(ss.str());
}

DayBase::~DayBase()
{
    if (testInputTwo.is_open())
        testInputTwo.close();

    testInput.close();
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

void DayBase::runTest()
{
    stringstream output;
    output << "Day " << day << " Test\n";
    output << "----------\n";
    output << "Question 1\n";
    output << "Answer: ";
    questionOne(testInput, output);
    output << "\n\n";

    if (!testInputTwo.is_open())
    {
        resetInput(testInput);
    }

    output << "Question 2\n";
    output << "Answer: ";
    questionTwo(testInputTwo.is_open() ? testInputTwo : testInput, output);
    output << "\n\n";

    cout << output.str();
}

long long DayBase::testPerformance(bool test /*= false*/)
{
    const int RUN_COUNT = 100;

    stringstream output;
    long long total = 0;

    cout << "Day " << day << (test ? " Test" : "") << "\n";
    cout << "----------\n";
    cout << "Question 1\n";

    auto start = chrono::high_resolution_clock::now();

    ifstream& q1Input = test ? testInput : input;

    for (int i = 0; i < RUN_COUNT; ++i)
    {
        questionOne(q1Input, output);
        resetInput(q1Input);
    }

    auto elapsed = chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<chrono::microseconds>(elapsed).count() / RUN_COUNT;
    cout << "Avg Time: " << microseconds << "us" << "\n";

    total += microseconds;

    cout << "Question 2\n";

    start = chrono::high_resolution_clock::now();

    ifstream& q2Input = test ? (testInputTwo.is_open() ? testInputTwo : testInput) : input;

    for (int i = 0; i < RUN_COUNT; ++i)
    {
        questionTwo(q2Input, output);
        resetInput(q2Input);
    }

    elapsed = chrono::high_resolution_clock::now() - start;
    microseconds = std::chrono::duration_cast<chrono::microseconds>(elapsed).count() / RUN_COUNT;
    cout << "Avg Time: " << microseconds << "us" << "\n\n";

    return total;
}