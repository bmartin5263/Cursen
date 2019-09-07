//
// Created by Brandon Martin on 7/28/19.
//

#ifndef CURSEN_MATCHCONNECTIONSEVERED_H
#define CURSEN_MATCHCONNECTIONSEVERED_H

#include <Uno/Forms/MatchForm.h>
#include "Uno/Data/DataManager.h"
#include "Uno/Match/MatchController.h"

class MatchConnectionSevered : public DataMessage {

public:

    MatchConnectionSevered() = default;

    MatchConnectionSevered(int sock) :
            sock(sock)
    {
    }

    MessageType getType() override
    {
        return MessageType::MatchConnectionSevered;
    }

    Context getContext() override
    {
        return Context::Match;
    }

    void execute() override
    {
        CONTEXT_CHECK_BEGIN

            MatchForm* matchForm = GetCurrentForm<MatchForm>();
            matchForm->getController()->handleDisconnect(getSender());

        CONTEXT_END
    }

    DataMessage* clone() override
    {
        return new MatchConnectionSevered(*this);
    }

    size_t serialize(char* const buffer) const override
    {
        size_t written = DataMessage::serialize(buffer);

        written += Serializable::Serialize(buffer + written, sock);

        return written;
    }

    size_t deserialize(const char* const buffer) override
    {
        size_t read = DataMessage::deserialize(buffer);

        read += Serializable::Deserialize(buffer + read, sock);

        return read;
    }

private:

    int sock;

};

#endif //CURSEN_MATCHCONNECTIONSEVERED_H
