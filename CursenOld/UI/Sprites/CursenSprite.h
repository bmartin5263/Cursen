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

class CursenSprite {


public:

    CursenSprite();
    CursenSprite(const CursenSprite&) = default;
    CursenSprite& operator = (const CursenSprite& other) = default;
    virtual ~CursenSprite() = default;

    void setPosition(const sf::Vector2i& position);
    sf::Vector2i getPosition() const;

private:

    // To help abstract away methods that the user needs vs methods CursenOld needs
    friend class TerminalManager;
    friend class SpriteManager;

    SpriteFrame getCurrentFrame() const;
    void addFrame(SpriteFrame frame);

    sf::Vector2i position;
    std::vector<SpriteFrame> frames;
    int totalFrames;
    int currentFrame;


};


#endif //CURSEN_CURSESSPRITE_H
