//
// Created by Brandon Martin on 11/21/18.
//

#ifndef CURSEN_ENGINEOBJECT_H
#define CURSEN_ENGINEOBJECT_H

#include "SceneManager.h"
#include <ncurses.h>

class CursenObject {

public:

    CursenObject(bool autoRegister);
    virtual ~CursenObject();

    virtual void update() {};
    virtual void draw() { };
    virtual void destroy() {};
    void markForDestroy();

    void registerToCurrentScene(bool draw = true, bool update = true) { SceneManager::GetCurrentScene()->registerCursenObject(this); };
    void deregisterFromCurrentScene() { SceneManager::GetCurrentScene()->deleteCursenObject(this); };
    void deregisterDraws() { SceneManager::GetCurrentScene()->removeFromDraw(this); };
    void deregisterUpdates() { SceneManager::GetCurrentScene()->removeFromUpdate(this); };
    void registerForDraws() { SceneManager::GetCurrentScene()->addToDraw(this); };
    void registerForUpdates() { SceneManager::GetCurrentScene()->addToUpdate(this); };

    int getUpdateOrder() { return updateOrder; };
    int getDrawOrder() { return drawOrder; };
    bool isExternallyManaged() { return externallyManaged; };

private:

    int updateOrder;
    int drawOrder;
    bool externallyManaged;
    bool markedForDestruction;

};


#endif //CURSEN_ENGINEOBJECT_H
