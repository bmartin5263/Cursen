//
// Created by Brandon Martin on 11/21/18.
//

#ifndef CURSEN_ENGINEOBJECT_H
#define CURSEN_ENGINEOBJECT_H

#include "SceneManager.h"
#include "TerminalManager.h"
#include "SFML/Graphics.hpp"
#include <ncurses.h>
#include "UITools.h"

class CursenObject {

public:

    // REGISTER = update and render
    // DRAW = render
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

protected:

    int updateOrder;
    int drawOrder;
    bool externallyManaged;
    bool markedForDestruction;

};


#endif //CURSEN_ENGINEOBJECT_H
