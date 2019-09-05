//
// Created by Brandon Martin on 6/4/19.
//

#ifndef CURSEN_CHATENTRY_H
#define CURSEN_CHATENTRY_H

#include <string>

#include "Uno/Messages/Serializable.h"
#include "Uno/GameObjects/PlayerColor.h"

class ChatEntry : public Serializable
{

public:

    ChatEntry();
    ChatEntry(int index, std::string message, PlayerColor color);

    void setColor(PlayerColor color);

    void setNull();
    bool isNull() { return index == -1; }
    PlayerColor getColor() { return color; }
    std::string& getMessage() { return message; }

    int getIndex() { return index; }
    void setIndex(int index) { this->index = index; }

    size_t serialize(char* const buffer) const override;
    size_t deserialize(const char* const buffer) override;
    size_t sizeOf() const override;

private:

    int index;
    PlayerColor color;
    std::string message;

};


#endif //CURSEN_CHATENTRY_H
