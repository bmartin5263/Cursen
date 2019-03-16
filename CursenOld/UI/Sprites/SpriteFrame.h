//
// Created by Brandon Martin on 12/15/18.
//

#ifndef CURSEN_SPRITEFRAME_H
#define CURSEN_SPRITEFRAME_H


#include <vector>
#include <string>

class SpriteFrame {

public:

    SpriteFrame();
    ~SpriteFrame();

    std::vector<std::string> getBody() const;

private:

    std::vector<std::string> body;

};


#endif //CURSEN_SPRITEFRAME_H
