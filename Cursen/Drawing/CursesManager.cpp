//
// Created by Brandon Martin on 3/7/19.
//

#include <thread>
#include <ncurses.h>

#include "Cursen/Components/TextComponent.h"
#include "CursesManager.h"
#include "Content.h"
#include "Cursen/CursenApplication.h"

namespace cursen
{

    chtype CursesManager::LLCORNER = '?';
    chtype CursesManager::LRCORNER = '?';
    chtype CursesManager::HLINE = '?';
    chtype CursesManager::VLINE = '?';
    chtype CursesManager::ULCORNER = '?';
    chtype CursesManager::URCORNER = '?';
    chtype CursesManager::LTEE = '?';
    chtype CursesManager::RTEE = '?';

    CursesManager::CursesManager()
    {
    }

    int CursesManager::getCharacter()
    {
        int c = getch();
        return c;
    }

    void CursesManager::initializeCurses(const Vect2& dim)
    {
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
        notimeout(stdscr, TRUE);

        CursesManager::LLCORNER = ACS_LLCORNER;
        CursesManager::LRCORNER = ACS_LRCORNER;
        CursesManager::HLINE = ACS_HLINE;
        CursesManager::VLINE = ACS_VLINE;
        CursesManager::ULCORNER = ACS_ULCORNER;
        CursesManager::URCORNER = ACS_URCORNER;
        CursesManager::LTEE = ACS_LTEE;
        CursesManager::RTEE = ACS_RTEE;

        // Draw A box onto main window 'stdscr'
        box(stdscr, 0, 0);
        refresh();
    }

    void CursesManager::putCharacter(int c)
    {
        addch((chtype) c);
        refresh();
    }

    CursesManager::~CursesManager()
    {
        flushinp();     // Flush any remaining curses input
        endwin();       // End curses
    }

    void CursesManager::doBeep()
    {
        beep();
    }

    void CursesManager::doFlash()
    {
        flash();
    }

    void CursesManager::drawString(const char* string)
    {
        short i = privGetColorPair(ColorPair());
        attron(i);
        addstr(string);
        attroff(i);
    }

    void CursesManager::drawString(const char* string, int x, int y)
    {
        short i = privGetColorPair(ColorPair());
        attron(i);
        mvaddstr(y, x, string);
        attroff(i);
    }

    short CursesManager::privGetColorPair(const ColorPair& colorPair)
    {
        ColorPairMap::iterator it;
        it = colorPairMap.find(colorPair);
        if (it != colorPairMap.end())
        {
            return COLOR_PAIR(colorPairMap[colorPair]);
        }
        else
        {
            short pairNum = (short) (colorPairMap.size() + 1);
            init_pair(pairNum, colorPair.fg.val, colorPair.bg.val);
            colorPairMap[colorPair] = pairNum;
            return COLOR_PAIR(pairNum);
        }
    }

    short CursesManager::privGetPairNumber(const ColorPair& colorPair)
    {
        ColorPairMap::iterator it;

        it = colorPairMap.find(colorPair);
        if (it != colorPairMap.end())
        {
            return colorPairMap[colorPair];
        }
        else
        {
            short pairNum = (short) (colorPairMap.size() + 1);
            init_pair(pairNum, colorPair.fg.val, colorPair.bg.val);
            colorPairMap[colorPair] = pairNum;
            return pairNum;
        }
    }

    void CursesManager::privResize(const Vect2& dim)
    {
        std::string resizeString = "\e[8;" + std::to_string(dim.y) + ";" + std::to_string(dim.x) + "t";
        //printf("%ConnectionSevered", resizeString.c_str());
        fflush(stdout);
    }

    void CursesManager::drawComponent(TextComponent& component)
    {
        // Check if component needs a redraw
        if (component.isInvalid())
        {
            component.render();
            component.validate();
        }

        Content& content = component.getContent();

        chtype** text = content.getText();
        Vect2 dimensions = content.getDimensions();
        Vect2 position = component.getPosition();

        for (int y = 0; y < dimensions.y; ++y)
        {
            chtype* row = text[y];
            int offset = 0;
            if (position.x < 0)
            {
                offset = -position.x;
            }
            if (offset < dimensions.x)
            {
                int i = 0;
                for (int x = offset; x < dimensions.x; ++x)
                {
                    chtype c = row[x];
                    if (c != Content::TRANSPARENT)
                    {
                        mvaddch(position.y + y, position.x + i, c);
                    }
                    i++;
                }
            }
        }
    }

    void CursesManager::privDrawStringBottomRight(const char* string)
    {
        int x = (int) (dimensions.x - strlen(string));
        int y = dimensions.y - 1;
        drawString(string, x, y);
    }

    void CursesManager::privDrawStringBottomLeft(const char* string)
    {
        int y = dimensions.y - 1;
        drawString(string, 0, y);
    }

    //void CursesManager::privRegisterComponent(TextComponent* component)
    //{
    //    auto it = componentMap[component->drawOrder].find(component);
    //    if (it == componentMap[component->drawOrder].end())
    //    {
    //        componentMap[component->drawOrder].insert(component);
    //    }
    //}
//
    //void CursesManager::privDeregisterComponent(TextComponent* component)
    //{
    //    auto it = componentMap[component->drawOrder].find(component);
    //    if (it != componentMap[component->drawOrder].end())
    //    {
    //        componentMap[component->drawOrder].erase(component);
    //    }
    //}
//
    //void CursesManager::privSetDrawOrder(TextComponent* component, int order)
    //{
    //    componentMap[component->getDrawOrder()].erase(component);
    //    componentMap[order].insert(component);
    //}

    void CursesManager::privDraw(ComponentMap& componentMap)
    {
        CursenDebugger& debugger = CursenApplication::GetDebugger();

        // Clear the old screen
        erase();

        for (auto pair = componentMap.begin(); pair != componentMap.end(); ++pair)
        {
            for (auto componentIter = (*pair).second.begin(); componentIter != (*pair).second.end(); ++componentIter)
            {
                TextComponent& component = *(*componentIter);
                if (!component.isHidden())
                {
                    drawComponent(component);
                }
            }
        }

        if (debugger.getInspectionPointer() != nullptr)
        {
            InspectionPointer* inspectionPointer = debugger.getInspectionPointer();
            drawComponent(*inspectionPointer);
            privDrawStringBottomRight(&(*inspectionPointer->getPosition().toString().c_str()));
            Vect2 boxSize = inspectionPointer->getBoxSize();
            privDrawStringBottomLeft(boxSize.toString().c_str());
            Vect2 boxPos = inspectionPointer->getBoxLoc();
            for (int y = 0; y < boxSize.y; y++)
            {
                mvchgat(boxPos.y + y, boxPos.x, boxSize.x, A_NORMAL,
                        privGetPairNumber(ColorPair(Color::WHITE, Color::DARK_BLUE)), NULL);
            }
        }

        move(cursor_pos.y, cursor_pos.x);

        //refresh();
    }

    void CursesManager::privMoveCursor(const Vect2& dim)
    {
        cursor_pos = dim;
    }

    void CursesManager::privSetCursor(const int level)
    {
        curs_set(level);
    }

    CursesManager& CursesManager::Instance()
    {
        return CursenApplication::GetCursesManager();
    }
}
