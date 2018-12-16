//
// Created by Brandon Martin on 12/15/18.
//

#include "SpriteFrame.h"

SpriteFrame::SpriteFrame() {
    body.push_back("Hello");
    body.push_back("World!");
}

std::vector<std::string> SpriteFrame::getBody() const {
    return body;
}

SpriteFrame::~SpriteFrame() {

}