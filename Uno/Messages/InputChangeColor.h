//
// Created by Brandon Martin on 6/6/19.
//

#ifndef CURSEN_INPUTCHANGECOLOR_H
#define CURSEN_INPUTCHANGECOLOR_H

#include "Uno/Forms/LobbyForm.h"
#include "DataMessage.h"
#include "Cursen/CursenApplication.h"
#include "Uno/Data/DataManager.h"
#include "ChangeColor.h"

class InputChangeColor : public DataMessage
{
public:

    InputChangeColor(int id) :
        id(id)
    {
    }

    MessageType getType() override
    {
        return MessageType::InputChangeColor;
    }

    void execute() override
    {
        if (DataManager::GetContext() == getContext())
        {
            DataMessage* msg = new ChangeColor(id);
            msg->setSendType(SendType::Both);
            DataManager::PushMessage(msg);
        }
    }

    size_t sizeOf() const override
    {
        return sizeof(InputChangeColor);
    }

    Context getContext() override
    {
        return Context::Lobby;
    }

    DataMessage* copy() override
    {
        return new InputChangeColor(*this);
    }

private:

    int id;

};


#endif //CURSEN_INPUTCHANGECOLOR_H
