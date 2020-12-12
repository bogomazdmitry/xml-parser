#pragma once
#include "Controller.h"
#include "ModelUser.h"
#include "ModelMessage.h"
#include "IDataFileMessage.h"

#include <fstream>
#include <iostream>
#include <string>
#include <string>

class MessageController : public Controller
{
private:
    IDataFileMessage* dfm;
public:
    MessageController(IDataFileMessage* dfm);

    bool sendMessage(const ModelUser* const user, const std::string& recipient, const std::string& text_message);

    bool deleteMessage(const ModelUser* const user, int begin = 1, int end = -1);

    std::string showMessage(const ModelUser* const user);

    virtual ~MessageController();
};