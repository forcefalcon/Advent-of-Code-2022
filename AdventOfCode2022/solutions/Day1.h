#pragma once

#include <Helpers.h>
#include <DayBase.h>

/**
* DayOne
* 
* This is a the solution for Day One of Advent of Code 2022.
* https://adventofcode.com/2022/day/1
* 
*/
class DayOne : public DayBase
{
public:
	DayOne()
		: DayBase("1")
	{}

protected:
	virtual void questionOne(istream& input, ostream& output);
	virtual void questionTwo(istream& input, ostream& output);
};
