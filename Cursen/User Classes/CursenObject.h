//
// Created by Brandon Martin on 11/21/18.
//

#ifndef CURSEN_ENGINEOBJECT_H
#define CURSEN_ENGINEOBJECT_H

#include "SceneManager.h"
#include "TerminalManager.h"
#include "SFML/Graphics.hpp"
#include <ncurses.h>
#include <UserInterface/UITools.h>

class CursenObject {

public:

    // REGISTER = update and draw
    // DRAW = draw
    // UPDATE = update
    // DEFERRED = no scene registration
    enum class Registration {
        REGISTER, DRAW, UPDATE, DEFERRED
    };

    CursenObject();
    CursenObject(Registration);

    virtual ~CursenObject();

    virtual void update() {};
    virtual void draw() {};
    virtual void destroy() {};

    void markForDestroy();

    void registerToCurrentScene(bool draw = true, bool update = true);
    void deregisterFromCurrentScene();
    void deregisterDraws();
    void deregisterUpdates();
    void registerForDraws();
    void registerForUpdates();

    int getUpdateOrder() { return updateOrder; };
    int getDrawOrder() { return drawOrder; };
    bool isExternallyManaged() { return externallyManaged; };

    void move(const sf::Vector2i& pos);
    void setBoundingBox(const sf::IntRect &box);
    sf::Vector2i getPosition();
    void setPosition(const sf::Vector2i& pos);

protected:

    sf::IntRect boundingBox;
    int updateOrder;
    int drawOrder;
    bool externallyManaged;
    bool markedForDestruction;

};


#endif //CURSEN_ENGINEOBJECT_H
