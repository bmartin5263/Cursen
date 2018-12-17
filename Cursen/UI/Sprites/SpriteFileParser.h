//
// Created by Brandon Martin on 12/15/18.
//

#ifndef CURSEN_SPRITEFILEPARSER_H
#define CURSEN_SPRITEFILEPARSER_H


#include <fstream>
#include <sstream>
#include <unordered_map>

struct SpriteData {

    std::string key;
    int frames;
    bool isStatic;

    SpriteData();

};

class SpriteFileParser {

public:

    SpriteFileParser(std::ifstream* file);
    void parse();

private:

    enum class ParseMode {
        SEEK_SIGIL, FRAME_ENTRY
    };

    enum class Directives {
        DEFINE, SPRITE, FORMAT
    };

    enum class Arguments {
        EQUALS, FRAME
    };

    static const char* DEFINE;
    static const char* SPRITE;

    static const char DIRECTIVE_SIGIL;
    static const char ARGUMENT_SIGIL;
    static const char FORMAT_START_SIGIL;
    static const char FORMAT_END_SIGIL;
    static const char COMMENT_SIGIL;

    void parseFrameLine();
    void parseSigil();
    void parseDirective();
    void parseAttribute(Directives directive){};

    std::vector<std::string> getSplit();

    std::ifstream* file;
    std::string currentLine;
    std::vector<SpriteData> rawSprites;
    std::unordered_map<std::string, std::string> defines;

    ParseMode parseMode;
    Directives currentDirective;
    SpriteData currentSprite;


};


#endif //CURSEN_SPRITEFILEPARSER_H
