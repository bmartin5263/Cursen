//
// Created by Brandon Martin on 7/19/19.
//

#ifndef CURSEN_INPUTBEGINGAME_H
#define CURSEN_INPUTBEGINGAME_H

#include "Uno/Data/DataManager.h"
#include "Uno/Messages/DataMessage.h"
#include "Uno/Match/FSM/MatchInputState.h"
#include "Uno/Forms/MatchForm.h"
#include "Uno/GameObjects/Match.h"
#include "BeginGame.h"

class InputBeginGame : public DataMessage
{
public:

    InputBeginGame() = default;

    InputBeginGame(int id) : id(id)
    {}

    MessageType getType() override
    {
        return MessageType::InputBeginGame;
    }

    Context getContext() override
    {
        return Context::Match;
    }

    void execute() override
    {
        CONTEXT_CHECK_BEGIN

            MatchForm* matchForm = GetCurrentForm<MatchForm>();
            if (matchForm->getMatch().getMyId() == id)
            {

                const Card& initial_card = matchForm->getMatch().getDeck().peekCard();

                DataMessage* msg = new BeginGame(initial_card);
                msg->setSendType(SendType::Both);
                DataManager::PushMessage(msg);
            }

        CONTEXT_END
    }

    DataMessage* clone() override
    {
        return new InputBeginGame(*this);
    }

    size_t serialize(char* const buffer) const override
    {
        size_t written =  DataMessage::serialize(buffer);

        written += Serializable::Serialize(buffer + written, id);

        return written;
    }

    size_t deserialize(const char* const buffer) override
    {
        size_t read = DataMessage::deserialize(buffer);

        read += Serializable::Deserialize(buffer + read, id);

        return read;
    }

private:

    int id;

};

#endif //CURSEN_INPUTBEGINGAME_H
