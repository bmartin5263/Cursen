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

    virtual void update() {
        color = (color + 1) % 4;
        sf::IntRect originalPos = boundingBox;
        move(sf::Vector2i(horizontal, vertical));
        if (UITools::IsHorizontallyOffscreen(boundingBox)) {
            horizontal = -horizontal;
            boundingBox = originalPos;
            move(sf::Vector2i(horizontal, vertical));
        }
        if (UITools::IsVerticallyOffscreen(boundingBox)) {
            vertical = -vertical;
            boundingBox = originalPos;
            move(sf::Vector2i(horizontal, vertical));
        }
        //if (position.y >= TerminalManager::GetRows()) position.y = 0;
    };

    virtual void draw() {
        attron(UITools::GetColor(colors[color]).colorPair);
        mvaddstr(boundingBox.top, boundingBox.left,   "XXXXXXXXXX");
        mvaddstr(boundingBox.top+1, boundingBox.left, "X        X");
        mvaddstr(boundingBox.top+2, boundingBox.left, "XXXXXXXXXX");
        attroff(UITools::GetColor(colors[color]).colorPair);
    };

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

private:

    static std::vector<std::string> colors;
    sf::IntRect boundingBox;
    int updateOrder;
    int drawOrder;
    int vertical;
    int horizontal;
    int color;
    bool externallyManaged;
    bool markedForDestruction;

};


#endif //CURSEN_ENGINEOBJECT_H
