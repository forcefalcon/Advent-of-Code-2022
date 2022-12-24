#include <Helpers.h>
#include <DayBase.h>

/**
* DayTwenty
*
* This is a the solution for Day Twenty of Advent of Code 2022.
* https://adventofcode.com/2022/day/20
*
*/
class DayTwenty : public DayBase
{
public:
	DayTwenty()
		: DayBase(20)
	{}

	typedef pair<int, bool> Position; // value, hasMoved
	typedef list<pair<int, bool>> PositionList;

	typedef pair<int, int> Q2Position;
	typedef list<Q2Position> Q2List;

protected:
	virtual void questionOne(istream& input, ostream& output)
	{
		PositionList pos;
		parse(input, pos);

		for (PositionList::iterator current = pos.begin(); current != pos.end(); )
		{
			Position currPos = *current;

			if (!currPos.second)
			{
				currPos.second = true;

				current = pos.erase(current);

				PositionList::iterator nextLoc = current;

				if (currPos.first < 0)
				{
					for (int i = 0; i > currPos.first; --i)
					{
						if (nextLoc == pos.begin())
						{
							nextLoc = pos.end();
						}

						--nextLoc;
					}

					if (nextLoc == pos.begin())
					{
						nextLoc = pos.end();
					}
				}
				else
				{
					if (nextLoc == pos.end())
					{
						nextLoc = pos.begin();
					}

					for (int i = 0; i < currPos.first; ++i)
					{
						++nextLoc;

						if (nextLoc == pos.end())
						{
							nextLoc = pos.begin();
						}
					}
				}

				pos.insert(nextLoc, currPos);
			}
			else
			{
				++current;
			}
		}

		int total = 0;
		PositionList::const_iterator location = pos.begin();

		while ((*location).first != 0)
		{
			++location;
		}

		for (int i = 1; i <= 3000; ++i)
		{
			++location;
			if (location == pos.end())
			{
				location = pos.begin();
			}

			if (i == 1000 || i == 2000 || i == 3000)
			{
				total += (*location).first;
			}
		}

		output << total;
	}

	virtual void questionTwo(istream& input, ostream& output)
	{
		Q2List pos;
		parse2(input, pos);
		applyKey(pos);

		vector<Q2List::iterator> iterators;
		for (Q2List::iterator i = pos.begin(); i != pos.end(); ++i)
		{
			iterators.push_back(i);
		}

		for (int k = 0; k < 10; ++k)
		{
			for (int i = 0; i < iterators.size(); ++i)
			{
				Q2List::iterator current = iterators[i];
				Q2Position currPos = (*current);

				current = pos.erase(current);

				if (currPos.second < 0)
				{
					for (int i = 0; i > currPos.second; --i)
					{
						if (current == pos.begin())
						{
							current = pos.end();
						}

						--current;
					}

					if (current == pos.begin())
					{
						current = pos.end();
					}
				}
				else if (currPos.second > 0)
				{
					if (current == pos.end())
					{
						current = pos.begin();
					}

					for (int i = 0; i < currPos.second; ++i)
					{
						++current;

						if (current == pos.end())
						{
							current = pos.begin();
						}
					}
				}

				iterators[i] = pos.insert(current, currPos);
			}
		}

		long long total = 0;
		Q2List::const_iterator location = pos.begin();

		while ((*location).first != 0)
		{
			++location;
		}

		for (int i = 1; i <= 3000; ++i)
		{
			++location;
			if (location == pos.end())
			{
				location = pos.begin();
			}

			if (i == 1000 || i == 2000 || i == 3000)
			{
				total += (long long)(*location).first * DECRYPTION_KEY;
			}
		}

		output << total;
	}
private:
	const long long DECRYPTION_KEY = 811589153;

	void parse(istream& input, PositionList& list)
	{
		string line;
		while (getline(input, line))
		{
			list.emplace_back(atoi(line.c_str()), false);
		}
	}

	void parse2(istream& input, Q2List& list)
	{
		string line;
		while (getline(input, line))
		{
			list.emplace_back(atoi(line.c_str()), 0);
		}
	}

	void applyKey(Q2List& list)
	{
		size_t maxSize = list.size()-1;

		for (auto iter = list.begin(); iter != list.end(); ++iter)
		{
			(*iter).second = (int)((abs((*iter).first) * DECRYPTION_KEY) % maxSize) * sign((*iter).first);
		}
	}

	void printList(Q2List& list)
	{
		for (auto iter = list.begin(); iter != list.end(); ++iter)
		{
			cout << (*iter).first * DECRYPTION_KEY << ", ";
		}

		cout << endl;
	}
};

DayTwenty g_dayTwenty = DayTwenty();
