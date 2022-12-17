#include "Day7.h"

struct File
{
    string name;
    int size;

    File(string aName, int aSize) : name(aName), size(aSize) {}
};

struct Directory
{
    string name;

    Directory* parent = nullptr;

    vector<Directory> directories;
    vector<File> files;

    Directory(string aName, Directory* aParent) : name(aName), parent(aParent) {}

    Directory* getDirectory(string name)
    {
        for (int d = 0; d < directories.size(); ++d)
        {
            Directory* current = &directories[d];
            if (current->name.compare(name) == 0)
            {
                return current;
            }
        }

        return nullptr;
    }

    int getTotalSize()
    {
        int total = 0;
        for (int d = 0; d < directories.size(); ++d)
        {
            total += directories[d].getTotalSize();
        }

        for (int f = 0; f < files.size(); ++f)
        {
            total += files[f].size;
        }

        return total;
    }
};

int traverseDirectories(Directory* current)
{
    int total = 0;
    if (current->getTotalSize() <= 100000)
    {
        total += current->getTotalSize();
    }

    for (int d = 0; d < current->directories.size(); ++d)
    {
        total += traverseDirectories(&current->directories[d]);
    }

    return total;
}

int findSmallest(Directory* current, int smallest, int freeSpace)
{
    int currentSmallest = smallest;
    int currentSize = current->getTotalSize();
    if (currentSize >= freeSpace && currentSize < currentSmallest)
    {
        currentSmallest = currentSize;
    }

    for (int d = 0; d < current->directories.size(); ++d)
    {
        int newSmallest = findSmallest(&current->directories[d], currentSmallest, freeSpace);
        if (newSmallest < currentSmallest)
        {
            currentSmallest = newSmallest;
        }
    }

    return currentSmallest;
}

void DaySeven::questionOne(istream& input, ostream& output)
{
    string line;

    Directory root("root", nullptr);
    Directory* current = &root;
    while (getline(input, line))
    {
        if (line[0] == '$')
        {
            size_t separator = line.find(' ', 2);
            string command = line.substr(2, separator - 2);

            if (command.compare("cd") == 0)
            {
                string argument = line.substr(separator + 1);

                if (argument.compare("/") == 0)
                {
                    current = &root;
                }
                else if (argument.compare("..") == 0)
                {
                    current = current->parent;
                }
                else
                {
                    current = current->getDirectory(argument);
                }
            }
            else //ls
            {
                //Do nothing
            }
        }
        else
        {
            size_t separator = line.find(' ');
            string first = line.substr(0, separator);
            string name = line.substr(separator + 1);

            if (first.compare("dir") == 0)
            {
                current->directories.emplace_back(name, current);
            }
            else
            {
                current->files.emplace_back(name, atoi(first.c_str()));
            }
        }
    }

    int total = traverseDirectories(&root);

    output << total;
}

void DaySeven::questionTwo(istream& input, ostream& output)
{
    string line;

    Directory root("root", nullptr);
    Directory* current = &root;
    while (getline(input, line))
    {
        if (line[0] == '$')
        {
            size_t separator = line.find(' ', 2);
            string command = line.substr(2, separator - 2);

            if (command.compare("cd") == 0)
            {
                string argument = line.substr(separator + 1);

                if (argument.compare("/") == 0)
                {
                    current = &root;
                }
                else if (argument.compare("..") == 0)
                {
                    current = current->parent;
                }
                else
                {
                    current = current->getDirectory(argument);
                }
            }
            else //ls
            {
                //Do nothing
            }
        }
        else
        {
            size_t separator = line.find(' ');
            string first = line.substr(0, separator);
            string name = line.substr(separator + 1);

            if (first.compare("dir") == 0)
            {
                current->directories.emplace_back(name, current);
            }
            else
            {
                current->files.emplace_back(name, atoi(first.c_str()));
            }
        }
    }

    int freeSpace = 70000000 - root.getTotalSize();
    int neededSpace = 30000000 - freeSpace;

    int total = findSmallest(&root, 70000000, neededSpace);

    output << total;
}
