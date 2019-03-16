//
// Created by Brandon Martin on 11/21/18.
//

#ifndef CURSEN_UITOOLS_H
#define CURSEN_UITOOLS_H

#include <string>
#include <unordered_map>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

struct TextColor {

    unsigned int pairNumber;
    unsigned int colorPair;

    TextColor() = default;
    TextColor(const unsigned int _pairNumber, const unsigned int _colorPair) :
            pairNumber(_pairNumber), colorPair(_colorPair)
    {
    }
};

class UITools {

public:

    static void AddColor(std::string key, short foreground, short background);
    static const TextColor& GetColor(std::string key);

    static void Flash();
    static void Beep();

    // Offscreen
    static bool IsOffscreen(const sf::IntRect &boundingBox);
    static bool IsCompletelyOffscreen(const sf::IntRect &boundingBox);
    static bool IsHorizontallyOffscreen(const sf::IntRect &boundingBox);
    static bool IsVerticallyOffscreen(const sf::IntRect &boundingBox);
    static bool IsCompletelyHorizontallyOffscreen(const sf::IntRect &boundingBox);
    static bool IsCompletelyVerticallyOffscreen(const sf::IntRect &boundingBox);

    static void DrawText(std::string, int x, int y);

private:

    static std::unordered_map<std::string, TextColor> colorMap;

};


#endif //CURSEN_UITOOLS_H
