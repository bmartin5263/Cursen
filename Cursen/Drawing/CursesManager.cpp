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
        auto constant_buffer = instance.constant_buffer;
        auto dimensions = instance.dimensions;
        auto buff_size = instance.buff_size;

        // Clear the old screen
        erase();
        instance.clearBuffer(instance.buffer);

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
        }
        for (int i = 0; i < buff_size; ++i)
        {
            if (constant_buffer[i] != ' ')
            {
                int x = i % dimensions.x;
                int y = i / dimensions.x;
                mvaddch(y, x, constant_buffer[i]);
            }
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

    void CursesManager::Write(const char* string, int x, int y, const ColorPair& color)
    {
        size_t len = strlen(string);
        chtype converted[len + 1];
        auto c = ColorPair(Color::WHITE, Color::NONE);
        short pair = c.getColorPair();
        for (int i = 0; i < len; i++) {
            converted[i] = ((chtype) string[i]) | pair;
        }
        converted[len] = Content::NULL_CHAR;
        Write(&converted[0], x, y, len);
    }

    void CursesManager::Write(const chtype* string, int x, int y)
    {
        Write(string, x, y, strlen((char*)string));
    }

    void CursesManager::Write(const chtype* string, int x, int y, size_t len)
    {
        auto& instance = Instance();
        Vect2 dimensions = instance.dimensions;
        const Vect2 dim = Vect2((int)len, 1);

        auto constant_buffer = instance.constant_buffer;
        auto buff_size = instance.buff_size;

        int offset = 0;
        if (x < 0)
        {
            offset = -x;
        }
        if (offset < dim.x)
        {
            int i = 0;
            for (int currentX = offset; currentX < dim.x; ++currentX)
            {
                const chtype c = string[currentX];
                if (c != Content::TRANSPARENT)
                {
                    int x_pos = x + i;
                    int index = (dimensions.x * y) + x_pos;
                    if (index >= 0 && index < buff_size) constant_buffer[index] = c;
                }
                i++;
            }
        }
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
            short fg = colorPair.fg.val != -1 ? colorPair.fg.val : static_cast<short>(0);
            short bg = colorPair.bg.val != -1 ? colorPair.bg.val : static_cast<short>(0);

            init_pair(pairNum, fg, bg);
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
            delete[] instance.constant_buffer;
        }

        instance.dimensions = dim;
        instance.buff_size = (size_t)instance.dimensions.x * instance.dimensions.y;
        instance.buffer = new chtype[instance.buff_size];
        instance.constant_buffer = new chtype[instance.buff_size];
        instance.clearBuffer(instance.buffer);
        instance.clearBuffer(instance.constant_buffer);
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

    void CursesManager::WriteBottomRight(const std::string& string)
    {
        int y = Instance().dimensions.y - 1;
        Write(string.c_str(), 0, y);
    }

    void CursesManager::WriteBottomLeft(const std::string& string)
    {

        int y = Instance().dimensions.y - 1;
        Write(string.c_str(), 0, y);
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

    void CursesManager::clearBuffer(chtype* buffer_to_clear)
    {
        for (int i = 0; i < buff_size; ++i)
        {
            buffer_to_clear[i] = ' ';
        }
    }

    void CursesManager::nullBuffer(chtype* buffer_to_clear)
    {
        for (int i = 0; i < buff_size; ++i)
        {
            buffer_to_clear[i] = ' ';
        }
    }
}
