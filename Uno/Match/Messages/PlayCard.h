//
// Created by Brandon Martin on 7/21/19.
//

#ifndef CURSEN_PLAYCARD_H
#define CURSEN_PLAYCARD_H

#include "Uno/Data/DataManager.h"
#include "Uno/Forms/MatchForm.h"

class PlayCard : public DataMessage
{
public:

    PlayCard() = default;
    PlayCard(int id, int card_index) :
            id(id), card_index(card_index)
    {}

    MessageType getType() override
    {
        return MessageType::PlayCard;
    }

    Context getContext() override
    {
        return Context::ContextMatch;
    }

    void execute() override
    {
        CONTEXT_CHECK_BEGIN

        MatchForm* matchForm = getCurrentForm<MatchForm>();
        matchForm->playCard(id, card_index);

        CONTEXT_CHECK_END
    }

    DataMessage* clone() override
    {
        return new PlayCard(*this);
    }

    size_t serialize(char* const buffer) const override
    {
        size_t written =  DataMessage::serialize(buffer);

        written += Serializable::Serialize(buffer + written, id);
        written += Serializable::Serialize(buffer + written, card_index);

        return written;
    }

    size_t deserialize(const char* const buffer) override
    {
        size_t read = DataMessage::deserialize(buffer);

        read += Serializable::Deserialize(buffer + read, id);
        read += Serializable::Deserialize(buffer + read, card_index);

        return read;
    }

private:

    int id;
    int card_index;

};


#endif //CURSEN_PLAYCARD_H
