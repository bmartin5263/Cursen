//
// Created by Brandon Martin on 11/21/18.
//

#include <TerminalManager.h>
#include "UITools.h"
#include "ncurses.h"
#include "assert.h"

std::unordered_map<std::string, TextColor> UITools::colorMap;

void UITools::AddColor(std::string key, short foreground, short background) {
    unsigned int pairNumber = static_cast<unsigned int>(colorMap.size()) + 1;
    init_pair(static_cast<short>(pairNumber), foreground, background);
    colorMap[key] = TextColor(pairNumber, COLOR_PAIR(pairNumber));
}

const TextColor& UITools::GetColor(std::string key) {
    auto found = colorMap.find(key);
    if (found == colorMap.end()) {
        DrawText(key, 1,10);
    }
    return colorMap[key];
}

void UITools::DrawText(std::string text, int x, int y) {
    attron(GetColor("white").colorPair);
    mvaddstr(y, x, text.c_str());
    attroff(GetColor("white").colorPair);
}

void UITools::Beep() {
    beep();
}

void UITools::Flash() {
    flash();
}

bool UITools::IsOffscreen(const sf::IntRect &boundingBox) {
    return UITools::IsHorizontallyOffscreen(boundingBox) || UITools::IsVerticallyOffscreen(boundingBox);
}

bool UITools::IsCompletelyOffscreen(const sf::IntRect &boundingBox) {
    return UITools::IsCompletelyHorizontallyOffscreen(boundingBox) || UITools::IsCompletelyVerticallyOffscreen(boundingBox);
}

bool UITools::IsVerticallyOffscreen(const sf::IntRect &boundingBox) {
    int topPos = boundingBox.top;
    int bottomPos = topPos + boundingBox.height;
    return topPos < 0 || bottomPos > TerminalManager::GetRows();
}

bool UITools::IsHorizontallyOffscreen(const sf::IntRect &boundingBox){
    int leftPos = boundingBox.left;
    int rightPos = leftPos + boundingBox.width;
    return leftPos < 0 || rightPos > TerminalManager::GetColumns();
}

bool UITools::IsCompletelyHorizontallyOffscreen(const sf::IntRect &boundingBox) {
    int leftPos = boundingBox.left;
    int rightPos = leftPos + boundingBox.width;
    int columns = TerminalManager::GetColumns();
    return (leftPos < 0 && rightPos < 0) || (leftPos > columns && rightPos > columns);
}

bool UITools::IsCompletelyVerticallyOffscreen(const sf::IntRect &boundingBox){
    int topPos = boundingBox.top;
    int bottomPos = topPos + boundingBox.height;
    int rows = TerminalManager::GetRows();
    return (topPos < 0 && bottomPos < 0) || (topPos > rows && bottomPos > rows);
}