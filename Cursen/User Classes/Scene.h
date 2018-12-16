//
// Created by Brandon Martin on 11/21/18.
//

#ifndef CURSEN_SCENE_H
#define CURSEN_SCENE_H

#include <unordered_set>
#include <unordered_map>
#include <set>

class CursenObject;

class Scene {

public:

    Scene() = default;
    Scene(const Scene& other) = default;
    Scene& operator = (const Scene& other) = default;
    virtual ~Scene() = default;

    // User Method Templates
    virtual void initialize();
    virtual void terminate() {};

    void finalize();
    void processFrame();
    void deleteMarkedObjects();
    void deleteUnmarkedObjects();

    // Object Registration
    void registerCursenObject(CursenObject* cursenObject, bool addToDraw = true, bool addToUpdate = true);
    void deregisterCursenObject(CursenObject* cursenObject);
    void removeFromUpdate(CursenObject* cursenObject);
    void removeFromDraw(CursenObject* cursenObject);
    void addToUpdate(CursenObject* cursenObject);
    void addToDraw(CursenObject* cursenObject);
    void deleteCursenObject(CursenObject* cursenObject);

private:

    void draw();
    void update();

    typedef std::unordered_set<CursenObject*> CursenObjects;
    typedef std::unordered_map<int, std::unordered_set<CursenObject*>> CursenObjectsMap;

    CursenObjects cursenObjects;
    CursenObjects markedObjects;
    CursenObjectsMap drawnObjects;
    CursenObjectsMap updatedObjects;

};


#endif //CURSEN_SCENE_H
