#pragma once
#include <string>
#include <iostream>

#include "ModelMessage.h"

class IDataFileMessage
{
public:
	virtual std::string get_message(const std::string& login) = 0;
	virtual bool sendMessage(const std::string &login, const std::string& loginEnd, const std::string &text_message) = 0;
	virtual bool deleteMessage(const std::string &login, int begin, int end) = 0;
}; 