//
// Created by Brandon Martin on 11/21/18.
//

#include <thread>
#include "TerminalManager.h"
#include "Canvas.h"
#include "SFML/Graphics.hpp"

TerminalManager* TerminalManager::managerInstance = nullptr;

TerminalManager::TerminalManager()
{
}

void TerminalManager::privInitialize()
{
    initializeCurses();
}

void TerminalManager::initializeCurses() {
    // Attempt to resize terminal
    std::string resizeString = "\e[8;" + std::to_string(WIN_COLS) + ";" + std::to_string(WIN_ROWS) + "t";
    printf("%s", resizeString.c_str());
    fflush(stdout);
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