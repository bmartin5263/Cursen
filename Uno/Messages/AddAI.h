//
// Created by Brandon Martin on 6/6/19.
//

#ifndef CURSEN_ADDAI_H
#define CURSEN_ADDAI_H

#include "DataMessage.h"
#include "Uno/Forms/LobbyForm.h"
#include "Uno/Lobby/LobbyController.h"
#include "Uno/Data/DataManager.h"
#include "Cursen/CursenApplication.h"

class AddAI : public DataMessage {

public:

    AddAI() = default;

    AddAI(const Player& p):
            new_ai(p)
    {}

    MessageType getType() override
    {
        return MessageType::AddAI;
    }

    Context getContext() override
    {
        return Context::ContextLobby;
    }

    void execute() override
    {
        if (DataManager::GetContext() == getContext())
        {
            LobbyForm* lobbyForm = (LobbyForm*)cursen::CursenApplication::GetCurrentForm();
            lobbyForm->getController().handleAddAi(new_ai);
        }
    }

    DataMessage* clone() override
    {
        return new AddAI(*this);
    }

    size_t sizeOf() const override
    {
        return sizeof(AddAI);
    }

    size_t serialize(char* const buffer) const override
    {
        size_t written = DataMessage::serialize(buffer);

        written += new_ai.serialize(buffer + written);

        return written;
    }

    size_t deserialize(const char* const buffer) override
    {
        size_t read = DataMessage::deserialize(buffer);

        read += new_ai.deserialize(buffer + read);

        return read;
    }

private:

    Player new_ai;

};


#endif //CURSEN_ADDAI_H
