//
// Created by Brandon Martin on 3/11/19.
//

#include <Drawing/CursesManager.h>
#include "TextComponent.h"

TextComponent::TextComponent() :
    clearRequest(ClearRequest()), position(Vect2d()), body(TextBody())
{
}

TextComponent::TextComponent(const Vect2d &pos) :
    clearRequest(ClearRequest()), position(pos), body(TextBody())
{
}

TextComponent::TextComponent(const Vect2d &pos, const Vect2d &dim) :
    clearRequest(ClearRequest()), position(pos), body(TextBody(dim))
{
}

void TextComponent::onCursor(std::function<void()> f) {
    f_onCursor = f;
}

void TextComponent::offCursor(std::function<void()> f) {
    f_offCursor = f;
}

void TextComponent::onClick(std::function<void()> f) {
    f_onClick = f;
}

void TextComponent::CallOnCursor() {
    try {
        f_onCursor();
    }
    catch (std::bad_function_call) {
        // Pass
    }
}

void TextComponent::CallOffCursor() {
    try {
        f_offCursor();
    }
    catch (std::bad_function_call) {
        // Pass
    }
}

void TextComponent::CallOnClick() {
    try {
        f_onClick();
    }
    catch (std::bad_function_call) {
        // Pass
    }
}

void TextComponent::move(const Vect2d& movement) {
    position.x += movement.x;
    position.y += movement.y;
    refresh();
}

void TextComponent::invalidate() {
    // Request Redraw
    CursesManager::EnqueueClear(clearRequest);
    DrawRequest drawRequest = CursesManager::GetDrawRequest();
    drawRequest.setBody(&this->body);
    drawRequest.setPosition(this->position);
    CursesManager::EnqueueDraw(drawRequest);
    clearRequest = CursesManager::GetClearRequest();
    clearRequest.setPosition(position);
    clearRequest.setDimensions(body.getDimensions());
}

void TextComponent::refresh() {
    draw();
    invalidate();
}
