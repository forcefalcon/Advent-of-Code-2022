#include "Day12.h"

int followPath(int x, int y, int endX, int endY, const vector<vector<char>>& grid, set<pair<int, int>>& visited)
{
    if (x == endX && y == endY)
    {
        return 0;
    }

    visited.insert(pair<int, int>(x, y));

    int bestTotal = -1;
    char current = grid[y][x];
    if (x > 0 && grid[y][x - 1] <= current + 1
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
        && visited.find(pair<int, int>(x, y + 1)) == visited.end())
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
        calculateValues(x - 1, y, grid, distanceToEnd, currDistance);
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

void DayTwelve::questionOne(istream& input, ostream& output)
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

void DayTwelve::questionTwo(istream& input, ostream& output)
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
