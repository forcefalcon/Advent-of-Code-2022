#include <Helpers.h>
#include <DayBase.h>

/**
* DayTwentyTwo
*
* This is a the solution for Day TwentyTwo of Advent of Code 2022.
* https://adventofcode.com/2022/day/22
*
*/
class DayTwentyTwo : public DayBase
{
public:
	DayTwentyTwo()
		: DayBase(22)
	{}

protected:
	virtual void questionOne(istream& input, ostream& output)
	{
		Grid grid;
		ActionList actions;
		parse(input, grid, actions);

		State player;

		for (int i = 0; i < grid[0].size(); ++i)
		{
			if (grid[0][i] == '.')
			{
				player.x = i;
				break;
			}
		}
		for (int a = 0; a < actions.size(); ++a)
		{
			if (actions[a].isTurn)
			{
				turn(actions[a].turnLeft, player);
			}
			else
			{
				move(actions[a].moveCount, grid, player);
			}
		}

		int total = (player.y + 1) * 1000 + (player.x + 1) * 4 + player.facing;
		output << total;
	}

	virtual void questionTwo(istream& input, ostream& output)
	{
		Grid grid;
		ActionList actions;
		FaceList faces;
		parse(input, grid, actions);

		findFaces(grid, faces);

		printFaces(grid, faces);

		State player;

		for (int i = 0; i < grid[0].size(); ++i)
		{
			if (grid[0][i] == '.')
			{
				player.x = i;
				break;
			}
		}
		for (int a = 0; a < actions.size(); ++a)
		{
			if (actions[a].isTurn)
			{
				turn(actions[a].turnLeft, player);
			}
			else
			{
				moveWithFaces(actions[a].moveCount, grid, faces, player);
			}
		}

		int total = (player.y + 1) * 1000 + (player.x + 1) * 4 + player.facing;
		output << total;
	}
private:
	typedef vector<vector<char>> Grid;

	struct Action
	{
		int moveCount = 0;
		bool isTurn = false;
		bool turnLeft = false; // Left = true, Right = false
	};

	typedef vector<Action> ActionList;

	enum Direction : int
	{
		Right = 0,
		Down,
		Left,
		Up
	};

	int getFaceSize() const {
		return isTest() ? 4 : 50;
	}

	int FACE_MAP[6][4] = { {1, 2, 3, 4}, {4, 5, 2, 0}, {1, 5, 3, 0}, {2, 5, 4, 0}, {3, 5, 1, 0}, {1, 4, 3, 2} };

	struct Face
	{
		int top = 0;
		int left = 0;

		int index = 0;
		int offset = 0;
	};
	
	typedef map<int, Face> FaceList;

	struct State
	{
		int x = 0;
		int y = 0;

		int facing = Right;
	};

	void parse(istream& input, Grid& grid, ActionList& actions)
	{
		int maxX = 0;

		string line;
		while (getline(input, line) && !line.empty())
		{
			grid.emplace_back();

			for (int i = 0; i < line.length(); ++i)
			{
				grid.back().emplace_back(line[i]);
			}

			if (line.length() > maxX)
			{
				maxX = (int)line.length();
			}
		}

		for (int i = 0; i < grid.size(); ++i)
		{
			grid[i].resize(maxX, ' ');
		}

		getline(input, line);

		int lastI = 0;
		int i = 0;
		while (i < line.length())
		{
			if (i < lastI)
			{
				cout << "FAIL";
			}

			lastI = i;

			int nextL = (int)line.find("L", i);
			int nextR = (int)line.find("R", i);

			if (nextL == -1 && nextR == -1)
			{
				actions.emplace_back();
				actions.back().moveCount = atoi(line.substr(i).c_str());

				i = (int)line.length();
			}
			else if (nextR == -1 || (nextL != -1 && nextL < nextR))
			{
				actions.emplace_back();
				actions.back().moveCount = atoi(line.substr(i, nextL).c_str());

				actions.emplace_back();
				actions.back().isTurn = true;
				actions.back().turnLeft = true;

				i = nextL + 1;
			}
			else
			{
				actions.emplace_back();
				actions.back().moveCount = atoi(line.substr(i, nextR).c_str());

				actions.emplace_back();
				actions.back().isTurn = true;
				actions.back().turnLeft = false;

				i = nextR + 1;
			}
		}
	}

	void findFaces(const Grid& grid, FaceList& faces)
	{
		int left = 0;

		while (grid[0][left] == ' ')
			left += getFaceSize();

		Face* currentFace = &faces[0];
		currentFace->left = left;

		deque<Face*> faceQueue;
		faceQueue.push_back(currentFace);
		
		while (!faceQueue.empty())
		{
			currentFace = faceQueue.front();

			for (int i = 0; i < 4; ++i)
			{
				int testFace = FACE_MAP[currentFace->index][i];
				// Does Face Exist already?
				if (faces.find(testFace) == faces.end())
				{
					// Check direction
					int dir = (i + currentFace->offset) % 4;

					int testLeft = currentFace->left;
					int testTop = currentFace->top;

					switch (dir)
					{
					case Right:
						testLeft += getFaceSize();
						break;
					case Down:
						testTop += getFaceSize();
						break;
					case Left:
						testLeft -= getFaceSize();
						break;
					case Up:
						testTop -= getFaceSize();
						break;
					default:
						cerr << "Wrong Direction!" << endl;
						break;
					}

					if (testTop >= 0 && testTop < grid.size()
						&& testLeft >= 0 && testLeft < grid[testTop].size()
						&& grid[testTop][testLeft] != ' ')
					{
						Face& newFace = faces[testFace];
						newFace.index = testFace;
						newFace.left = testLeft;
						newFace.top = testTop;

						int toLast = 0;
						for (int f = 0; f < 4; ++f)
						{
							if (FACE_MAP[testFace][f] == currentFace->index)
							{
								toLast = f;
								break;
							}
						}

						newFace.offset = ((dir + 2) % 4 - toLast) % 4;
						if (newFace.offset < 0)
							newFace.offset += 4;

						faceQueue.push_back(&newFace);
					}
				}
			}

			faceQueue.pop_front();
		}
	}

	void turn(bool turnLeft, State& player)
	{
		if (turnLeft)
		{
			player.facing--;
			if (player.facing < Right)
				player.facing = Up;
		}
		else
		{
			player.facing++;
			if (player.facing > Up)
				player.facing = Right;
		}
	}

	void move(int moveAmount, const Grid& grid, State& player)
	{
		int xMove = player.facing == Right ? 1 : (player.facing == Left ? -1 : 0);
		int yMove = player.facing == Down ? 1 : (player.facing == Up ? -1 : 0);

		for (int m = 0; m < moveAmount; ++m)
		{
			int newX = player.x + xMove;
			int newY = player.y + yMove;

			if (newX >= (int)grid[player.y].size())
			{
				newX = 0;
			}
			else if (newX < 0)
			{
				newX = (int)grid[player.y].size() - 1;
			}

			if (newY >= (int)grid.size())
			{
				newY = 0;
			}
			else if (newY < 0)
			{
				newY = (int)grid.size() - 1;
			}

			char atPos = grid[newY][newX];

			if (atPos == '#')
			{
				return;
			}
			else if (atPos == '.')
			{
				player.x = newX;
				player.y = newY;
			}
			else // Wrap around
			{
				if (xMove > 0)
				{
					for (int i = 0; i < (int)grid[newY].size(); ++i)
					{
						if (grid[newY][i] == '#')
						{
							return;
						}
						else if (grid[newY][i] == '.')
						{
							player.x = i;
							player.y = newY;
							break;
						}
					}
				}
				else if (xMove < 0)
				{
					for (int i = (int)grid[newY].size()-1; i >= 0; --i)
					{
						if (grid[newY][i] == '#')
						{
							return;
						}
						else if (grid[newY][i] == '.')
						{
							player.x = i;
							player.y = newY;
							break;
						}
					}
				}
				else if (yMove > 0)
				{
					for (int i = 0; i < (int)grid.size(); ++i)
					{
						if (grid[i][newX] == '#')
						{
							return;
						}
						else if (grid[i][newX] == '.')
						{
							player.x = newX;
							player.y = i;
							break;
						}
					}
				}
				else if (yMove < 0)
				{
					for (int i = (int)grid.size() - 1; i >= 0; --i)
					{
						if (grid[i][newX] == '#')
						{
							return;
						}
						else if (grid[i][newX] == '.')
						{
							player.x = newX;
							player.y = i;
							break;
						}
					}
				}
			}
		}
	}

	void moveWithFaces(int moveAmount, const Grid& grid, const FaceList& faces, State& player)
	{
		for (int m = 0; m < moveAmount; ++m)
		{
			int xMove = player.facing == Right ? 1 : (player.facing == Left ? -1 : 0);
			int yMove = player.facing == Down ? 1 : (player.facing == Up ? -1 : 0);
			int newX = player.x + xMove;
			int newY = player.y + yMove;

			if (newX >= (int)grid[player.y].size()
				|| (newX < 0)
				|| (newY >= (int)grid.size())
				|| (newY < 0))
			{
				findConnectingPoint(xMove, yMove, grid, faces, player);
				continue;
			}

			char atPos = grid[newY][newX];

			if (atPos == '#')
			{
				return;
			}
			else if (atPos == '.')
			{
				player.x = newX;
				player.y = newY;
			}
			else // Wrap around
			{
				findConnectingPoint(xMove, yMove, grid, faces, player);
			}
		}
	}

	void findConnectingPoint(int xMove, int yMove, const Grid& grid, const FaceList& faces, State& player)
	{
		int newX = player.x;
		int newY = player.y;
		int newFacing = player.facing;

		for (auto faceIt = faces.begin(); faceIt != faces.end(); ++faceIt)
		{
			const Face& face = (*faceIt).second;

			if (player.x >= face.left && player.x < face.left + getFaceSize()
				&& player.y >= face.top && player.y < face.top + getFaceSize())
			{
				int startDir = xMove > 0 ? Right : xMove < 0 ? Left : yMove > 0 ? Down : Up;
				int nextFaceIndex = FACE_MAP[face.index][(startDir - face.offset + 4) % 4];

				const Face& nextFace = faces.at(nextFaceIndex);

				int endDir = 0;

				for (int i = 0; i < 4; ++i)
				{
					if (FACE_MAP[nextFaceIndex][i] == face.index)
					{
						endDir = (i + nextFace.offset) % 4;
						break;
					}
				}

				int relX = player.x - face.left;
				int relY = player.y - face.top;

				switch (startDir)
				{
				case Right:
					switch (endDir)
					{
					case Right:
					{
						newFacing = (player.facing + 2) % 4;
						relY = getFaceSize() - relY - 1;
					}
						break;
					case Down:
					{
						newFacing = (player.facing - 1) % 4;
						int tempX = relX;
						relX = relY;
						relY = tempX;
					}
						break;
					case Left:
					{
						relX = getFaceSize() - relX - 1;
					}
						break;
					case Up:
					{
						newFacing = (player.facing + 1) % 4;
						int tempX = relX;
						relX = getFaceSize() - relY - 1;
						relY = getFaceSize() - tempX - 1;
					}
						break;
					}
					break;
				case Down:
					switch (endDir)
					{
					case Right:
					{
						newFacing = (player.facing + 1) % 4;
						int tempX = relX;
						relX = relY;
						relY = tempX;
					}
						break;
					case Down:
					{
						newFacing = (player.facing + 2) % 4;
						relX = getFaceSize() - relX - 1;
					}
						break;
					case Left:
					{
						newFacing = (player.facing - 1) % 4;
						int tempX = relX;
						relX = getFaceSize() - relY - 1;
						relY = getFaceSize() - tempX - 1;
					}
						break;
					case Up:
					{
						relY = getFaceSize() - relY - 1;
					}
						break;
					}
					break;
				case Left:
					switch (endDir)
					{
					case Right:
					{
						relX = getFaceSize() - relX - 1;
					}
						break;
					case Down:
					{
						newFacing = (player.facing + 1) % 4;
						int tempX = relX;
						relX = getFaceSize() - relY - 1;
						relY = getFaceSize() - tempX - 1;
					}
						break;
					case Left:
					{
						newFacing = (player.facing + 2) % 4;
						relY = getFaceSize() - relY - 1;
					}
						break;
					case Up:
					{
						newFacing = (player.facing - 1) % 4;
						int tempX = relX;
						relX = relY;
						relY = tempX;
					}
						break;
					}
					break;
				case Up:
					switch (endDir)
					{
					case Right:
					{
						newFacing = (player.facing - 1) % 4;
						int tempX = relX;
						relX = getFaceSize() - relY - 1;
						relY = getFaceSize() - tempX - 1;
					}
						break;
					case Down:
					{
						relY = getFaceSize() - relY - 1;
					}
						break;
					case Left:
					{
						newFacing = (player.facing + 1) % 4;
						int tempX = relX;
						relX = relY;
						relY = tempX;
					}
						break;
					case Up:
					{
						newFacing = (player.facing + 2) % 4;
						relX = getFaceSize() - relX - 1;
					}
						break;
					}
					break;
				}

				if (newFacing < 0)
					newFacing += 4;

				newX = relX + nextFace.left;
				newY = relY + nextFace.top;

				cout << "Transition from " << face.index << " to " << nextFace.index << ": " << player.x << ", " << player.y << " -> " << newX << ", " << newY << " Facing: " << player.facing << " -> " << newFacing << endl;

				break;
			}
		}

		if (grid[newY][newX] == '#')
		{
			return;
		}
		else if (grid[newY][newX] == '.')
		{
			player.x = newX;
			player.y = newY;
			player.facing = newFacing;
		}
	}

	void printFaces(const Grid& grid, const FaceList& faces)
	{
		for (int y = 0; y < grid.size(); y += getFaceSize())
		{
			for (int x = 0; x < grid[y].size(); x += getFaceSize())
			{
				bool found = false;
				for (auto f = faces.begin(); f != faces.end(); ++f)
				{
					const Face& face = (*f).second;
					if (face.left == x && face.top == y)
					{
						found = true;
						cout << face.index << "(" << face.offset << ") ";
						break;
					}
				}

				if (!found)
					cout << "     ";
			}

			cout << endl << endl;
		}

		cout << endl;
	}
};

DayTwentyTwo g_dayTwentyTwo = DayTwentyTwo();
