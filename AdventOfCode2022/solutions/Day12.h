#pragma once

#include <Helpers.h>
#include <DayBase.h>

/**
* DayTwelve
* 
* This is a the solution for Day Twelve of Advent of Code 2022.
* https://adventofcode.com/2022/day/12
* 
*/
class DayTwelve : public DayBase
{
public:
	DayTwelve()
		: DayBase("Twelve", "input\\Day12_Input.txt")
	{}

protected:
	virtual void questionOne(istream& input, ostream& output);
	virtual void questionTwo(istream& input, ostream& output);
};
