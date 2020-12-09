#pragma once
#include <iostream>
#include <string>

class ModelUser
{
private:
    std::string login;
    std::string password;
    
public:
    ModelUser(const std::string& login, const std::string& password);

    std::string get_login() const;
    std::string get_password() const;

    void set_login(const std::string& login);
    void set_password(const std::string& password);
};