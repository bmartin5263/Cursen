//
// Created by Brandon Martin on 11/21/18.
//

#ifndef CURSEN_CURSESSPRITE_H
#define CURSEN_CURSESSPRITE_H

#include <ncurses.h>
#include "SFML/Graphics.hpp"
#include "UITools.h"
#include "SpriteFrame.h"

class Canvas;

class CursesSprite {


public:

    CursesSprite();
    CursesSprite(const CursesSprite&) = default;
    CursesSprite& operator = (const CursesSprite& other) = default;
    virtual ~CursesSprite() = default;

    void setPosition(const sf::Vector2i& position);
    sf::Vector2i getPosition() const;

private:

    friend class TerminalManager;

    SpriteFrame getCurrentFrame() const;

    sf::Vector2i position;
    std::vector<SpriteFrame> frames;
    int totalFrames;
    int currentFrame;


};


#endif //CURSEN_CURSESSPRITE_H
