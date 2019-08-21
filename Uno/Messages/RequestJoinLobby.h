//
// Created by Brandon Martin on 6/11/19.
//

#ifndef CURSEN_ENTERLOBBY_H
#define CURSEN_ENTERLOBBY_H

#include "DataMessage.h"
#include "Uno/Forms/LobbyForm.h"
#include "Uno/Data/DataManager.h"
#include "Cursen/CursenApplication.h"

class RequestJoinLobby : public DataMessage {

public:

    RequestJoinLobby() = default;
    RequestJoinLobby(std::string name) :
            name(name)
    {}

    MessageType getType() override
    {
        return MessageType::RequestJoinLobby;
    }

    Context getContext() override
    {
        return Context::ContextLobby;
    }

    void execute() override
    {
        CONTEXT_CHECK_BEGIN

            LobbyForm* lobbyForm = GetCurrentForm<LobbyForm>();
            lobbyForm->requestClient(getSender(), name);

        CONTEXT_CHECK_END
    }

    DataMessage* clone() override
    {
        return new RequestJoinLobby(*this);
    }

    size_t sizeOf() const override
    {
        return sizeof(RequestJoinLobby);
    }

    size_t serialize(char* const buffer) const override
    {
        size_t written = DataMessage::serialize(buffer);

        written += Serializable::Serialize(buffer + written, name);

        return written;
    }

    size_t deserialize(const char* const buffer) override
    {
        size_t read = DataMessage::deserialize(buffer);

        read += Serializable::Deserialize(buffer + read, name);

        return read;
    }

private:

    std::string name;

};

#endif //CURSEN_ENTERLOBBY_H
