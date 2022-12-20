#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <deque>
#include <map>
#include <set>
#include <chrono>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <list>

using namespace std;

/*
 * Helpers
 */
inline int sign(int x) {
    return (x > 0) - (x < 0);
}

vector<string> splitString(const string& input, const string& delimeter);
