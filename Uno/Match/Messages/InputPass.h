//
// Created by Brandon Martin on 8/11/19.
//

#ifndef CURSEN_INPUTPASS_H
#define CURSEN_INPUTPASS_H

#include <Uno/Constants.h>
#include "Uno/Data/DataManager.h"
#include "Uno/Forms/MatchForm.h"
#include "Uno/Match/MatchController.h"
#include "Uno/GameObjects/Match.h"
#include "IllegalAction.h"
#include "PassTurn.h"

class InputPass : public DataMessage
{

public:

    InputPass() = default;
    InputPass(int id) :
            id(id)
    {}

    MessageType getType() override
    {
        return MessageType::InputPass;
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
            int index = match.getIndex(id);
            if (match.canPass(index))
            {
                if (match.getConsecutivePasses() + 1 >= match.getNumPlayers())
                {
                    CardColor new_color = Constants::getRandomCardColor(match.getPile().peekCard().getColor());
                    DataMessage* msg = new PassTurn(new_color);
                    msg->setSendType(SendType::Both);
                    DataManager::PushMessage(msg);
                }
                else
                {
                    DataMessage* msg = new PassTurn(CardColor::WHITE);
                    msg->setSendType(SendType::Both);
                    DataManager::PushMessage(msg);
                }
            }
            else
            {
                std::string msg;
                if (match.getDeck().size() > 0)
                {
                    msg = "Can't pass while the deck has cards";
                }
                else
                {
                    msg = "Can't pass with playable cards";
                }
                DataMessage* data_msg = new IllegalAction(msg);
                data_msg->setSendType(SendType::Network);
                data_msg->setRecipient(getSender());
                data_msg->setRecipientType(RecipientType::Single);
                DataManager::PushMessage(data_msg);
            }

        CONTEXT_CHECK_END
    }

    DataMessage* clone() override
    {
        return new InputPass(*this);
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


#endif //CURSEN_INPUTPASS_H
