#include "Utils.h"

std::string Utils::get_firstWord(const std::string& command, size_t &start)
{
    if (command.empty() || start >= command.length())
    {
        return std::string("");
    }
    size_t i, j;
    for (j = start; j < command.length() && command[j] == ' '; ++j);
    for (i = j + 1; i < command.length() && command[i] != ' '; ++i);
    std::string temp;
    temp.append(command.substr(j, i - j));
    start = i;
    return temp;
}
