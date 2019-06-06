//
// Created by Brandon Martin on 6/6/19.
//

#ifndef CURSEN_CHANGECOLOR_H
#define CURSEN_CHANGECOLOR_H

#include "DataMessage.h"
#include "Cursen/CursenApplication.h"
#include "Uno/Forms/LobbyForm.h"
#include "Uno/Data/DataManager.h"

class ChangeColor : public DataMessage
{
public:

    ChangeColor() = default;

    ChangeColor(int id) :
        id(id)
    {}

    MessageType getType() override
    {
        return MessageType::ChangeColor;
    }

    Context getContext() override
    {
        return Context::Lobby;
    }

    void execute() override
    {
        if (DataManager::GetContext() == getContext())
        {
            LobbyForm* lobby = (LobbyForm*)cursen::CursenApplication::GetCurrentForm();
            lobby->changeColor(id);
        }
    }

    size_t sizeOf() const override
    {
        return sizeof(ChangeColor);
    }

    DataMessage* copy() override
    {
        return new ChangeColor(*this);
    }

private:

    int id;

};

#endif //CURSEN_CHANGECOLOR_H
