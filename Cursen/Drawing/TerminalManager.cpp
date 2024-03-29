//
// Created by Brandon Martin on 3/7/19.
//

#include <ncurses.h>

#include "Cursen/Components/TextComponent.h"
#include "TerminalManager.h"
#include "Cursen/CursenApplication.h"

namespace cursen
{

    chtype TerminalManager::LLCORNER = '?';
    chtype TerminalManager::LRCORNER = '?';
    chtype TerminalManager::HLINE = '?';
    chtype TerminalManager::VLINE = '?';
    chtype TerminalManager::ULCORNER = '?';
    chtype TerminalManager::URCORNER = '?';
    chtype TerminalManager::LTEE = '?';
    chtype TerminalManager::RTEE = '?';

    TerminalManager::TerminalManager() :
            component_layer(nullptr), type_pos(0), buffer_size(0)
    {
    }

    int TerminalManager::GetChar()
    {
        int c = getch();
        return c;
    }

    void TerminalManager::Draw(ComponentMap& componentMap)
    {
        auto& debugger = CursenApplication::GetDebugger();
        auto& instance = Instance();
        auto buffer = instance.component_layer;
        auto constant_buffer = instance.text_layer;
        auto dimensions = instance.dimensions;
        auto buff_size = instance.buffer_size;

        // Clear the old screen
        instance.clearScreen();

        for (auto& pair : componentMap)
        {
            for (auto& componentIter : pair.second)
            {
                TextComponent& component = *componentIter;
                if (!component.isHidden())
                {
                    instance.render(component);
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

    void TerminalManager::Initialize(const cursen::Vect2& dim){
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

        TerminalManager::LLCORNER = ACS_LLCORNER;
        TerminalManager::LRCORNER = ACS_LRCORNER;
        TerminalManager::HLINE = ACS_HLINE;
        TerminalManager::VLINE = ACS_VLINE;
        TerminalManager::ULCORNER = ACS_ULCORNER;
        TerminalManager::URCORNER = ACS_URCORNER;
        TerminalManager::LTEE = ACS_LTEE;
        TerminalManager::RTEE = ACS_RTEE;

        // Draw A box onto main window 'stdscr'
        box(stdscr, 0, 0);
        refresh();
    }

    void TerminalManager::putCharacter(int c)
    {
        addch((chtype) c);
        refresh();
    }

    TerminalManager::~TerminalManager()
    {
        flushinp();     // Flush any remaining curses input
        endwin();       // End curses
    }

    void TerminalManager::doBeep()
    {
        beep();
    }

    void TerminalManager::doFlash()
    {
        flash();
    }

    void TerminalManager::drawString(const char* string)
    {
        short i = privGetColorPair(ColorPair());
        attron(i);
        addstr(string);
        attroff(i);
    }

    void TerminalManager::drawString(const char* string, int x, int y)
    {
        short i = COLOR_PAIR(0);
        attron(i);
        mvaddstr(y, x, string);
        attroff(i);
    }

    void TerminalManager::Write(const char* string, int x, int y, const ColorPair& color)
    {
        size_t len = strlen(string);
        chtype converted[len + 1];
        short pair = color.getColorPair();
        for (int i = 0; i < len; i++) {
            converted[i] = ((chtype) string[i]) | pair;
        }
        converted[len] = Content::NULL_CHAR;
        Write(&converted[0], x, y, len);
    }

    void TerminalManager::Write(const chtype* string, int x, int y)
    {
        Write(string, x, y, strlen((char*)string));
    }

    void TerminalManager::Write(const chtype* string, int x, int y, size_t len)
    {
        auto& instance = Instance();
        Vect2 dimensions = instance.dimensions;
        const Vect2 dim = Vect2((int)len, 1);

        auto constant_buffer = instance.text_layer;
        auto buff_size = instance.buffer_size;

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

    short TerminalManager::privGetColorPair(const ColorPair& colorPair)
    {
        ColorPair pair_to_check = colorPair;
        pair_to_check.reset();
        ColorPairMap::const_iterator it = colorPairMap.find(pair_to_check);;
        if (it != colorPairMap.cend())
        {
            return COLOR_PAIR(colorPairMap[pair_to_check]);
        }
        else
        {
            short pairNum = (short) (colorPairMap.size() + 1);
            short fg = pair_to_check.fg.val;
            short bg = pair_to_check.bg.val;

            init_pair(pairNum, fg, bg);
            colorPairMap[pair_to_check] = pairNum;

            return COLOR_PAIR(pairNum);
        }
    }

    void TerminalManager::Resize(const Vect2& dim)
    {
        TerminalManager& instance = Instance();
        std::string resizeString = "\e[8;" + std::to_string(dim.y) + ";" + std::to_string(dim.x) + "t";
        //printf("%s", resizeString.c_str());
        fflush(stdout);

        if (instance.component_layer != nullptr)
        {
            delete[] instance.component_layer;
            delete[] instance.text_layer;
        }

        instance.dimensions = dim;
        instance.buffer_size = (size_t)instance.dimensions.x * instance.dimensions.y;
        instance.component_layer = new chtype[instance.buffer_size];
        instance.text_layer = new chtype[instance.buffer_size];
        instance.clearBuffer(instance.component_layer);
        instance.clearBuffer(instance.text_layer);
    }

    void TerminalManager::render(TextComponent& component)
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
                        if (index >= 0 && index < buffer_size) component_layer[index] = c;
                    }
                    i++;
                }
            }
        }
    }

    void TerminalManager::WriteBottomRight(const std::string& string)
    {
        int y = Instance().dimensions.y - 1;
        Write(string.c_str(), 0, y);
    }

    void TerminalManager::WriteBottomLeft(const std::string& string)
    {

        int y = Instance().dimensions.y - 1;
        Write(string.c_str(), 0, y);
    }

    void TerminalManager::privMoveCursor(const Vect2& dim)
    {
        cursor_pos = dim;
    }

    void TerminalManager::privSetCursor(int level)
    {
        curs_set(level);
    }

    TerminalManager& TerminalManager::Instance()
    {
        return CursenApplication::GetCursesManager();
    }

    void TerminalManager::clearBuffer(chtype* buffer_to_clear)
    {
        for (int i = 0; i < buffer_size; ++i)
        {
            buffer_to_clear[i] = ' ';
        }
    }

    void TerminalManager::nullBuffer(chtype* buffer_to_clear)
    {
        for (int i = 0; i < buffer_size; ++i)
        {
            buffer_to_clear[i] = ' ';
        }
    }

    void TerminalManager::clearScreen()
    {
        erase();
        clearBuffer(component_layer);
    }

    void TerminalManager::Type(const char* string, size_t len, const ColorPair& color)
    {
        chtype converted[len + 1];
        short pair = color.getColorPair();
        for (int i = 0; i < len; i++) {
            converted[i] = ((chtype) string[i]) | pair;
        }
        converted[len] = Content::NULL_CHAR;
        Type(&converted[0], len);
    }

    void TerminalManager::Type(const std::string& string, const ColorPair& color)
    {
        Type(string.c_str(), string.length(), color);
    }

    void TerminalManager::Type(const chtype* string, size_t len)
    {
        auto text_layer = Instance().text_layer;
        auto buffer_size = Instance().buffer_size;
        auto& type_pos = Instance().type_pos;
        for (int i = 0; i < len; ++i)
        {
            text_layer[type_pos++] = string[i];
            if (type_pos >= buffer_size) type_pos = 0;
        }
    }

    void TerminalManager::Type(char character)
    {
        auto text_layer = Instance().text_layer;
        auto buffer_size = Instance().buffer_size;
        auto& type_pos = Instance().type_pos;
        text_layer[type_pos++] = static_cast<chtype>(character);
        if (type_pos >= buffer_size) type_pos = 0;
    }

    void TerminalManager::Type(chtype character)
    {
        auto text_layer = Instance().text_layer;
        auto buffer_size = Instance().buffer_size;
        auto& type_pos = Instance().type_pos;
        text_layer[type_pos++] = character;
        if (type_pos >= buffer_size) type_pos = 0;
    }
}
