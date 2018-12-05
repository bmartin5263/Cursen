//
// Created by Brandon Martin on 12/4/18.
//

#ifndef CURSEN_BOUNCYBOX_H
#define CURSEN_BOUNCYBOX_H

#include "CursenObject.h"

class BouncyBox : public CursenObject {

public:

    BouncyBox();
    ~BouncyBox() = default;

    void draw() override;
    void update() override;

private:

    static std::vector<std::string> colors;
    int vertical;
    int horizontal;
    int color;

};


#endif //CURSEN_BOUNCYBOX_H
