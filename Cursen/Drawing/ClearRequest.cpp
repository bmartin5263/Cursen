//
// Created by Brandon Martin on 3/11/19.
//

#include "ClearRequest.h"

void ClearRequest::setPosition(Vect2i const position) {
    this->position = position;
}

void ClearRequest::setDimensions(Vect2i const dimensions) {
    this->dimensions = dimensions;
}

Vect2i ClearRequest::getDimensions() {
    return this->dimensions;
}

Vect2i ClearRequest::getPosition() {
    return this->position;
}
