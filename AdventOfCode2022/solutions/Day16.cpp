#include "Day16.h"

class Valve
{
public:
    string name;
    int pressure;
    int index;

    bool open = false;

    vector<string> pipeNames;
    vector<Valve*> pipes;
};

struct State
{
    vector<Valve> valves;
};

struct Input
{
    Valve* currPlayer = nullptr;
    Valve* currElephant = nullptr;

    int etaPlayer = 0;
    int etaElephant = 0;
};

void getShortestDistances(Valve* start, vector<int>& dist)
{
    vector<bool> visited;
    visited.resize(dist.size(), false);

    dist[start->index] = 0;

    deque<pair<Valve*, int>> toCheck;
    toCheck.push_back(pair<Valve*, int>(start, 0));
    while (!toCheck.empty())
    {
        Valve* valve = toCheck.front().first;
        int nextDepth = toCheck.front().second + 1;

        for (int i = 0; i < valve->pipes.size(); ++i)
        {
            Valve* next = valve->pipes[i];
            if (!visited[next->index])
            {
                visited[next->index] = true;
                dist[next->index] = nextDepth;

                toCheck.push_back(pair<Valve*, int>(next, nextDepth));
            }
        }

        toCheck.pop_front();
    }
}

void parse(istream& input, vector<Valve>& valves)
{
    string line;
    while (getline(input, line))
    {
        valves.emplace_back();

        Valve& currentValve = valves.back();

        vector<string> strings = splitString(line, " ");

        currentValve.name = strings[1];

        currentValve.pressure = atoi(strings[4].substr(5, strings[4].length() - 6).c_str());

        for (int i = 9; i < strings.size(); ++i)
        {
            currentValve.pipeNames.emplace_back(strings[i].substr(0, 2));
        }
    }

    for (int v = 0; v < valves.size(); ++v)
    {
        Valve& currentValve = valves[v];

        for (int i = 0; i < currentValve.pipeNames.size(); ++i)
        {
            for (int oV = 0; oV < valves.size(); ++oV)
            {
                if (oV != v)
                {
                    if (currentValve.pipeNames[i].compare(valves[oV].name) == 0)
                    {
                        currentValve.pipes.push_back(&valves[oV]);
                        break;
                    }
                }
            }
        }
    }
}

int getBestPressure(int turn, Valve* currentValve, State& state)
{
    size_t valveCount = state.valves.size();

    int currIndex = currentValve->index;

    vector<int> dist;
    vector<bool> visited;
    dist.resize(valveCount, INT_MAX);
    visited.resize(valveCount, false);

    dist[currIndex] = 0;

    deque<pair<Valve*, int>> toCheck;
    toCheck.push_back(pair<Valve*, int>(currentValve, 0));
    while (!toCheck.empty())
    {
        Valve* valve = toCheck.front().first;
        int nextDepth = toCheck.front().second + 1;

        for (int i = 0; i < valve->pipes.size(); ++i)
        {
            Valve* next = valve->pipes[i];
            if (!visited[next->index])
            {
                visited[next->index] = true;
                dist[next->index] = nextDepth;

                toCheck.push_back(pair<Valve*, int>(next, nextDepth));
            }
        }

        toCheck.pop_front();
    }

    int bestPressure = 0;

    for (int i = 0; i < valveCount; ++i)
    {
        Valve& toCheck = state.valves[i];
        if (!toCheck.open && toCheck.pressure != 0)
        {
            int nextTurn = turn - dist[i] - 1;

            if (nextTurn <= 0)
                continue;

            toCheck.open = true;

            int newPressure = (nextTurn * toCheck.pressure) + getBestPressure(nextTurn, &toCheck, state);

            if (newPressure > bestPressure)
            {
                bestPressure = newPressure;
            }

            toCheck.open = false;
        }
    }

    return bestPressure;
}

int getBestPressureV2(int turn, State& state, Input& input)
{
    if (turn <= 0)
        return 0;

    size_t valveCount = state.valves.size();

    vector<int> distPlayer;
    vector<int> distElephant;

    if (input.etaPlayer == 0)
    {
        distPlayer.resize(valveCount, INT_MAX);
        getShortestDistances(input.currPlayer, distPlayer);
    }

    if (input.etaElephant == 0)
    {
        distElephant.resize(valveCount, INT_MAX);
        getShortestDistances(input.currElephant, distElephant);
    }

    int bestPressure = 0;

    vector<Valve*> openValves;

    for (int i = 0; i < valveCount; ++i)
    {
        Valve& toCheck = state.valves[i];
        if (!toCheck.open && toCheck.pressure != 0)
        {
            openValves.push_back(&toCheck);
        }
    }

    if (input.etaPlayer == 0 && input.etaElephant == 0)
    {
        for (int p = 0; p < openValves.size(); ++p)
        {
            for (int e = 0; e < openValves.size(); ++e)
            {
                if (p != e)
                {
                    Input newInput(input);

                    int pI = openValves[p]->index;
                    int eI = openValves[e]->index;

                    int playerNextTurn = turn - distPlayer[pI] - 1;
                    int elephantNextTurn = turn - distElephant[eI] - 1;

                    int playerPressure = 0;
                    if (playerNextTurn > 0)
                    {
                        openValves[p]->open = true;
                        playerPressure = playerNextTurn * openValves[p]->pressure;
                        newInput.currPlayer = openValves[p];
                    }
                    else
                    {
                        newInput.etaPlayer = turn;
                    }

                    int elephantPressure = 0;
                    if (elephantNextTurn > 0)
                    {
                        openValves[e]->open = true;
                        elephantPressure = elephantNextTurn * openValves[e]->pressure;
                        newInput.currElephant = openValves[e];
                    }
                    else
                    {
                        newInput.etaElephant = turn;
                    }

                    int nextTurn = playerNextTurn;

                    if (playerNextTurn < elephantNextTurn)
                    {
                        nextTurn = elephantNextTurn;
                        newInput.etaPlayer = elephantNextTurn - playerNextTurn;
                    }
                    else if (playerNextTurn > elephantNextTurn)
                    {
                        newInput.etaElephant = playerNextTurn - elephantNextTurn;
                    }

                    int newPressure = playerPressure + elephantPressure + getBestPressureV2(nextTurn, state, newInput);

                    if (newPressure > bestPressure)
                    {
                        bestPressure = newPressure;
                    }

                    if (elephantNextTurn > 0)
                    {
                        openValves[e]->open = false;
                    }

                    if (playerNextTurn > 0)
                    {
                        openValves[p]->open = false;
                    }
                }
            }
        }
    }
    else if (input.etaPlayer == 0)
    {
        for (int v = 0; v < openValves.size(); ++v)
        {
            Input newInput(input);
            Valve* curr = openValves[v];

            int nextTurn = turn - distPlayer[curr->index] - 1;
            int pressure = nextTurn * curr->pressure;

            curr->open = true;
            newInput.currPlayer = curr;

            if (input.etaElephant < (turn - nextTurn))
            {
                newInput.etaPlayer = turn - newInput.etaElephant - nextTurn;

                nextTurn = turn - newInput.etaElephant;
                newInput.etaElephant = 0;
            }
            else
            {
                newInput.etaPlayer = 0;
                newInput.etaElephant -= (turn - nextTurn);
            }

            int newPressure = pressure + getBestPressureV2(nextTurn, state, newInput);

            if (newPressure > bestPressure)
            {
                bestPressure = newPressure;
            }

            curr->open = false;
        }
    }
    else // state.etaElephant == 0
    {
        for (int v = 0; v < openValves.size(); ++v)
        {
            Input newInput(input);
            Valve* curr = openValves[v];
            int nextTurn = turn - distElephant[curr->index] - 1;
            int pressure = nextTurn * curr->pressure;

            curr->open = true;
            newInput.currElephant = curr;

            if (newInput.etaPlayer < (turn - nextTurn))
            {
                newInput.etaElephant = turn - newInput.etaPlayer - nextTurn;

                nextTurn = turn - newInput.etaPlayer;
                newInput.etaPlayer = 0;
            }
            else
            {
                newInput.etaElephant = 0;
                newInput.etaPlayer -= (turn - nextTurn);
            }

            int newPressure = pressure + getBestPressureV2(nextTurn, state, newInput);

            if (newPressure > bestPressure)
            {
                bestPressure = newPressure;
            }

            curr->open = false;
        }
    }

    return bestPressure;
}

void DaySixteen::questionOne(istream& input, ostream& output)
{
    State state;
    vector<Valve>& valves = state.valves;
    parse(input, valves);

    size_t valveCount = valves.size();

    Valve* currentValve = nullptr;
    for (int i = 0; i < valveCount; ++i)
    {
        if (valves[i].name.compare("AA") == 0)
        {
            currentValve = &valves[i];
        }

        valves[i].index = i;
    }

    int total = getBestPressure(30, currentValve, state);

    output << total;
}

void DaySixteen::questionTwo(istream& input, ostream& output)
{
    State state;
    vector<Valve>& valves = state.valves;
    parse(input, valves);

    size_t valveCount = valves.size();

    Valve* currentValve = nullptr;
    for (int i = 0; i < valveCount; ++i)
    {
        if (valves[i].name.compare("AA") == 0)
        {
            currentValve = &valves[i];
        }

        valves[i].index = i;
    }

    Input funcInput;

    funcInput.currPlayer = currentValve;
    funcInput.currElephant = currentValve;

    int total = getBestPressureV2(26, state, funcInput);

    output << total;
}
