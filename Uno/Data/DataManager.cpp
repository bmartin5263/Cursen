//
// Created by Brandon Martin on 5/20/19.
//

#include <cassert>
#include "DataManager.h"
#include "../Network/NetworkManager.h"

DataManager* DataManager::instance = nullptr;

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
        QueueEntry entry = in.dequeue();
        DataMessage* msg = entry.message;
        msg->execute();
        delete msg;
    }
}

void DataManager::processOut()
{
    while (!out.isEmpty())
    {
        QueueEntry entry = out.dequeue();
        DataMessage* msg = entry.message;

        SendType sendType = msg->getSendType();

        switch (sendType) {
            case SendType::Uninitialized:
                assert(false);
                break;
            case SendType::Local:
                ForwardToInput(entry);
                break;
            case SendType::Network:
                NetworkManager::Write(entry);
                break;
            case SendType::Both:
                ForwardToInput(entry);
                NetworkManager::Write(entry);
                break;
        }
    }
}

void DataManager::ForwardToInput(QueueEntry entry)
{
    Instance().in.enqueue(entry);
}
