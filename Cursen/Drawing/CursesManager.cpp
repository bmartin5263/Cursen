//
// Created by Brandon Martin on 3/7/19.
//

#include <Components/Component.h>
#include <thread>
#include "CursesManager.h"
#include "ncurses.h"
#include "Drawing/TextBody.h"

CursesManager* CursesManager::instance = nullptr;

CursesManager::CursesManager() :
    requestingFullRedraw(false)
{
}

int CursesManager::getCharacter() {
    int c = getch();
    return c;
}

void CursesManager::initializeCurses() {
    Vect2i dimensions = CursenApplication::GetCurrentForm()->getDimensions();
    Resize(dimensions);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

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

short CursesManager::privGetColorPair(const ColorPair & colorPair) {
    ColorPairMap::iterator it;

    it = colorPairMap.find(colorPair);
    if (it != colorPairMap.end() )
    {
        return COLOR_PAIR(colorPairMap[colorPair]);
    }
    else {
        short pairNum = (short)(colorPairMap.size() + 1);
        init_pair(pairNum, colorPair.fg.val, colorPair.bg.val);
        colorPairMap[colorPair] = pairNum;
        return COLOR_PAIR(pairNum);
    }
}

void CursesManager::privDraw() {

    // Clear the old screen
    erase();
    box(stdscr, 0, 0);

    // Set up the queue for a BFS traversal
    std::queue<Component*> drawQueue;
    Component* node;
    drawQueue.push(CursenApplication::GetCurrentForm());

    while(!drawQueue.empty()) {
        node = drawQueue.front();

        // Push on children
        for (Component* child : node->components) {
            drawQueue.push(child);
        }

        // Check if component needs a redraw
        if (node->isInvalid()) {
            node->render();
            node->validate();
        }

        TextBody& body = node->content;
        chtype** content = body.getContent();
        Vect2i dimensions = body.getDimensions();
        Vect2i position = node->position;

        for (int i = 0; i < dimensions.y; i++) {
            chtype* row = content[i];
            int offset = 0;
            if (position.x < 0) {
                offset = -position.x;
            }
            if (offset < dimensions.x) {
                mvaddchstr(position.y + i, position.x + offset, &row[0 + offset]);
            }
        }

        drawQueue.pop();
    }
    refresh();
}

void CursesManager::privRequestCompleteRedraw() {
    if (!requestingFullRedraw) {
        CursenApplication::GetCurrentForm()->invalidate();
        requestingFullRedraw = true;
    }
}

void CursesManager::privResize(const Vect2i &dim) {
    std::string resizeString = "\e[8;" + std::to_string(dim.y) + ";" + std::to_string(dim.x) + "t";
    printf("%s", resizeString.c_str());
    fflush(stdout);
}