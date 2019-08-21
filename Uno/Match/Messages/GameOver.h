//
// Created by Brandon Martin on 8/11/19.
//

#ifndef CURSEN_GAMEOVER_H
#define CURSEN_GAMEOVER_H


#include <Uno/Forms/MatchForm.h>
#include "Uno/Data/DataManager.h"
#include "Uno/Match/MatchController.h"

class GameOver : public DataMessage
{
public:

    GameOver() = default;
    GameOver(int winner_index, Match match) :
            match_state(match), winner_index(winner_index)
    {}

    MessageType getType() override
    {
        return MessageType::GameOver;
    }

    Context getContext() override
    {
        return Context::ContextMatch;
    }

    void execute() override
    {
        CONTEXT_CHECK_BEGIN

            MatchForm* matchForm = getCurrentForm<MatchForm>();
            matchForm->getController()->handleGameOver(match_state, winner_index);

        CONTEXT_CHECK_END
    }

    DataMessage* clone() override
    {
        return new GameOver(*this);
    }

    size_t serialize(char* const buffer) const override
    {
        size_t written =  DataMessage::serialize(buffer);

        written += Serializable::Serialize(buffer + written, winner_index);
        written += match_state.serialize(buffer + written);

        return written;
    }

    size_t deserialize(const char* const buffer) override
    {
        size_t read = DataMessage::deserialize(buffer);

        read += Serializable::Deserialize(buffer + read, winner_index);
        read += match_state.deserialize(buffer + read);

        return read;
    }

private:

    Match match_state;
    int winner_index;

};




#endif //CURSEN_GAMEOVER_H
