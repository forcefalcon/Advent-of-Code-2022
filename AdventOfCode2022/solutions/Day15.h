#pragma once

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
		: DayBase("15")
	{}

protected:
	virtual void questionOne(istream& input, ostream& output);
	virtual void questionTwo(istream& input, ostream& output);
};
