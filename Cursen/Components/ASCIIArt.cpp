//
// Created by Brandon Martin on 4/10/19.
//

#include <fstream>
#include "ASCIIArt.h"

namespace cursen {

    ASCIIArt::ASCIIArt() :
            StandardComponent(), max_columns(0)
    {}

    ASCIIArt::ASCIIArt(const Vect2 &pos) :
            StandardComponent(pos), max_columns(0)
    {}

    void ASCIIArt::initialize()
    {
        StandardComponent::initialize();
    }


    void ASCIIArt::render() {
        StandardComponent::render();
        Content& content = getContent();

        content.resize(Vect2(max_columns, (int)raw_data.size()));
        int offset = 0;
        for (auto line : raw_data) {
            content.writeLine(line, Vect2(0, offset), TextAlignment::LEFT, getCurrentDrawColor());
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

    void ASCIIArt::loadFromVector(const std::vector<std::string>& data)
    {
        raw_data = data;
        for (auto& str : data)
        {
            int len = (int)str.length();
            if (len > max_columns) max_columns = len;
        }
        invalidate();
    }


}