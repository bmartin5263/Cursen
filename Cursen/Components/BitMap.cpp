//
// Created by Brandon Martin on 9/25/19.
//

#include <cassert>
#include "BitMap.h"

using namespace cursen;

BitMap::BitMap() : TextComponent(), scale(Vect2(1,1))
{
}

BitMap::BitMap(const cursen::Vect2 pos) : TextComponent(pos), scale(Vect2(1,1))
{

}

BitMap::BitMap(const cursen::Vect2 pos, const cursen::Vect2 size) : TextComponent(pos, size),
        unscaled_content(size), scale(Vect2(1,1)), base_size(size)
{
    assert(size.x > 0 && size.y > 0 && "Dimensions must be a positive integer.");
}

void BitMap::initialize()
{
    TextComponent::initialize();
}

void BitMap::render()
{
    Content& content = getContent();
    Vect2 dim = unscaled_content.getSize();

    for (int y = 0; y < dim.y; ++y)
    {
        for (int x = 0; x < dim.x; ++x)
        {
            chtype c = unscaled_content[y][x];
            Vect2 top_left_pos = Vect2(x, y) * scale;
            for (int x_offset = 0; x_offset < scale.x; ++x_offset)
            {
                for (int y_offset = 0; y_offset < scale.y; ++y_offset)
                {
                    content[top_left_pos.y + y_offset][top_left_pos.x + x_offset] = c;
                }
            }
        }
    }
}

void BitMap::setSize(const Vect2& size)
{
    base_size = size;
    unscaled_content.resize(size);
    TextComponent::setSize(base_size * scale);
}

Vect2 BitMap::getSize() const
{
    return base_size;
}

chtype*& BitMap::operator[](int row)
{
    invalidate();
    return unscaled_content[row];
}

void BitMap::setScale(const cursen::Vect2& scale)
{
    this->scale = scale;
    TextComponent::setSize(base_size * scale);
}

cursen::Vect2 BitMap::getScale() const
{
    return scale;
}

cursen::Vect2 BitMap::getCombinedSize()
{
    return TextComponent::getSize();
}

void BitMap::setBitMap(chtype** data, const Vect2& size)
{
    for (int y = 0; y < size.y; ++y)
    {
        for (int x = 0; x < size.x; ++x)
        {
            unscaled_content[y][x] = data[y][x];
        }
    }
    invalidate();
}


