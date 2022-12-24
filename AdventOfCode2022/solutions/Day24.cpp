#include <Helpers.h>
#include <DayBase.h>

/**
* DayTwentyFour
*
* This is a the solution for Day TwentyFour of Advent of Code 2022.
* https://adventofcode.com/2022/day/24
*
*/
class DayTwentyFour : public DayBase
{
public:
	DayTwentyFour()
		: DayBase(24)
	{}

protected:
	virtual void questionOne(istream& input, ostream& output)
	{
		State state;
		parse(input, state);

		PlayerState start;
		for (int x = 0; x < state.grid[0].size(); ++x)
		{
			if (state.grid[0][x] == '.')
			{
				start.x = x;
				break;
			}
		}

		generateGridPermutations(state);

		int totalTurns = 0;
	
		set<PlayerState, decltype(&cmpPlayerState)> playerQueue(cmpPlayerState);
		playerQueue.insert(start);

		while (!playerQueue.empty())
		{
			const PlayerState currentState = *playerQueue.begin();
			playerQueue.erase(playerQueue.begin());
			int nextTurn = currentState.time + 1;
			Grid& currGrid = state.permutations[(nextTurn - 1) % state.permutations.size()];

			if (currentState.y == currGrid.size() - 1)
			{
				totalTurns = currentState.time;
				break;
			}


			if (currGrid[currentState.y][currentState.x + 1] == '.')
			{
				PlayerState nextState;
				nextState.x = currentState.x + 1;
				nextState.y = currentState.y;
				nextState.time = nextTurn;

				playerQueue.insert(nextState);
			}

			if (currGrid[currentState.y][currentState.x - 1] == '.')
			{
				PlayerState nextState;
				nextState.x = currentState.x - 1;
				nextState.y = currentState.y;
				nextState.time = nextTurn;

				playerQueue.insert(nextState);
			}

			if (currGrid[currentState.y + 1][currentState.x] == '.')
			{
				PlayerState nextState;
				nextState.x = currentState.x;
				nextState.y = currentState.y + 1;
				nextState.time = nextTurn;

				playerQueue.insert(nextState);
			}

			if (currentState.y > 0 && currGrid[currentState.y - 1][currentState.x] == '.')
			{
				PlayerState nextState;
				nextState.x = currentState.x;
				nextState.y = currentState.y - 1;
				nextState.time = nextTurn;

				playerQueue.insert(nextState);
			}

			if (currGrid[currentState.y][currentState.x] == '.')
			{
				PlayerState nextState;
				nextState.x = currentState.x;
				nextState.y = currentState.y;
				nextState.time = nextTurn;

				playerQueue.insert(nextState);
			}
		}

		output << totalTurns;
	}

	virtual void questionTwo(istream& input, ostream& output)
	{
		State state;
		parse(input, state);

		PlayerState start;
		for (int x = 0; x < state.grid[0].size(); ++x)
		{
			if (state.grid[0][x] == '.')
			{
				start.x = x;
				break;
			}
		}

		generateGridPermutations(state);

		int totalTurns = 0;

		set<PlayerState, decltype(&cmpPlayerState)> playerQueue(cmpPlayerState);
		playerQueue.insert(start);

		PlayerState end;
		while (!playerQueue.empty())
		{
			const PlayerState currentState = *playerQueue.begin();
			playerQueue.erase(playerQueue.begin());
			int nextTurn = currentState.time + 1;
			Grid& currGrid = state.permutations[(nextTurn - 1) % state.permutations.size()];

			if (currentState.y == currGrid.size() - 1)
			{
				end = currentState;
				totalTurns += currentState.time;
				break;
			}

			if (currGrid[currentState.y][currentState.x + 1] == '.')
			{
				PlayerState nextState;
				nextState.x = currentState.x + 1;
				nextState.y = currentState.y;
				nextState.time = nextTurn;

				playerQueue.insert(nextState);
			}

			if (currGrid[currentState.y][currentState.x - 1] == '.')
			{
				PlayerState nextState;
				nextState.x = currentState.x - 1;
				nextState.y = currentState.y;
				nextState.time = nextTurn;

				playerQueue.insert(nextState);
			}

			if (currGrid[currentState.y + 1][currentState.x] == '.')
			{
				PlayerState nextState;
				nextState.x = currentState.x;
				nextState.y = currentState.y + 1;
				nextState.time = nextTurn;

				playerQueue.insert(nextState);
			}

			if (currentState.y > 0 && currGrid[currentState.y - 1][currentState.x] == '.')
			{
				PlayerState nextState;
				nextState.x = currentState.x;
				nextState.y = currentState.y - 1;
				nextState.time = nextTurn;

				playerQueue.insert(nextState);
			}

			if (currGrid[currentState.y][currentState.x] == '.')
			{
				PlayerState nextState;
				nextState.x = currentState.x;
				nextState.y = currentState.y;
				nextState.time = nextTurn;

				playerQueue.insert(nextState);
			}
		}

		set<PlayerState, decltype(&cmpPlayerStateInv)> playerQueueInv(cmpPlayerState);
		playerQueueInv.insert(end);

		while (!playerQueueInv.empty())
		{
			const PlayerState currentState = *playerQueueInv.begin();
			playerQueueInv.erase(playerQueueInv.begin());
			int nextTurn = currentState.time + 1;
			Grid& currGrid = state.permutations[(nextTurn - 1) % state.permutations.size()];

			if (currentState.y == 0)
			{
				start = currentState;
				totalTurns += currentState.time;
				break;
			}

			if (currGrid[currentState.y][currentState.x + 1] == '.')
			{
				PlayerState nextState;
				nextState.x = currentState.x + 1;
				nextState.y = currentState.y;
				nextState.time = nextTurn;

				playerQueueInv.insert(nextState);
			}

			if (currGrid[currentState.y][currentState.x - 1] == '.')
			{
				PlayerState nextState;
				nextState.x = currentState.x - 1;
				nextState.y = currentState.y;
				nextState.time = nextTurn;

				playerQueueInv.insert(nextState);
			}

			if (currentState.y < currGrid.size() - 1 && currGrid[currentState.y + 1][currentState.x] == '.')
			{
				PlayerState nextState;
				nextState.x = currentState.x;
				nextState.y = currentState.y + 1;
				nextState.time = nextTurn;

				playerQueueInv.insert(nextState);
			}

			if (currentState.y > 0 && currGrid[currentState.y - 1][currentState.x] == '.')
			{
				PlayerState nextState;
				nextState.x = currentState.x;
				nextState.y = currentState.y - 1;
				nextState.time = nextTurn;

				playerQueueInv.insert(nextState);
			}

			if (currGrid[currentState.y][currentState.x] == '.')
			{
				PlayerState nextState;
				nextState.x = currentState.x;
				nextState.y = currentState.y;
				nextState.time = nextTurn;

				playerQueueInv.insert(nextState);
			}
		}

		playerQueue.clear();
		playerQueue.insert(start);

		while (!playerQueue.empty())
		{
			const PlayerState currentState = *playerQueue.begin();
			playerQueue.erase(playerQueue.begin());
			int nextTurn = currentState.time + 1;
			Grid& currGrid = state.permutations[(nextTurn - 1) % state.permutations.size()];

			if (currentState.y == currGrid.size() - 1)
			{
				totalTurns = currentState.time;
				break;
			}

			if (currGrid[currentState.y][currentState.x + 1] == '.')
			{
				PlayerState nextState;
				nextState.x = currentState.x + 1;
				nextState.y = currentState.y;
				nextState.time = nextTurn;

				playerQueue.insert(nextState);
			}

			if (currGrid[currentState.y][currentState.x - 1] == '.')
			{
				PlayerState nextState;
				nextState.x = currentState.x - 1;
				nextState.y = currentState.y;
				nextState.time = nextTurn;

				playerQueue.insert(nextState);
			}

			if (currGrid[currentState.y + 1][currentState.x] == '.')
			{
				PlayerState nextState;
				nextState.x = currentState.x;
				nextState.y = currentState.y + 1;
				nextState.time = nextTurn;

				playerQueue.insert(nextState);
			}

			if (currentState.y > 0 && currGrid[currentState.y - 1][currentState.x] == '.')
			{
				PlayerState nextState;
				nextState.x = currentState.x;
				nextState.y = currentState.y - 1;
				nextState.time = nextTurn;

				playerQueue.insert(nextState);
			}

			if (currGrid[currentState.y][currentState.x] == '.')
			{
				PlayerState nextState;
				nextState.x = currentState.x;
				nextState.y = currentState.y;
				nextState.time = nextTurn;

				playerQueue.insert(nextState);
			}
		}

		output << totalTurns;
	}

private:
	enum Direction
	{
		Right = 0,
		Down,
		Left,
		Up
	};

	typedef vector<vector<char>> Grid;

	struct Blizzard
	{
		Direction dir;
		int x;
		int y;

		Blizzard(int startX, int startY, Direction startDir) : x(startX), y(startY), dir(startDir) {}
	};

	struct PlayerState
	{
		int x = 0;
		int y = 0;
		int time = 0;
	};

	static bool cmpPlayerState(const PlayerState& left, const PlayerState& right)
	{
		int leftVal = left.x + left.y - left.time;
		int rightVal = right.x + right.y - right.time;

		return leftVal > rightVal || (leftVal == rightVal &&
			(left.time < right.time ||
				(left.time == right.time &&
				((left.x + left.y) > (right.x + right.y)
					|| (left.x > right.x)
					|| ((left.x == right.x) && (left.y > right.y))
				)
			)));
	}

	static bool cmpPlayerStateInv(const PlayerState& left, const PlayerState& right)
	{
		int leftVal = left.x + left.y + left.time;
		int rightVal = right.x + right.y + right.time;

		return leftVal < rightVal || (leftVal == rightVal &&
			(left.time < right.time ||
				(left.time == right.time &&
					((left.x + left.y) < (right.x + right.y)
						|| (left.x < right.x)
						|| ((left.x == right.x) && (left.y < right.y))
						)
					)));
	}

	struct State
	{
		Grid grid;
		vector<Blizzard> blizzards;

		vector<Grid> permutations;
	};
	
	void parse(istream& input, State& state)
	{
		string line;
		int y = 0;
		while (getline(input, line))
		{
			state.grid.emplace_back();

			for (int x = 0; x < line.length(); ++x)
			{
				if (line[x] == '#' || line[x] == '.')
				{
					state.grid.back().emplace_back(line[x]);
				}
				else
				{
					Direction dir = line[x] == '>' ? Right : line[x] == '<' ? Left : line[x] == '^' ? Up : Down;

					state.blizzards.emplace_back(x, y, dir);
					state.grid.back().emplace_back('.');
				}
			}

			++y;
		}
	}

	void generateGridPermutations(State& state)
	{
		int gridWidth = (int)state.grid[0].size();
		int gridHeight = (int)state.grid.size();

		int permutationCount = (gridHeight - 2) * (gridWidth - 2);

		vector<Blizzard> tempBlizz = state.blizzards;

		for (int i = 0; i < permutationCount; ++i)
		{
			state.permutations.emplace_back();
			Grid& currentPerm = state.permutations.back();
			currentPerm = state.grid;

			for (auto blizz = tempBlizz.begin(); blizz != tempBlizz.end(); ++blizz)
			{
				Blizzard& currBliz = *blizz;
				
				switch (currBliz.dir)
				{
				case Right:
				{
					currBliz.x++;
					if (currBliz.x == gridWidth - 1)
						currBliz.x = 1;
				}
					break;
				case Down:
				{
					currBliz.y++;
					if (currBliz.y == gridHeight - 1)
						currBliz.y = 1;
				}
					break;
				case Left:
				{
					currBliz.x--;
					if (currBliz.x == 0)
						currBliz.x = gridWidth - 2;
				}
					break;
				case Up:
				{
					currBliz.y--;
					if (currBliz.y == 0)
						currBliz.y = gridHeight - 2;
				}
					break;
				}

				currentPerm[currBliz.y][currBliz.x] = '*';
			}
		}
	}
};

DayTwentyFour g_dayTwentyFour = DayTwentyFour();
