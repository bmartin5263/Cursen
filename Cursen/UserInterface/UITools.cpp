//
// Created by Brandon Martin on 11/21/18.
//

#include "UITools.h"
#include "ncurses.h"

std::unordered_map<std::string, TextColor> UITools::colorMap;

void UITools::AddColor(std::string key, short foreground, short background) {
    unsigned int pairNumber = static_cast<unsigned int>(colorMap.size()) + 1;
    init_pair(static_cast<short>(pairNumber), foreground, background);
    colorMap[key] = TextColor(pairNumber, COLOR_PAIR(pairNumber));
}

const TextColor& UITools::GetColor(std::string key) {
    auto found = colorMap.find(key);
    if (found == colorMap.end()) {
        throw std::exception();
    }
    return colorMap[key];
}

void UITools::DrawText(std::string text, int x, int y) {
    attron(GetColor("white").colorPair);
    mvaddstr(y, x, text.c_str());
    attroff(GetColor("white").colorPair);
    refresh();
}