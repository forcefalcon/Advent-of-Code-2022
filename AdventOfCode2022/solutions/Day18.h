#pragma once

#include <Helpers.h>
#include <DayBase.h>

/**
* DayEighteen
* 
* This is a the solution for Day Eighteen of Advent of Code 2022.
* https://adventofcode.com/2022/day/18
* 
*/
class DayEighteen : public DayBase
{
public:
	DayEighteen()
		: DayBase("18")
	{}

protected:
	virtual void questionOne(istream& input, ostream& output);
	virtual void questionTwo(istream& input, ostream& output);
};
