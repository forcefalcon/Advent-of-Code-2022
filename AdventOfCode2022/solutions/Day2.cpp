#include <Helpers.h>
#include <DayBase.h>

/**
* DayTwo
*
* This is a the solution for Day Two of Advent of Code 2022.
* https://adventofcode.com/2022/day/2
*
*/
class DayTwo : public DayBase
{
public:
    DayTwo()
        : DayBase(2)
    {}

protected:
    virtual void questionOne(istream& input, ostream& output)
    {
        string line;

        int total = 0;

        while (getline(input, line))
        {
            Hand opponent;
            Hand player;

            switch (line[0])
            {
            case 'A':
                opponent = Rock;
                break;
            case 'B':
                opponent = Paper;
                break;
            case 'C':
                opponent = Scissors;
                break;
            default:
                cerr << "Error with Opponent!" << "\n";
                continue;
            }

            switch (line[2])
            {
            case 'X':
                player = Rock;
                total += 1;
                break;
            case 'Y':
                player = Paper;
                total += 2;
                break;
            case 'Z':
                player = Scissors;
                total += 3;
                break;
            default:
                cerr << "Error with Player!" << "\n";
                continue;
            }

            // Points for Game
            if (opponent == Rock && player == Paper ||
                opponent == Paper && player == Scissors ||
                opponent == Scissors && player == Rock)
            {
                total += 6;
            }
            else if (opponent == player)
            {
                total += 3;
            }
        }

        output << (total);
    }

    virtual void questionTwo(istream& input, ostream& output)
    {
        string line;
        int total = 0;
        while (getline(input, line))
        {
            Hand opponent;
            Hand player;

            switch (line[0])
            {
            case 'A':
                opponent = Rock;
                break;
            case 'B':
                opponent = Paper;
                break;
            case 'C':
                opponent = Scissors;
                break;
            default:
                cerr << "Error with Opponent!" << "\n";
                continue;
            }

            switch (line[2])
            {
            case 'X':
                switch (opponent)
                {
                case Rock:
                    player = Scissors;
                    break;
                case Paper:
                    player = Rock;
                    break;
                case Scissors:
                    player = Paper;
                    break;
                }
                break;
            case 'Y':
                switch (opponent)
                {
                case Rock:
                    player = Rock;
                    break;
                case Paper:
                    player = Paper;
                    break;
                case Scissors:
                    player = Scissors;
                    break;
                }
                break;
            case 'Z':
                switch (opponent)
                {
                case Rock:
                    player = Paper;
                    break;
                case Paper:
                    player = Scissors;
                    break;
                case Scissors:
                    player = Rock;
                    break;
                }
                break;
            default:
                cerr << "Error with Player!" << "\n";
                continue;
            }

            // Points for Symbol
            switch (player)
            {
            case Rock:
                total += 1;
                break;
            case Paper:
                total += 2;
                break;
            case Scissors:
                total += 3;
                break;
            }

            // Points for Game
            if (opponent == Rock && player == Paper ||
                opponent == Paper && player == Scissors ||
                opponent == Scissors && player == Rock)
            {
                total += 6;
            }
            else if (opponent == player)
            {
                total += 3;
            }
        }

        output << (total);
    }

private:
    enum Hand
    {
        Rock,
        Paper,
        Scissors
    };
};

DayTwo g_dayTwo = DayTwo();
