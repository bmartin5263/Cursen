//
// Created by Brandon Martin on 3/7/19.
//

#include "CursesManager.h"
#include "ncurses.h"

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
    while (!drawQueue.empty()) {
        drawRequest = drawQueue.front();
        drawQueue.pop();
        std::vector<std::vector<chtype>>* body = drawRequest.getBody();

        // Get Position of Component
        Position* position = drawRequest.getPosition();

        // Clear old area
        for (int i = 0; i < position->current.rows; i++) {
            for (int j = 0; j < position->current.cols; j++) {
                mvaddch(position->current.y + i, position->current.x + j, ' ');
            }
        }

        for (int i = 0; i < position->next.rows; i++) {
            std::vector<chtype> line = (*body)[i];
            mvaddchstr(position->next.y + i, position->next.x, &line[0]);
        }

        position->current = position->next;
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
