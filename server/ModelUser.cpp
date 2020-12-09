#include "ModelUser.h"

ModelUser::ModelUser(const std::string& login, const std::string& password) :
    login(login),
    password(password){}

std::string ModelUser::get_login() const
{
    return login;
}

std::string ModelUser::get_password() const
{
    return password;
}

void ModelUser::set_login(const std::string& login)
{
    this->login = login;
}

void ModelUser::set_password(const std::string& password)
{
    this->password = password;
}
