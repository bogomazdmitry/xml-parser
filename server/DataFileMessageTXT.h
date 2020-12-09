#pragma once

#include "IDataFileMessage.h"

#include <fstream>
#include <iostream>

class DataFileMessageTXT : public IDataFileMessage
{
	std::string nameOfFile;
public:
	DataFileMessageTXT();

	virtual std::string get_message(const std::string& login) const;

	virtual bool sendMessage(const std::string& login, const std::string& loginEnd, const std::string& message);

	virtual bool deleteMessage(const std::string& login, int begin, int end);
};