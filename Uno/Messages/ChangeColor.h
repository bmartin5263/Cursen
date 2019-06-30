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

    ChangeColor(int id, PlayerColor color) :
        id(id), new_color(color)
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
            lobby->changeColor(id, new_color);
        }
    }

    size_t sizeOf() const override
    {
        return sizeof(ChangeColor);
    }

    DataMessage* clone() override
    {
        return new ChangeColor(*this);
    }

    size_t serialize(char* const buffer) const override
    {
        size_t written =  DataMessage::serialize(buffer);

        written += Serializable::Serialize(buffer + written, id);
        written += Serializable::Serialize(buffer + written, (int)new_color);

        return written;
    }

    size_t deserialize(const char* const buffer) override
    {
        size_t read = DataMessage::deserialize(buffer);

        read += Serializable::Deserialize(buffer + read, id);

        int raw_color;
        read += Serializable::Deserialize(buffer + read, raw_color);
        new_color = (PlayerColor)raw_color;

        return read;
    }

private:

    int id;
    PlayerColor new_color;

};

#endif //CURSEN_CHANGECOLOR_H
