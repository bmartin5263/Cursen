//
// Created by Brandon Martin on 5/20/19.
//

#ifndef CURSEN_DEMOS_H
#define CURSEN_DEMOS_H

//#include <iostream>
//#include <fstream>
//#include <string>
//#include <ncurses.h>
//#include <thread>
//#include <Cursen/Tools/StopWatch.h>
//
//void cursesTest()
//{
//    initscr();                  // First step to initialize curses
//    start_color();              // Allow color
//    curs_set(0);                // Turn off cursor
//    cbreak();
//    keypad(stdscr, TRUE);
//    noecho();                   // Don't echo characters
//    nodelay(stdscr, TRUE);
//
//    // Draw A box onto main window 'stdscr'
//    box(stdscr, 0, 0);
//
//    addstr("start writing some chars");
//    refresh();
//    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
//    while (getch() != ERR) {
//        addch('1');
//    }
//    refresh();
//    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//
//    endwin();
//}
//
//void speedTest()
//{
//
//    int x = 0;
//    int y = 0;
//    int length = 20;
//    int height = 3;
//
//    StopWatch cursesWatch;
//    cursesWatch.tick();
//
//    for (int j = 0; j < 100000; j++) {
//        erase();
//        for (int i = 1; i < length - 1; i++) {
//            mvaddch(y, x + i, ACS_HLINE);
//            mvaddch(y + 2, x + i, ACS_HLINE);
//        }
//        mvaddch(y, x, ACS_ULCORNER);
//        mvaddch(y + height - 1, x, ACS_LLCORNER);
//        mvaddch(y + 1, x, ACS_VLINE);
//        mvaddch(y + 1, x + length - 1, ACS_VLINE);
//        mvaddch(y, x + length - 1, ACS_URCORNER);
//        mvaddch(y + height - 1, x + length - 1, ACS_LRCORNER);
//
//        int textField = length - 2;
//        int center = (int) floor(textField / 2);
//        int offset = (int) floor(11 / 2);
//        mvaddstr(y + 1, x + 1 + center - offset, "Hello World");
//
//        refresh();
//    }
//
//    cursesWatch.tock();
//
//    StopWatch bodyWatch;
//    bodyWatch.tick();
//
//    // Construct Body
//
//    std::vector<std::vector<chtype>> body;
//    std::vector<chtype> userContent = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '\0'};
//
//    std::vector<chtype> line1(21);
//    std::vector<chtype> line2(21);
//    std::vector<chtype> line3(21);
//
//    line1[0] = ACS_ULCORNER;
//    line2[0] = ACS_VLINE;
//    line3[0] = ACS_LLCORNER;
//    for (int i = 0; i < 18; i++) {
//        line1[1 + i] = ACS_HLINE | COLOR_PAIR(1);
//        line2[1 + i] = ' ';
//        line3[1 + i] = ACS_HLINE;
//    }
//    line1[19] = ACS_URCORNER;
//    line2[19] = ACS_VLINE;
//    line3[19] = ACS_LRCORNER;
//
//    line1[20] = '\0';
//    line2[20] = '\0';
//    line3[20] = '\0';
//
//    body.push_back(line1);
//    body.push_back(line2);
//    body.push_back(line3);
//
//    for (int j = 0; j < 100000; j++) {
//        erase();
//
//        for (int i = 0; i < body.size(); i++) {
//            mvaddchstr(0 + i, 0, &body[i][0]);
//        }
//        mvaddchstr(1, 1, &userContent[0]);
//        refresh();
//    }
//
//    bodyWatch.tock();
//
//    mvaddstr(5, 0, ("Curses: " + std::to_string(cursesWatch.getMilliseconds()) + "ms").c_str());
//    mvaddstr(6, 0, ("Bodied: " + std::to_string(bodyWatch.getMilliseconds()) + "ms").c_str());
//    refresh();
//    getch();
//
//}

//std::this_thread::sleep_for(std::chrono::seconds(5));
//    CursesManager::Initialize(Vect2(70,33));
//
//    chtype c = 'X';
//    c |= Color::ORANGE;
//    c ^= Color::ORANGE;
//    chtype c2 = 'X' | Color::BLUE;
//    chtype c3 = c2 ^ Color::BLUE;
//    chtype c4 = 'X' | Color::GREEN;
//    chtype c5 = 'X' | Color::GREEN;
//    chtype c6 = 'X' | Color::YELLOW;
//
//    chtype s1 = CursesManager::LLCORNER;
//    chtype s2 = CursesManager::LLCORNER | Color::BLUE;
//    chtype s3 = s2 ^ Color::BLUE;
//
//    std::string binary1 = std::bitset<32>(c).to_string();
//    std::string binary2 = std::bitset<32>(c2).to_string();
//    std::string binary3 = std::bitset<32>(c3).to_string();
//    std::string binary4 = std::bitset<32>(c4).to_string();
//    std::string binary5 = std::bitset<32>(c5).to_string();
//    std::string binary6 = std::bitset<32>(c6).to_string();
//
//    std::string sBinary1 = std::bitset<32>(s1).to_string();
//    std::string sBinary2 = std::bitset<32>(s2).to_string();
//    std::string sBinary3 = std::bitset<32>(s3).to_string();
//
//    addch(c);
//    addch(' ');
//    addstr(std::to_string(c).c_str());
//    move(1,0);
//    addstr(binary1.c_str());
//
//    move(3,0);
//    addch(c2);
//    addch(' ');
//    addstr(std::to_string(c2).c_str());
//    move(4,0);
//    addstr(binary2.c_str());
//
//    move(6,0);
//    addch(c3);
//    addch(' ');
//    addstr(std::to_string(c3).c_str());
//    move(7,0);
//    addstr(binary3.c_str());
//
//    move(9,0);
//    addch(c4);
//    addch(' ');
//    addstr(std::to_string(c4).c_str());
//    move(10,0);
//    addstr(binary4.c_str());
//
//    move(12,0);
//    addch(c5);
//    addch(' ');
//    addstr(std::to_string(c5).c_str());
//    move(13,0);
//    addstr(binary5.c_str());
//
//    move(15,0);
//    addch(c6);
//    addch(' ');
//    addstr(std::to_string(c6).c_str());
//    move(16,0);
//    addstr(binary6.c_str());
//
//    move(18,0);
//    addch(s1);
//    addch(' ');
//    addstr(std::to_string(s1).c_str());
//    move(19,0);
//    addstr(sBinary1.c_str());
//
//    move(21,0);
//    addch(s2);
//    addch(' ');
//    addstr(std::to_string(s2).c_str());
//    move(22,0);
//    addstr(sBinary2.c_str());
//
//    move(24,0);
//    addch(s3);
//    addch(' ');
//    addstr(std::to_string(s3).c_str());
//    move(25,0);
//    addstr(sBinary3.c_str());
//
//    refresh();
//    while (getch() != 'X');
//
//    CursesManager::Terminate();


#endif //CURSEN_DEMOS_H
