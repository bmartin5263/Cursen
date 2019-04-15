//
// Created by Brandon Martin on 4/11/19.
//

#include "Player.h"

const std::string Player::COMP_NAMES[] = { "Watson", "SkyNet", "Hal 9000", "Metal Gear" };

Player::Player() :
    points(0), name("Unknown")
{
}

Player::Player(const std::string &name) :
    points(0), name(name)
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

const std::string Player::getComputerName(int i) {
    return COMP_NAMES[i];
}