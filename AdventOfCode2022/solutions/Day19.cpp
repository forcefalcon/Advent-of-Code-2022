#include <Helpers.h>
#include <DayBase.h>

/**
* DayNineteen
*
* This is a the solution for Day Nineteen of Advent of Code 2022.
* https://adventofcode.com/2022/day/19
*
*/
class DayNineteen : public DayBase
{
public:
	DayNineteen()
		: DayBase(19)
	{}

protected:
	virtual void questionOne(istream& input, ostream& output)
	{
		parse(input);

		int total = 0;
		for (int i = 0; i < blueprints.size(); ++i)
		{
			State state;
			state.currentBlueprint = i;
			state = calculateGeodes(24, 0, state);

			total += state.resources[Geode] * (i+1);
		}

		output << total;
	}

	virtual void questionTwo(istream& input, ostream& output)
	{
		parse(input);

		long long total = 1;
		for (int i = 0; i < min(3, (int)blueprints.size()); ++i)
		{
			State state;
			state.currentBlueprint = i;
			state = calculateGeodes(32, 0, state);

			total *= state.resources[Geode];
		}

		output << total;
	}

private:
	enum ResourceType
	{
		Ore = 0,
		Clay,
		Obsidian,
		Geode,

		NumTypes = 4
	};

	struct RobotCost
	{
		int resource[NumTypes-1] = { 0,0,0 };
	};

	struct Blueprint
	{
		RobotCost costs[NumTypes];
	};

	vector<Blueprint> blueprints;

	struct State
	{
		int currentBlueprint = 0;
		int robots[NumTypes] = { 1,0,0,0 };
		int resources[NumTypes] = { 0,0,0,0 };

		//vector<pair<int, int>> purchases;
	};

	void parse(istream& input)
	{
		if (!blueprints.empty())
			blueprints.clear();

		string line;
		while (getline(input, line))
		{
			Blueprint& current = blueprints.emplace_back();
			
			vector<string> words = splitString(line, " ");

			current.costs[Ore].resource[Ore] = atoi(words[6].c_str());

			current.costs[Clay].resource[Ore] = atoi(words[12].c_str());

			current.costs[Obsidian].resource[Ore] = atoi(words[18].c_str());
			current.costs[Obsidian].resource[Clay] = atoi(words[21].c_str());

			current.costs[Geode].resource[Ore] = atoi(words[27].c_str());
			current.costs[Geode].resource[Obsidian] = atoi(words[30].c_str());
		}
	}

	State calculateGeodes(int turn, int currentBest, State& state)
	{
		State bestState(state);

		if (turn == 0)
			return bestState;

		{
			int possibleBest = state.resources[Geode] + state.robots[Geode] * turn;
			int futureTurns = turn-1;

			if (state.robots[Clay] == 0)
				futureTurns--;
			if (state.robots[Obsidian] == 0)
				futureTurns--;

			for (int i = futureTurns; i > 0; --i)
			{
				possibleBest += i;
			}
			if (possibleBest <= currentBest)
				return bestState;
		}

		bool canPurchase = false;
		for (int i = NumTypes - 1; i >= 0; --i)
		{
			int turns = turnsToPurchase((ResourceType)i, state);

			//if (i == 2 && turn == 14)
			//{
			//	cout << "HERE";
			//}

			if (turns > 0 && turn - turns > 0)
			{
				canPurchase = true;

				State newState(state);

				gatherResources(turns, newState);

				purchaseRobot((ResourceType)i, newState);

				//newState.purchases.emplace_back(24 - (turn - turns), i);

				newState = calculateGeodes(turn - turns, currentBest, newState);

				if (newState.resources[Geode] > bestState.resources[Geode])
				{
					bestState = newState;
					currentBest = bestState.resources[Geode];
				}
			}
		}

		// Gather Resources until the End
		if (!canPurchase)
		{
			State newState(state);
			gatherResources(turn, newState);

			if (newState.resources[Geode] > bestState.resources[Geode])
			{
				bestState = newState;
			}
		}

		return bestState;
	}

	void gatherResources(int numTurns, State& state)
	{
		for (int i = 0; i < NumTypes; ++i)
		{
			state.resources[i] += state.robots[i] * numTurns;
		}
	}

	bool canAfford(ResourceType type, const State& state)
	{
		for (int i = 0; i < NumTypes-1; ++i)
		{
			if (state.resources[i] < blueprints[state.currentBlueprint].costs[type].resource[i])
			{
				return false;
			}
		}

		return true;
	}

	int turnsToPurchase(ResourceType type, const State& state)
	{
		int maxTurns = 0;

		for (int i = 0; i < NumTypes - 1; ++i)
		{
			int cost = blueprints[state.currentBlueprint].costs[type].resource[i];
			
			if (cost > 0)
			{
				if (state.robots[i] == 0)
					return -1;

				cost = max(0, cost - state.resources[i]);

				int turns = cost / state.robots[i];
				if (cost % state.robots[i])
					turns++;

				if (turns > maxTurns)
					maxTurns = turns;
			}
		}

		return maxTurns + 1;
	}

	void purchaseRobot(ResourceType type, State& state)
	{
		for (int i = 0; i < NumTypes - 1; ++i)
		{
			state.resources[i] -= blueprints[state.currentBlueprint].costs[type].resource[i];
		}

		state.robots[type]++;
	}
};

DayNineteen g_dayNineteen = DayNineteen();
