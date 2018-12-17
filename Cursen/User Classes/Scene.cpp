//
// Created by Brandon Martin on 11/21/18.
//

#include "Scene.h"
#include "CursenObject.h"
#include "TerminalManager.h"
#include "Engine.h"
#include "ncurses.h"
#include "UITools.h"
#include "../../Demo/BouncyBox.h"

void Scene::processFrame() {
    static long long frames = 0;
    static long long total = 0;
    //MyAlarmManager.ProcessTimeEvents();
    //MyInputEventMgr.ProcessInputEvents();

    update();

    TerminalManager::ClearScreen();
    draw();
    frames++;
    total += 1/Engine::GetFrameTime();
    UITools::DrawText(("FPS " + std::to_string(total/frames)).c_str(), 0, 0);
    TerminalManager::RefreshScreen();

    deleteMarkedObjects();
}

void Scene::initialize() {
}

void Scene::draw()
{
    for(auto mapPair = drawnObjects.begin(); mapPair != drawnObjects.end(); ++mapPair)
    {
        for(auto cursenObject = mapPair->second.begin(); cursenObject != mapPair->second.end(); ++cursenObject)
        {
            (*cursenObject)->draw();
        }
    }
}

void Scene::update()
{
    for(auto mapPair = updatedObjects.begin(); mapPair != updatedObjects.end(); ++mapPair)
    {
        for(auto cursenObject = mapPair->second.begin(); cursenObject != mapPair->second.end(); ++cursenObject)
        {
            (*cursenObject)->update();
        }
    }
}

void Scene::deleteMarkedObjects()
{
    for (auto cursenObject = markedObjects.begin(); cursenObject != markedObjects.end(); ++cursenObject)
    {
        removeFromUpdate(*cursenObject);
        removeFromDraw(*cursenObject);
        deleteCursenObject(*cursenObject);
    }
    markedObjects.clear();
}

void Scene::deleteUnmarkedObjects() {
    for (auto cursenObject = markedObjects.begin(); cursenObject != markedObjects.end(); ++cursenObject)
    {
        (*cursenObject)->destroy();
        deleteCursenObject(*cursenObject);
    }
}

void Scene::deleteCursenObject(CursenObject *cursenObject) {
    if (!cursenObject->isExternallyManaged())
    {
        delete cursenObject;
    }
    else
    {
        //(go->ManagedDeleteOperation)(go);
    }
}

void Scene::removeFromUpdate(CursenObject* cursenObject) {
    auto found = updatedObjects[cursenObject->getUpdateOrder()].find(cursenObject);
    if (found == updatedObjects[cursenObject->getUpdateOrder()].end()) {
        return;
    } else {
        updatedObjects[cursenObject->getUpdateOrder()].erase(cursenObject);
    }
}

void Scene::removeFromDraw(CursenObject* cursenObject) {
    auto found = drawnObjects[cursenObject->getDrawOrder()].find(cursenObject);
    if (found == drawnObjects[cursenObject->getDrawOrder()].end()) {
        return;
    } else {
        drawnObjects[cursenObject->getDrawOrder()].erase(cursenObject);
    }
}

void Scene::addToDraw(CursenObject* cursenObject) {
    auto found = drawnObjects[cursenObject->getDrawOrder()].find(cursenObject);
    if (found == drawnObjects[cursenObject->getDrawOrder()].end()) {
        drawnObjects[cursenObject->getDrawOrder()].insert(cursenObject);
    } else {
        return;
    }
}

void Scene::addToUpdate(CursenObject* cursenObject) {
    auto found = updatedObjects[cursenObject->getUpdateOrder()].find(cursenObject);
    if (found == updatedObjects[cursenObject->getUpdateOrder()].end()) {
        updatedObjects[cursenObject->getUpdateOrder()].insert(cursenObject);
    } else {
        return;
    }
}

/*
 * Adds CursenObject to the scene. Drawing and Updating are defaulted to true, but are optional.
 */
void Scene::registerCursenObject(CursenObject *cursenObject, bool draw, bool update) {
    cursenObjects.insert(cursenObject);
    if (draw) addToDraw(cursenObject);
    if (update) addToUpdate(cursenObject);
}

/*
 * Place object into marked object set, which will be deleted at the end of the scene.
 */
void Scene::deregisterCursenObject(CursenObject *cursenObject) {
    markedObjects.insert(cursenObject);
}

void Scene::finalize() {
    deleteUnmarkedObjects();
    terminate();
}