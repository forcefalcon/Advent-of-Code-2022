#pragma once

#include <Helpers.h>
#include <DayBase.h>

/**
* DayThree
* 
* This is a the solution for Day Three of Advent of Code 2022.
* https://adventofcode.com/2022/day/3
*/
class DayThree : public DayBase
{
public:
	DayThree()
		: DayBase("Three", "input\\Day3_Input.txt")
	{}

protected:
	virtual void questionOne(istream& input, ostream& output);
	virtual void questionTwo(istream& input, ostream& output);
};
