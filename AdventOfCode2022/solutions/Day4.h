#pragma once

#include <Helpers.h>
#include <DayBase.h>

/**
* DayFour
* 
* This is a the solution for Day Four of Advent of Code 2022.
* https://adventofcode.com/2022/day/4
* 
*/
class DayFour : public DayBase
{
public:
	DayFour()
		: DayBase("4")
	{}

protected:
	virtual void questionOne(istream& input, ostream& output);
	virtual void questionTwo(istream& input, ostream& output);
};
