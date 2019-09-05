//
// Created by Brandon Martin on 5/20/19.
//

#ifndef CURSEN_CLIENTCONTROLLER_H
#define CURSEN_CLIENTCONTROLLER_H


#include "LobbyController.h"

class ClientController : public LobbyController
{
public:

    ClientController(LobbyForm* form);
    void initialize() override;
    void clickStart() override;
    void clickAddAI() override;
    void clickSearch() override;
    void clickClose() override;
    void clickChangeColor() override;
    void sendChat() override;
    void selectPlayerToKick(int id) override;
    void handleClose(std::string msg, bool kicked) override;
    void handleStartSearch() override;
    void handleStopSearch() override;
    void handleKickPlayer(int id) override;
    void sendKickMessages(int id) override;
    void handleDisconnect(int sock) override;
    void sendCloseMessages() override;
    void handleEnterMatch() override;
    void handleAddPlayer(Player new_player) override;
    void handleRequestJoinLobby(const std::string& name, int sock_fd) override;
    void handleUpdatePlayer(const Player& player, int index) override;
    void handleInputColorChange(int sender) override;

};


#endif //CURSEN_CLIENTCONTROLLER_H
