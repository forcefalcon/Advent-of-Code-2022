#pragma once

#include <Helpers.h>
#include <DayBase.h>

/**
* DayNine
* 
* This is a the solution for Day Nine of Advent of Code 2022.
* https://adventofcode.com/2022/day/9
* 
*/
class DayNine : public DayBase
{
public:
	DayNine()
		: DayBase("Nine", "input\\Day9_Input.txt")
	{}

protected:
	virtual void questionOne(istream& input, ostream& output);
	virtual void questionTwo(istream& input, ostream& output);
};
