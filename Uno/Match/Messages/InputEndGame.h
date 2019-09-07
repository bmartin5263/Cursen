//
// Created by Brandon Martin on 8/22/19.
//

#ifndef CURSEN_INPUTENDGAME_H
#define CURSEN_INPUTENDGAME_H

#include <Uno/Forms/MatchForm.h>
#include "Uno/Data/DataManager.h"
#include "EndGame.h"

class InputEndGame : public DataMessage
{
public:

    InputEndGame() = default;

    MessageType getType() override
    {
        return MessageType::InputEndGame;
    }

    Context getContext() override
    {
        return Context::Match;
    }

    void execute() override
    {
        CONTEXT_CHECK_BEGIN

        DataMessage* msg = new EndGame;
        msg->setSendType(SendType::Both);
        DataManager::PushMessage(msg);

        CONTEXT_END
    }

    DataMessage* clone() override
    {
        return new InputEndGame(*this);
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

#endif //CURSEN_INPUTENDGAME_H
