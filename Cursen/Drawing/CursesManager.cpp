//
// Created by Brandon Martin on 3/7/19.
//

#include <Components/Component.h>
#include <thread>
#include "CursesManager.h"
#include "ncurses.h"
#include "Drawing/Content.h"

CursesManager* CursesManager::instance = nullptr;

const chtype CursesManager::LOWER_LEFT = ACS_LLCORNER;
const chtype CursesManager::LOWER_RIGHT = ACS_LRCORNER;
const chtype CursesManager::HLINE = ACS_HLINE;
const chtype CursesManager::VLINE = ACS_VLINE;
const chtype CursesManager::UPPER_LEFT = ACS_ULCORNER;
const chtype CursesManager::UPPER_RIGHT = ACS_URCORNER;
const chtype CursesManager::LEFT_T = ACS_LTEE;
const chtype CursesManager::RIGHT_T = ACS_RTEE;

CursesManager::CursesManager() :
    requestingFullRedraw(false)
{
}

int CursesManager::getCharacter() {
    int c = getch();
    return c;
}

void CursesManager::initializeCurses(const Size& dim) {
    dimensions = dim;
    Resize(dimensions);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // initialize Curses
    initscr();                  // First step to initialize curses
    start_color();              // Allow color
    curs_set(0);                // Turn off cursor
    cbreak();
    keypad(stdscr, TRUE);
    noecho();                   // Don't echo characters
    nodelay(stdscr, TRUE);

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
    short i = privGetColorPair(ColorPair());
    attron(i);
    addstr(string);
    attroff(i);
}

void CursesManager::drawString(const char *string, int x, int y) {
    short i = privGetColorPair(ColorPair());
    attron(i);
    mvaddstr(y, x, string);
    attroff(i);
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

short CursesManager::privGetPairNumber(const ColorPair &colorPair) {
    ColorPairMap::iterator it;

    it = colorPairMap.find(colorPair);
    if (it != colorPairMap.end() )
    {
        return colorPairMap[colorPair];
    }
    else {
        short pairNum = (short)(colorPairMap.size() + 1);
        init_pair(pairNum, colorPair.fg.val, colorPair.bg.val);
        colorPairMap[colorPair] = pairNum;
        return pairNum;
    }
}


void CursesManager::privDraw() {
    CursenDebugger& debugger = CursenApplication::GetDebugger();

    // Clear the old screen
    erase();
    //bkgd(GetColorPair(ColorPair(CursenApplication::GetColorPalette().getForeground(), CursenApplication::GetColorPalette().getBackground())));
    short i = privGetColorPair(ColorPair());
    attron(i);
    box(stdscr, 0, 0);
    attroff(i);

    // Set up the queue for a BFS traversal
    std::queue<Component*> drawQueue;
    Component* component;
    drawQueue.push(CursenApplication::GetCurrentForm());

    while(!drawQueue.empty()) {
        component = drawQueue.front();

        // Push on children
        for (Component* child : component->children) {
            drawQueue.push(child);
        }

        if (!component->isHidden()) {
            drawComponent(*component);
        }

        drawQueue.pop();
    }

    if (debugger.getInspectionPointer() != nullptr) {
        InspectionPointer* inspectionPointer = debugger.getInspectionPointer();
        drawComponent(*inspectionPointer);
        privDrawStringBottomRight(&(*inspectionPointer->getPosition().toString().c_str()));
        Size boxSize = inspectionPointer->getBoxSize();
        privDrawStringBottomLeft(boxSize.toString().c_str());
        Size boxPos = inspectionPointer->getBoxLoc();
        for (int y = 0; y < boxSize.y; y++) {
            mvchgat(boxPos.y + y, boxPos.x , boxSize.x, A_NORMAL, privGetPairNumber(ColorPair(Color::WHITE, Color::DARK_BLUE)), NULL);
        }
    }

    refresh();
}

void CursesManager::privResize(const Size &dim) {
    std::string resizeString = "\e[8;" + std::to_string(dim.y) + ";" + std::to_string(dim.x) + "t";
    printf("%s", resizeString.c_str());
    fflush(stdout);
}

void CursesManager::drawComponent(Component &component) {
    // Check if component needs a redraw
    if (component.isInvalid()) {
        component.render();
        component.validate();
    }

    Content* content = component.getContent();

    if (content != nullptr) {
        chtype** text = content->getText();
        Size dimensions = content->getDimensions();
        Size position = component.getPosition();

        for (int i = 0; i < dimensions.y; i++) {
            chtype* row = text[i];
            int offset = 0;
            if (position.x < 0) {
                offset = -position.x;
            }
            if (offset < dimensions.x) {
                mvaddchstr(position.y + i, position.x + offset, &row[0 + offset]);
            }
        }
        if (component.debug_coordinates) {
            std::string coordinates = std::to_string(position.x) + "," + std::to_string(position.y);
            unsigned long len = coordinates.size();
            mvaddstr(position.y, position.x + dimensions.x - len, coordinates.c_str());
        }
    }
}

void CursesManager::privDrawStringBottomRight(const char *string) {
    int x = (int)(dimensions.x - strlen(string));
    int y = dimensions.y - 1;
    drawString(string, x, y);
}

void CursesManager::privDrawStringBottomLeft(const char *string) {
    int y = dimensions.y - 1;
    drawString(string, 0, y);
}

void CursesManager::privRegisterComponent(Component *component){
    auto it = componentMap[component->drawOrder].find(component);
    if (it == componentMap[component->drawOrder].end())
    {
        componentMap[component->drawOrder].insert(component);
    }
}

void CursesManager::privDeregisterComponent(Component *component) {
    auto it = componentMap[component->drawOrder].find(component);
    if (it != componentMap[component->drawOrder].end())
    {
        componentMap[component->drawOrder].erase(component);
    }
}

void CursesManager::privSetDrawOrder(Component *component, int order) {
    componentMap[component->getDrawOrder()].erase(component);
    componentMap[order].insert(component);
}

void CursesManager::privNewDraw() {
    CursenDebugger& debugger = CursenApplication::GetDebugger();

    // Clear the old screen
    erase();
    //bkgd(GetColorPair(ColorPair(CursenApplication::GetColorPalette().getForeground(), CursenApplication::GetColorPalette().getBackground())));

    // Set up the queue for a BFS traversal

    for(auto pair = componentMap.begin(); pair != componentMap.end(); ++pair)
    {
        for(auto componentIter = pair->second.begin(); componentIter != pair->second.end(); ++componentIter)
        {
            Component& component = *(*componentIter);
            if (!component.isHidden()) {
                drawComponent(component);
            }
        }
    }

    if (debugger.getInspectionPointer() != nullptr) {
        InspectionPointer* inspectionPointer = debugger.getInspectionPointer();
        drawComponent(*inspectionPointer);
        privDrawStringBottomRight(&(*inspectionPointer->getPosition().toString().c_str()));
        Size boxSize = inspectionPointer->getBoxSize();
        privDrawStringBottomLeft(boxSize.toString().c_str());
        Size boxPos = inspectionPointer->getBoxLoc();
        for (int y = 0; y < boxSize.y; y++) {
            mvchgat(boxPos.y + y, boxPos.x , boxSize.x, A_NORMAL, privGetPairNumber(ColorPair(Color::WHITE, Color::DARK_BLUE)), NULL);
        }
    }

    refresh();
}
