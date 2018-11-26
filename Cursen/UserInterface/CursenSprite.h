//
// Created by Brandon Martin on 11/21/18.
//

#ifndef CURSEN_CURSESSPRITE_H
#define CURSEN_CURSESSPRITE_H

#include "SFML/Graphics.hpp"

class Canvas;

class CursesSprite {

public:

    CursesSprite() = default;
    CursesSprite(const CursesSprite&) = default;
    CursesSprite& operator = (const CursesSprite& other) = default;
    virtual ~CursesSprite() = default;

    virtual void draw() = 0;

protected:

    sf::Vector2i position;

};


#endif //CURSEN_CURSESSPRITE_H
