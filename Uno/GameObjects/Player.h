//
// Created by Brandon Martin on 4/11/19.
//

#ifndef CURSEN_PLAYER_H
#define CURSEN_PLAYER_H


#include <string>

class Player {

public:

    Player();

    void setName(const std::string& name);
    std::string getName();

    void addPoints(const int& points);
    int getPoints();


private:

    std::string name;
    int points;

};


#endif //CURSEN_PLAYER_H
