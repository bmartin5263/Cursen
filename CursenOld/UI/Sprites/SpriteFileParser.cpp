//
// Created by Brandon Martin on 12/15/18.
//

#include <vector>
#include <cassert>
#include "SpriteFileParser.h"

const char* SpriteFileParser::DEFINE = "define";
const char* SpriteFileParser::SPRITE = "sprite";

const char SpriteFileParser::COMMENT_SIGIL = '#';
const char SpriteFileParser::ARGUMENT_SIGIL = '$';
const char SpriteFileParser::DIRECTIVE_SIGIL = '!';
const char SpriteFileParser::FORMAT_START_SIGIL = '{';
const char SpriteFileParser::FORMAT_END_SIGIL = '}';

SpriteData::SpriteData() :
    key(""), frames(0), isStatic(false)
{
}

SpriteFileParser::SpriteFileParser(std::ifstream *file) :
    file(file), parseMode(ParseMode::SEEK_SIGIL), currentLine("")
{

}

void SpriteFileParser::parse() {
    while (std::getline(*file, currentLine)) {
        parseSigil();
    }
}

void SpriteFileParser::parseSigil() {
    if (currentLine.length() != 0) {
        char sigil = currentLine[0];
        if (sigil == '#') {
            return;
        }
        else if (sigil == '!') {
            parseDirective();
        }
        else if (sigil == '$') {
            assert(false);
        }
        else {
            assert(false);
        }
    }
}

std::vector<std::string> SpriteFileParser::getSplit() {
    std::istringstream textToSplit(currentLine);
    return std::vector<std::string>((std::istream_iterator<std::string>(textToSplit)), std::istream_iterator<std::string>());
}

void SpriteFileParser::parseDirective() {
    std::string directiveKey;
    std::string directiveValue = "";
    std::vector<std::string> split = getSplit();

    assert(split.size() > 0);
    if (split.size() == 2) {
        directiveValue = split[1];
    }

    directiveKey = split[0].substr(1);
    std::transform(directiveKey.begin(), directiveKey.end(), directiveKey.begin(), ::tolower);

    printf("Found Key %s\n", directiveKey.c_str());

    //if (directiveKey == DEFINE) {
    //    // Do define
    //    if (split.size() < 2) {
//
    //    }
    //} else if (directiveKey == SPRITE) {
    //    // Do sprite
    //    assert(directiveValue != "");
    //    parseMode = ParseMode::SEEK_FRAME
    //}
}

void SpriteFileParser::parseFrameLine() {

}

//void SpriteFileParser::parseAttribute() {
//
//}
