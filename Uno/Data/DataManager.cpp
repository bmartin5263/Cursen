//
// Created by Brandon Martin on 5/20/19.
//

#include <cassert>
#include "DataManager.h"
#include "Uno/Network/NetworkManager.h"

DataManager::DataManager() :
    context(Context::None)
{

}

void DataManager::ProcessDataMessages()
{
    Instance().processOut();
    Instance().processIn();
}

void DataManager::privPushMessage(DataMessage* message)
{
    out.enqueue(message);
}

void DataManager::processIn()
{
    while (!in.isEmpty())
    {
        QueueEntry* entry = in.dequeue();
        DataMessage* msg = entry->getMessage();
        msg->execute();
        delete entry;
    }
}

void DataManager::processOut()
{
    while (!out.isEmpty())
    {
        QueueEntry* entry = out.dequeue();
        SendType sendType = entry->getMessage()->getSendType();

        switch (sendType) {
            case SendType::Uninitialized:
                assert(false);
                break;
            case SendType::Local:
                ForwardToInput(entry);
                break;
            case SendType::Network:
                NetworkManager::WriteMessage(entry);
                delete entry;
                break;
            case SendType::Both:
                ForwardToInput(entry);
                NetworkManager::WriteMessage(entry);
                break;
        }
    }
}

void DataManager::ForwardToInput(QueueEntry* entry)
{
    Instance().in.enqueue(entry);
}

void DataManager::SetContext(Context new_context)
{
    Instance().context = new_context;
}

Context DataManager::GetContext()
{
    return Instance().context;
}