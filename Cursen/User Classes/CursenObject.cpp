//
// Created by Brandon Martin on 11/21/18.
//

#include <SceneManager.h>
#include <assert.h>
#include "CursenObject.h"

//CursenObject::CursenObject() :
//        updateOrder(0), drawOrder(0), externallyManaged(false)
//{
//    registerToCurrentScene(true, true);
//}

CursenObject::CursenObject(bool autoRegister) :
    updateOrder(0), drawOrder(0), externallyManaged(false), markedForDestruction(false)
{
    if (autoRegister) {
        registerToCurrentScene(true, true);
    }
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

CursenObject::~CursenObject() {
    flash();
}