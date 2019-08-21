//
// Created by Brandon Martin on 7/28/19.
//

#ifndef CURSEN_ENTERMATCH_H
#define CURSEN_ENTERMATCH_H

#include <Uno/Data/DataManager.h>
#include "DataMessage.h"

class EnterMatch : public DataMessage
{

public:

    EnterMatch() = default;

    MessageType getType() override
    {
        return MessageType::EnterMatch;
    }

    Context getContext() override
    {
        return Context::ContextLobby;
    }

    void execute() override
    {
        CONTEXT_CHECK_BEGIN

            LobbyForm* lobbyForm = GetCurrentForm<LobbyForm>();
            lobbyForm->enterMatch();

        CONTEXT_CHECK_END
    }

    DataMessage* clone() override
    {
        return new EnterMatch(*this);
    }

    size_t sizeOf() const override
    {
        return sizeof(EnterMatch);
    };

private:

};

#endif //CURSEN_ENTERMATCH_H
