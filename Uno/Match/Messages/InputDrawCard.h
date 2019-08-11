//
// Created by Brandon Martin on 7/20/19.
//

#ifndef CURSEN_INPUTDRAWCARDS_H
#define CURSEN_INPUTDRAWCARDS_H

#include <Uno/Data/DataManager.h>
#include <Uno/Forms/MatchForm.h>
#include "Uno/Messages/DataMessage.h"
#include "Uno/GameObjects/Match.h"
#include "DrawCard.h"

class InputDrawCard : public DataMessage
{
public:

    InputDrawCard() = default;
    InputDrawCard(int id) :
        id(id)
    {}

    MessageType getType() override
    {
        return MessageType::InputDrawCard;
    }

    Context getContext() override
    {
        return Context::ContextMatch;
    }

    void execute() override
    {
        CONTEXT_CHECK_BEGIN

            MatchForm* matchForm = getCurrentForm<MatchForm>();
            Match& match = matchForm->getMatch();
            if (match.canDrawCard(id))
            {
                int index = match.getIndex(id);
                Card drawn_card = match.peekCardFromDeck();

                DataMessage* msg = new DrawCard(index, drawn_card);
                msg->setSendType(SendType::Local);
                DataManager::PushMessage(msg);

                if (id == match.getMyId())
                {
                    msg = new DrawCard(index, Card());
                    msg->setSendType(SendType::Network);
                    DataManager::PushMessage(msg);
                }
                else
                {
                    msg = new DrawCard(index, drawn_card);
                    msg->setSendType(SendType::Network);
                    msg->setRecipient(getSender());
                    msg->setRecipientType(RecipientType::Single);
                    DataManager::PushMessage(msg);

                    msg = new DrawCard(index, Card());
                    msg->setSendType(SendType::Network);
                    msg->setRecipient(getSender());
                    msg->setRecipientType(RecipientType::Broadcast_Except_Recipient);
                    DataManager::PushMessage(msg);
                }
            }

        CONTEXT_CHECK_END
    }

    DataMessage* clone() override
    {
        return new InputDrawCard(*this);
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


#endif //CURSEN_INPUTDRAWCARDS_H
