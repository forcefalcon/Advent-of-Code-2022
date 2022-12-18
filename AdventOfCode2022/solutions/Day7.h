#pragma once

#include <Helpers.h>
#include <DayBase.h>

/**
* DaySeven
* 
* This is a the solution for Day Seven of Advent of Code 2022.
* https://adventofcode.com/2022/day/7
* 
*/
class DaySeven : public DayBase
{
public:
	DaySeven()
		: DayBase("7")
	{}

protected:
	virtual void questionOne(istream& input, ostream& output);
	virtual void questionTwo(istream& input, ostream& output);
};
