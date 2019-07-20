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

            MatchForm* matchForm = getCurrentForm<MatchForm>();
            matchForm->beginGame();

        CONTEXT_CHECK_END
    }

    DataMessage* clone() override
    {
        return nullptr;
    }

    size_t serialize(char* const buffer) const override
    {
        return DataMessage::serialize(buffer);
    }

    size_t deserialize(const char* const buffer) override
    {
        return DataMessage::deserialize(buffer);
    }

};

#endif //CURSEN_BEGINGAME_H
