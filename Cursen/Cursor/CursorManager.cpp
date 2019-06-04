//
// Created by Brandon Martin on 5/24/19.
//

#include "CursorManager.h"
#include "Cursen/CursenApplication.h"
#include "Cursor.h"

namespace cursen {

    CursorManager* CursorManager::instance = nullptr;

    void CursorManager::RefreshCursors()
    {
        std::set<Cursor*>& cursors = Instance().cursors;
        for (auto& cursor : Instance().cursors) {
            cursor->refresh();
        }
    }

    void CursorManager::Register(Cursor* cursor)
    {
        std::set<Cursor*>& cursors = Instance().cursors;
        if (cursors.find(cursor) == cursors.end()) {
            cursors.insert(cursor);
        }
    }

    void CursorManager::Deregister(Cursor* cursor)
    {
        std::set<Cursor*>& cursors = Instance().cursors;
        if (cursors.find(cursor) != cursors.end()) {
            cursors.erase(cursor);
        }
    }

    CursorManager& CursorManager::Instance()
    {
        return CursenApplication::GetCursorManager();
    }

}