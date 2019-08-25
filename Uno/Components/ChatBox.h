//
// Created by Brandon Martin on 5/31/19.
//

#ifndef CURSEN_CHATBOX_H
#define CURSEN_CHATBOX_H

#include <Cursen/Components/AggregateComponent.h>
#include "Cursen/Components/Box.h"
#include "Cursen/Components/Label.h"
#include "Cursen/Components/TextField.h"
#include "ChatLog.h"

class ChatBox : public cursen::AggregateComponent
{
public:

    ChatBox();
    ChatBox(const cursen::Vect2& pos);
    void initialize() override;

    void setEnabled(bool value) override;
    void setActive(bool value);
    bool isActive();

    std::string getMessage();
    void clearMessage();

    void update(ChatEntry* messages);
    void clearAllMessages();

private:

    cursen::Box border;
    cursen::Box titleBox;
    cursen::Box messageBox;
    cursen::Label title;
    cursen::TextField chat_entry;
    ChatLog log;
    bool active;

};


#endif //CURSEN_CHATBOX_H
