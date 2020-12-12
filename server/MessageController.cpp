#include "MessageController.h"

MessageController::MessageController(IDataFileMessage* dfm) :
    dfm(dfm)
{
}

bool MessageController::sendMessage(const ModelUser* const user, const std::string& recipient, const std::string& text_message)
{
    return dfm->sendMessage(user->get_login(), recipient, text_message);
}

bool MessageController::deleteMessage(const ModelUser* const user, int begin, int end)
{
    return dfm->deleteMessage(user->get_login(), begin, end);
}

std::string MessageController::showMessage(const ModelUser* const user)
{
    return dfm->get_message(user->get_login());
}

MessageController::~MessageController()
{
}
