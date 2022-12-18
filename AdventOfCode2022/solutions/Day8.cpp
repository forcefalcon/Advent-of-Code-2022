#include <Helpers.h>
#include <DayBase.h>

/**
* DayEight
*
* This is a the solution for Day Eight of Advent of Code 2022.
* https://adventofcode.com/2022/day/8
*
*/
class DayEight : public DayBase
{
public:
    DayEight()
        : DayBase(8)
    {}

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

DayEight g_dayEight = DayEight();
