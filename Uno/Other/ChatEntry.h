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
    ChatEntry(int id, std::string message, PlayerColor color);

    void setColor(PlayerColor color);

    void setNull();
    bool isNull() { return id == -1; }
    PlayerColor getColor() { return color; }
    std::string& getMessage() { return message; }
    int getId() { return id; }

    size_t serialize(char* const buffer) const override;
    size_t deserialize(const char* const buffer) override;
    size_t sizeOf() const override;

private:

    int id;
    PlayerColor color;
    std::string message;

};


#endif //CURSEN_CHATENTRY_H
