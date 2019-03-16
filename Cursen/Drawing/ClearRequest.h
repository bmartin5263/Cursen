//
// Created by Brandon Martin on 3/11/19.
//

#ifndef CURSEN_CLEARREQUEST_H
#define CURSEN_CLEARREQUEST_H


#include "Vect2d.h"

using namespace cursen;

class ClearRequest {

public:

    void setPosition(Vect2d const position);
    void setDimensions(Vect2d const dimensions);
    Vect2d getDimensions();
    Vect2d getPosition();

private:

    Vect2d position;
    Vect2d dimensions;

};


#endif //CURSEN_CLEARREQUEST_H
