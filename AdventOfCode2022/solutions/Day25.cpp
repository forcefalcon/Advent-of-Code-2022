#include <Helpers.h>
#include <DayBase.h>

/**
* DayTwentyFive
*
* This is a the solution for Day TwentyFive of Advent of Code 2022.
* https://adventofcode.com/2022/day/25
*
*/
class DayTwentyFive : public DayBase
{
public:
	DayTwentyFive()
		: DayBase(25)
	{}

protected:
	virtual void questionOne(istream& input, ostream& output)
	{
		long long total = 0;
		string line;
		while (getline(input, line))
		{
			total += fromSNAFU(line);
		}

		output << toSNAFU(total);
	}

	virtual void questionTwo(istream& input, ostream& output)
	{
	}

private:

	string toSNAFU(long long value)
	{
		string ret;
		long long currentValue = value;

		while (currentValue > 0)
		{
			int mod = currentValue % 5;
			currentValue = currentValue / 5;

			if (mod == 0)
			{
				ret = '0' + ret;
			}
			else if (mod == 1)
			{
				ret = '1' + ret;
			}
			else if (mod == 2)
			{
				ret = '2' + ret;
			}
			else if (mod == 3)
			{
				currentValue++;
				ret = '=' + ret;
			}
			else if (mod == 4)
			{
				currentValue++;
				ret = '-' + ret;
			}

		}
		
		return ret;
	}

	long long fromSNAFU(string value)
	{
		long long ret = 0;

		for (int d = 0; d <= value.length() - 1; ++d)
		{
			int index = value.length() - d - 1;

			long long multiplier = pow((long long)5, (long long)d);

			if (value[index] == '-')
			{
				ret -= multiplier;
			}
			else if (value[index] == '=')
			{
				ret -= 2 * multiplier;
			}
			else
			{
				ret += (value[index] - '0') * multiplier;
			}
		}

		return ret;
	}
};

DayTwentyFive g_dayTwentyFive = DayTwentyFive();
