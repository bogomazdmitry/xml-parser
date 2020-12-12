#include "DataFileMessageXML.h"

#include <cstring>
#include <string>
#include <fstream>
#include <streambuf>

using namespace rapidxml;

DataFileMessageXML::DataFileMessageXML() :
    fileName("messages.xml")
{
}

DataFileMessageXML* DataFileMessageXML::getInstance()
{
    static DataFileMessageXML* instance = new DataFileMessageXML();
    return instance;
}

std::string DataFileMessageXML::get_message(const std::string &login)
{
    mtx.lock();
    read();

    std::string answer = "";
    
    std::string sender   = "";
    std::string reciever = "";
    std::string message  = "";
    
    for(xml_node<> *node = doc.first_node(); node; node = node->next_sibling())  
    {
        std::cout << "node: " << *node << std::endl;

        for (xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute())
        {
            // std::cout << "attr: \"" << attr->value() << "\""<< std::endl;
            // std::cout << "attr: \"" << text_sender.c_str() << "\"" << std::endl;
            if(strcmp(attr->name(), text_sender.c_str())   == 0)    { sender    = std::string(attr->value()); continue; }
            if(strcmp(attr->name(), text_reciever.c_str()) == 0)    { reciever  = std::string(attr->value()); continue; }
            if(strcmp(attr->name(), text_message.c_str())  == 0)    { message   = std::string(attr->value()); continue; }
        }

        // std::cout << "login: " << login << std::endl;
        // std::cout << "reciever: " << reciever << std::endl;

        if(reciever == login)
        {
            answer += sender + " -> " + reciever + "\n" + message + "\n\n";
        }
    }

    // std::cout << "read: " << answer << std::endl;
    // std::cout << "*********" << std::endl;

    mtx.unlock();
    return answer;
}

bool DataFileMessageXML::sendMessage(const std::string& login, const std::string& loginEnd, const std::string& message)
{
    mtx.lock();
    read();

    xml_node<> *node = new xml_node<>(node_element);
    node->name("one");

    xml_attribute<>* attr1 = new xml_attribute<>();
    attr1->name(text_sender.c_str());
    attr1->value(login.c_str());

    xml_attribute<>* attr2 = new xml_attribute<>();
    attr2->name(text_reciever.c_str());
    attr2->value(loginEnd.c_str());

    xml_attribute<>* attr3 = new xml_attribute<>();
    attr3->name(text_message.c_str());
    attr3->value(message.c_str());

    node->append_attribute(attr1);
    node->append_attribute(attr2);
    node->append_attribute(attr3);

    doc.append_node(node);

    // std::cout << "-----\n";
    // std::cout << doc << std::endl;
    // std::cout << "-----\n";

    write();
    mtx.unlock();
    return true;
}

bool DataFileMessageXML::deleteMessage(const std::string& login, int begin, int end)
{
    mtx.lock();
    read();

    int count = 0;

    std::string sender = "";
    std::string reciever = "";
    std::string message = "";
    
    for(xml_node<> *node = doc.first_node(); node; node = node->next_sibling())  
    {
        for(xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) 
        {
            if(strcmp(attr->name(), text_reciever.c_str()) == 0)    { reciever  = std::string(attr->value()); break; }
        }
        
        if(reciever == login)
        {
            if(count >= begin && count <= end || end < 0)
            {
                doc.remove_node(node);
                continue;
            }
            ++count;
        }
        node = node->next_sibling();
    }

    write();
    mtx.unlock();
    return true;
}

void DataFileMessageXML::read()
{
    std::ifstream t(fileName);
    std::string rawData((std::istreambuf_iterator<char>(t)), 
            std::istreambuf_iterator<char>());

    // std::cout << rawData << std::endl;

    t.close();

    char *c = new char[rawData.length()];
    
    strcpy(c, rawData.c_str());

    try{
        const int flags = parse_full;
        doc.parse<flags>(c);
        // std::cout << doc << std::endl;
    }
    catch (parse_error* x)
    {
        std::cerr << x;
    }
    catch(...)
    {
        ////////
    }

    delete[] c;
}

void DataFileMessageXML::write()
{
    std::ofstream t(fileName);

    t << doc << std::flush;

    t.close();
}