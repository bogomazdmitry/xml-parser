#pragma once
#include <string>
#include <iostream>

#include "ModelUser.h"

class IDataFileWithUser
{
public:
	virtual bool WriteUser(ModelUser* user) = 0;
	virtual ModelUser* GetUser(std::string login) = 0;
	virtual bool CheckUser(std::string login, std::string password) = 0;
};