//
// Created by Brandon Martin on 8/22/19.
//

#ifndef CURSEN_ENDGAME_H
#define CURSEN_ENDGAME_H

#include <Uno/Forms/MatchForm.h>
#include "Uno/Data/DataManager.h"
#include "Uno/Match/MatchController.h"

class EndGame : public DataMessage
{
public:

    EndGame() = default;

    MessageType getType() override
    {
        return MessageType::EndGame;
    }

    Context getContext() override
    {
        return Context::ContextMatch;
    }

    void execute() override
    {
        CONTEXT_CHECK_BEGIN

            GetCurrentForm<MatchForm>()->getController()->handleClose("Closed", false);

        CONTEXT_CHECK_END
    }

    DataMessage* clone() override
    {
        return new EndGame(*this);
    }

    size_t serialize(char* const buffer) const override
    {
        size_t written = DataMessage::serialize(buffer);

        //written += Serializable::Serialize(buffer + written, winner_index);

        return written;
    }

    size_t deserialize(const char* const buffer) override
    {
        size_t read = DataMessage::deserialize(buffer);

        //read += Serializable::Deserialize(buffer + read, winner_index);

        return read;
    }

private:

};

#endif //CURSEN_ENDGAME_H
