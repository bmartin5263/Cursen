//
// Created by Brandon Martin on 3/8/19.
//

#ifndef CURSEN_DRAWREQUEST_H
#define CURSEN_DRAWREQUEST_H

#include <ncurses.h>
#include <Drawing/Position.h>

class TextBody;

class DrawRequest {

public:

    void setBody(TextBody*);
    void setPosition(Vect2d);
    TextBody* getBody();
    Vect2d getPosition();

private:

    friend class CursesManager;

    TextBody* body;
    Vect2d position;

};


#endif //CURSEN_DRAWREQUEST_H
