#pragma once
#include "Controller.h"
#include "ModelUser.h"
#include "IDataFileWithUser.h"

#include <iostream>
#include <fstream>
#include <string>

class UserController
{
private:
    bool UserIsReal(std::string log, std::string password);

    IDataFileWithUser* dbc;

public:
    UserController(IDataFileWithUser* dbc);

    ModelUser* Registr(const std::string& log, const std::string& password);

    ModelUser* Login(std::string log, std::string password);

    void Logout(ModelUser*& user);

    virtual ~UserController();
};