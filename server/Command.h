#pragma once

#include "MessageController.h"
#include "UserController.h"
#include "Utils.h"
#include "DataFileWithUserTXT.h"
#include "DataFileMessageTXT.h"

#include <iostream>
#include <string>

class Command
{
private:
    std::string answer;
    UserController* userController;
    MessageController* messageController;
public:
    Command();

    void simpleCommand(ModelUser*& user, const std::string& command);

    std::string get_answer();

    ModelUser* loginCommand(const std::string& command);

    ~Command();
};
