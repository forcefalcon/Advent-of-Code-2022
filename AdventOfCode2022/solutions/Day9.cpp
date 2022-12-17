#include "Day9.h"

void calculateTail(const int headX, const int headY, int& tailX, int& tailY)
{
    if (headY > tailY + 1)
    {
        tailY = headY - 1;
        if (headX != tailX)
        {
            int diff = headX - tailX;

            tailX += sign(diff);
        }
    }
    else if (headY < tailY - 1)
    {
        tailY = headY + 1;
        if (headX != tailX)
        {
            int diff = headX - tailX;

            tailX += sign(diff);
        }
    }
    else if (headX > tailX + 1)
    {
        tailX = headX - 1;
        if (headY != tailY)
        {
            int diff = headY - tailY;

            tailY += sign(diff);
        }
    }
    else if (headX < tailX - 1)
    {
        tailX = headX + 1;
        if (headY != tailY)
        {
            int diff = headY - tailY;

            tailY += sign(diff);
        }
    }
}

//void calculateTailTake2(const int headX, const int headY, int& tailX, int& tailY)
//{
//    int diffX = headX - tailX;
//    int diffY = headY - tailY;
//
//    if (abs(diffY) >= 2)
//    {
//        tailY += sign(diffY);
//
//        if (headX != tailX)
//        {
//            tailX += sign(diffX);
//        }
//    }
//
//    if (abs(diffX) >= 2)
//    {
//        tailX += sign(diffX);
//
//        if (headY != tailY)
//        {
//            tailY += sign(diffY);
//        }
//    }
//}

void DayNine::questionOne(istream& input, ostream& output)
{
    string line;

    int totalCount = 0;
    set<string> moves;

    int headX = 0; int headY = 0; int tailX = 0; int tailY = 0;
    moves.insert("0,0");

    stringstream ss;
    while (getline(input, line))
    {
        int moveCount = atoi(line.substr(2).c_str());

        for (int i = 0; i < moveCount; ++i)
        {
            switch (line[0])
            {
            case 'R':
                headX++;
                break;
            case 'L':
                headX--;
                break;
            case 'U':
                headY++;
                break;
            case 'D':
                headY--;
                break;
            }

            calculateTail(headX, headY, tailX, tailY);
            ss << tailX << "," << tailY;
            moves.insert(ss.str());
            ss.str(string());
        }
    }

    output << moves.size();
}

void DayNine::questionTwo(istream& input, ostream& output)
{
    string line;

    int totalCount = 0;
    set<string> moves;

    const int NUM_KNOTS = 10;
    int X[NUM_KNOTS];
    int Y[NUM_KNOTS];
    moves.insert("0,0");

    for (int i = 0; i < NUM_KNOTS; ++i)
    {
        X[i] = 0;
        Y[i] = 0;
    }

    stringstream ss;
    while (getline(input, line))
    {
        int moveCount = atoi(line.substr(2).c_str());

        for (int i = 0; i < moveCount; ++i)
        {
            switch (line[0])
            {
            case 'R':
                X[0]++;
                break;
            case 'L':
                X[0]--;
                break;
            case 'U':
                Y[0]++;
                break;
            case 'D':
                Y[0]--;
                break;
            }

            for (int i = 0; i < NUM_KNOTS - 1; ++i)
            {
                calculateTail(X[i], Y[i], X[i + 1], Y[i + 1]);
            }
            ss << X[9] << "," << Y[9];
            moves.insert(ss.str());
            ss.str(string());
        }
    }

    output << moves.size();
}

//void Day9Q1Take2(istream& input)
//{
//    string line;
//
//    int totalCount = 0;
//    set<pair<int, int>> moves;
//
//    int headX = 0; int headY = 0; int tailX = 0; int tailY = 0;
//    moves.insert(pair<int,int>(0,0));
//
//    while (getline(input, line))
//    {
//        int moveCount = atoi(line.substr(2).c_str());
//
//        char dir = line[0];
//
//        for (int i = 0; i < moveCount; ++i)
//        {
//            switch (dir)
//            {
//            case 'R':
//                headX++;
//                break;
//            case 'L':
//                headX--;
//                break;
//            case 'U':
//                headY++;
//                break;
//            case 'D':
//                headY--;
//                break;
//            }
//
//            calculateTailTake2(headX, headY, tailX, tailY);
//            moves.insert(pair<int,int>(tailX, tailY));
//        }
//    }
//
//    cout << "Answer: " << moves.size() << endl;
//}
//
//void Day9Q2Take2(istream& input)
//{
//    string line;
//
//    int totalCount = 0;
//    set<pair<int, int>> moves;
//
//    const int NUM_KNOTS = 10;
//    int X[NUM_KNOTS];
//    int Y[NUM_KNOTS];
//    moves.insert(pair<int, int>(0, 0));
//
//    for (int i = 0; i < NUM_KNOTS; ++i)
//    {
//        X[i] = 0;
//        Y[i] = 0;
//    }
//
//    while (getline(input, line))
//    {
//        int moveCount = atoi(line.substr(2).c_str());
//
//        char dir = line[0];
//        for (int i = 0; i < moveCount; ++i)
//        {
//            switch (dir)
//            {
//            case 'R':
//                X[0]++;
//                break;
//            case 'L':
//                X[0]--;
//                break;
//            case 'U':
//                Y[0]++;
//                break;
//            case 'D':
//                Y[0]--;
//                break;
//            }
//
//            for (int i = 0; i < NUM_KNOTS - 1; ++i)
//            {
//                calculateTail(X[i], Y[i], X[i + 1], Y[i + 1]);
//            }
//            moves.insert(pair<int, int>(X[9], Y[9]));
//        }
//    }
//
//    cout << "Answer: " << moves.size() << endl;
//}