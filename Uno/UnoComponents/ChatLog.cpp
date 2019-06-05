//
// Created by Brandon Martin on 6/4/19.
//

#include "ChatLog.h"
#include "Cursen/Drawing/CursesManager.h"

using namespace cursen;

ChatLog::ChatLog() :
        TextComponent(), lobby(nullptr)
{

}

ChatLog::ChatLog(const cursen::Vect2& pos) : TextComponent(pos), lobby(nullptr)
{

}

void ChatLog::initialize()
{
    blue_pair = CursesManager::GetColorPair(ColorPair(Color::BLUE));
    red_pair = CursesManager::GetColorPair(ColorPair(Color::RED));
    green_pair = CursesManager::GetColorPair(ColorPair(Color::GREEN));
    yellow_pair = CursesManager::GetColorPair(ColorPair(Color::YELLOW));
    purple_pair = CursesManager::GetColorPair(ColorPair(Color::PURPLE));
    orange_pair = CursesManager::GetColorPair(ColorPair(Color::ORANGE));

    setPosition(Vect2(1, 3));
    setSize(Vect2(32, 9));
}

void ChatLog::render()
{
    Content& content = getContent();
    content.clear();
    for (int i = 0; i < 9; i++)
    {
        if (!entries[i].isNull()) {
            content.writeLine(entries[i].getMessage(), Vect2(0,i), TextAlignment::LEFT, Player::ConvertColor(entries[i].getColor()));
        }
    }
}

void ChatLog::setLobby(Lobby* lobby)
{
    this->lobby = lobby;
}

void ChatLog::pushMessage(ChatEntry entry)
{
    for (int i = 0; i < 8; i++)
    {
        entries[i] = entries[i+1];
    }
    entries[8] = entry;
    invalidate();
}

void ChatLog::reassignColor(int id, PlayerColor color)
{
    for (auto& entry : entries) {
        if (entry.getId() == id)
        {
            entry.setColor(color);
        }
    }
    invalidate();
}

void ChatLog::clear()
{
    for (int i = 0; i < 9; i++) {
        entries[i] = ChatEntry();
    }
    invalidate();
}
