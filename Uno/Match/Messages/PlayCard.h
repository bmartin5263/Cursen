//
// Created by Brandon Martin on 7/21/19.
//

#ifndef CURSEN_PLAYCARD_H
#define CURSEN_PLAYCARD_H

#include <Uno/Match/Events/PlaceCardEvent.h>
#include "Uno/Data/DataManager.h"
#include "Uno/Forms/MatchForm.h"

class PlayCard : public DataMessage
{
public:

    PlayCard() = default;
    PlayCard(int index, int card_index, Card played_card) :
            index(index), card_index(card_index), played_card(played_card)
    {}

    MessageType getType() override
    {
        return MessageType::PlayCard;
    }

    Context getContext() override
    {
        return Context::Match;
    }

    void execute() override
    {
        CONTEXT_CHECK_BEGIN

        MatchForm* matchForm = GetCurrentForm<MatchForm>();
        matchForm->getMatchEventQueue().pushEvent(new PlaceCardEvent(index, card_index, played_card));

        CONTEXT_END
    }

    DataMessage* clone() override
    {
        return new PlayCard(*this);
    }

    size_t serialize(char* const buffer) const override
    {
        size_t written =  DataMessage::serialize(buffer);

        written += Serializable::Serialize(buffer + written, index);
        written += Serializable::Serialize(buffer + written, card_index);
        written += played_card.serialize(buffer + written);

        return written;
    }

    size_t deserialize(const char* const buffer) override
    {
        size_t read = DataMessage::deserialize(buffer);

        read += Serializable::Deserialize(buffer + read, index);
        read += Serializable::Deserialize(buffer + read, card_index);
        read += played_card.deserialize(buffer + read);

        return read;
    }

private:

    int index;
    int card_index;
    Card played_card;

};


#endif //CURSEN_PLAYCARD_H
