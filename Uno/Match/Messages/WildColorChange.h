//
// Created by Brandon Martin on 7/27/19.
//

#ifndef CURSEN_WILDCOLORCHANGE_H
#define CURSEN_WILDCOLORCHANGE_H

#include "Uno/Data/DataManager.h"
#include "Uno/Forms/MatchForm.h"
#include "Uno/GameObjects/Match.h"

class WildColorChange : public DataMessage
{
public:

    WildColorChange() = default;
    WildColorChange(CardColor color) :
            color(color)
    {}

    MessageType getType() override
    {
        return MessageType::WildColorChange;
    }

    Context getContext() override
    {
        return Context::ContextMatch;
    }

    void execute() override
    {
        CONTEXT_CHECK_BEGIN

        MatchForm* matchForm = getCurrentForm<MatchForm>();
        matchForm->wildColorChange(color);

        CONTEXT_CHECK_END
    }

    DataMessage* clone() override
    {
        return new WildColorChange(*this);
    }

    size_t serialize(char* const buffer) const override
    {
        size_t written =  DataMessage::serialize(buffer);

        written += Serializable::Serialize(buffer + written, (int)color);

        return written;
    }

    size_t deserialize(const char* const buffer) override
    {
        size_t read = DataMessage::deserialize(buffer);

        int raw_color = 0;
        read += Serializable::Deserialize(buffer + read, raw_color);
        color = (CardColor)raw_color;

        return read;
    }

private:

    CardColor color;

};

#endif //CURSEN_WILDCOLORCHANGE_H
