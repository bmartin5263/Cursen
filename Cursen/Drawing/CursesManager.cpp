//
// Created by Brandon Martin on 3/7/19.
//

#include <Components/Component.h>
#include "CursesManager.h"
#include "ncurses.h"
#include "Drawing/TextBody.h"

CursesManager* CursesManager::instance = nullptr;

CursesManager::CursesManager() {
}

int CursesManager::getCharacter() {
    int c = getch();
    return c;
}

void CursesManager::initializeCurses() {
    // initialize Curses
    initscr();                  // First step to initialize curses
    start_color();              // Allow color
    curs_set(0);                // Turn off cursor
    cbreak();
    keypad(stdscr, TRUE);
    noecho();                   // Don't echo characters

    // Draw A box onto main window 'stdscr'
    box(stdscr, 0, 0);
    refresh();
}

void CursesManager::putCharacter(int c) {
    addch((chtype)c);
    refresh();
}

void CursesManager::terminateCurses() {
    delete instance;
    instance = nullptr;
}

CursesManager::~CursesManager() {
    flushinp();     // Flush any remaining curses input
    endwin();       // End curses
}

void CursesManager::doBeep() {
    beep();
}

void CursesManager::doFlash() {
    flash();
}

void CursesManager::drawString(const char *string) {
    addstr(string);
}

void CursesManager::drawString(const char *string, int x, int y) {
    mvaddstr(y, x, string);
}

short CursesManager::privGetColorPair(const cursen::Color& color) {
    ColorMap::iterator it;

    it = colorMap.find(color);
    if (it != colorMap.end() )
    {
        return COLOR_PAIR(colorMap[color]);
    }
    else {
        short pairNum = (short)(colorMap.size() + 1);
        init_pair(pairNum, color.fg, color.bg);
        colorMap[color] = pairNum;
        return COLOR_PAIR(colorMap[color]);
    }
}

void CursesManager::privRequestDraw(Component *component) {
    componentQueue.push(component);
    clearQueue.push(component->clearRequest);
}

void CursesManager::privDraw() {

    ClearRequest clearRequest;

    while(!clearQueue.empty()) {
        clearRequest = clearQueue.front();
        clearQueue.pop();

        Vect2i position = clearRequest.getPosition();
        Vect2i dimensions = clearRequest.getDimensions();

        for (int i = 0; i < dimensions.y; i++) {
            for (int j = 0; j < dimensions.x; j++) {
                mvaddch(position.y + i, position.x + j, ' ');
            }
        }
    }

    Component* next;
    while (!componentQueue.empty()) {
        next = componentQueue.front();
        componentQueue.pop();

        TextBody& body = next->body;
        chtype** content = body.getContent();
        Vect2i dimensions = body.getDimensions();
        Vect2i position = next->position;

        for (int i = 0; i < dimensions.y; i++) {
            chtype* row = content[i];
            mvaddchstr(position.y + i, position.x, &row[0]);
        }

        clearRequest = ClearRequest();
        clearRequest.setPosition(position);
        clearRequest.setDimensions(body.getDimensions());
        next->clearRequest = clearRequest;
    }
    refresh();

}

void CursesManager::privRequestCompleteRedraw() {
    CursenApplication::GetCurrentForm()->invalidate();
}