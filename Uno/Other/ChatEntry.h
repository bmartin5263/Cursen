//
// Created by Brandon Martin on 6/4/19.
//

#ifndef CURSEN_CHATENTRY_H
#define CURSEN_CHATENTRY_H

#include <string>

#include "Uno/GameObjects/PlayerColor.h"

class ChatEntry
{

public:

    ChatEntry();
    ChatEntry(int id, std::string message, PlayerColor color);

    void setColor(PlayerColor color);

    bool isNull() { return id == -1; }
    PlayerColor getColor() { return color; }
    std::string& getMessage() { return message; }
    int getId() { return id; }

private:

    int id;
    PlayerColor color;
    std::string message;

};


#endif //CURSEN_CHATENTRY_H
