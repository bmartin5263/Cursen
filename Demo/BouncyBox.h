//
// Created by Brandon Martin on 12/4/18.
//

#ifndef CURSEN_BOUNCYBOX_H
#define CURSEN_BOUNCYBOX_H

#include "CursenObject.h"

class BouncyBox : public CursenObject {

public:

    BouncyBox(int);
    ~BouncyBox() = default;

    void draw() override;
    void update() override;
    void move(sf::Vector2i p);

private:

    static std::vector<std::string> colors;
    sf::IntRect boundingBox;
    CursenSprite sprite;
    chtype body[2];
    int vertical;
    int horizontal;
    int color;
    int count;
    bool dirty;

};


#endif //CURSEN_BOUNCYBOX_H
