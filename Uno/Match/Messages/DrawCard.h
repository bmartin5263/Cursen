//
// Created by Brandon Martin on 7/20/19.
//

#ifndef CURSEN_DRAWCARD_H
#define CURSEN_DRAWCARD_H

#include <Uno/Data/DataManager.h>
#include <Uno/Forms/MatchForm.h>
#include "Uno/Messages/DataMessage.h"
#include "Uno/GameObjects/Match.h"

class DrawCard : public DataMessage
{
public:

    DrawCard() = default;
    DrawCard(int id, Card drawn_card) :
            index(id), drawn_card(drawn_card)
    {}

    MessageType getType() override
    {
        return MessageType::DrawCard;
    }

    Context getContext() override
    {
        return Context::ContextMatch;
    }

    void execute() override
    {
        CONTEXT_CHECK_BEGIN

            MatchForm* matchForm = GetCurrentForm<MatchForm>();
            matchForm->drawCard(index, drawn_card);

        CONTEXT_CHECK_END
    }

    DataMessage* clone() override
    {
        return new DrawCard(*this);
    }

    size_t serialize(char* const buffer) const override
    {
        size_t written =  DataMessage::serialize(buffer);

        written += Serializable::Serialize(buffer + written, index);
        written += drawn_card.serialize(buffer + written);

        return written;
    }

    size_t deserialize(const char* const buffer) override
    {
        size_t read = DataMessage::deserialize(buffer);

        read += Serializable::Deserialize(buffer + read, index);
        read += drawn_card.deserialize(buffer + read);

        return read;
    }

private:

    int index;
    Card drawn_card;

};


#endif //CURSEN_DRAWCARD_H
