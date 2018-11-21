//
// Created by Brandon Martin on 11/21/18.
//

#include <thread>
#include "TerminalManager.h"
#include "Canvas.h"
#include "SFML/Graphics.hpp"
#include "UITools.h"

TerminalManager* TerminalManager::managerInstance = nullptr;

TerminalManager::TerminalManager() :
    mainCanvas(nullptr)
{
}

void TerminalManager::privInitialize()
{
    initializeCurses();
    initializeCanvas();

    // Placing color initializing here for now
    UITools::AddColor("white", 15, COLOR_BLACK);
    UITools::AddColor("blue", 39, COLOR_BLACK);
    UITools::AddColor("red", 199, COLOR_BLACK);
    UITools::AddColor("green", 82, COLOR_BLACK);
    UITools::AddColor("white", 226, COLOR_BLACK);
    UITools::AddColor("gray", 8, COLOR_BLACK);
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

void TerminalManager::initializeCanvas() {
    mainCanvas = new Canvas(sf::Vector2i(0,0), sf::Vector2i(WIN_COLS, WIN_ROWS));
}


Canvas& TerminalManager::privGetCanvas()
{
    return *mainCanvas;
}

void TerminalManager::Terminate() {
    delete managerInstance;
    managerInstance = nullptr;
}

TerminalManager::~TerminalManager()
{
    delete mainCanvas;

    flushinp();     // Flush any remaining curses input
    endwin();       // End curses
    printf("[Terminal Manager] Deconstructed\n");
}