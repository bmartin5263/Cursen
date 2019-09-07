//
// Created by Brandon Martin on 4/11/19.
//

#ifndef CURSEN_LOBBY_H
#define CURSEN_LOBBY_H

#include "Uno/Messages/Serializable.h"
#include "LobbyType.h"
#include "Player.h"
#include "Uno/Other/ChatEntry.h"

class Lobby : public Serializable {

public:

    static const int MAX_PLAYERS = 4;
    static const int MIN_PLAYERS_TO_START = 2;
    static const int MAX_CHAT = 9;

    Lobby();
    virtual ~Lobby() = default;

    Player createPlayer(std::string name, PlayerColor color);
    Player createAI(std::string name, PlayerColor color);
    Player createDummy();

    void addPlayer(Player player);
    void setPlayer(const Player& player, int index);

    void removePlayer(int index);

    Player& getPlayer(int index);
    Player* getPlayers();

    void changePlayerColor(int index, PlayerColor color);

    PlayerColor getPlayerColor(int player_index) const;
    int getNumPlayers() const;

    void pushMessage(ChatEntry msg);
    void removeMessages(int index);
    ChatEntry* getMessages();

    void startSearch();
    void stopSearch();
    bool isSearching() const;

    bool colorTaken(PlayerColor color) const;

    int getMyId();
    void setMyId(int id);

    void setMyIndex(int index);
    int getMyIndex();

    PlayerColor getAvailableColor() const;
    PlayerColor getAvailableColorRGBY() const;

    size_t serialize(char* const buffer) const override;
    size_t deserialize(const char* const buffer) override;
    size_t sizeOf() const override;

private:

    bool idTaken(int id);

    Player players[MAX_PLAYERS];
    ChatEntry chat_messages[MAX_CHAT];
    int my_id;
    int my_index;
    int numPlayers;
    bool searching;

};


#endif //CURSEN_LOBBY_H
