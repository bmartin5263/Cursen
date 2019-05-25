//
// Created by Brandon Martin on 5/24/19.
//

#ifndef CURSEN_CURSORMANAGER_H
#define CURSEN_CURSORMANAGER_H

#include <set>

namespace cursen {

    class Cursor;

    class CursorManager {

    public:

        static void RefreshCursors();

        static void Register(Cursor* cursor);
        static void Deregister(Cursor* cursor);

    private:

        std::set<Cursor*> cursors;

        static CursorManager* instance;

        static CursorManager& Instance() {
            if (instance == nullptr)
                instance = new CursorManager;
            return *instance;
        }

        CursorManager() = default;
        CursorManager(const CursorManager& other) = delete;
        CursorManager(CursorManager&& other) noexcept = delete;
        CursorManager& operator = (const CursorManager& other) = delete;
        CursorManager& operator = (CursorManager&& other) = delete;
        ~CursorManager() = default;

    };

}

#endif //CURSEN_CURSORMANAGER_H
