#include <iostream>
#include <fstream>
#include <string>
#include <ncurses.h>
#include <cmath>
#include <thread>
#include <TerminalManager.h>
#include <StopWatch.h>
#include <Cursor/Cursor.h>
#include "Engine.h"
#include "SFML/Network.hpp"
#include "CursenApplication.h"
#include "Demo/TestForm.h"

void speedTest() {

    int x = 0;
    int y = 0;
    int length = 20;
    int height = 3;

    StopWatch cursesWatch;
    cursesWatch.tick();

    for (int j = 0; j < 100000; j++) {
        erase();
        for (int i = 1; i < length-1; i++) {
            mvaddch(y, x+i, ACS_HLINE);
            mvaddch(y+2, x+i, ACS_HLINE);
        }
        mvaddch(y, x, ACS_ULCORNER);
        mvaddch(y+height-1, x, ACS_LLCORNER);
        mvaddch(y+1, x, ACS_VLINE);
        mvaddch(y+1, x+length-1, ACS_VLINE);
        mvaddch(y, x+length-1, ACS_URCORNER);
        mvaddch(y+height-1, x+length-1, ACS_LRCORNER);

        int textField = length - 2;
        int center = (int)floor(textField/2);
        int offset = (int)floor(11/2);
        mvaddstr(y+1, x+1+center-offset, "Hello World");

        refresh();
    }

    cursesWatch.tock();

    StopWatch bodyWatch;
    bodyWatch.tick();

    // Construct Body

    std::vector<std::vector<chtype>> body;
    std::vector<chtype> userContent = {'H','e','l','l','o',' ','W','o','r','l','d','\0'};

    std::vector<chtype> line1(21);
    std::vector<chtype> line2(21);
    std::vector<chtype> line3(21);

    line1[0] = ACS_ULCORNER;
    line2[0] = ACS_VLINE;
    line3[0] = ACS_LLCORNER;
    for (int i = 0; i < 18; i++) {
        line1[1+i] = ACS_HLINE | COLOR_PAIR(1);
        line2[1+i] = ' ';
        line3[1+i] = ACS_HLINE;
    }
    line1[19] = ACS_URCORNER;
    line2[19] = ACS_VLINE;
    line3[19] = ACS_LRCORNER;

    line1[20] = '\0';
    line2[20] = '\0';
    line3[20] = '\0';

    body.push_back(line1);
    body.push_back(line2);
    body.push_back(line3);

    for (int j = 0; j < 100000; j++) {
        erase();

        for (int i = 0; i < body.size(); i++) {
            mvaddchstr(0 + i, 0, &body[i][0]);
        }
        mvaddchstr(1, 1, &userContent[0]);
        refresh();
    }

    bodyWatch.tock();

    mvaddstr(5, 0, ("Curses: " + std::to_string(cursesWatch.getMilliseconds()) + "ms").c_str());
    mvaddstr(6, 0, ("Bodied: " + std::to_string(bodyWatch.getMilliseconds()) + "ms").c_str());
    refresh();
    getch();

}

int main() {
    //CursenApplication::SetColorPalette(ColorPalette::LIGHT);
    CursenApplication::Run(new TestForm());
}