#include "Day13.h"

class ListItem
{
public:
    vector<ListItem> elements;

    int value = -1;

    bool isDecoder = false;

    ListItem* parent;

    ListItem(ListItem* aParent) : parent(aParent) {}
};

void parseLine(string line, ListItem& root)
{
    ListItem* currentItem = &root;
    stringstream ss;
    for (int i = 1; i < line.length(); ++i)
    {
        if (line[i] == '[')
        {
            currentItem->elements.emplace_back(currentItem);
            currentItem = &currentItem->elements.back();
        }
        else if (line[i] == ']')
        {
            if (ss.str().length() > 0)
            {
                currentItem->elements.emplace_back(currentItem);
                currentItem->elements.back().value = atoi(ss.str().c_str());

                ss.str("");
            }

            currentItem = currentItem->parent;
        }
        else if (line[i] == ',')
        {
            if (ss.str().length() > 0)
            {
                currentItem->elements.emplace_back(currentItem);
                currentItem->elements.back().value = atoi(ss.str().c_str());

                ss.str("");
            }
        }
        else
        {
            ss << line[i];
        }
    }
}

enum VALUE
{
    TRUE,
    FALSE,
    UNSURE
};

static VALUE compare(const ListItem& left, const ListItem& right)
{
    if (left.value != -1 && right.value != -1)
    {
        if (left.value < right.value)
        {
            return TRUE;
        }
        else if (left.value == right.value)
        {
            return UNSURE;
        }
        else
        {
            return FALSE;
        }

    }
    else if (left.value != -1)
    {
        if (right.elements.size() == 0)
        {
            return FALSE;
        }

        VALUE ret = compare(left, right.elements[0]);

        if (ret != UNSURE)
        {
            return ret;
        }

        if (right.elements.size() > 1)
        {
            return TRUE;
        }

        return UNSURE;
    }
    else if (right.value != -1)
    {
        if (left.elements.size() == 0)
        {
            return TRUE;
        }

        VALUE ret = compare(left.elements[0], right);

        if (ret != UNSURE)
        {
            return ret;
        }

        if (left.elements.size() > 1)
        {
            return FALSE;
        }

        return UNSURE;
    }

    for (int i = 0; i < left.elements.size(); ++i)
    {
        if (right.elements.size() <= i)
        {
            return FALSE;
        }

        VALUE ret = compare(left.elements[i], right.elements[i]);

        if (ret != UNSURE)
        {
            return ret;
        }
    }

    if (left.elements.size() == right.elements.size())
    {
        return UNSURE;
    }

    return TRUE;
}

static bool vectorCompare(const ListItem& left, const ListItem& right)
{
    return compare(left, right) != FALSE;
}

void DayThirteen::questionOne(istream& input, ostream& output)
{
    string line1;
    string line2;

    int current = 1;
    int total = 0;

    while (getline(input, line1) && getline(input, line2))
    {

        ListItem line1Item(nullptr);
        ListItem line2Item(nullptr);

        parseLine(line1, line1Item);
        parseLine(line2, line2Item);

        VALUE ret = compare(line1Item, line2Item);

        if (ret == TRUE || ret == UNSURE)
        {
            total += current;
        }

        string skip;
        getline(input, skip);

        current++;
    }

    output << total;
}

void DayThirteen::questionTwo(istream& input, ostream& output)
{
    string line1;
    string line2;

    vector<ListItem> items;

    items.emplace_back(nullptr);
    ListItem& item2 = items.back();
    item2.isDecoder = true;
    item2.elements.emplace_back(item2);
    item2.elements[0].elements.emplace_back(item2.elements[0]);
    item2.elements[0].elements[0].value = 2;

    items.emplace_back(nullptr);
    ListItem& item6 = items.back();
    item6.isDecoder = true;
    item6.elements.emplace_back(item6);
    item6.elements[0].elements.emplace_back(item6.elements[0]);
    item6.elements[0].elements[0].value = 6;

    while (getline(input, line1) && getline(input, line2))
    {
        items.emplace_back(nullptr);
        ListItem& line1Item = items.back();
        parseLine(line1, line1Item);

        items.emplace_back(nullptr);
        ListItem& line2Item = items.back();
        parseLine(line2, line2Item);

        string skip;
        getline(input, skip);
    }

    sort(items.begin(), items.end(), vectorCompare);

    int total = 1;

    for (int i = 0; i < items.size(); ++i)
    {
        if (items[i].isDecoder)
        {
            total *= i + 1;
        }
    }

    output << total;
}