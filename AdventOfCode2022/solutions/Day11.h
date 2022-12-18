#pragma once

#include <Helpers.h>
#include <DayBase.h>

/**
* DayEleven
* 
* This is a the solution for Day Eleven of Advent of Code 2022.
* https://adventofcode.com/2022/day/11
* 
*/
class DayEleven : public DayBase
{
public:
	DayEleven()
		: DayBase("11")
	{}

protected:
	virtual void questionOne(istream& input, ostream& output);
	virtual void questionTwo(istream& input, ostream& output);
};
