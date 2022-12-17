#include "Helpers.h"

vector<string> splitString(const string& input, const string& delimeter)
{
    vector<string> result;
    size_t start = 0;
    size_t end = input.find(delimeter, start);
    size_t delimeterLength = delimeter.length();

    while (end != -1)
    {
        result.push_back(input.substr(start, end - start));
        start = end + delimeterLength;
        end = input.find(delimeter, start);
    }

    result.push_back(input.substr(start));

    return result;
}
