//
// Created by Brandon Martin on 3/8/19.
//

#ifndef CURSEN_DRAWREQUEST_H
#define CURSEN_DRAWREQUEST_H


#include <vector>
#include <ncurses.h>
#include <Drawing/IntRect.h>
#include <Drawing/Position.h>

class DrawRequest {

public:

    void setBody(std::vector<std::vector<chtype>>*);
    void setPosition(Position*);

private:

    friend class CursesManager;

    std::vector<std::vector<chtype>>* getBody();
    Position* getPosition();

    std::vector<std::vector<chtype>>* body;
    Position* position;

};


#endif //CURSEN_DRAWREQUEST_H
