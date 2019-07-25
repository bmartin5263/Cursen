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
    DrawCard(int id) :
            id(id)
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

            MatchForm* matchForm = getCurrentForm<MatchForm>();
            matchForm->drawCard(id);

        CONTEXT_CHECK_END
    }

    DataMessage* clone() override
    {
        return new DrawCard(*this);
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


#endif //CURSEN_DRAWCARD_H
