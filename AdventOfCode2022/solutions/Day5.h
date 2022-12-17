#pragma once

#include <Helpers.h>
#include <DayBase.h>

/**
* DayFive
* 
* This is a the solution for Day Five of Advent of Code 2022.
* https://adventofcode.com/2022/day/5
* 
*/
class DayFive : public DayBase
{
public:
	DayFive()
		: DayBase("Five", "input\\Day5_Input.txt")
	{}

protected:
	virtual void questionOne(istream& input, ostream& output);
	virtual void questionTwo(istream& input, ostream& output);
};
