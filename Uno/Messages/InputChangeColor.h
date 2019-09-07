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

    InputChangeColor() = default;

    MessageType getType() override
    {
        return MessageType::InputChangeColor;
    }

    void execute() override
    {
        CONTEXT_CHECK_BEGIN

            LobbyForm* lobbyForm = GetCurrentForm<LobbyForm>();
            lobbyForm->getController().handleInputColorChange(getSender());

        CONTEXT_END
    }

    size_t sizeOf() const override
    {
        return sizeof(InputChangeColor);
    }

    Context getContext() override
    {
        return Context::ContextLobby;
    }

    DataMessage* clone() override
    {
        return new InputChangeColor(*this);
    }

    size_t serialize(char* const buffer) const override
    {
        size_t written =  DataMessage::serialize(buffer);
        return written;
    }

    size_t deserialize(const char* const buffer) override
    {
        size_t read = DataMessage::deserialize(buffer);
        return read;
    }

};


#endif //CURSEN_INPUTCHANGECOLOR_H
