#pragma once

#include <Helpers.h>
#include <DayBase.h>

/**
* DayTen
* 
* This is a the solution for Day Ten of Advent of Code 2022.
* https://adventofcode.com/2022/day/10
* 
*/
class DayTen : public DayBase
{
public:
	DayTen()
		: DayBase("10")
	{}

protected:
	virtual void questionOne(istream& input, ostream& output);
	virtual void questionTwo(istream& input, ostream& output);
};
