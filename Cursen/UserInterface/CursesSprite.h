//
// Created by Brandon Martin on 11/21/18.
//

#ifndef CURSEN_CURSESSPRITE_H
#define CURSEN_CURSESSPRITE_H

#include "SFML/Graphics.hpp"

class Canvas;

class CursesSprite {

public:

    CursesSprite();
    CursesSprite(const CursesSprite&);
    CursesSprite& operator = (const CursesSprite& other);
    virtual ~CursesSprite();

    virtual void draw(Canvas& canvas);

protected:

    sf::Vector2i position;

};


#endif //CURSEN_CURSESSPRITE_H
