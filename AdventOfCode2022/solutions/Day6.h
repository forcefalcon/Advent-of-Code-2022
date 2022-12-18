#pragma once

#include <Helpers.h>
#include <DayBase.h>

/**
* DaySix
* 
* This is a the solution for Day Six of Advent of Code 2022.
* https://adventofcode.com/2022/day/6
* 
*/
class DaySix : public DayBase
{
public:
	DaySix()
		: DayBase("6")
	{}

protected:
	virtual void questionOne(istream& input, ostream& output);
	virtual void questionTwo(istream& input, ostream& output);
};
