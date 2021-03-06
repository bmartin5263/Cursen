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
    DataManager& instance = Instance();
    MessageQueue& in = instance.in;
    instance.processIn();
    instance.processOut();
    while (!in.isEmpty())
    {
        instance.processIn();
        instance.processOut();
    }
}

void DataManager::privPushMessage(DataMessage* message)
{
    message->setSender(DataManager::LOOP_BACK);  // sent locally
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
                if (entry->getRecipient() == DataManager::LOOP_BACK && entry->getMessage()->canLoopback())
                {
                    ForwardToInput(entry);
                }
                else NetworkManager::WriteMessage(entry);
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