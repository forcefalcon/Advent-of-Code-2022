#include "Day14.h"

int startX = 500;

void resizeGrid(size_t width, size_t height, vector<vector<char>>& grid, bool addFloor = false)
{
    if (grid.size() < height)
    {
        grid.resize(height);
    }

    size_t newWidth = grid[0].size() < width ? width : grid[0].size();

    if (grid[grid.size() - 1].size() < newWidth)
    {
        for (int i = 0; i < grid.size(); ++i)
        {
            grid[i].resize(newWidth, (addFloor && i == grid.size() - 1) ? '#' : '.');
        }
    }
}

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

void DayFourteen::questionOne(istream& input, ostream& output)
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

void DayFourteen::questionTwo(istream& input, ostream& output)
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