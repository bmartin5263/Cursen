//
// Created by Brandon Martin on 5/20/19.
//

#ifndef CURSEN_LOCALCONTROLLER_H
#define CURSEN_LOCALCONTROLLER_H

#include "LobbyController.h"

class LocalController : public LobbyController
{
public:

    LocalController(LobbyForm* form);
    void initialize() override;
    void clickStart() override;
    void clickAddAI() override;
    void clickSearch() override;
    void clickClose() override;
    void clickChangeColor() override;
    void sendChat() override;

    void handleClose(std::string msg, bool kicked) override;
    void handleStartSearch() override;
    void handleStopSearch() override;
    void handleKickPlayer(int index) override;
    void handleInputKick(int index) override;
    void handleDisconnect(int sock) override;
    void sendCloseMessages() override;
    void handleEnterMatch() override;
    void handleAddPlayer(Player new_player) override;
    void handleRequestJoinLobby(const std::string& name, int sock_fd) override;
    void handleUpdatePlayer(const Player& player, int index) override;
    void handleInputColorChange(int sender) override;
    void handleChatInput(int sender, const std::string& message) override;
};


#endif //CURSEN_LOCALCONTROLLER_H
