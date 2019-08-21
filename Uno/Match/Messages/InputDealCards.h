//
// Created by Brandon Martin on 7/14/19.
//

#ifndef CURSEN_INPUTENTERMESSAGE_H
#define CURSEN_INPUTENTERMESSAGE_H

#include "Uno/Data/DataManager.h"
#include "Uno/Messages/DataMessage.h"
#include "Uno/Match/FSM/MatchInputState.h"
#include "Uno/Forms/MatchForm.h"
#include "Uno/GameObjects/Match.h"
#include "DealCards.h"
#include "BeginGame.h"

class InputDealCards : public DataMessage
{
public:

    InputDealCards() = default;

    InputDealCards(int id) : id(id)
    {}

    MessageType getType() override
    {
        return MessageType::InputDealCards;
    }

    Context getContext() override
    {
        return Context::ContextMatch;
    }

    void execute() override
    {
        CONTEXT_CHECK_BEGIN

            MatchForm* matchForm = GetCurrentForm<MatchForm>();
            if (matchForm->getMatch().getMyId() == id)
            {
                DataMessage* msg = new DealCards;
                msg->setSendType(SendType::Both);
                DataManager::PushMessage(msg);
            }

        CONTEXT_CHECK_END
    }

    DataMessage* clone() override
    {
        return new InputDealCards(*this);
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

#endif //CURSEN_INPUTENTERMESSAGE_H
