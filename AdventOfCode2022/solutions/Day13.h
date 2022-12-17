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
		: DayBase("Thirteen", "input\\Day13_Input.txt")
	{}

protected:
	virtual void questionOne(istream& input, ostream& output);
	virtual void questionTwo(istream& input, ostream& output);
};
