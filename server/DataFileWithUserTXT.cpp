#include "DataFileWithUserTXT.h"

DataFileWithUserTXT::DataFileWithUserTXT() :
	fileName("user.txt")
{}

bool DataFileWithUserTXT::WriteUser(ModelUser* user)
{
	if (!CheckUser(user->get_login(), user->get_password()))
	{
		std::ofstream file(fileName, std::ios::app);
		file << user->get_login() << std::endl << user->get_password() << std::endl;
		file.close();
		return true;
	}
	else
	{
		return false;
	}
}

ModelUser* DataFileWithUserTXT::GetUser(std::string login)
{
	std::ifstream file(fileName);
	std::string str;
	size_t i = 0;
	while (std::getline(file, str))
	{
		if (i % 2 == 0 && str == login)
		{
			std::getline(file, str);
			file.close();
			return new ModelUser(login, str);
		}
		++i;
	}
	file.close();
	return NULL;
}

bool DataFileWithUserTXT::CheckUser(std::string login, std::string password)
{
	std::ifstream file(fileName);
	std::string str;
	size_t i = 0;
	while (std::getline(file, str))
	{
		if (i % 2 == 0 && str == login)
		{
			std::getline(file, str);
			file.close();
			if (str == password)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		++i;
	}
	file.close();
	return false;
}
