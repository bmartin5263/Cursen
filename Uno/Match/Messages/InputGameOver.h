//
// Created by Brandon Martin on 8/11/19.
//

#ifndef CURSEN_INPUTGAMEOVER_H
#define CURSEN_INPUTGAMEOVER_H

#include <Uno/Forms/MatchForm.h>
#include "Uno/Data/DataManager.h"
#include "GameOver.h"

class InputGameOver : public DataMessage
{
public:

    InputGameOver() = default;
    InputGameOver(int winner_index) :
            winner_index(winner_index)
    {}

    MessageType getType() override
    {
        return MessageType::InputGameOver;
    }

    Context getContext() override
    {
        return Context::ContextMatch;
    }

    void execute() override
    {
        CONTEXT_CHECK_BEGIN

        MatchForm* matchForm = GetCurrentForm<MatchForm>();
        Match& match = matchForm->getMatch();

        DataMessage* msg = new GameOver(winner_index, match);
        msg->setSendType(SendType::Both);
        DataManager::PushMessage(msg);

        CONTEXT_CHECK_END
    }

    DataMessage* clone() override
    {
        return new InputGameOver(*this);
    }

    size_t serialize(char* const buffer) const override
    {
        size_t written = DataMessage::serialize(buffer);

        written += Serializable::Serialize(buffer + written, winner_index);

        return written;
    }

    size_t deserialize(const char* const buffer) override
    {
        size_t read = DataMessage::deserialize(buffer);

        read += Serializable::Deserialize(buffer + read, winner_index);

        return read;
    }

private:

    int winner_index;

};


#endif //CURSEN_INPUTGAMEOVER_H
