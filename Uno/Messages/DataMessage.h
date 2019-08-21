//
// Created by Brandon Martin on 5/20/19.
//

#ifndef CURSEN_DATAMESSAGE_H
#define CURSEN_DATAMESSAGE_H

#include "Uno/Data/Context.h"
#include "MessageType.h"
#include "SendType.h"
#include "Serializable.h"
#include "Uno/Forms/LobbyForm.h"
#include "Uno/Lobby/LobbyController.h"
#include "Cursen/CursenApplication.h"

#define CONTEXT_CHECK_BEGIN if (DataManager::GetContext() == getContext()) {
#define CONTEXT_CHECK_END }

class DataMessage : public Serializable
{

public:

    static DataMessage* Parse(MessageType type);
    size_t serialize(char* const buffer) const override;
    size_t deserialize(const char* const buffer) override;

    DataMessage() :
            sendType(SendType::Uninitialized), recipientType(RecipientType::Broadcast), senderId(-1), recipientId(-1),
            allow_loopback(true)
    {}

    virtual ~DataMessage() = default;

    virtual MessageType getType() = 0;
    virtual Context getContext() = 0;
    virtual void execute() = 0;
    virtual DataMessage* clone() = 0;

    SendType getSendType() { return sendType; };
    void setSendType(SendType type) { this->sendType = type; };

    RecipientType getRecipientType() { return this->recipientType; };
    void setRecipientType(RecipientType type) { this->recipientType = type; };

    void setRecipient(int id) { this->recipientId = id; };
    int getRecipient() { return recipientId; }

    void setSender(int id) { this->senderId = id; };
    int getSender() { return senderId; }

    void noLoopback() { allow_loopback = false; };
    bool canLoopback() { return allow_loopback; };

    size_t sizeOf() const override;

    template<typename T>
    static T* GetCurrentForm()
    {
        return (T*)cursen::CursenApplication::GetCurrentForm();
    }

private:

    SendType sendType;
    RecipientType recipientType;

    int senderId;           // For host incoming messages
    int recipientId;        // For host outgoing messages
    bool allow_loopback;    // TODO poor design

};


#endif //CURSEN_DATAMESSAGE_H
