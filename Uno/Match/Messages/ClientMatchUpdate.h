//
// Created by Brandon Martin on 7/28/19.
//

#ifndef CURSEN_MATCHUPDATE_H
#define CURSEN_MATCHUPDATE_H

#include <Uno/Messages/DataMessage.h>
#include <Uno/GameObjects/ClientMatch.h>
#include <Uno/Data/DataManager.h>
#include <Uno/Forms/MatchForm.h>

class ClientMatchUpdate : public DataMessage
{
public:

    ClientMatchUpdate() = default;
    ClientMatchUpdate(ClientMatch clientMatch) : clientMatch(clientMatch)
    {};

    MessageType getType() override
    {
        return MessageType::ClientMatchUpdate;
    }

    Context getContext() override
    {
        return Context::ContextMatch;
    }

    void execute() override
    {
        CONTEXT_CHECK_BEGIN

            MatchForm* matchForm = GetCurrentForm<MatchForm>();
            matchForm->updateMatch(clientMatch);

        CONTEXT_CHECK_END
    }

    DataMessage* clone() override
    {
        return new ClientMatchUpdate(*this);
    }

    size_t serialize(char* const buffer) const override
    {
        size_t written = DataMessage::serialize(buffer);

        written += clientMatch.serialize(buffer + written);

        return written;
    }

    size_t deserialize(const char* const buffer) override
    {
        size_t read = DataMessage::deserialize(buffer);

        read += clientMatch.deserialize(buffer + read);

        return read;
    }

private:

    ClientMatch clientMatch;

};

#endif //CURSEN_MATCHUPDATE_H
