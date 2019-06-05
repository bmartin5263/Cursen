//
// Created by Brandon Martin on 6/4/19.
//

#include "ChatEntry.h"

ChatEntry::ChatEntry() :
    id(-1), message("null")
{

}

ChatEntry::ChatEntry(int id, std::string message, PlayerColor color) :
    id(id), message(message), color(color)
{

}

void ChatEntry::setColor(PlayerColor color)
{
    this->color = color;
}
