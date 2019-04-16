//
// Created by Brandon Martin on 4/11/19.
//

#include "Player.h"

const std::string Player::COMP_NAMES[] = { "Watson", "SkyNet", "Hal 9000", "Metal Gear" };

Player::Player() :
    points(0), name("Unknown"), color(PlayerColor::BLUE)
{
}

Player::Player(const std::string &name, const PlayerColor& color) :
    points(0), name(name), color(color)
{
}


void Player::setName(const std::string &name) {
    this->name = name;
}

std::string Player::getName() const {
    return name;
}

void Player::addPoints(const int &points) {
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
    }
}
