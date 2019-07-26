//
// Created by Brandon Martin on 6/4/19.
//

#include "ChatEntry.h"

ChatEntry::ChatEntry() :
    id(-1), color(PlayerColor::GRAY), message("")
{

}

ChatEntry::ChatEntry(int id, std::string message, PlayerColor color) :
    id(id), color(color), message(message)
{

}

void ChatEntry::setColor(PlayerColor color)
{
    this->color = color;
}

void ChatEntry::setNull()
{
    this->id = -1;
    this->color = PlayerColor::GRAY;
}

size_t ChatEntry::serialize(char* const buffer) const
{
    size_t written = 0;
    written += Serializable::Serialize(buffer + written, id);
    written += Serializable::Serialize(buffer + written, (int)color);
    written += Serializable::Serialize(buffer + written, message.length());
    written += Serializable::Serialize(buffer + written, message.c_str(), message.length());
    return written;
}

size_t ChatEntry::deserialize(const char* const buffer)
{
    size_t read = 0;
    read += Serializable::Deserialize(buffer + read, id);

    int raw_color;
    read += Serializable::Deserialize(buffer + read, raw_color);
    color = (PlayerColor)raw_color;

    size_t msgLen = 0;
    read += Serializable::Deserialize(buffer + read, msgLen);
    if (msgLen > 0)
    {
        char raw_msg[msgLen + 1];
        read += Serializable::Deserialize(buffer + read, raw_msg, msgLen);
        raw_msg[msgLen] = '\0';
        message = std::string(raw_msg);
    }
    return read;
}

size_t ChatEntry::sizeOf() const
{
    return sizeof(ChatEntry);
}
