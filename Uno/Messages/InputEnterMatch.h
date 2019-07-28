//
// Created by Brandon Martin on 7/28/19.
//

#ifndef CURSEN_INPUTENTERMATCH_H
#define CURSEN_INPUTENTERMATCH_H

#include <Uno/Data/DataManager.h>
#include "DataMessage.h"
#include "EnterMatch.h"

class InputEnterMatch : public DataMessage
{

public:

    InputEnterMatch() = default;
    InputEnterMatch(int id) :
            id(id)
    {}

    MessageType getType() override
    {
        return MessageType::InputEnterMatch;
    }

    Context getContext() override
    {
        return Context::ContextLobby;
    }

    void execute() override
    {
        CONTEXT_CHECK_BEGIN

            LobbyForm* lobbyForm = getCurrentForm<LobbyForm>();
            if (id == lobbyForm->getLobby().getMyId() && lobbyForm->getLobby().getNumPlayers() >= Lobby::MIN_PLAYERS_TO_START)
            {
                DataMessage* msg = new EnterMatch;
                msg->setSendType(SendType::Both);
                DataManager::PushMessage(msg);
            }

        CONTEXT_CHECK_END
    }

    DataMessage* clone() override
    {
        return new InputEnterMatch(*this);
    }

    size_t sizeOf() const override
    {
        return sizeof(InputEnterMatch);
    };

    size_t serialize(char* const buffer) const override
    {
        size_t written =  DataMessage::serialize(buffer);

        written += Serializable::Serialize(buffer + written, id);

        return written;
    }

    size_t deserialize(const char* const buffer) override
    {
        size_t read = DataMessage::deserialize(buffer);

        read += Serializable::Deserialize(buffer + read, id);

        return read;
    }

private:

    int id;

};

#endif //CURSEN_INPUTENTERMATCH_H
