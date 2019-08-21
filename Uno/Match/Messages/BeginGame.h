//
// Created by Brandon Martin on 7/19/19.
//

#ifndef CURSEN_BEGINGAME_H
#define CURSEN_BEGINGAME_H

#include <Uno/Data/DataManager.h>
#include <Uno/Forms/MatchForm.h>
#include "Uno/Messages/DataMessage.h"
#include "Uno/GameObjects/Match.h"

class BeginGame : public DataMessage
{
public:

    BeginGame() = default;
    BeginGame(Card initial_card) : initial_card(initial_card)
    {}

    MessageType getType() override
    {
        return MessageType::BeginGame;
    }

    Context getContext() override
    {
        return Context::ContextMatch;
    }

    void execute() override
    {
        CONTEXT_CHECK_BEGIN

            MatchForm* matchForm = GetCurrentForm<MatchForm>();
            matchForm->beginGame(initial_card);

        CONTEXT_CHECK_END
    }

    DataMessage* clone() override
    {
        return nullptr;
    }

    size_t serialize(char* const buffer) const override
    {
        size_t written = DataMessage::serialize(buffer);

        written += initial_card.serialize(buffer + written);

        return written;
    }

    size_t deserialize(const char* const buffer) override
    {
        size_t read = DataMessage::deserialize(buffer);

        read += initial_card.deserialize(buffer + read);

        return read;
    }

private:

    Card initial_card;

};

#endif //CURSEN_BEGINGAME_H
