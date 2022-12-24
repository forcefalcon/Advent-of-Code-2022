#include <Helpers.h>
#include <DayBase.h>

/**
* DayTwentyThree
*
* This is a the solution for Day TwentyThree of Advent of Code 2022.
* https://adventofcode.com/2022/day/23
*
*/
class DayTwentyThree : public DayBase
{
public:
	DayTwentyThree()
		: DayBase(23)
	{}

protected:
	virtual void questionOne(istream& input, ostream& output)
	{
		State state;
		parse(input, state);

		//print(state);

		int currDirection = North;
		for (int i = 0; i < NUM_ROUNDS; ++i)
		{
			for (int e = 0; e < state.elves.size(); ++e)
			{
				tryMoveElf(e, currDirection, state);
			}

			for (int left = 0; left < state.elves.size() - 1; ++left)
			{
				Elf& leftElf = state.elves[left];

				for (int right = left + 1; right < state.elves.size(); ++right)
				{
					Elf& rightElf = state.elves[right];

					if (leftElf.nextX == rightElf.nextX && leftElf.nextY == rightElf.nextY)
					{
						leftElf.nextX = leftElf.x;
						leftElf.nextY = leftElf.y;

						rightElf.nextX = rightElf.x;
						rightElf.nextY = rightElf.y;
					}
				}
			}

			for (int e = 0; e < state.elves.size(); ++e)
			{
				moveElf(e, state);
			}

			currDirection++;
			if (currDirection > East)
				currDirection = North;

			//print(state);
		}

		int minX = state.elves[0].x;
		int maxX = state.elves[0].x;
		int minY = state.elves[0].y;
		int maxY = state.elves[0].y;
		for (int e = 1; e < state.elves.size(); ++e)
		{
			Elf& elf = state.elves[e];
			if (elf.x < minX)
				minX = elf.x;
			if (elf.x > maxX)
				maxX = elf.x;
			if (elf.y < minY)
				minY = elf.y;
			if (elf.y > maxY)
				maxY = elf.y;
		}

		//print(state);
		int total = (maxX - minX + 1) * (maxY - minY + 1) - (int)state.elves.size();
		output << total;
	}

	virtual void questionTwo(istream& input, ostream& output)
	{
		State state;
		parse(input, state);

		//print(state);

		int roundCount = 0;
		int currDirection = North;
		bool elfMoved = true;
		while (elfMoved)
		{
			roundCount++;

			for (int e = 0; e < state.elves.size(); ++e)
			{
				tryMoveElf(e, currDirection, state);
			}

			for (int left = 0; left < state.elves.size() - 1; ++left)
			{
				Elf& leftElf = state.elves[left];

				for (int right = left + 1; right < state.elves.size(); ++right)
				{
					Elf& rightElf = state.elves[right];

					if (leftElf.nextX == rightElf.nextX && leftElf.nextY == rightElf.nextY)
					{
						leftElf.nextX = leftElf.x;
						leftElf.nextY = leftElf.y;

						rightElf.nextX = rightElf.x;
						rightElf.nextY = rightElf.y;
					}
				}
			}

			elfMoved = false;
			for (int e = 0; e < state.elves.size(); ++e)
			{
				elfMoved = moveElf(e, state) || elfMoved;
			}

			currDirection++;
			if (currDirection > East)
				currDirection = North;

			//print(state);
		}

		//print(state);
		int total = roundCount;
		output << total;
	}

private:
	const int NUM_ROUNDS = 10;

	enum Direction
	{
		North = 0,
		South,
		West,
		East
	};

	struct Elf
	{
		int x = 0;
		int y = 0;
		int nextX = 0;
		int nextY = 0;
	};

	struct State
	{
		vector<Elf> elves;
		deque<deque<char>> grid;

		int xOffset = 0;
		int yOffset = 0;
	};

	void parse(istream& input, State& state)
	{
		int y = 0;
		string line;
		while (getline(input, line))
		{
			state.grid.emplace_back();

			for (int x = 0; x < line.length(); ++x)
			{
				state.grid.back().emplace_back(line[x]);

				if (line[x] == '#')
				{
					state.elves.emplace_back();
					state.elves.back().x = x;
					state.elves.back().y = y;
				}
			}
			++y;
		}

		expandGrid(NUM_ROUNDS, state);
	}

	void expandGrid(int amount, State& state)
	{
		state.xOffset += amount;
		state.yOffset += amount;

		int currWidth = (int)state.grid[0].size();
		int currHeight = (int)state.grid.size();

		for (int y = 0; y < currHeight; ++y)
		{
			for (int x = 0; x < amount; ++x)
			{
				state.grid[y].emplace_front();
				state.grid[y].front() = '.';

				state.grid[y].emplace_back();
				state.grid[y].back() = '.';
			}
		}

		for (int y = 0; y < amount; ++y)
		{
			state.grid.emplace_front();
			state.grid.front().resize(currWidth + amount * 2, '.');

			state.grid.emplace_back();
			state.grid.back().resize(currWidth + amount * 2, '.');
		}
	}

	void tryMoveElf(int index, int direction, State& state)
	{
		Elf& elf = state.elves[index];

		elf.nextX = elf.x;
		elf.nextY = elf.y;

		bool bIsFree = true;
		for (int y = elf.y - 1; y <= elf.y + 1; ++y)
		{
			for (int x = elf.x - 1; x <= elf.x + 1; ++x)
			{
				if (x != elf.x || y != elf.y)
				{
					bIsFree = bIsFree && isFree(x, y, state);
				}
			}
		}

		if (bIsFree)
			return;

		for (int i = 0; i < 4; ++i)
		{
			int nextDir = (direction + i) % 4;

			switch (nextDir)
			{
			case North:
				if (isFree(elf.x, elf.y - 1, state) && isFree(elf.x - 1, elf.y - 1, state) && isFree(elf.x + 1, elf.y - 1, state))
				{
					elf.nextY = elf.y - 1;
					return;
				}
				break;
			case South:
				if (isFree(elf.x, elf.y + 1, state) && isFree(elf.x - 1, elf.y + 1, state) && isFree(elf.x + 1, elf.y + 1, state))
				{
					elf.nextY = elf.y + 1;
					return;
				}
				break;
			case West:
				if (isFree(elf.x - 1, elf.y, state) && isFree(elf.x - 1, elf.y - 1, state) && isFree(elf.x - 1, elf.y + 1, state))
				{
					elf.nextX = elf.x - 1;
					return;
				}
				break;
			case East:
				if (isFree(elf.x + 1, elf.y, state) && isFree(elf.x + 1, elf.y - 1, state) && isFree(elf.x + 1, elf.y + 1, state))
				{
					elf.nextX = elf.x + 1;
					return;
				}
				break;
			}
		}
	}

	bool isFree(int x, int y, State& state)
	{
		return state.grid[state.yOffset + y][state.xOffset + x] != '#';
	}

	bool moveElf(int index, State& state)
	{
		Elf& elf = state.elves[index];

		if (elf.nextX != elf.x || elf.nextY != elf.y)
		{
			state.grid[state.yOffset + elf.y][state.xOffset + elf.x] = '.';
			state.grid[state.yOffset + elf.nextY][state.xOffset + elf.nextX] = '#';

			elf.x = elf.nextX;
			elf.y = elf.nextY;

			if (elf.x + state.xOffset == 0
				|| elf.x + state.xOffset == state.grid[0].size() - 1
				|| elf.y + state.yOffset == 0
				|| elf.y + state.yOffset == state.grid.size() - 1)
			{
				expandGrid(10, state);
			}

			return true;
		}
		else
		{
			return false;
		}
	}
	
	void print(State& state)
	{
		for(int y = 0; y < state.grid.size(); ++y)
		{
			for (int x = 0; x < state.grid[y].size(); ++x)
			{
				cout << state.grid[y][x];
			}

			cout << endl;
		}

		cout << endl;
	}
};

DayTwentyThree g_dayTwentyThree = DayTwentyThree();
