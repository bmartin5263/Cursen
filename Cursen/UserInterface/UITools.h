//
// Created by Brandon Martin on 11/21/18.
//

#ifndef CURSEN_UITOOLS_H
#define CURSEN_UITOOLS_H

#include <string>
#include <unordered_map>

struct TextColor {

    unsigned int pairNumber;
    unsigned int colorPair;

    TextColor() = default;
    TextColor(const unsigned int _pairNumber, const unsigned int _colorPair) :
            pairNumber(_pairNumber), colorPair(_colorPair)
    {}
};

class UITools {

public:

    static void AddColor(std::string key, short foreground, short background);
    static const TextColor& GetColor(std::string key);

    static void Flash();
    static void Beep();

    static void DrawText(std::string, int x, int y);

private:

    static std::unordered_map<std::string, TextColor> colorMap;

};


#endif //CURSEN_UITOOLS_H
