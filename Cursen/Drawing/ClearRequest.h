//
// Created by Brandon Martin on 3/11/19.
//

#ifndef CURSEN_CLEARREQUEST_H
#define CURSEN_CLEARREQUEST_H


#include "Vect2i.h"

using namespace cursen;

class ClearRequest {

public:

    void setPosition(Vect2i const position);
    void setDimensions(Vect2i const dimensions);
    Vect2i getDimensions();
    Vect2i getPosition();

private:

    Vect2i position;
    Vect2i dimensions;

};


#endif //CURSEN_CLEARREQUEST_H
