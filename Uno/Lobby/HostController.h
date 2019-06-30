//
// Created by Brandon Martin on 5/20/19.
//

#ifndef CURSEN_HOSTCONTROLLER_H
#define CURSEN_HOSTCONTROLLER_H

#include <map>

#include "LobbyController.h"

class HostController : public LobbyController
{
public:

    HostController(LobbyForm* lobbyForm);
    void initialize() override;
    void destroy() override;
    void clickStart() override;
    void clickAddAI() override;
    void clickSearch() override;
    void clickClose() override;
    void clickChangeColor() override;
    void sendChat() override;
    void selectPlayerToKick(int id) override;

    void handleClose(std::string msg, bool kicked) override;
    void handleStartSearch() override ;
    void handleStopSearch() override ;
    void handleAddAi(Player new_ai) override;

    void putSocket(int playerId, int sock);

    void handleKickPlayer(int id) override;
    void sendKickMessages(int id) override;
    void handleDisconnect(int sock) override;
    void sendCloseMessages() override;

private:

    std::map<int, int> socket_map;

};


#endif //CURSEN_HOSTCONTROLLER_H
