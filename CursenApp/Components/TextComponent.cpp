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
