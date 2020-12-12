#pragma once

#include "IDataFileMessage.h"
#include "../rapidxml/rapidxml.hpp"
#include "../rapidxml/rapidxml_print.hpp"

#include <fstream>
#include <string>
#include <mutex>

class DataFileMessageXML : public IDataFileMessage
{
    std::string fileName;
    
    rapidxml::xml_document<> doc;

    const std::string text_sender    = "sender";
    const std::string text_reciever  = "reciever";
    const std::string text_message   = "message";  

    DataFileMessageXML();

    virtual void read();
    virtual void write();

    std::mutex mtx;    
public:

    static DataFileMessageXML* getInstance();

    virtual std::string get_message(const std::string &login);

    virtual bool sendMessage(const std::string& login, const std::string& loginEnd, const std::string& text_message);

    virtual bool deleteMessage(const std::string& login, int begin, int end);
};