#include "Command.h"

Command::Command() :
    userController(new UserController(new DataFileWithUserTXT())),
    messageController(new MessageController(DataFileMessageXML::getInstance())){}
    // messageController(new MessageController( new DataFileWithUserTXT() )){}

void Command::simpleCommand(ModelUser*& user, const std::string& command)
{
    size_t startCommand = 0;
    auto k = Utils::get_firstWord(command, startCommand);
    if (k == "send")
    {
        auto recipient = Utils::get_firstWord(command, startCommand);
        auto text_message = command.substr(startCommand);
        if (messageController->sendMessage(user, recipient, text_message))
        {
            answer = "Send successfull";
        }
        else
        {
            answer = "Send unsuccessfull";
        }
        return;
    }

    if (k == "delete")
    {
        auto start = 1;
        auto end = -1;
        bool success = false;
        auto startStr = Utils::get_firstWord(command, startCommand);
        try
        {
            start = std::stoi(startStr);
            if (start <= 0)
            {
                throw std::invalid_argument("No zero");
            }
        }
        catch (const std::invalid_argument& e)
        {
            start = 1;
        }

        try
        {
            end = std::stoi(Utils::get_firstWord(command, startCommand));
        }
        catch (const std::invalid_argument& e)
        {
            end = -1;
        }

        success = messageController->deleteMessage(user, start, end);
        if (success)
        {
            answer = "Delete successfull";
        }
        else
        {
            answer = "Delete unsuccessfull";
        }
        return;
    }

    if (k == "show")
    {
        answer = messageController->showMessage(user);
        if (answer.empty())
        {
            answer = "You don't have any text_message";
        }
        return;
    }

    if (k == "logout")
    {
        delete user;
        user = NULL;
        answer = "You are logout";
        return;
    }

    answer = "Error with command";
}

std::string Command::get_answer()
{
    return answer;
}

ModelUser* Command::loginCommand(const std::string& command)
{
    size_t startCommand = 0;
    auto k = Utils::get_firstWord(command, startCommand);
    auto login = Utils::get_firstWord(command, startCommand);
    auto password = Utils::get_firstWord(command, startCommand);
    if (k == "login")
    {
        ModelUser* user = userController->Login(login, password);
        if (user != NULL)
        {
            answer = "Successfull login";
            return user;
        }
        else
        {
            answer = "Error with login or password";
            return NULL;
        }
    }
    if (k == "register")
    {
        auto user = userController->Registr(login, password);
        if (user != NULL)
        {
            answer = "Successfull register";
            return user;
        }
        else
        {
            answer = "User with this login already exists";
            return NULL;
        }
    }

    answer = "Error with command";
    return NULL;
}

Command::~Command()
{
    delete userController;
    delete messageController;
}
