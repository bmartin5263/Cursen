//
// Created by Brandon Martin on 3/11/19.
//

#include <Drawing/CursesManager.h>
#include <Events/AlarmManager.h>
#include "Label.h"

Label::Label() :
        TextComponent(Size(0,0), Size(1,1))
{
}

Label::Label(const Size& pos, const Size& dim) :
        TextComponent(pos, dim)
{
}

void Label::initialize() {
    TextComponent::initialize();
    this->text = "";
    this->alignment = TextAlignment::LEFT;
    this->glow_frame = 0;
}

void Label::render() {
    Content* content = getContent();
    ColorPair& draw_color = getCurrentDrawColor();
    content->writeLine(text, Size(0,0), alignment, draw_color);
}

void Label::emplaceText(const std::string& text) {
    this->text = text;
    invalidate();
}

void Label::setText(const std::string& text) {
    setSize(Size((int)text.length(), 1));
    emplaceText(text);
}

void Label::startGlow() {
    AlarmManager::StartTimer(this, std::bind(&Label::animate_glow, this), .07);
}

void Label::stopGlow() {
    AlarmManager::StopTimer(this);
}

void Label::animate_glow() {
    if (glow_frame == 0) {
        setForeground(Color(225));
    }
    else if (glow_frame == 1) {
        setForeground(Color(219));
    }
    else if (glow_frame == 2) {
        setForeground(Color(213));
    }
    else if (glow_frame == 3) {
        setForeground(Color(207));
    }
    else if (glow_frame == 4) {
        setForeground(Color(201));
    }
    else if (glow_frame == 5) {
        setForeground(Color(199));
    }
    else if (glow_frame == 6) {
        setForeground(Color(199));
    }
    else if (glow_frame == 7) {
        setForeground(Color(199));
    }
    else if (glow_frame == 8) {
        setForeground(Color(199));
    }
    else if (glow_frame == 9) {
        setForeground(Color(199));
    }
    else if (glow_frame == 10) {
        setForeground(Color(201));
    }
    else if (glow_frame == 11) {
        setForeground(Color(207));
    }
    else if (glow_frame == 12) {
        setForeground(Color(213));
    }
    else if (glow_frame == 13) {
        setForeground(Color(219));
    }
    else if (glow_frame == 14) {
        setForeground(Color(225));
    }
    glow_frame = (glow_frame + 1) % 15;
}