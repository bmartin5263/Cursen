//
// Created by Brandon Martin on 6/6/19.
//

#ifndef CURSEN_INPUTCLOSE_H
#define CURSEN_INPUTCLOSE_H

#include "DataMessage.h"
#include "CloseRoom.h"
#include "KickPlayer.h"
#include "Uno/Data/DataManager.h"
#include "Uno/Forms/LobbyForm.h"
#include "Cursen/CursenApplication.h"

class InputCloseRoom : public DataMessage
{

public:

    InputCloseRoom() = default;
    InputCloseRoom(int id) :
        id(id)
    {}

    MessageType getType() override
    {
        return MessageType::InputClose;
    }

    Context getContext() override
    {
        return Context::ContextLobby;
    }

    void execute() override
    {
        CONTEXT_CHECK_BEGIN

            LobbyForm* lobbyForm = GetCurrentForm<LobbyForm>();
            if (id == lobbyForm->getLobby().getMyId())
            {
                // Security - the host should reject messages without the host's id
                lobbyForm->getController().sendCloseMessages();
            }

        CONTEXT_END
    }

    DataMessage* clone() override
    {
        return new InputCloseRoom(*this);
    }

    size_t sizeOf() const override
    {
        return sizeof(InputCloseRoom);
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

#endif //CURSEN_INPUTCLOSE_H
