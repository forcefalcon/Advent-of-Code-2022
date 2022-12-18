#include <Helpers.h>
#include <DayBase.h>

/**
* DaySeventeen
*
* This is a the solution for Day Seventeen of Advent of Code 2022.
* https://adventofcode.com/2022/day/17
*
*/
class DaySeventeen : public DayBase
{
public:
    DaySeventeen()
        : DayBase(17)
    {
        initRockShapes();
    }

protected:
    virtual void questionOne(istream& input, ostream& output)
    {
        string line;
        getline(input, line);

        int currLineIndex = 0;

        const long long NUM_ROCKS = 2022;

        for (int i = 0; i < NUM_ROCKS; ++i)
        {
            Rock rock;
            spawnRock(rock);

            bool isDone = false;
            while (!isDone)
            {
                moveRock(rock, line[currLineIndex] == '<' ? -1 : 1, 0);
                ++currLineIndex;
                if (currLineIndex >= line.length())
                    currLineIndex = 0;

                isDone = !moveRock(rock, 0, -1);

                if (isDone)
                {
                    settleRock(rock);
                }
            }

            //print();
            //cout << endl;
        }

        output << getTowerHeight();
    }

    virtual void questionTwo(istream& input, ostream& output)
    {
        CurrentRock = 0;
        grid.resize(0);
        yOffset = 0;

        vector<long long> towerHeights;

        string line;
        getline(input, line);

        int currLineIndex = 0;

        const long long NUM_ROCKS = 100000;

        int patternCount = 0;
        int testPatternCount = 5;

        for (long long i = 0; i < NUM_ROCKS; ++i)
        {
            Rock rock;
            spawnRock(rock);

            bool isDone = false;
            while (!isDone)
            {
                moveRock(rock, line[currLineIndex] == '<' ? -1 : 1, 0);
                ++currLineIndex;
                if (currLineIndex >= line.length())
                    currLineIndex = 0;

                isDone = !moveRock(rock, 0, -1);

                if (isDone)
                {
                    settleRock(rock);
                }
            }

            towerHeights.emplace_back(getTowerHeight());

            patternCount = getPatternCount(towerHeights, i, testPatternCount);

            if (patternCount != 0)
                break;
        }

        long long countAt = 1000000000000;
        long long diff = towerHeights[towerHeights.size() - 1] - towerHeights[towerHeights.size() - 1 - patternCount];

        long long total = towerHeights[countAt % patternCount - 1] + (countAt / patternCount) * diff;
        output << total;
    }

private:
    // Static
    static vector<vector<char>>* FlatShape;
    static vector<vector<char>>* CrossShape;
    static vector<vector<char>>* LShape;
    static vector<vector<char>>* TallShape;
    static vector<vector<char>>* BlockShape;

    static void initRockShapes()
    {
        FlatShape = new vector<vector<char>>();
        FlatShape->emplace_back();
        FlatShape->back().resize(4, '#');

        CrossShape = new vector<vector<char>>();
        CrossShape->emplace_back();
        CrossShape->back().resize(3, '.');
        CrossShape->back()[1] = '#';
        CrossShape->emplace_back();
        CrossShape->back().resize(3, '#');
        CrossShape->emplace_back();
        CrossShape->back().resize(3, '.');
        CrossShape->back()[1] = '#';

        LShape = new vector<vector<char>>();
        LShape->emplace_back();
        LShape->back().resize(3, '#');
        LShape->emplace_back();
        LShape->back().resize(3, '.');
        LShape->back()[2] = '#';
        LShape->emplace_back();
        LShape->back().resize(3, '.');
        LShape->back()[2] = '#';

        TallShape = new vector<vector<char>>();
        TallShape->emplace_back();
        TallShape->back().emplace_back('#');
        TallShape->emplace_back();
        TallShape->back().emplace_back('#');
        TallShape->emplace_back();
        TallShape->back().emplace_back('#');
        TallShape->emplace_back();
        TallShape->back().emplace_back('#');

        BlockShape = new vector<vector<char>>();
        BlockShape->emplace_back();
        BlockShape->back().resize(2, '#');
        BlockShape->emplace_back();
        BlockShape->back().resize(2, '#');
    }

    // Classes
    enum RockShape
    {
        Flat = 0,
        Cross,
        L,
        Tall,
        Block
    };

    struct Rock
    {
        RockShape shape;
        int x; // Left
        long long y; // Bottom

        int width;
        int height;

        const vector<vector<char>>& pixels()
        {
            switch (shape)
            {
            case Flat:
                return *FlatShape;
            case Cross:
                return *CrossShape;
            case L:
                return *LShape;
            case Tall:
                return *TallShape;
            case Block:
                return *BlockShape;
            default:
                return *FlatShape;
            }
        }
    };

    // State
    const int TOWER_WIDTH = 7;
    long long yOffset = 0;
    int CurrentRock = Flat;

    typedef deque<vector<char>> Grid;
    Grid grid;

    void addRow()
    {
        grid.emplace_back();
        grid.back().resize(TOWER_WIDTH, '.');

        const int ADJUST = 1000;

        if (grid.size() > ADJUST * 2)
        {
            for (int i = 0; i < ADJUST; ++i)
            {
                grid.pop_front();
            }

            yOffset += ADJUST;
        }
    }

    long long getTowerHeight()
    {
        for (int y = (int)grid.size() - 1; y >= 0; --y)
        {
            for (int x = 0; x < TOWER_WIDTH; ++x)
            {
                if (grid[y][x] != '.')
                {
                    return y + 1 + yOffset;
                }
            }
        }

        return 0;
    }

    void spawnRock(Rock& rock)
    {
        rock.shape = (RockShape)CurrentRock;
        rock.x = 2;
        rock.y = getTowerHeight() + 3;

        switch (rock.shape)
        {
        case Flat:
            rock.width = 4;
            rock.height = 1;
            break;
        case Cross:
            rock.width = 3;
            rock.height = 3;
            break;
        case L:
            rock.width = 3;
            rock.height = 3;
            break;
        case Tall:
            rock.width = 1;
            rock.height = 4;
            break;
        case Block:
            rock.width = 2;
            rock.height = 2;
            break;
        }

        if (++CurrentRock > Block)
        {
            CurrentRock = Flat;
        }

        long long addedHeight = (rock.y + rock.height + 3) - (grid.size() + yOffset);
        for (int i = 0; i < addedHeight; ++i)
            addRow();
    }

    bool moveRock(Rock& rock, int xDir, int yDir)
    {
        int newX = rock.x + xDir;
        long long newY = rock.y + yDir;

        if (newX < 0 || newX + rock.width > TOWER_WIDTH)
        {
            return false;
        }
        if (newY < 0)
        {
            return false;
        }

        for (int y = 0; y < rock.height; ++y)
        {
            for (int x = 0; x < rock.width; ++x)
            {
                if (grid[y + newY - yOffset][x + newX] != '.' && rock.pixels()[y][x] != '.')
                {
                    return false;
                }
            }
        }

        rock.x = newX;
        rock.y = newY;

        return true;
    }

    void settleRock(Rock& rock)
    {
        long long yAdjust = 0;
        for (int y = 0; y < rock.height; ++y)
        {
            for (int x = 0; x < rock.width; ++x)
            {
                if (rock.pixels()[y][x] != '.')
                {
                    grid[y + rock.y - yOffset][x + rock.x] = '#';
                }
            }
        }
    }

    int getPatternCount(vector<long long> values, long long maxValue, int& currentPatternCount)
    {
        if (maxValue < 15)
            return 0;

        int numToCheck = 5;

        bool matched = false;
        while (!matched && currentPatternCount * 4 < maxValue)
        {
            matched = true;
            for (int i = 0; i < currentPatternCount; ++i)
            {
                long long diffOne = values[i + 2 * currentPatternCount] - values[i + currentPatternCount];
                long long diffTwo = values[i + 3 * currentPatternCount] - values[i + 2 * currentPatternCount];

                if (diffOne != diffTwo)
                    matched = false;
            }

            if (!matched)
            {
                currentPatternCount++;
            }
            else
            {
                return currentPatternCount;
            }
        }

        return 0;
    }

    void print()
    {
        for (int y = (int)grid.size() - 1; y >= 0; --y)
        {
            for (int x = 0; x < TOWER_WIDTH; ++x)
            {
                cout << grid[y][x];
            }
            cout << endl;
        }
    }
};

DaySeventeen g_daySeventeen = DaySeventeen();

vector<vector<char>>* DaySeventeen::FlatShape = nullptr;
vector<vector<char>>* DaySeventeen::CrossShape = nullptr;
vector<vector<char>>* DaySeventeen::LShape = nullptr;
vector<vector<char>>* DaySeventeen::TallShape = nullptr;
vector<vector<char>>* DaySeventeen::BlockShape = nullptr;
