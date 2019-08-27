//
// Created by Brandon Martin on 7/21/19.
//

#ifndef CURSEN_INPUTPLAYCARD_H
#define CURSEN_INPUTPLAYCARD_H

#include "Uno/Messages/DataMessage.h"
#include "Uno/Data/DataManager.h"
#include "Uno/Forms/MatchForm.h"
#include "Uno/Match/MatchController.h"
#include "Uno/GameObjects/Match.h"
#include "PlayCard.h"
#include "IllegalAction.h"

class InputPlayCard : public DataMessage
{
public:

    InputPlayCard() = default;
    InputPlayCard(int id, int card_index) :
        id(id), card_index(card_index)
    {}

    MessageType getType() override
    {
        return MessageType::InputPlayCard;
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
            if (index != -1 && match.canPlayCard(index, card_index))
            {
                Card played_card = match.getCardFromPlayer(index, card_index);
                DataMessage* msg = new PlayCard(index, card_index, played_card);
                msg->setSendType(SendType::Both);
                DataManager::PushMessage(msg);
            }
            else
            {
                std::string reason;
                if (match.getCurrentTurn() != index)
                {
                    reason = "Can't play a card when it isn't your turn!";
                }
                else if (match.getCardFromPlayer(index, card_index).getValue() == CardValue::DRAW_4)
                {
                    reason = "Can't play +4 card unless it is the only playable card in your hand!";
                }
                else
                {
                    const Card& top_card = match.getPile().peekCard();
                    std::string color_str = Card::ToString(top_card.getColor());
                    std::string value_str = Card::ToString(top_card.getValue());
                    reason =  "Card does not have the color " + color_str + " or the value " + value_str + "!";
                }
                DataMessage* data_msg = new IllegalAction(reason);
                data_msg->setSendType(SendType::Network);
                data_msg->setRecipient(getSender());
                data_msg->setRecipientType(RecipientType::Single);
                DataManager::PushMessage(data_msg);
            }

        CONTEXT_CHECK_END
    }

    DataMessage* clone() override
    {
        return new InputPlayCard(*this);
    }

    size_t serialize(char* const buffer) const override
    {
        size_t written =  DataMessage::serialize(buffer);

        written += Serializable::Serialize(buffer + written, id);
        written += Serializable::Serialize(buffer + written, card_index);

        return written;
    }

    size_t deserialize(const char* const buffer) override
    {
        size_t read = DataMessage::deserialize(buffer);

        read += Serializable::Deserialize(buffer + read, id);
        read += Serializable::Deserialize(buffer + read, card_index);

        return read;
    }

private:

    int id;
    int card_index;

};

#endif //CURSEN_INPUTPLAYCARD_H
