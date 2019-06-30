//
// Created by Brandon Martin on 5/20/19.
//

#ifndef CURSEN_DATAMANAGER_H
#define CURSEN_DATAMANAGER_H


#include <queue>
#include "Uno/Messages/DataMessage.h"
#include "QueueEntry.h"
#include "MessageQueue.h"

class DataManager
{
public:

    static void PushMessage(DataMessage* message) { Instance().privPushMessage(message); };
    static void ProcessDataMessages();
    static void ForwardToInput(QueueEntry* entry);

    static void SetContext(Context new_context);
    static Context GetContext();

private:

    void privPushMessage(DataMessage* message);

    void processIn();
    void processOut();

    static DataManager& Instance() {
        static DataManager instance;
        return instance;
    }

    DataManager();
    DataManager(const DataManager& other) = delete;
    DataManager(DataManager&& other) noexcept = delete;
    DataManager& operator = (const DataManager& other) = delete;
    DataManager& operator = (DataManager&& other) = delete;
    ~DataManager() = default;

    MessageQueue in;
    MessageQueue out;
    Context context;

};


#endif //CURSEN_DATAMANAGER_H
