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

    void leaveLocal();
    void leaveHost();
    void leaveClient(std::string msg, bool kicked);

    void startSearch();
    void stopSearch();

    void enableRemovePlayerCursor();
    void selectPlayerToRemove(int index);
    void removePlayer(int index);

    void setMainPlayerName();

    void clickStart();
    void clickAddAI();
    void clickSearch();
    void clickKick();
    void clickClose();
    void clickSettings();
    void clickLocal();
    void clickHost();
    void clickJoin();
    void clickExit();
    void clickChangeColor();
    void clickChat();

    void tryJoin();

    // Inline because CLion is reporting non-existent errors
    void updateLobby(Lobby& lobby)
    {
        if (this->lobby == nullptr)
        {
            this->lobby = new Lobby(lobby);
            initializeForClient();
        }
        else {
            *this->lobby = lobby;
        }

        chat_box.update(lobby.getMessages());
        playerStaging.update(lobby);
        if (lobby.isSearching())
        {
            startSearch();
        }
        else {
            stopSearch();
        }
    };

    void startChat();
    void stopChat();
    void sendChatMessage();

    void changeColor(int playerId, PlayerColor color);
    void pushChatMessage(int playerId, std::string message);
    void addPlayer(Player p, int sock);

    void enterMatch();

    UnoConsole& getConsole() { return this->console; };
    Lobby& getLobby();
    ChatBox& getChatBox() { return this->chat_box; };
    LobbyController& getController() { return *this->controller; }
    PlayerStaging& getPlayerStaging() { return playerStaging; }
    cursen::Button& getSearchButton() { return search_button; }

    void requestAI();
    void requestClient(int sock_id, std::string name);
    void kickPlayer(int id);

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
