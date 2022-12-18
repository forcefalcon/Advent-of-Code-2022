#pragma once

#include <Helpers.h>
#include <DayBase.h>

/**
* DayThirteen
* 
* This is a the solution for Day Thirteen of Advent of Code 2022.
* https://adventofcode.com/2022/day/13
* 
*/
class DayThirteen : public DayBase
{
public:
	DayThirteen()
		: DayBase("13")
	{}

protected:
	virtual void questionOne(istream& input, ostream& output);
	virtual void questionTwo(istream& input, ostream& output);
};
