#pragma once
#include <iostream>
#include <string>

class ModelMessage
{
private:
	std::string loginAuthor;
	std::string loginRecipient;
	std::string message;
public:
	ModelMessage(const std::string& loginAuthor, std::string loginRecipient, const std::string& message) :
		loginAuthor(loginAuthor),
		loginRecipient(loginRecipient),
		message(message)
	{}

	std::string get_loginAuthor() const;
	std::string get_loginRecipient() const;
	std::string get_message() const;


	void set_loginAuthor(const std::string& loginAuthor);
	void set_loginRecipient(const std::string& loginRecipient);
	void set_message(const std::string &message);

	std::string to_string() const;
};