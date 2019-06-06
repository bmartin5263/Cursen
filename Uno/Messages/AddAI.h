//
// Created by Brandon Martin on 6/6/19.
//

#ifndef CURSEN_ADDAI_H
#define CURSEN_ADDAI_H

#include "DataMessage.h"
#include "Uno/Forms/LobbyForm.h"
#include "Uno/Data/DataManager.h"
#include "Cursen/CursenApplication.h"

class AddAI : public DataMessage {
public:

    AddAI() = default;

    AddAI(char* name, PlayerColor color):
        name(name), color(color)
    {}

    ~AddAI()
    {
        delete name;
    }

    MessageType getType() override
    {
        return MessageType::AddAI;
    }

    Context getContext() override
    {
        return Context::Lobby;
    }

    void execute() override
    {
        if (DataManager::GetContext() == getContext())
        {
            LobbyForm* lobbyForm = (LobbyForm*)cursen::CursenApplication::GetCurrentForm();
            lobbyForm->addAi(name, color);
        }
    }

    DataMessage* copy() override
    {
        return new AddAI(*this);
    }

    size_t sizeOf() const override
    {
        return sizeof(AddAI);
    }

private:

    char* name;
    PlayerColor color;

};

#endif //CURSEN_ADDAI_H
