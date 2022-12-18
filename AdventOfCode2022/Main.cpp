// AdventOfCode2022.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Helpers.h>
#include <DayBase.h>

#include <solutions/Day1.h>
#include <solutions/Day2.h>
#include <solutions/Day3.h>
#include <solutions/Day4.h>
#include <solutions/Day5.h>
#include <solutions/Day6.h>
#include <solutions/Day7.h>
#include <solutions/Day8.h>
#include <solutions/Day9.h>
#include <solutions/Day10.h>
#include <solutions/Day11.h>
#include <solutions/Day12.h>
#include <solutions/Day13.h>
#include <solutions/Day14.h>
#include <solutions/Day15.h>
#include <solutions/Day16.h>
#include <solutions/Day17.h>
#include <solutions/Day18.h>
#include <solutions/Day19.h>

/*
 * Main
 */

int main()
{
    const bool TEST_PERFORMANCE = true;
    const bool USE_TEST_DATA = true;
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
    days.push_back(new DayEighteen());
    days.push_back(new DayNineteen());


    if (TEST_PERFORMANCE)
    {
        long long total = 0;
        for (int i = 0; i < days.size(); ++i)
        {
            total += days[i]->testPerformance(USE_TEST_DATA);
        }

        cout << "Total Time:" << total / 1000.0f << "ms" << endl;
    }
    else if (RUN_ALL)
    {
        for(int i = 0; i < days.size(); ++ i)
        {
            USE_TEST_DATA ? days[i]->runTest() : days[i]->run();
        }
    }
    else
    {
        days[days.size() - 1]->runTest();
        days[days.size() - 1]->run();
    }

    for (int i = 0; i < days.size(); ++i)
    {
        delete days[i];
    }

    days.clear();

    return 0;
}
