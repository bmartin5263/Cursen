//
// Created by Brandon Martin on 6/4/19.
//

#ifndef CURSEN_CHATLOG_H
#define CURSEN_CHATLOG_H

#include "Cursen/Components/TextComponent.h"
#include "Uno/GameObjects/Lobby.h"
#include "Uno/Other/ChatEntry.h"

class ChatLog : public cursen::TextComponent
{

public:

    ChatLog();
    ChatLog(const cursen::Vect2& pos);
    void initialize() override;
    void render() override;

    void setLobby(Lobby* lobby);

    void pushMessage(ChatEntry entry);
    void reassignColor(int id, PlayerColor color);
    void clear();

private:

    Lobby* lobby;

    ChatEntry entries[9];

    short blue_pair;
    short red_pair;
    short yellow_pair;
    short green_pair;
    short purple_pair;
    short orange_pair;

};


#endif //CURSEN_CHATLOG_H
