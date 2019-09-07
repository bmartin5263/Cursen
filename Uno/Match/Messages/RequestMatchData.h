//
// Created by Brandon Martin on 7/28/19.
//

#ifndef CURSEN_REQUESTMATCHDATA_H
#define CURSEN_REQUESTMATCHDATA_H

#include <Uno/Messages/DataMessage.h>
#include <Uno/Data/DataManager.h>
#include <Uno/Forms/MatchForm.h>
#include <Uno/GameObjects/Match.h>
#include "ClientMatchUpdate.h"

class RequestMatchData : public DataMessage
{
public:

    RequestMatchData() = default;
    RequestMatchData(int id) : id(id)
    {};

    MessageType getType() override
    {
        return MessageType::RequestMatchData;
    }

    Context getContext() override
    {
        return Context::Match;
    }

    void execute() override
    {
        CONTEXT_CHECK_BEGIN

            MatchForm* matchForm = GetCurrentForm<MatchForm>();
            Match& match = matchForm->getMatch();
            if (match.hasId(id))
            {
                matchForm->getController()->handleRequestMatch(id, getSender());
            }

        CONTEXT_END
    }

    DataMessage* clone() override
    {
        return new RequestMatchData(*this);
    }

    size_t serialize(char* const buffer) const override
    {
        size_t written = DataMessage::serialize(buffer);

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

#endif //CURSEN_REQUESTMATCHDATA_H
