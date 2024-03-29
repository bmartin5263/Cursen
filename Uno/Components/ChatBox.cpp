//
// Created by Brandon Martin on 5/31/19.
//

#include <Cursen/Drawing/TerminalManager.h>
#include "ChatBox.h"

using namespace cursen;

ChatBox::ChatBox() : AggregateComponent(),
    active(false)
{

}

ChatBox::ChatBox(const cursen::Vect2& pos) : AggregateComponent(pos),
     active(false)
{

}

void ChatBox::initialize()
{

    border.initialize();
    border.setSize(Vect2(34, 15));
    border.setPosition(Vect2(0, 0));
    addRelative(border);

    titleBox.initialize();
    titleBox.setSize(Vect2(34, 3));
    titleBox.setPosition(Vect2(0, 0));
    titleBox.setLowerLeft(TerminalManager::LTEE);
    titleBox.setLowerRight(TerminalManager::RTEE);
    addRelative(titleBox);

    messageBox.initialize();
    messageBox.setSize(Vect2(34, 3));
    messageBox.setPosition(Vect2(0,12));
    messageBox.setUpperRight(TerminalManager::RTEE);
    messageBox.setUpperLeft(TerminalManager::LTEE);
    addRelative(messageBox);

    title.initialize();
    title.setSize(Vect2(32, 1));
    title.setPosition(Vect2(1,1));
    title.setTextAlignment(TextAlignment::CENTER);
    title.emplaceText("Chat");
    addRelative(title);

    chat_entry.initialize();
    chat_entry.setSize(Vect2(32, 1));
    chat_entry.setPosition(Vect2(Vect2(1,13)));
    chat_entry.setForeground(Color::WHITE);
    chat_entry.setBackground(Color::DARK_BLUE);
    addRelative(chat_entry);

    log.initialize();
    addRelative(log);

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
    this->active = value;
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

void ChatBox::update(ChatEntry* messages)
{
    log.update(messages);
}

void ChatBox::clearAllMessages()
{
    clearMessage();
    log.clear();
}

bool ChatBox::isActive()
{
    return active;
}
