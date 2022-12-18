#include "Day18.h"

struct Cube
{
	int x = 0;
	int y = 0;
	int z = 0;

	int adjacent = 0;

	Cube() {}
	Cube(int x, int y, int z) : x(x), y(y), z(z) {}
};

bool lessThan(const Cube& left, const Cube& right)
{
	return left.x < right.x ||
		(left.x == right.x && left.y < right.y) ||
		(left.x == right.x && left.y == right.y && left.z < right.z);
}

typedef set<Cube, decltype(lessThan)*> CubeSet;

class DayEighteenState
{
public:
	int minX = INT_MAX;
	int maxX = 0;

	int minY = INT_MAX;
	int maxY = 0;

	int minZ = INT_MAX;
	int maxZ = 0;

	CubeSet filled = CubeSet(lessThan);
};

bool isAdjacent(const Cube& left, const Cube& right)
{
	return (left.x == right.x && left.y == right.y && abs(left.z - right.z) == 1)
		|| (left.x == right.x && abs(left.y - right.y) == 1 && left.z == right.z)
		|| (abs(left.x - right.x) == 1 && left.y == right.y && left.z == right.z);
}

void parse(istream& input, vector<Cube>& cubes, DayEighteenState& state)
{
	string line;

	while (getline(input, line))
	{
		Cube& cube = cubes.emplace_back();

		vector<string> coords = splitString(line, ",");
		
		cube.x = atoi(coords[0].c_str());
		cube.y = atoi(coords[1].c_str());
		cube.z = atoi(coords[2].c_str());

		if (cube.x < state.minX)
		{
			state.minX = cube.x;
		}
		if (cube.x > state.maxX)
		{
			state.maxX = cube.x;
		}

		if (cube.y < state.minY)
		{
			state.minY = cube.y;
		}
		if (cube.y > state.maxY)
		{
			state.maxY = cube.y;
		}

		if (cube.z < state.minZ)
		{
			state.minZ = cube.z;
		}
		if (cube.z > state.maxZ)
		{
			state.maxZ = cube.z;
		}
	}
}

void DayEighteen::questionOne(istream& input, ostream& output)
{
	vector<Cube> cubes;
	DayEighteenState state;
	parse(input, cubes, state);

	int totalArea = 0;

	for (int i = 0; i < cubes.size(); ++i)
	{
		Cube& left = cubes[i];

		for (int j = i + 1; j < cubes.size(); ++j)
		{
			Cube& right = cubes[j];

			if (isAdjacent(left, right))
			{
				left.adjacent++;
				right.adjacent++;
			}
		}

		totalArea += 6 - (int)left.adjacent;
	}

	output << totalArea;
}

bool expand(Cube& start, CubeSet& shape, DayEighteenState& state)
{
	bool isExterior = false;

	deque<Cube> toProcess;
	toProcess.push_back(start);

	while (!toProcess.empty())
	{
		Cube current = toProcess.front();
		toProcess.pop_front();

		if (current.x + 1 <= state.maxX)
		{
			Cube next(current.x + 1, current.y, current.z);
			if (state.filled.find(next) == state.filled.end()
				&& shape.find(next) == shape.end())
			{
				shape.insert(next);
				
				toProcess.push_back(next);
			}
		}
		else
		{
			isExterior = true;
		}

		if (current.x - 1 >= state.minX)
		{
			Cube next(current.x - 1, current.y, current.z);
			if (state.filled.find(next) == state.filled.end()
				&& shape.find(next) == shape.end())
			{
				shape.insert(next);

				toProcess.push_back(next);
			}
		}
		else
		{
			isExterior = true;
		}

		if (current.y + 1 <= state.maxY)
		{
			Cube next(current.x, current.y + 1, current.z);
			if (state.filled.find(next) == state.filled.end()
				&& shape.find(next) == shape.end())
			{
				shape.insert(next);

				toProcess.push_back(next);
			}
		}
		else
		{
			isExterior = true;
		}

		if (current.y - 1 >= state.minY)
		{
			Cube next(current.x, current.y - 1, current.z);
			if (state.filled.find(next) == state.filled.end()
				&& shape.find(next) == shape.end())
			{
				shape.insert(next);

				toProcess.push_back(next);
			}
		}
		else
		{
			isExterior = true;
		}

		if (current.z + 1 <= state.maxZ)
		{
			Cube next(current.x, current.y, current.z + 1);
			if (state.filled.find(next) == state.filled.end()
				&& shape.find(next) == shape.end())
			{
				shape.insert(next);

				toProcess.push_back(next);
			}
		}
		else
		{
			isExterior = true;
		}

		if (current.z - 1 >= state.minZ)
		{
			Cube next(current.x, current.y, current.z - 1);
			if (state.filled.find(next) == state.filled.end()
				&& shape.find(next) == shape.end())
			{
				shape.insert(next);

				toProcess.push_back(next);
			}
		}
		else
		{
			isExterior = true;
		}
	}

	return isExterior;
}

void DayEighteen::questionTwo(istream& input, ostream& output)
{
	DayEighteenState state;
	vector<Cube> cubes;
	parse(input, cubes, state);

	int totalArea = 0;

	for (int i = 0; i < cubes.size(); ++i)
	{
		Cube& left = cubes[i];

		for (int j = i + 1; j < cubes.size(); ++j)
		{
			Cube& right = cubes[j];

			if (isAdjacent(left, right))
			{
				left.adjacent++;
				right.adjacent++;
			}
		}

		state.filled.insert(left);
	}

	set<Cube, decltype(lessThan)*> remaining(lessThan);
	for (int x = state.minX; x <= state.maxX; ++x)
	{
		for (int y = state.minY; y <= state.maxY; ++y)
		{
			for (int z = state.minZ; z <= state.maxZ; ++z)
			{
				Cube cube(x, y, z);

				if (state.filled.find(cube) == state.filled.end())
				{
					remaining.insert(cube);
				}
			}
		}
	}

	CubeSet interior(lessThan);
	CubeSet exterior(lessThan);
	while (!remaining.empty())
	{
		CubeSet shape(lessThan);
		Cube start = *remaining.begin();
		shape.insert(start);

		bool isExterior = expand(start, shape, state);

		for (auto i = shape.begin(); i != shape.end(); ++i)
		{
			remaining.erase(*i);

			if (isExterior)
			{
				exterior.insert(*i);
			}
			else
			{
				interior.insert(*i);
			}
		}
	}

	for (int i = 0; i < cubes.size(); ++i)
	{
		Cube& left = cubes[i];

		for (auto j = interior.begin(); j != interior.end(); ++j)
		{
			if (isAdjacent(left, *j))
			{
				left.adjacent++;
			}
		}

		totalArea += 6 - (int)left.adjacent;
	}

	output << totalArea;
}
