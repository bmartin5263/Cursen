//
// Created by Brandon Martin on 6/10/19.
//

#ifndef CURSEN_CLOSEROOM_H
#define CURSEN_CLOSEROOM_H

#include "DataMessage.h"
#include "Uno/Data/DataManager.h"
#include "Uno/Forms/LobbyForm.h"
#include "Cursen/CursenApplication.h"
#include "Uno/Lobby/LobbyController.h"

class CloseRoom : public DataMessage
{
public:

    CloseRoom() = default;
    CloseRoom(const std::string& msg, bool kick) :
        message(msg), kicked(kick)
    {};

    MessageType getType() override
    {
        return MessageType::CloseRoom;
    }

    Context getContext() override
    {
        return Context::ContextLobby;
    }

    void execute() override
    {
        CONTEXT_CHECK_BEGIN

            LobbyForm* lobbyForm = GetCurrentForm<LobbyForm>();
            lobbyForm->getController().handleClose(message, kicked);

        CONTEXT_END
    }

    DataMessage* clone() override
    {
        return new CloseRoom(*this);
    }

    size_t sizeOf() const override
    {
        return sizeof(CloseRoom);
    }

    size_t serialize(char* const buffer) const override
    {
        size_t written = DataMessage::serialize(buffer);

        written += Serializable::Serialize(buffer + written, message);
        written += Serializable::Serialize(buffer + written, kicked);

        return written;
    }

    size_t deserialize(const char* const buffer) override
    {
        size_t read = DataMessage::deserialize(buffer);

        read += Serializable::Deserialize(buffer + read, message);
        read += Serializable::Deserialize(buffer + read, kicked);

        return read;
    }

private:

    std::string message;
    bool kicked;

};


#endif //CURSEN_CLOSEROOM_H
