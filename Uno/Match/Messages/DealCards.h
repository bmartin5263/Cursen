//
// Created by Brandon Martin on 7/14/19.
//

#ifndef CURSEN_DEALCARDS_H
#define CURSEN_DEALCARDS_H

#include "Uno/Data/DataManager.h"
#include "Uno/Messages/DataMessage.h"
#include "Uno/Match/FSM/MatchInputState.h"
#include "Uno/Forms/MatchForm.h"
#include "Uno/GameObjects/Match.h"

class DealCards : public DataMessage
{
public:

    DealCards() = default;

    MessageType getType() override
    {
        return MessageType::DealCards;
    }

    Context getContext() override
    {
        return Context::Match;
    }

    void execute() override
    {
        CONTEXT_CHECK_BEGIN

            MatchForm* matchForm = GetCurrentForm<MatchForm>();
            matchForm->dealCards();

        CONTEXT_END
    }

    DataMessage* clone() override
    {
        return new DealCards(*this);
    }

    size_t serialize(char* const buffer) const override
    {
        return 0;
    }

    size_t deserialize(const char* const buffer) override
    {
        return 0;
    }

private:

};

#endif //CURSEN_DEALCARDS_H
