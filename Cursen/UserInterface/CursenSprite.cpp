//
// Created by Brandon Martin on 11/21/18.
//

#include <TerminalManager.h>
#include "CursenSprite.h"

CursesSprite::CursesSprite() :
    position(sf::Vector2i(0,0))
{
    int y = rand() % TerminalManager::GetRows();
    position = sf::Vector2i(1, y);
}

void CursesSprite::setPosition(const sf::Vector2i &position) {
    this->position = position;
}

sf::Vector2i CursesSprite::getPosition() {
    return this->position;
}