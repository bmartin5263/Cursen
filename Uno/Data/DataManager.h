//
// Created by Brandon Martin on 5/20/19.
//

#ifndef CURSEN_DATAMANAGER_H
#define CURSEN_DATAMANAGER_H


#include <queue>
#include "../Messages/DataMessage.h"
#include "QueueEntry.h"
#include "MessageQueue.h"

class DataManager
{
public:

    static void PushMessage(DataMessage* message) { Instance().privPushMessage(message); };
    static void ProcessDataMessages();
    static void ForwardToInput(QueueEntry entry);

private:

    void privPushMessage(DataMessage* message);

    void processIn();
    void processOut();

    static DataManager* instance;

    static DataManager& Instance() {
        if (instance == nullptr)
            instance = new DataManager;
        return *instance;
    }

    DataManager() = default;
    DataManager(const DataManager& other) = delete;
    DataManager(DataManager&& other) noexcept = delete;
    DataManager& operator = (const DataManager& other) = delete;
    DataManager& operator = (DataManager&& other) = delete;
    ~DataManager() = default;

    MessageQueue in;
    MessageQueue out;

};


#endif //CURSEN_DATAMANAGER_H
