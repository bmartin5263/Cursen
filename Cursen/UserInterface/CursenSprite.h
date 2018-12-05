//
// Created by Brandon Martin on 11/21/18.
//

#ifndef CURSEN_CURSESSPRITE_H
#define CURSEN_CURSESSPRITE_H

#include <ncurses.h>
#include "SFML/Graphics.hpp"
#include "UITools.h"

class Canvas;

class CursesSprite {

public:

    CursesSprite();
    CursesSprite(const CursesSprite&) = default;
    CursesSprite& operator = (const CursesSprite& other) = default;
    virtual ~CursesSprite() = default;

    virtual void draw() {
        attron(UITools::GetColor("blue").colorPair);
        mvaddstr(position.y,1,"Hello!");
        attroff(UITools::GetColor("blue").colorPair);
    };

    void setPosition(const sf::Vector2i& position);
    sf::Vector2i getPosition();

protected:

    sf::Vector2i position;

};


#endif //CURSEN_CURSESSPRITE_H
