//
// Created by Brandon Martin on 4/10/19.
//

#ifndef CURSEN_LOBBYFORM_H
#define CURSEN_LOBBYFORM_H

#include "Cursen/Components/TextField.h"
#include "Cursen/Components/Form.h"
#include "Cursen/Components/Button.h"
#include "Cursen/Components/ASCIIArt.h"
#include "Cursen/Cursor/Cursor.h"
#include "Uno/Components/LobbyGlowBorder.h"
#include "Uno/Components/UnoConsole.h"
#include "Uno/Components/PlayerStaging.h"
#include "Uno/Components/ModeSelectBox.h"
#include "Uno/GameObjects/Lobby.h"
#include "Uno/Components/ChatBox.h"

class Lobby;
class LobbyController;

class LobbyForm : public cursen::Form {

public:

    LobbyForm();
    void initialize() override;
    void cleanLobby(std::string exit_message, bool was_kicked);

    void initializeForLocal();
    void initializeForHost();
    void initializeForClient();

    void startSearch();
    void stopSearch();

    void enableRemovePlayerCursor();
    void selectPlayerToRemove(int index);
    void sendInputRemovePlayer(int index);
    void kickPlayer(int index);

    void setMainPlayerName();

    void tryJoin();

    void updateLobby(Lobby& lobby);

    void startChat();
    void stopChat();

    void addPlayerToStaging(const Player& player);
    void removePlayerFromStaging(int index);
    void setPlayerToStaging(const Player& player, int index);

    void changeColor(int playerId, PlayerColor color);
    void pushChatMessage(int player_index, std::string message);
    //void addPlayer(Player p, int sock);

    void enterMatch();

    UnoConsole& getConsole() { return this->console; };
    Lobby& getLobby();
    ChatBox& getChatBox() { return this->chat_box; };
    LobbyController& getController() { return *this->controller; }
    PlayerStaging& getPlayerStaging() { return playerStaging; }
    ModeSelectBox& getModeSelectBox() { return mode_select_box; }
    cursen::Button& getSearchButton() { return search_button; }

private:

    // Instance Data
    Lobby* lobby;
    LobbyController* controller;

    // Components
    cursen::ASCIIArt art;
    cursen::Box border;
    cursen::Button start_button;
    cursen::Button add_ai_button;
    cursen::Button search_button;
    cursen::Button kick_button;
    cursen::Button close_button;
    cursen::Button change_color_button;
    cursen::Button chat_button;
    cursen::TextField text_field;
    cursen::Cursor lobby_cursor;

    UnoConsole console;
    PlayerStaging playerStaging;
    ChatBox chat_box;
    ModeSelectBox mode_select_box;
    LobbyGlowBorder glowBorder;

    //Player my_player;

};


#endif //CURSEN_LOBBYFORM_H
