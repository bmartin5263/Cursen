//
// Created by Brandon Martin on 4/11/19.
//

#ifndef CURSEN_PLAYER_H
#define CURSEN_PLAYER_H

#include <string>

#include "Cursen/Drawing/Color.h"
#include "PlayerColor.h"

class Player {

public:

    Player();
    Player(const std::string& name, const PlayerColor& color);

    void setName(const std::string& name);
    std::string getName() const;

    void addPoints(const int& points);
    int getPoints() const;

    void setColor(const PlayerColor& color);
    PlayerColor getColor() const;

    static const std::string GetComputerName();
    static cursen::Color ConvertColor(const PlayerColor& color);

private:

    static const std::string COMP_NAMES[];


    std::string name;
    PlayerColor color;
    int points;

};


#endif //CURSEN_PLAYER_H
