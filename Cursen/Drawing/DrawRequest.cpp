//
// Created by Brandon Martin on 3/8/19.
//

#include "DrawRequest.h"
#include "TextBody.h"


void DrawRequest::setPosition(Vect2i position){
    this->position = position;
}

void DrawRequest::setBody(TextBody *body) {
    this->body = body;
}

TextBody *DrawRequest::getBody(){
    return body;
}

Vect2i DrawRequest::getPosition() {
    return position;
}

