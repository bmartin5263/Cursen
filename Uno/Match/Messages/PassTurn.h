//
// Created by Brandon Martin on 8/11/19.
//

#ifndef CURSEN_PASSTURN_H
#define CURSEN_PASSTURN_H

#include "Uno/Data/DataManager.h"
#include "Uno/Forms/MatchForm.h"
#include "Uno/Match/MatchController.h"

class PassTurn : public DataMessage
{

public:

    PassTurn() = default;
    PassTurn(CardColor new_color) :
        new_color(new_color)
    {};

    MessageType getType() override
    {
        return MessageType::PassTurn;
    }

    Context getContext() override
    {
        return Context::ContextMatch;
    }

    void execute() override
    {
        CONTEXT_CHECK_BEGIN

            MatchForm* matchForm = getCurrentForm<MatchForm>();
            matchForm->passTurn(new_color);

        CONTEXT_CHECK_END
    }

    DataMessage* clone() override
    {
        return new PassTurn(*this);
    }

    size_t serialize(char* const buffer) const override
    {
        return DataMessage::serialize(buffer);
    }

    size_t deserialize(const char* const buffer) override
    {
        return DataMessage::deserialize(buffer);
    }

private:

    CardColor new_color;

};

#endif //CURSEN_PASSTURN_H
