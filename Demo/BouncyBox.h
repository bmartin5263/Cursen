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

private:

    static std::vector<std::string> colors;
    CursenSprite sprite;
    int vertical;
    int horizontal;
    int color;
    int count;

};


#endif //CURSEN_BOUNCYBOX_H
