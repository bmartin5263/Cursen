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

        static void Write(const std::string& string, int x, int y, const ColorPair& color = ColorPair::NONE) { Write(string.c_str(), x, y, color); }
        static void Write(const char* string, int x, int y, const ColorPair& color = ColorPair::NONE);
        static void Write(const chtype* string, int x, int y);
        static void Write(const chtype* string, int x, int y, size_t len);

        static void WriteBottomRight(const std::string& string);
        static void WriteBottomLeft(const std::string& string);

        static int GetChar();

        static short GetColorPair(const ColorPair& color)
        {
            return Instance().privGetColorPair(color);
        }

        static void Beep() { Instance().doBeep(); }
        static void Flash() { Instance().doFlash(); }
        static void Resize(const Vect2& dim);

        static void Draw(ComponentMap& componentMap);
        static void Refresh() { refresh(); }

        static void SetCursor(int level) { Instance().privSetCursor(level); }
        static void MoveCursor(const Vect2& pos) { Instance().privMoveCursor(pos); }

    private:

        typedef std::unordered_map<Color, short, color_hash> ColorMap;
        typedef std::unordered_map<ColorPair, short, color_pair_hash> ColorPairMap;

        // Instance Data
        Vect2 dimensions;
        Vect2 cursor_pos;
        int inputTimeout;
        size_t buffer_size;
        ColorMap colorMap;
        ColorPairMap colorPairMap;

        chtype* component_layer;
        chtype* text_layer;

        // Static to Instance Methods
        void putCharacter(int c);
        void drawString(const char *string);
        void drawString(const char *string, int x, int y);
        void doBeep();
        void doFlash();
        short privGetColorPair(const ColorPair&);
        void privMoveCursor(const Vect2& dim);
        void privSetCursor(int level);

        void render(TextComponent& component);
        void clearBuffer(chtype* buffer_to_clear);
        void nullBuffer(chtype* buffer_to_clear);

        void clearScreen();

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
