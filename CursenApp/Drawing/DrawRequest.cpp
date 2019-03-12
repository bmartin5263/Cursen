//
// Created by Brandon Martin on 3/8/19.
//

#include "DrawRequest.h"


void DrawRequest::setPosition(Position *position){
    this->position = position;
}

void DrawRequest::setBody(std::vector<std::vector<chtype>> *body) {
    this->body = body;
}

std::vector<std::vector<chtype>> *DrawRequest::getBody(){
    return body;
}

Position *DrawRequest::getPosition() {
    return position;
}

