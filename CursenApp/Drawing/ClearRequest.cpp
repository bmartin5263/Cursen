//
// Created by Brandon Martin on 3/11/19.
//

#include "ClearRequest.h"

void ClearRequest::setPosition(Vect2d const position) {
    this->position = position;
}

void ClearRequest::setDimensions(Vect2d const dimensions) {
    this->dimensions = dimensions;
}

Vect2d ClearRequest::getDimensions() {
    return this->dimensions;
}

Vect2d ClearRequest::getPosition() {
    return this->position;
}
