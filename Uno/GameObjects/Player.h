//
// Created by Brandon Martin on 4/11/19.
//

#ifndef CURSEN_PLAYER_H
#define CURSEN_PLAYER_H


#include <string>
#include "Drawing/Color.h"

class Player {

public:

    Player();
    Player(const std::string& name);

    void setName(const std::string& name);
    std::string getName() const;

    void addPoints(const int& points);
    int getPoints() const;

    static const std::string GetComputerName();

private:

    static const std::string COMP_NAMES[];

    std::string name;
    int points;

};


#endif //CURSEN_PLAYER_H
