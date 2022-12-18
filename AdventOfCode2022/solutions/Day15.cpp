#include <Helpers.h>
#include <DayBase.h>

/**
* DayFifteen
*
* This is a the solution for Day Fifteen of Advent of Code 2022.
* https://adventofcode.com/2022/day/15
*
*/
class DayFifteen : public DayBase
{
public:
    DayFifteen()
        : DayBase(15)
    {}

protected:
    virtual void questionOne(istream& input, ostream& output)
    {
        string line;
        vector<pair<int, int>> sensors;
        vector<pair<int, int>> closestBeacons;
        vector<int> distances;

        int maxDistance = -1;

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
};

DayFifteen g_dayFifteen = DayFifteen();
