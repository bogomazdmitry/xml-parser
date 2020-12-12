#pragma once

#include "IDataFileMessage.h"

#include <fstream>

class DataFileMessageTXT : public IDataFileMessage
{
	std::string fileName;
public:
	DataFileMessageTXT();

	virtual std::string get_message(const std::string& login) const;

	virtual bool sendMessage(const std::string& login, const std::string& loginEnd, const std::string& text_message);

	virtual bool deleteMessage(const std::string& login, int begin, int end);
};