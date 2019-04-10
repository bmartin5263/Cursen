//
// Created by Brandon Martin on 3/7/19.
//

#ifndef CURSEN_CURSESMANAGER_H
#define CURSEN_CURSESMANAGER_H

#include <ncurses.h>
#include <queue>
#include <string>
#include <unordered_map>
#include <Components/Form.h>
#include <CursenApplication.h>
#include "Color.h"
#include "ColorPair.h"

using namespace cursen;

class Component;

class CursesManager {

public:

    static const int ESCAPE = 27;
    static const int ENTER = 10;
    static const int BACKSPACE = 127;
    static const int UP = KEY_UP;
    static const int DOWN = KEY_DOWN;
    static const int LEFT = KEY_LEFT;
    static const int RIGHT = KEY_RIGHT;

    static const chtype LOWER_LEFT;
    static const chtype LOWER_RIGHT;
    static const chtype UPPER_LEFT;
    static const chtype UPPER_RIGHT;
    static const chtype LEFT_T;
    static const chtype RIGHT_T;
    static const chtype VLINE;
    static const chtype HLINE;


    static void Initialize(const Size& dim) { Instance().initializeCurses(dim); }
    static void Terminate() { Instance().terminateCurses(); }

    static void DrawChar(int c) { instance->putCharacter(c); }
    static void DrawString(const std::string &string) { instance->drawString(string.c_str()); }
    static void DrawString(const char *string) { instance->drawString(string); }
    static void DrawString(const std::string &string, int x, int y) { instance->drawString(string.c_str(), x, y); }
    static void DrawString(const char *string, int x, int y) { instance->drawString(string, x, y); }

    static void DrawStringBottomRight(const std::string &string) { Instance().privDrawStringBottomRight(string.c_str()); }
    static void DrawStringBottomLeft(const std::string &string) { Instance().privDrawStringBottomLeft(string.c_str()); }

    static int GetChar() { return instance->getCharacter(); }

    static short GetColorPair(const ColorPair& color) { return instance->privGetColorPair(color); }
    static short GetPairNumber(const ColorPair& color) { return instance->privGetPairNumber(color); }

    static void Beep() { instance->doBeep(); }
    static void Flash() { instance->doFlash(); }
    static void Resize(const Size& dim) { Instance().privResize(dim); }

    static void Draw() { Instance().privDraw(); };

private:

    typedef std::unordered_map<Color, short, color_hash> ColorMap;
    typedef std::unordered_map<ColorPair, short, color_pair_hash> ColorPairMap;

    // Instance Data
    Size dimensions;
    int inputTimeout;
    ColorMap colorMap;
    ColorPairMap colorPairMap;
    bool requestingFullRedraw;

    // Methods
    void initializeCurses(const Size& dim);
    void terminateCurses();

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
    void privDraw();
    void privResize(const Size& dim);

    void drawComponent(Component& component);

    // Static Data

    static CursesManager* instance;

    static CursesManager& Instance() {
        if (instance == nullptr)
            instance = new CursesManager;
        return *instance;
    }

    CursesManager();
    CursesManager(const CursesManager& other) = delete;
    CursesManager(CursesManager&& other) noexcept = delete;
    CursesManager& operator = (const CursesManager& other) = delete;
    CursesManager& operator = (CursesManager&& other) = delete;
    ~CursesManager();

};


#endif //CURSEN_CURSESMANAGER_H
