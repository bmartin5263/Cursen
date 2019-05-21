//
// Created by Brandon Martin on 5/20/19.
//

#ifndef CURSEN_LOBBYCONTROLLER_H
#define CURSEN_LOBBYCONTROLLER_H


#include "../Forms/LobbyForm.h"

class LobbyController
{

public:

    LobbyController(LobbyForm* lobbyForm) :
        lobbyForm(lobbyForm)
    {};
    virtual ~LobbyController() = default;

    virtual void initialize() = 0;
    virtual void destroy() = 0;
    virtual void clickStart() = 0;          // HOST, LOCAL
    virtual void clickAddAI() = 0;          // HOST, LOCAL
    virtual void clickSearch() = 0;         // HOST
    virtual void clickKick() = 0;           // HOST, LOCAL
    virtual void clickClose() = 0;          // HOST, CLIENT, LOCAL
    virtual void clickChangeColor() = 0;    // HOST, CLIENT, LOCAL
    virtual void clickChat() = 0;           // HOST, CLIENT


protected:

    LobbyForm* lobbyForm;

};


#endif //CURSEN_LOBBYCONTROLLER_H
