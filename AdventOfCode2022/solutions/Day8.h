#pragma once

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
		: DayBase("8")
	{}

protected:
	virtual void questionOne(istream& input, ostream& output);
	virtual void questionTwo(istream& input, ostream& output);
};
