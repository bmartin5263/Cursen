//
// Created by Brandon Martin on 6/12/19.
//

#ifndef CURSEN_REQUESTLEAVELOBBY_H
#define CURSEN_REQUESTLEAVELOBBY_H

#include "Uno/Data/DataManager.h"

class RequestLeaveLobby : public DataMessage
{
public:

    RequestLeaveLobby() = default;

    RequestLeaveLobby(int id) :
        id(id)
    {};

    MessageType getType() override
    {
        return MessageType::RequestLeaveLobby;
    }

    Context getContext() override
    {
        return Context::Lobby;
    }

    void execute() override
    {
        if (DataManager::GetContext() == getContext())
        {
        }
    }

    DataMessage* clone() override
    {
        return new RequestLeaveLobby(*this);
    }

private:

    int id;


};

#endif //CURSEN_REQUESTLEAVELOBBY_H
