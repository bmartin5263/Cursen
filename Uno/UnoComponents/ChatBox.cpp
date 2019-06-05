//
// Created by Brandon Martin on 5/31/19.
//

#include <Cursen/Drawing/CursesManager.h>
#include "ChatBox.h"

using namespace cursen;

ChatBox::ChatBox() : AggregateComponent()
{

}

ChatBox::ChatBox(const cursen::Vect2& pos) : AggregateComponent(pos)
{

}

void ChatBox::initialize()
{

    border.initialize();
    border.setSize(Vect2(34, 15));
    border.setPosition(Vect2(0, 0));
    addRelative(&border);

    titleBox.initialize();
    titleBox.setSize(Vect2(34, 3));
    titleBox.setPosition(Vect2(0, 0));
    titleBox.setLowerLeft(CursesManager::LTEE);
    titleBox.setLowerRight(CursesManager::RTEE);
    addRelative(&titleBox);

    messageBox.initialize();
    messageBox.setSize(Vect2(34, 3));
    messageBox.setPosition(Vect2(0,12));
    messageBox.setUpperRight(CursesManager::RTEE);
    messageBox.setUpperLeft(CursesManager::LTEE);
    addRelative(&messageBox);

    title.initialize();
    title.setSize(Vect2(32, 1));
    title.setPosition(Vect2(1,1));
    title.setTextAlignment(TextAlignment::CENTER);
    title.emplaceText("Chat");
    addRelative(&title);

    chat_entry.initialize();
    chat_entry.setSize(Vect2(32, 1));
    chat_entry.setPosition(Vect2(Vect2(1,13)));
    chat_entry.setForeground(Color::WHITE);
    chat_entry.setBackground(Color::DARK_BLUE);
    addRelative(&chat_entry);

    log.initialize();
    addRelative(&log);

}

void ChatBox::setEnabled(bool value)
{
    title.setEnabled(value);
    border.setEnabled(value);
    titleBox.setEnabled(value);
    messageBox.setEnabled(value);
}

void ChatBox::setActive(bool value)
{
    setSilenced(!value);
    chat_entry.setEnabled(value);
    chat_entry.setHidden(!value);
    if (!value) {
        chat_entry.setText("");
    }
}

std::string ChatBox::getMessage()
{
    return chat_entry.getText();
}

void ChatBox::clearMessage()
{
    chat_entry.setText("");
}

void ChatBox::pushMessage(ChatEntry entry)
{
    log.pushMessage(entry);
}

void ChatBox::reassignColor(int id, PlayerColor color)
{
    log.reassignColor(id, color);
}

void ChatBox::clearAll()
{
    clearMessage();
    log.clear();
}
