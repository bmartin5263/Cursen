//
// Created by Brandon Martin on 11/21/18.
//

#include <TerminalManager.h>
#include "CursenSprite.h"
#include "SpriteFrame.h"

CursenSprite::CursenSprite() :
    position(sf::Vector2i(1,1)), currentFrame(0), totalFrames(0)
{
}

void CursenSprite::setPosition(const sf::Vector2i &position) {
    this->position = position;
}

sf::Vector2i CursenSprite::getPosition() const {
    return this->position;
}

void CursenSprite::addFrame(SpriteFrame frame) {
    frames.push_back(frame);
}

SpriteFrame CursenSprite::getCurrentFrame() const {
    return frames[currentFrame];
}