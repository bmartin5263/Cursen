//
// Created by Brandon Martin on 3/11/19.
//

#ifndef CURSEN_VISUALCOMPONENT_H
#define CURSEN_VISUALCOMPONENT_H


#include "Component.h"

using namespace cursen;

class TextComponent : public Component {

public:

    TextComponent();
    TextComponent(const Vect2d& pos);
    TextComponent(const Vect2d& pos, const Vect2d& dim);

    // Virtual Methods
    virtual void draw() = 0;

    // Methods
    void move(const Vect2d& movement);
    void invalidate();
    void refresh();

protected:

    ClearRequest clearRequest;
    TextBody body;
    Vect2d position;

};


#endif //CURSEN_VISUALCOMPONENT_H
