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

    InputChangeColor() :
        id(-1)
    {}

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
            auto lobbyForm = (LobbyForm*)cursen::CursenApplication::GetCurrentForm();
            PlayerColor new_color = lobbyForm->getLobby().getAvailableColor();

            DataMessage* msg = new ChangeColor(id, new_color);
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

    DataMessage* clone() override
    {
        return new InputChangeColor(*this);
    }

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


#endif //CURSEN_INPUTCHANGECOLOR_H
