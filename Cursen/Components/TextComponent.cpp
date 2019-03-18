//
// Created by Brandon Martin on 3/11/19.
//

#include <Drawing/CursesManager.h>
#include "TextComponent.h"

TextComponent::TextComponent()
{
}

TextComponent::TextComponent(const Vect2i &pos) :
    position(pos)
{
}

TextComponent::TextComponent(const Vect2i &pos, const Vect2i &dim) :
    position(pos), body(TextBody(dim))
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

void TextComponent::move(const Vect2i& movement) {
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
    render();
    invalidate();
}
