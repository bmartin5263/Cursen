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
        return Context::Match;
    }

    void execute() override
    {
        CONTEXT_CHECK_BEGIN

            MatchForm* matchForm = GetCurrentForm<MatchForm>();
            matchForm->passTurn(new_color);

        CONTEXT_END
    }

    DataMessage* clone() override
    {
        return new PassTurn(*this);
    }

    size_t serialize(char* const buffer) const override
    {
        size_t written = DataMessage::serialize(buffer);

        written += DataMessage::Serialize(buffer + written, (int)new_color);

        return written;
    }

    size_t deserialize(const char* const buffer) override
    {
        size_t read = DataMessage::deserialize(buffer);
        int raw_color;

        read += DataMessage::Deserialize(buffer + read, raw_color);
        new_color = static_cast<CardColor>(raw_color);

        return read;
    }

private:

    CardColor new_color;

};

#endif //CURSEN_PASSTURN_H
