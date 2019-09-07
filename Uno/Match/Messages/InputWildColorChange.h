//
// Created by Brandon Martin on 7/27/19.
//

#ifndef CURSEN_INPUTWILDCOLORCHANGE_H
#define CURSEN_INPUTWILDCOLORCHANGE_H

#include "Uno/Messages/DataMessage.h"
#include "Uno/Data/DataManager.h"
#include "Uno/Forms/MatchForm.h"
#include "Uno/GameObjects/Match.h"
#include "WildColorChange.h"

class InputWildColorChange : public DataMessage
{
public:

    InputWildColorChange() = default;
    InputWildColorChange(int id, CardColor color) :
            id(id), color(color)
    {}

    MessageType getType() override
    {
        return MessageType::InputWildColorChange;
    }

    Context getContext() override
    {
        return Context::Match;
    }

    void execute() override
    {
        CONTEXT_CHECK_BEGIN

            MatchForm* matchForm = GetCurrentForm<MatchForm>();
            Match& match = matchForm->getMatch();
            if (
                    match.isWildCard()
                 && match.getCurrentTurnId() == id
                 && color != CardColor::WHITE
                    )
            {
                DataMessage* msg = new WildColorChange(color);
                msg->setSendType(SendType::Both);
                DataManager::PushMessage(msg);
            }

        CONTEXT_END
    }

    DataMessage* clone() override
    {
        return new InputWildColorChange(*this);
    }

    size_t serialize(char* const buffer) const override
    {
        size_t written =  DataMessage::serialize(buffer);

        written += Serializable::Serialize(buffer + written, id);
        written += Serializable::Serialize(buffer + written, (int)color);

        return written;
    }

    size_t deserialize(const char* const buffer) override
    {
        size_t read = DataMessage::deserialize(buffer);

        read += Serializable::Deserialize(buffer + read, id);
        int raw_color = 0;
        read += Serializable::Deserialize(buffer + read, raw_color);
        color = (CardColor)raw_color;

        return read;
    }

private:

    int id;
    CardColor color;

};

#endif //CURSEN_INPUTWILDCOLORCHANGE_H
