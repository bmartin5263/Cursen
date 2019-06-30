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

    static const int MAX_MESSAGES = 9;

    ChatLog();
    ChatLog(const cursen::Vect2& pos);
    void initialize() override;
    void render() override;

    void clear();
    void update(ChatEntry* messages);

private:

    ChatEntry entries[MAX_MESSAGES];

};


#endif //CURSEN_CHATLOG_H
