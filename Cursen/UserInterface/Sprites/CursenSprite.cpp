//
// Created by Brandon Martin on 11/21/18.
//

#include <TerminalManager.h>
#include "CursenSprite.h"
#include "SpriteFrame.h"

CursesSprite::CursesSprite() :
    position(sf::Vector2i(1,1)), currentFrame(0), totalFrames(0)
{
    frames.push_back(SpriteFrame());
}

void CursesSprite::setPosition(const sf::Vector2i &position) {
    this->position = position;
}

sf::Vector2i CursesSprite::getPosition() const {
    return this->position;
}

SpriteFrame CursesSprite::getCurrentFrame() const {
    return frames[currentFrame];
}