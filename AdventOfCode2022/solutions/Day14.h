#pragma once

#include <Helpers.h>
#include <DayBase.h>

/**
* DayFourteen
* 
* This is a the solution for Day Fourteen of Advent of Code 2022.
* https://adventofcode.com/2022/day/14
* 
*/
class DayFourteen : public DayBase
{
public:
	DayFourteen()
		: DayBase("14")
	{}

protected:
	virtual void questionOne(istream& input, ostream& output);
	virtual void questionTwo(istream& input, ostream& output);
};
