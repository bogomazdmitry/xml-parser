#include "ModelMessage.h"

std::string ModelMessage::get_loginAuthor() const
{
    return loginAuthor;
}

std::string ModelMessage::get_loginRecipient() const
{
    return loginRecipient;
}

std::string ModelMessage::get_message() const
{
    return message;
}

void ModelMessage::set_loginAuthor(const std::string& loginAuthor) 
{
    this->loginAuthor = loginAuthor;
}

void ModelMessage::set_loginRecipient(const std::string &loginRecipient) 
{
    this->loginRecipient = loginRecipient;
}

void ModelMessage::set_message(const std::string& message) 
{
    this->message = message;
}

std::string ModelMessage::to_string() const
{
    return loginAuthor + "->" + loginRecipient + "\n" + "message";
}
