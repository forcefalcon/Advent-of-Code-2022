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
			state.currentBlueprint = &blueprints[i];
			int geodes = calculateGeodes(24, 0, state);

			total += geodes * (i+1);
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
			state.currentBlueprint = &blueprints[i];
			int geodes = calculateGeodes(32, 0, state);

			total *= geodes;
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
		const Blueprint* currentBlueprint = nullptr;
		int robots[NumTypes] = { 1,0,0,0 };
		int resources[NumTypes] = { 0,0,0,0 };
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

	int calculateGeodes(int turn, int currentBest, State& state)
	{
		int bestState = currentBest;

		if (turn == 0)
			return bestState;

		{
			int possibleBest = state.resources[Geode] + state.robots[Geode] * turn;
			int futureTurns = turn-1;

			if (state.robots[Clay] == 0)
				futureTurns--;
			if (state.robots[Obsidian] == 0)
				futureTurns--;

			possibleBest += futureTurns * (futureTurns + 1) / 2;

			if (possibleBest <= currentBest)
				return bestState;
		}

		bool canPurchase = false;
		for (int i = NumTypes - 1; i >= 0; --i)
		{
			int turns = turnsToPurchase((ResourceType)i, state);

			if (turns > 0 && turn - turns > 0)
			{
				canPurchase = true;

				State newState = state;

				gatherResources(turns, newState);

				purchaseRobot((ResourceType)i, newState);

				bestState = calculateGeodes(turn - turns, bestState, newState);
			}
		}

		// Gather Resources until the End
		if (!canPurchase)
		{
			State newState = state;
			gatherResources(turn, newState);

			if (newState.resources[Geode] > bestState)
			{
				bestState = newState.resources[Geode];
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
			if (state.resources[i] < state.currentBlueprint->costs[type].resource[i])
			{
				return false;
			}
		}

		return true;
	}

	int turnsToPurchase(ResourceType type, const State& state)
	{
		int maxTurns = 0;

		switch (type)
		{
		case Ore:
			{
				int cost = state.currentBlueprint->costs[type].resource[Ore];
				maxTurns = (cost + state.robots[Ore] - 1 - state.resources[Ore]) / state.robots[Ore];
			}
			break;
		case Clay:
			{
				int cost = state.currentBlueprint->costs[type].resource[Ore];
				maxTurns = (cost + state.robots[Ore] - 1 - state.resources[Ore]) / state.robots[Ore];
			}
			break;
		case Obsidian:
			{
				if (state.robots[Clay] == 0)
					return -1;

				int cost = state.currentBlueprint->costs[type].resource[Ore];
				int turnsOre = (cost + state.robots[Ore] - 1 - state.resources[Ore]) / state.robots[Ore];

				cost = state.currentBlueprint->costs[type].resource[Clay];
				int turnsClay = (cost + state.robots[Clay] - 1 - state.resources[Clay]) / state.robots[Clay];

				maxTurns = max(turnsOre, turnsClay);
			}
			break;
		case Geode:
			{
				if (state.robots[Obsidian] == 0)
					return -1;

				int cost = state.currentBlueprint->costs[type].resource[Ore];
				int turnsOre = (cost + state.robots[Ore] - 1 - state.resources[Ore]) / state.robots[Ore];

				cost = state.currentBlueprint->costs[type].resource[Obsidian];
				int turnsObsidian = (cost + state.robots[Obsidian] - 1 - state.resources[Obsidian]) / state.robots[Obsidian];

				maxTurns = max(turnsOre, turnsObsidian);
			}
			break;
		}

		return maxTurns + 1;
	}

	void purchaseRobot(ResourceType type, State& state)
	{
		for (int i = 0; i < NumTypes - 1; ++i)
		{
			state.resources[i] -= state.currentBlueprint->costs[type].resource[i];
		}

		state.robots[type]++;
	}
};

DayNineteen g_dayNineteen = DayNineteen();
