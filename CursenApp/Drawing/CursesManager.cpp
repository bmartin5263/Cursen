//
// Created by Brandon Martin on 3/7/19.
//

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
    // Initialize Curses
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

void CursesManager::processDrawEvents() {
    DrawRequest drawRequest;
    ClearRequest clearRequest;

    while(!clearQueue.empty()) {
        clearRequest = clearQueue.front();
        clearQueue.pop();

        Vect2d position = clearRequest.getPosition();
        Vect2d dimensions = clearRequest.getDimensions();

        for (int i = 0; i < dimensions.y; i++) {
            for (int j = 0; j < dimensions.x; j++) {
                mvaddch(position.y + i, position.x + j, ' ');
            }
        }
    }

    while (!drawQueue.empty()) {
        drawRequest = drawQueue.front();
        drawQueue.pop();

        // Get Text Body
        TextBody* body = drawRequest.getBody();
        chtype** content = body->getContent();
        Vect2d dimensions = body->getDimensions();

        // Get Position of Component
        Vect2d position = drawRequest.getPosition();

        for (int i = 0; i < dimensions.y; i++) {
            chtype* row = content[i];
            mvaddchstr(position.y + i, position.x, &row[0]);
        }

    }
    refresh();
}

void CursesManager::drawString(const char *string, int x, int y) {
    mvaddstr(y, x, string);
}

void CursesManager::enqueueDraw(DrawRequest request) {
    drawQueue.push(request);
}

DrawRequest CursesManager::getDrawRequest() {
    return DrawRequest();
}

ClearRequest CursesManager::getClearRequest() {
    return ClearRequest();
}

void CursesManager::enqueueClear(ClearRequest request) {
    clearQueue.push(request);
}
