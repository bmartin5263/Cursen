//
// Created by Brandon Martin on 5/24/19.
//

#ifndef CURSEN_CURSORMANAGER_H
#define CURSEN_CURSORMANAGER_H

#include <set>
#include <unordered_set>

namespace cursen {

    class Cursor;

    class CursorManager {

    private:

        //typedef std::unordered_set<Cursor*> CursorSet;

    public:

        static void RefreshCursors();
        static void RefreshCursors(std::unordered_set<Cursor*> cursors);

        static void Register(Cursor* cursor);
        static void Deregister(Cursor* cursor);

    private:

        std::set<Cursor*> cursors;

        static CursorManager* instance;

        friend class CursenApplication;
        static CursorManager& Instance();

        CursorManager() = default;
        CursorManager(const CursorManager& other) = delete;
        CursorManager(CursorManager&& other) noexcept = delete;
        CursorManager& operator = (const CursorManager& other) = delete;
        CursorManager& operator = (CursorManager&& other) = delete;
        ~CursorManager() = default;

    };

}

#endif //CURSEN_CURSORMANAGER_H
