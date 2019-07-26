//
// Created by Brandon Martin on 3/7/19.
//

#ifndef CURSEN_CURSESMANAGER_H
#define CURSEN_CURSESMANAGER_H

#include <ncurses.h>
#include <queue>
#include <string>
#include <unordered_map>
#include <set>
#include <map>

#include "Cursen/Components/Form.h"
#include "Color.h"
#include "ColorPair.h"

class TextComponent;

namespace cursen {

    class CursesManager {

    public:

        typedef std::set<TextComponent*> ComponentSet;
        typedef std::map<int, std::set<TextComponent*> > ComponentMap;

        static const int ESCAPE = 27;
        static const int ENTER = 10;
        static const int BACKSPACE = 127;
        static const int UP = KEY_UP;
        static const int DOWN = KEY_DOWN;
        static const int LEFT = KEY_LEFT;
        static const int RIGHT = KEY_RIGHT;

        static chtype LLCORNER;
        static chtype LRCORNER;
        static chtype ULCORNER;
        static chtype URCORNER;
        static chtype LTEE;
        static chtype RTEE;
        static chtype VLINE;
        static chtype HLINE;


        static void Initialize(const Vect2& dim);

        static void DrawChar(int c) { Instance().putCharacter(c); }
        static void DrawString(const std::string &string) { Instance().drawString(string.c_str()); }
        static void DrawString(const char *string) { Instance().drawString(string); }
        static void DrawString(const std::string &string, int x, int y) { Instance().drawString(string.c_str(), x, y); }
        static void DrawString(const char *string, int x, int y) { Instance().drawString(string, x, y); }

        static void DrawStringBottomRight(const std::string &string) { Instance().privDrawStringBottomRight(string.c_str()); }
        static void DrawStringBottomLeft(const std::string &string) { Instance().privDrawStringBottomLeft(string.c_str()); }

        static int GetChar();

        static short GetColorPair(const ColorPair& color) {
            return Instance().privGetColorPair(color);
        }
        static short GetPairNumber(const ColorPair& color) {
            return Instance().privGetPairNumber(color);
        }

        static void Beep() { Instance().doBeep(); }
        static void Flash() { Instance().doFlash(); }
        static void Resize(const Vect2& dim);

        static void Draw(ComponentMap& componentMap);
        static void Refresh() { refresh(); }

        static void SetCursor(const int level) { Instance().privSetCursor(level); }
        static void MoveCursor(const Vect2& pos) { Instance().privMoveCursor(pos); }

    private:

        typedef std::unordered_map<Color, short, color_hash> ColorMap;
        typedef std::unordered_map<ColorPair, short, color_pair_hash> ColorPairMap;

        // Instance Data
        Vect2 dimensions;
        Vect2 cursor_pos;
        int inputTimeout;
        size_t buff_size;
        ColorMap colorMap;
        ColorPairMap colorPairMap;

        chtype* buffer;

        // Static to Instance Methods
        int getCharacter();
        void putCharacter(int c);
        void drawString(const char *string);
        void drawString(const char *string, int x, int y);
        void privDrawStringBottomRight(const char *string);
        void privDrawStringBottomLeft(const char *string);
        void doBeep();
        void doFlash();
        short privGetColorPair(const ColorPair&);
        short privGetPairNumber(const ColorPair&);
        void privMoveCursor(const Vect2& dim);
        void privSetCursor(const int level);

        void drawComponent(TextComponent& component);
        void clearBuffer();

        // Static Data


        static CursesManager& Instance();
        friend class CursenApplication;

        CursesManager();
        CursesManager(const CursesManager& other) = delete;
        CursesManager(CursesManager&& other) noexcept = delete;
        CursesManager& operator = (const CursesManager& other) = delete;
        CursesManager& operator = (CursesManager&& other) = delete;
        ~CursesManager();

    };

}

#endif //CURSEN_CURSESMANAGER_H
