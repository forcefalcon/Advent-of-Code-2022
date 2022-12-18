// AdventOfCode2022.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <DayBase.h>

/*
 * Main
 */

int main()
{
    enum DataToUse
    {
        Regular = 1,
        Test = 2
    };

    const char DATA_TO_USE = Regular | Test;
    const bool TEST_PERFORMANCE = false;
    const bool RUN_ALL = false;
    const int RUN_SPECIFIC = 0;

    if (RUN_ALL)
    {
        if (TEST_PERFORMANCE)
        {
            if (DATA_TO_USE & Test)
            {
                long long total = 0;
                for (int i = 0; i < g_days.size(); ++i)
                {
                    total += g_days[i]->testPerformance(true);
                }

                cout << "Total Time Test:" << total / 1000.0f << "ms" << endl;
            }

            if (DATA_TO_USE & Regular)
            {
                long long total = 0;
                for (int i = 0; i < g_days.size(); ++i)
                {
                    total += g_days[i]->testPerformance(false);
                }

                cout << "Total Time:" << total / 1000.0f << "ms" << endl;
            }
        }
        else
        {
            if (DATA_TO_USE & Test)
            {
                for (int i = 0; i < g_days.size(); ++i)
                {
                    g_days[i]->runTest();
                }
            }

            if (DATA_TO_USE & Regular)
            {
                for (int i = 0; i < g_days.size(); ++i)
                {
                    g_days[i]->run();
                }
            }
        }
    }
    else
    {
        int toRun = (RUN_SPECIFIC == 0 || RUN_SPECIFIC > (int)g_days.size()) ?  (int)g_days.size() - 1 : RUN_SPECIFIC - 1;

        if (TEST_PERFORMANCE)
        {
            if (DATA_TO_USE & Test)
            {
                g_days[toRun]->testPerformance(true);
            }

            if (DATA_TO_USE & Regular)
            {
                g_days[toRun]->testPerformance(false);
            }
        }
        else
        {
            if (DATA_TO_USE & Test)
            {
                g_days[toRun]->runTest();
            }

            if (DATA_TO_USE & Regular)
            {
                g_days[toRun]->run();
            }
        }
    }

    return 0;
}
