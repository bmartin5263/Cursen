//
// Created by Brandon Martin on 11/21/18.
//

#include <thread>
#include "SpriteFrame.h"
#include "TerminalManager.h"
#include "SFML/Graphics.hpp"

TerminalManager* TerminalManager::managerInstance = nullptr;

TerminalManager::TerminalManager()
{
}

void TerminalManager::privInitialize()
{
    initializeCurses();
}

void TerminalManager::Draw(const CursenSprite &sprite) {
    SpriteFrame frame = sprite.getCurrentFrame();
    sf::Vector2i pos = sprite.getPosition();

    auto body = frame.getBody();
    int verticalOffset = 0;

    for (std::string line : body) {
        mvaddstr(pos.y + verticalOffset, pos.x, line.c_str());
        verticalOffset++;
    }
}

void TerminalManager::Resize(int rows, int columns) {
    std::string resizeString = "\e[8;" + std::to_string(rows) + ";" + std::to_string(columns) + "t";
    printf("%s", resizeString.c_str());
    fflush(stdout);
}

void TerminalManager::initializeCurses() {
    // Attempt to resize terminal
    Resize(WIN_ROWS, WIN_COLS);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));    // slight delay for change to take effect

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

void TerminalManager::privClearScreen() {
    erase();
    box(stdscr, 0, 0);
}

void TerminalManager::privRefreshScreen() {
    refresh();
}

void TerminalManager::Terminate() {
    delete managerInstance;
    managerInstance = nullptr;
}

TerminalManager::~TerminalManager()
{
    flushinp();     // Flush any remaining curses input
    endwin();       // End curses
    printf("[Terminal Manager] Deconstructed\n");
}