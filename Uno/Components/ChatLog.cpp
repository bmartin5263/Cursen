//
// Created by Brandon Martin on 6/4/19.
//

#include "ChatLog.h"
#include "Cursen/Drawing/TerminalManager.h"

using namespace cursen;

ChatLog::ChatLog() :
        TextComponent()
{

}

ChatLog::ChatLog(const cursen::Vect2& pos) : TextComponent(pos)
{

}

void ChatLog::initialize()
{
    TextComponent::initialize();
    setPosition(Vect2(1, 3));
    setSize(Vect2(32, 9));
}

void ChatLog::render()
{
    Content& content = getContent();
    content.clear();
    for (int i = 0; i < 9; i++)
    {
        content.writeLine(entries[i].getMessage(), Vect2(0,i), TextAlignment::LEFT, Player::ConvertColor(entries[i].getColor()));
    }
}

void ChatLog::clear()
{
    for (int i = 0; i < 9; i++) {
        entries[i] = ChatEntry();
    }
    invalidate();
}

void ChatLog::update(ChatEntry* messages)
{
    for (int i = 0; i < MAX_MESSAGES; ++i)
    {
        entries[i] = messages[i];
    }
    invalidate();
}
