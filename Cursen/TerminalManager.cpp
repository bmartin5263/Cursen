//
// Created by Brandon Martin on 11/21/18.
//

#include "TerminalManager.h"
#include "Canvas.h"
#include "SFML/Graphics.hpp"

TerminalManager* TerminalManager::managerInstance = nullptr;

TerminalManager::TerminalManager() :
    mainCanvas(nullptr)
{
}

void TerminalManager::privInitialize()
{
    initializeCurses();
    mainCanvas = new Canvas(sf::Vector2i(0,0), sf::Vector2i(0,0));
}

void TerminalManager::initializeCurses() {
    printf("\e[8;26;50t");
    initscr();
    start_color();
    curs_set(0);
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    box(stdscr, 0, 0);
    refresh();
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
    printf("Deconstructed Terminal Manager\n");
}