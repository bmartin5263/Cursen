//
// Created by Brandon Martin on 4/11/19.
//

#include <cassert>
#include "Lobby.h"
#include "../Constants.h"

Lobby::Lobby() :
    my_id(-1), numPlayers(0), searching(false)
{
}

void Lobby::addPlayer(Player player) {
    if (numPlayers >= MAX_PLAYERS) {
        assert(false);
    }
    players[numPlayers++] = player;
}

void Lobby::removePlayer(const int id) {
    if (numPlayers <= 0) {
        assert(false);
    }

    int i;
    for (i = 0; i < numPlayers; ++i)
    {
        if (players[i].getId() == id)
        {
            players[i] = Player();
            numPlayers--;

            for (int j = i + 1; j < MAX_PLAYERS; j++) {
                players[j-1] = players[j];
            }
        }
    }
    removeMessageById(id);
}

Player& Lobby::getPlayer(const int id) {
    for (auto& player : players)
    {
        if (player.getId() == id)
        {
            return player;
        }
    }
    assert(false);
    return players[0];
}

Player& Lobby::getPlayerByIndex(const int index)
{
    assert(index >= 0 && index <= MAX_PLAYERS);
    return players[index];
}

PlayerColor Lobby::getPlayerColor(const int id) const
{
    for (auto& player : players)
    {
        if (player.getId() == id)
        {
            return player.getColor();
        }
    }
    return PlayerColor::GRAY;
}

int Lobby::getNumPlayers() const {
    return numPlayers;
}

void Lobby::startSearch() {
    searching = true;
}

void Lobby::stopSearch() {
    searching = false;
}

bool Lobby::isSearching() const {
    return searching;
}

PlayerColor Lobby::getAvailableColor() const {
    static int i = 0;

    int start = i;
    while (true) {
        PlayerColor color = Constants::COLORS[i];
        i = (i + 1) % Constants::NUM_COLORS;
        bool ok = true;
        for (int j = 0; j < numPlayers; j++) {
            if (players[j].getColor() == color) {
                ok = false;
                break;
            }
        }
        if (ok) return color;
        if (i == start) assert(false);
    }
}

PlayerColor Lobby::getAvailableColorRGBY() const {
    static int i = 0;

    int num_colors_rgb = Constants::NUM_COLORS - 2;
    int start = i;
    while (true) {
        PlayerColor color = Constants::COLORS[i];
        if (!colorTaken(color)) return color;
        i = (i + 1) % num_colors_rgb;
        if (i == start) assert(false);
    }
}

bool Lobby::colorTaken(PlayerColor color) const
{
    for (int j = 0; j < numPlayers; j++) {
        if (players[j].getColor() == color) {
           return true;
        }
    }
    return false;
}

size_t Lobby::serialize(char* const buffer) const
{
    size_t written = 0;
    written += Serializable::Serialize(buffer + written, numPlayers);
    for (int i = 0; i < numPlayers; ++i)
    {
        written += players[i].serialize(buffer + written);
    }
    for (int i = 0; i < MAX_CHAT; i++)
    {
        written += chat_messages[i].serialize(buffer + written);
    }
    written += Serializable::Serialize(buffer + written, searching);
    written += Serializable::Serialize(buffer + written, my_id);
    return written;
}

size_t Lobby::deserialize(const char* const buffer)
{
    size_t read = 0;
    read += Serializable::Deserialize(buffer + read, numPlayers);
    for (int i = 0; i < numPlayers; ++i)
    {
        read += players[i].deserialize(buffer + read);
    }
    for (int i = 0; i < MAX_CHAT; ++i)
    {
        read += chat_messages[i].deserialize(buffer + read);
    }
    read += Serializable::Deserialize(buffer + read, searching);
    read += Serializable::Deserialize(buffer + read, my_id);
    return read;
}

size_t Lobby::sizeOf() const
{
    return sizeof(Lobby);
}

void Lobby::pushMessage(ChatEntry msg)
{
    for (int i = 0; i < 8; i++)
    {
        chat_messages[i] = chat_messages[i+1];
    }
    chat_messages[8] = msg;
}

void Lobby::removeMessageById(int id)
{
    for (int i = 0; i < 9; i++) {
        if (chat_messages[i].getId() == id)
        {
            chat_messages[i].setNull();
        }
    }
}

ChatEntry* Lobby::getMessages()
{
    return chat_messages;
}

void Lobby::changePlayerColorById(const int id, PlayerColor color)
{
    for (auto& player : players)
    {
        if (player.getId() == id)
        {
            player.setColor(color);
            for (auto& message : chat_messages) {
                if (message.getId() == id)
                {
                    message.setColor(color);
                }
            }
        }
    }
}

int Lobby::getMyId()
{
    return my_id;
}

void Lobby::setMyId(int id)
{
    my_id = id;
}

Player Lobby::createPlayer(std::string name, PlayerColor color)
{
    // Create a player with a random id
    int id;
    do {
        id = rand();
    }
    while (idTaken(id));
    return Player(name, color, id, false);
}

Player Lobby::createAI(std::string name, PlayerColor color)
{
    // Create an ai with a random id
    int id;
    do {
        id = rand();
    }
    while (idTaken(id));
    return Player(name, color, id, true);
}


bool Lobby::idTaken(int id)
{
    for (int i = 0; i < numPlayers; i++)
    {
        if (players[i].getId() == id) return true;
    }
    return false;
}

bool Lobby::hasId(const int id)
{
    for (auto& player : players)
    {
        if (player.getId() == id)
        {
            return true;
        }
    }
    return false;
}

Player* Lobby::getPlayers()
{
    return players;
}