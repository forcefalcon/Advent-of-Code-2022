#pragma once

#include <Helpers.h>
#include <DayBase.h>

/**
* DaySixteen
* 
* This is a the solution for Day Sixteen of Advent of Code 2022.
* https://adventofcode.com/2022/day/16
* 
*/
class DaySixteen : public DayBase
{
public:
	DaySixteen()
		: DayBase("Sixteen", "input\\Day16_Input.txt")
	{}

protected:
	virtual void questionOne(istream& input, ostream& output);
	virtual void questionTwo(istream& input, ostream& output);
};
