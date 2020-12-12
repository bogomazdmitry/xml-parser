#include "DataFileMessageTXT.h"

DataFileMessageTXT::DataFileMessageTXT() :
	fileName("text_message.txt")
{
}

std::string DataFileMessageTXT::get_message(const std::string& login) const
{
	std::string result = "";
	std::ifstream file(fileName);
	std::string str;
	std::string str_prev;
	size_t i = 0;
	while (std::getline(file, str))
	{
		if (i % 3 == 1 && str == login)
		{
			result += str_prev + " -> " + str + "\n";
			++i;
			std::getline(file, str);
			result += str + "\n\n";
		}
		++i;
		str_prev = std::move(str);
	}
	file.close();
	return result;
}

bool DataFileMessageTXT::sendMessage(const std::string& login, const std::string& loginEnd, const std::string& text_message)
{
	std::ofstream file(fileName, std::ios::app);
	file << login << std::endl << loginEnd << std::endl << text_message << std::endl;
	file.close();
	return true;
}

bool DataFileMessageTXT::deleteMessage(const std::string& login, int begin, int end)
{
	std::ifstream file(fileName);
	std::string result = "";
	std::string str;
	std::string str_prev = "";
	size_t i = 1;
	size_t count = 0;
	std::getline(file, str_prev);
	while (std::getline(file, str))
	{
		if (i % 3 == 1 && str == login && (begin <= end || end < 0))
		{
			++count;
			if (count >= begin && (count <= end || end < 0))
			{
				++begin;
				std::getline(file, str);
				str = "";
				std::getline(file, str_prev);
				i += 3;
				continue;
			}
		}
		result += str_prev + "\n";
		str_prev = std::move(str);
		++i;
	}
	result += str_prev + "\n";
	file.close();
	std::ofstream fileO(fileName);
	fileO << result;
	fileO.close();
	return false;
}
