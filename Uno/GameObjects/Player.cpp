//
// Created by Brandon Martin on 4/11/19.
//

#include "Player.h"

const std::string Player::COMP_NAMES[] = { "Watson", "SkyNet", "Hal 9000", "Metal Gear" };

Player::Player() :
    name("Null"), color(PlayerColor::GRAY), points(-1), id(-1)
{
}

Player::Player(const std::string &name, const PlayerColor& color, int id) :
    name(name), color(color), points(0), id(id)
{
}

void Player::clear()
{
    name = "Null";
    color = PlayerColor::GRAY;
    points = -1;
    id = -1;
}

void Player::setName(const std::string &name) {
    this->name = name;
}

std::string Player::getName() const {
    return name;
}

void Player::addPoints(const int points) {
    this->points += points;
}

int Player::getPoints() const {
    return points;
}

const std::string Player::GetComputerName() {
    static int i = -1;
    i = (i+1) % 4;
    return COMP_NAMES[i];
}

void Player::setColor(const PlayerColor &color) {
    this->color = color;
}

PlayerColor Player::getColor() const {
    return color;
}

cursen::Color Player::ConvertColor(const PlayerColor &color) {
    switch (color) {
        case PlayerColor::BLUE:
            return cursen::Color::BLUE;
        case PlayerColor::RED:
            return cursen::Color::RED;
        case PlayerColor::GREEN:
            return cursen::Color::GREEN;
        case PlayerColor::YELLOW:
            return cursen::Color::YELLOW;
        case PlayerColor::PURPLE:
            return cursen::Color::VIOLET;
        case PlayerColor::ORANGE:
            return cursen::Color::ORANGE;
        case PlayerColor::GRAY:
            return cursen::Color::GRAY;
    }
}

size_t Player::serialize(char* const buffer) const
{
    size_t written = 0;
    written += Serializable::Serialize(buffer, name.length());
    written += Serializable::Serialize(buffer + written, name.c_str(), name.length());
    written += Serializable::Serialize(buffer + written, (int)color);
    written += Serializable::Serialize(buffer + written, points);
    written += Serializable::Serialize(buffer + written, id);
    written += hand.serialize(buffer + written);
    return written;
}

size_t Player::deserialize(const char* const buffer)
{
    size_t read = 0;
    size_t len;
    read += Serializable::Deserialize(buffer, len);
    char raw_name[len + 1];
    read += Serializable::Deserialize(buffer + read, raw_name, len);
    raw_name[len] = '\0';
    name = std::string(raw_name);
    int col;
    read += Serializable::Deserialize(buffer + read, col);
    color = (PlayerColor)col;
    read += Serializable::Deserialize(buffer + read, points);
    read += Serializable::Deserialize(buffer + read, id);
    read += hand.deserialize(buffer + read);
    return read;
}

size_t Player::sizeOf() const
{
    return sizeof(Player);
}

int Player::getId() const
{
    return id;
}

size_t Player::getHandSize() const
{
    return hand.size();
}

Hand& Player::getHand()
{
    return hand;
}

size_t Player::safe_serialize(char* const buffer) const
{
    size_t written = 0;
    written += Serializable::Serialize(buffer, name.length());
    written += Serializable::Serialize(buffer + written, name.c_str(), name.length());
    written += Serializable::Serialize(buffer + written, (int)color);
    written += Serializable::Serialize(buffer + written, points);
    written += Serializable::Serialize(buffer + written, -1);
    written += hand.safe_serialize(buffer + written);
    return written;
}
