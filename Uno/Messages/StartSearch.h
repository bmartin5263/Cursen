//
// Created by Brandon Martin on 6/12/19.
//

#ifndef CURSEN_STARTSEARCH_H
#define CURSEN_STARTSEARCH_H

#include "Uno/Data/DataManager.h"
#include "Uno/Forms/LobbyForm.h"
#include "Cursen/CursenApplication.h"
#include "Uno/Lobby/LobbyController.h"

class StartSearch : public DataMessage {

public:

    MessageType getType() override
    {
        return MessageType::StartSearch;
    }

    Context getContext() override
    {
        return Context::ContextLobby;
    }

    void execute() override
    {
        CONTEXT_CHECK_BEGIN

            LobbyForm* lobbyForm = GetCurrentForm<LobbyForm>();
            lobbyForm->getController().handleStartSearch();

        CONTEXT_CHECK_END
    }

    DataMessage* clone() override
    {
        return new StartSearch(*this);
    }

    size_t sizeOf() const override
    {
        return sizeof(StartSearch);
    }

};

#endif //CURSEN_STARTSEARCH_H
