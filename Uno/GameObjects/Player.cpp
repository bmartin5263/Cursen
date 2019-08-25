//
// Created by Brandon Martin on 4/11/19.
//

#include <Uno/Constants.h>
#include "Player.h"

const std::string Player::COMP_NAMES[] = { "Watson", "SkyNet", "Hal 9000", "Metal Gear" };

Player::Player() :
    name("Null"), color(PlayerColor::GRAY), points(-1), id(-1), force_draws(0), ai(false)
{
}

Player::Player(const std::string &name, const PlayerColor& color, int id, bool ai) :
    name(name), color(color), points(0), id(id), force_draws(0), ai(ai)
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

void Player::addPoints(int points) {
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
            return cursen::Color::MAGENTA;
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

cursen::Color Player::ConvertColorLight(const PlayerColor &color) {
    switch (color) {
        case PlayerColor::BLUE:
            return cursen::Color(87);
        case PlayerColor::RED:
            return cursen::Color(213);
        case PlayerColor::GREEN:
            return cursen::Color(159);
        case PlayerColor::YELLOW:
            return cursen::Color(231);
        case PlayerColor::PURPLE:
            return cursen::Color(177);
        case PlayerColor::ORANGE:
            return cursen::Color(220);
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
    written += Serializable::Serialize(buffer + written, ai);
    written += Serializable::Serialize(buffer + written, force_draws);
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
    read += Serializable::Deserialize(buffer + read, ai);
    read += Serializable::Deserialize(buffer + read, force_draws);
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

size_t Player::safeSerialize(char* const buffer, bool safe_serialize_hand) const
{
    size_t written = 0;
    written += Serializable::Serialize(buffer, name.length());
    written += Serializable::Serialize(buffer + written, name.c_str(), name.length());
    written += Serializable::Serialize(buffer + written, (int)color);
    written += Serializable::Serialize(buffer + written, points);
    written += Serializable::Serialize(buffer + written, -1);
    written += Serializable::Serialize(buffer + written, ai);
    written += Serializable::Serialize(buffer + written, force_draws);
    if (safe_serialize_hand) written += hand.safe_serialize(buffer + written);
    else written += hand.serialize(buffer + written);
    return written;
}

bool Player::isAI()
{
    return ai;
}

bool Player::hasPlayableCard(const Card& card)
{
    return hand.hasPlayableCardFor(card);
}

int Player::getPlayableCardIndex(const Card& card)
{
    if (force_draws > 0) return -1;
    bool hasWild = false;
    int wild_index = -1;
    int index = -1;
    CardValue value = card.getValue();
    CardColor color = card.getColor();
    for (int i = 0; i < hand.size(); ++i)
    {
        const Card& hand_card = hand.get(i);
        if ((hand_card.getColor() == color || hand_card.getValue() == value) && !hand_card.isWild())
        {
            index = i;
            break;
        }
        else if (hand_card.isWild())
        {
            hasWild = true;
            wild_index = i;
        }
    }
    if (index == -1 && hasWild) index = wild_index;
    return index;
}

void Player::addForceDraws(int count)
{
    this->force_draws += count;
}

void Player::decrementForceDraws()
{
    if (force_draws > 0) force_draws--;
}

int Player::getForceDraws()
{
    return force_draws;
}

CardColor Player::getWildColor()
{
    std::unordered_map<CardColor, int, EnumHash> color_map;
    for (int i = 0; i < hand.size(); ++i)
    {
        const Card& card = hand.get(i);
        if (!card.isWild()) color_map[card.getColor()] += 1;
    }
    auto x = std::max_element(color_map.begin(), color_map.end(),
                              [](const std::pair<CardColor, int>& p1, const std::pair<CardColor, int>& p2)
                              {
                                  return p1.second < p2.second;
                              });
    if (x == color_map.end())
    {
        return CardColor::BLUE;
    }
    return x->first;
}

void Player::clearForceDraws()
{
    force_draws = 0;
}
