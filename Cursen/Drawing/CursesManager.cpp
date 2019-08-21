//
// Created by Brandon Martin on 3/7/19.
//

#include <ncurses.h>

#include "Cursen/Components/TextComponent.h"
#include "CursesManager.h"
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

    CursesManager::CursesManager() :
        buff_size(0), buffer(nullptr)
    {
    }

    int CursesManager::GetChar()
    {
        int c = getch();
        return c;
    }

    void CursesManager::Draw(ComponentMap& componentMap)
    {
        auto& debugger = CursenApplication::GetDebugger();
        auto& instance = Instance();
        auto buffer = instance.buffer;
        auto dimensions = instance.dimensions;

        // Clear the old screen
        erase();
        instance.clearBuffer();

        for (auto& pair : componentMap)
        {
            for (auto& componentIter : pair.second)
            {
                TextComponent& component = *componentIter;
                if (!component.isHidden())
                {
                    instance.drawComponent(component);
                }
            }
        }
        move(0,0);
        for (int y = 0; y < dimensions.y; ++y)
        {
            mvaddchnstr(y, 0, &buffer[y*dimensions.x], dimensions.x);
//            for (int x = 0; x < dimensions.x; ++x)
//            {
//                int index = (y * dimensions.x) + x;
//                //mvaddchnstr(y, 0, &buffer[index], dimensions.x);
//                chtype c = buffer[index];
//                addch(c);
//            }
        }

        //        if (debugger.getInspectionPointer() != nullptr)
//        {
//            InspectionPointer* inspectionPointer = debugger.getInspectionPointer();
//            drawComponent(*inspectionPointer);
//            privDrawStringBottomRight(&(*inspectionPointer->getPosition().toString().c_str()));
//            Vect2 boxSize = inspectionPointer->getBoxSize();
//            privDrawStringBottomLeft(boxSize.toString().c_str());
//            Vect2 boxPos = inspectionPointer->getBoxLoc();
//            for (int y = 0; y < boxSize.y; y++)
//            {
//                mvchgat(boxPos.y + y, boxPos.x, boxSize.x, A_NORMAL,
//                        privGetPairNumber(ColorPair(Color::WHITE, Color::DARK_BLUE)), NULL);
//            }
//        }

        move(instance.cursor_pos.y, instance.cursor_pos.x);

        //refresh();
    }

    void CursesManager::Initialize(const cursen::Vect2& dim){
        Resize(dim);
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
        short i = COLOR_PAIR(0);
        attron(i);
        mvaddstr(y, x, string);
        attroff(i);
    }

    short CursesManager::privGetColorPair(const ColorPair& colorPair)
    {
        ColorPairMap::const_iterator it;
        it = colorPairMap.find(colorPair);
        if (it != colorPairMap.cend())
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

    void CursesManager::Resize(const Vect2& dim)
    {
        CursesManager& instance = Instance();
        std::string resizeString = "\e[8;" + std::to_string(dim.y) + ";" + std::to_string(dim.x) + "t";
        //printf("%s", resizeString.c_str());
        fflush(stdout);

        if (instance.buffer != nullptr)
        {
            delete[] instance.buffer;
        }

        instance.dimensions = dim;
        instance.buff_size = (size_t)instance.dimensions.x * instance.dimensions.y;
        instance.buffer = new chtype[instance.buff_size];
        instance.clearBuffer();
    }

    void CursesManager::drawComponent(TextComponent& component)
    {
        /* Check if component needs a redraw */
        if (component.isInvalid())
        {
            component.render();
            component.validate();
        }

        const Content& content = component.getContentConst();

        chtype** const text = content.getText();
        const Vect2 dim = content.getSize();
        const Vect2 position = component.getPosition();

        for (int y = 0; y < dim.y; ++y)
        {
            chtype* const row = text[y];
            int offset = 0;
            if (position.x < 0)
            {
                offset = -position.x;
            }
            if (offset < dim.x)
            {
                int i = 0;
                for (int x = offset; x < dim.x; ++x)
                {
                    const chtype c = row[x];
                    if (c != Content::TRANSPARENT)
                    {
                        int y_pos = position.y + y;
                        int x_pos = position.x + i;
                        int index = (dimensions.x * y_pos) + x_pos;
                        if (index >= 0 && index < buff_size) buffer[index] = c;
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

    void CursesManager::privMoveCursor(const Vect2& dim)
    {
        cursor_pos = dim;
    }

    void CursesManager::privSetCursor(int level)
    {
        curs_set(level);
    }

    CursesManager& CursesManager::Instance()
    {
        return CursenApplication::GetCursesManager();
    }

    void CursesManager::clearBuffer()
    {
        for (int i = 0; i < buff_size; ++i)
        {
            buffer[i] = ' ';
        }
    }
}
