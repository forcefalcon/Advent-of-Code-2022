#include <Helpers.h>
#include <DayBase.h>

/**
* DayTwentyOne
*
* This is a the solution for Day Twenty One of Advent of Code 2022.
* https://adventofcode.com/2022/day/21
*
*/
class DayTwentyOne : public DayBase
{
	enum Operator
	{
		Add,
		Subtract,
		Multiply,
		Divide,
		None
	};

	struct Eval
	{
		int value = 0;
		string e1;
		string e2;
		Operator op = None;
	};

	typedef map<string, Eval> EvalMap;

public:
	DayTwentyOne()
		: DayBase(21)
	{}

protected:
	virtual void questionOne(istream& input, ostream& output)
	{
		EvalMap evals;
		parse(input, evals);

		long long total = eval("root", evals);
		output << total;
	}

	virtual void questionTwo(istream& input, ostream& output)
	{
		finalPath.clear();
		EvalMap evals;
		parse(input, evals);

		Eval& val = evals["root"];
		bool found = false;
		deque<string> currentPath;
		long long  otherVal = eval2(val.e1, evals, found, currentPath);
		long long total = 0;

		if (found)
		{
			otherVal = eval(val.e2, evals);

			finalPath.pop_front();
			total = calculate(val.e1, evals, otherVal, finalPath);
		}
		else
		{
			eval2(val.e2, evals, found, currentPath);

			finalPath.pop_front();
			total = calculate(val.e2, evals, otherVal, finalPath);
		}

		output << total;
	}
private:
	deque<string> finalPath;

	void parse(istream& input, EvalMap& map)
	{
		string line;
		while (getline(input, line))
		{
			vector<string> words = splitString(line, " ");

			if (words.size() == 4)
			{
				map[words[0].substr(0, 4)].e1 = words[1];
				map[words[0].substr(0, 4)].e2 = words[3];

				switch (words[2][0])
				{
				case '+':
					map[words[0].substr(0, 4)].op = Add;
					break;
				case '-':
					map[words[0].substr(0, 4)].op = Subtract;
					break;
				case '*':
					map[words[0].substr(0, 4)].op = Multiply;
					break;
				case '/':
					map[words[0].substr(0, 4)].op = Divide;
					break;
				}
			}
			else
			{
				map[words[0].substr(0, 4)].value = atoi(words[1].c_str());
			}
		}
	}

	long long eval(string key, EvalMap& map)
	{
		Eval& val = map[key];

		switch (val.op)
		{
		case Add:
			return eval(val.e1, map) + eval(val.e2, map);
		case Subtract:
			return eval(val.e1, map) - eval(val.e2, map);
		case Multiply:
			return eval(val.e1, map) * eval(val.e2, map);
		case Divide:
			return eval(val.e1, map) / eval(val.e2, map);
		default:
			return val.value;
		}
	}

	long long eval2(string key, EvalMap& map, bool& found, deque<string> currentPath)
	{
		currentPath.push_back(key);

		if (key.compare("humn") == 0)
		{
			found = true;
			finalPath = currentPath;
			return 0;
		}

		Eval& val = map[key];

		switch (val.op)
		{
		case Add:
			return eval2(val.e1, map, found, currentPath) + eval2(val.e2, map, found, currentPath);
		case Subtract:
			return eval2(val.e1, map, found, currentPath) - eval2(val.e2, map, found, currentPath);
		case Multiply:
			return eval2(val.e1, map, found, currentPath) * eval2(val.e2, map, found, currentPath);
		case Divide:
			return eval2(val.e1, map, found, currentPath) / eval2(val.e2, map, found, currentPath);
		default:
			return val.value;
		}
	}

	long long calculate(string key, EvalMap& map, long long currValue, deque<string> currentPath)
	{
		if (key.compare("humn") == 0)
		{
			return currValue;
		}

		Eval& val = map[key];
		string pathVal = currentPath.front();
		currentPath.pop_front();

		if (pathVal.compare(val.e1) == 0)
		{
			long long otherVal = eval(val.e2, map);

			switch (val.op)
			{
			case Add:
				currValue = currValue - otherVal;
				return calculate(val.e1, map, currValue, currentPath);
			case Subtract:
				currValue = currValue + otherVal;
				return calculate(val.e1, map, currValue, currentPath);
			case Multiply:
				currValue = currValue / otherVal;
				return calculate(val.e1, map, currValue, currentPath);
			case Divide:
				currValue = currValue * otherVal;
				return calculate(val.e1, map, currValue, currentPath);
			default:
				cerr << "NOT SUPPOSED TO BE HERE";
				return 0;
			}
		}
		else
		{
			long long otherVal = eval(val.e1, map);

			switch (val.op)
			{
			case Add:
				currValue = currValue - otherVal;
				return calculate(val.e2, map, currValue, currentPath);
			case Subtract:
				currValue = otherVal - currValue;
				return calculate(val.e2, map, currValue, currentPath);
			case Multiply:
				currValue = currValue / otherVal;
				return calculate(val.e2, map, currValue, currentPath);
			case Divide:
				currValue = otherVal / currValue;
				return calculate(val.e2, map, currValue, currentPath);
			default:
				cerr << "NOT SUPPOSED TO BE HERE";
				return 0;
			}
		}
	}
};

DayTwentyOne g_dayTwentyOne = DayTwentyOne();
