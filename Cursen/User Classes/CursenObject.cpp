//
// Created by Brandon Martin on 11/21/18.
//

#include <SceneManager.h>
#include <assert.h>
#include <SFML/System.hpp>
#include "CursenObject.h"

/*
 * Automatically registers for draws and updates in the current scene.
 */
CursenObject::CursenObject() :
    updateOrder(0), drawOrder(0), externallyManaged(false), markedForDestruction(false)
{
}

CursenObject::CursenObject(CursenObject::Registration registration) :
    updateOrder(0), drawOrder(0), externallyManaged(false), markedForDestruction(false)
{
    if (registration != Registration::DEFERRED) {
        registerToCurrentScene(false, false);
        switch (registration) {
            case Registration::UPDATE:
                registerForUpdates();
                break;
            case Registration::DRAW:
                registerForDraws();
                break;
            case Registration::REGISTER:
                registerForUpdates();
                registerForDraws();
                break;
            default:
                assert(false);
                break;
        }
    }
}

void CursenObject::deregisterFromCurrentScene() {
    SceneManager::GetCurrentScene()->deleteCursenObject(this);
    //isDrawn = false;
    //isUpdated = false;
};

void CursenObject::deregisterDraws() {
    //assert(isDrawn);
    //isDrawn = false;
    SceneManager::GetCurrentScene()->removeFromDraw(this);
};

void CursenObject::deregisterUpdates() {
    //assert(isUpdated);
    //isUpdated = false;
    SceneManager::GetCurrentScene()->removeFromUpdate(this);
};

void CursenObject::registerForDraws() {
    //assert(!isDrawn);
    //isDrawn = true;
    SceneManager::GetCurrentScene()->addToDraw(this);
};

void CursenObject::registerForUpdates() {
    //assert(!isUpdated);
    //isUpdated = true;
    SceneManager::GetCurrentScene()->addToUpdate(this);
};

void CursenObject::registerToCurrentScene(bool draw, bool update) {
    SceneManager::GetCurrentScene()->registerCursenObject(this, draw, update);
    //isDrawn = draw;
    //isUpdated = update;
}

void CursenObject::markForDestroy() {
    assert(!markedForDestruction);
    if (!markedForDestruction)
    {
        markedForDestruction = true;
        destroy();
        SceneManager::GetCurrentScene()->deregisterCursenObject(this);
    }
}

sf::Vector2i CursenObject::getPosition() {
    return sf::Vector2i(boundingBox.left, boundingBox.top);
}

void CursenObject::move(const sf::Vector2i& pos) {
    this->boundingBox.left += pos.x;
    this->boundingBox.top += pos.y;
}

void CursenObject::setBoundingBox(const sf::IntRect &box) {
    this->boundingBox = box;
}

void CursenObject::setPosition(const sf::Vector2i &pos) {
    this->boundingBox.left = pos.x;
    this->boundingBox.top = pos.y;
}

CursenObject::~CursenObject() {
}