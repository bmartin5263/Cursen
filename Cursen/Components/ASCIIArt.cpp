//
// Created by Brandon Martin on 4/10/19.
//

#include <fstream>
#include "ASCIIArt.h"

ASCIIArt::ASCIIArt() :
    TextComponent(), max_columns(0)
{}

ASCIIArt::ASCIIArt(const Vect2 &pos) :
    TextComponent(pos), max_columns(0)
{}



void ASCIIArt::render() {
    TextComponent::render();
    Content* content = getContent();
    content->resize(Vect2(max_columns, (int)raw_data.size()));

    int offset = 0;
    for (auto line : raw_data) {
        content->writeLine(line, Vect2(0, offset), TextAlignment::LEFT, getCurrentDrawColor());
        offset++;
    }
}

void ASCIIArt::loadFromFile(const char *filename) {
    raw_data.clear();
    max_columns = 0;

    std::ifstream file(filename);
    std::string line;

    while (getline(file, line)) {
        raw_data.push_back(line);
        int len = (int)line.length();
        if (len > max_columns) max_columns = len;
    }

    invalidate();
}

