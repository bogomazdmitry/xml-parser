#include "UserController.h"

bool UserController::UserIsReal(std::string log, std::string password)
{
    return true;
}

UserController::UserController(IDataFileWithUser* dbc) :
    dbc(dbc)
{
}

ModelUser* UserController::Registr(const std::string& log, const std::string& password)
{
    auto user = new ModelUser(log, password);
    if (dbc->WriteUser(user))
    {
        return user;
    }
    else
    {
        delete user;
        return NULL;
    }
}

ModelUser* UserController::Login(std::string log, std::string password)
{
    if (dbc->CheckUser(log, password))
    {
        return new ModelUser(log, password);
    }
    else
    {
        return NULL;
    }
}

void UserController::Logout(ModelUser*& user)
{
    delete user;
    user = NULL;
}

UserController::~UserController()
{
}
