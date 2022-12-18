#pragma once

#include <Helpers.h>
#include <DayBase.h>

/**
* DayTwo
* 
* This is a the solution for Day Two of Advent of Code 2022.
* https://adventofcode.com/2022/day/2
*/
class DayTwo : public DayBase
{
public:
	DayTwo()
		: DayBase("2")
	{}

protected:
	virtual void questionOne(istream& input, ostream& output);
	virtual void questionTwo(istream& input, ostream& output);
};
