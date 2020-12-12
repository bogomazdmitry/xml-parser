#pragma once
#include <iostream>
#include <string>
#include <fstream>

#include "IDataFileWithUser.h"

class DataFileWithUserTXT : public IDataFileWithUser
{
	std::string fileName;

public:
	DataFileWithUserTXT();

	virtual bool WriteUser(ModelUser* user);

	virtual ModelUser* GetUser(std::string login);

	virtual bool CheckUser(std::string login, std::string password);

};