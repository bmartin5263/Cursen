//
// Created by Brandon Martin on 5/20/19.
//

#ifndef CURSEN_LOBBYCONTROLLER_H
#define CURSEN_LOBBYCONTROLLER_H

#ifndef UNUSED_VAR
    #define UNUSED_VAR(x) (void)x;
#endif

#ifndef UNUSED_PTR
    #define UNUSED_PTR(x) (void*)x;
#endif

#include "../Forms/LobbyForm.h"

class LobbyController
{

public:

    LobbyController(LobbyForm* lobbyForm) :
        lobbyForm(lobbyForm)
    {};
    virtual ~LobbyController() = default;

    virtual void initialize() = 0;
    virtual void clickStart() = 0;          // HOST, LOCAL
    virtual void clickAddAI() = 0;          // HOST, LOCAL
    virtual void clickSearch() = 0;         // HOST
    virtual void clickClose() = 0;          // HOST, CLIENT, LOCAL
    virtual void clickChangeColor() = 0;    // HOST, CLIENT, LOCAL
    virtual void sendChat() = 0;           // HOST, CLIENT
    virtual void selectPlayerToKick(int id) = 0;

    virtual void handleInputColorChange(int sender) = 0;

    virtual void handleClose(std::string msg, bool kicked) = 0;
    virtual void handleStartSearch() = 0;
    virtual void handleStopSearch() = 0;

    virtual void handleAddPlayer(Player new_player) = 0;
    virtual void handleRequestJoinLobby(const std::string& name, int sock_fd) = 0;
    virtual void handleUpdatePlayer(const Player& player, int index) = 0;

    virtual void sendKickMessages(int id) = 0;
    virtual void handleKickPlayer(int id) = 0;
    virtual void handleDisconnect(int sock) = 0;
    virtual void sendCloseMessages() = 0;

    virtual void handleEnterMatch() = 0;

protected:

    LobbyForm* lobbyForm;

};


#endif //CURSEN_LOBBYCONTROLLER_H
