#pragma once

#include <Helpers.h>
#include <DayBase.h>

/**
* DayTemplate
* 
* This is a template for all Advent of Code Days. To use this copy it and rename to the appropriate Day.
*/
class DayTemplate : public DayBase
{
public:
	DayTemplate()
		: DayBase("Template", "input\\DayTemplate_Input.txt")
	{}

protected:
	virtual void questionOne(istream& input, ostream& output);
	virtual void questionTwo(istream& input, ostream& output);
};
