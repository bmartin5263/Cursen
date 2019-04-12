//
// Created by Brandon Martin on 4/11/19.
//

#include "Player.h"

Player::Player() :
    points(0), name("Unknown")
{
}


void Player::setName(const std::string &name) {
    this->name = name;
}

std::string Player::getName() {
    return name;
}

void Player::addPoints(const int &points) {
    this->points += points;
}

int Player::getPoints() {
    return points;
}