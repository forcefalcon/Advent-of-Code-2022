#pragma once

#include <Helpers.h>
#include <DayBase.h>

/**
* DaySeventeen
* 
* This is a the solution for Day Seventeen of Advent of Code 2022.
* https://adventofcode.com/2022/day/17
* 
*/
class DaySeventeen : public DayBase
{
public:
	DaySeventeen()
		: DayBase("Seventeen", "input\\Day17_Input.txt")
	{}

protected:
	virtual void questionOne(istream& input, ostream& output);
	virtual void questionTwo(istream& input, ostream& output);
};
