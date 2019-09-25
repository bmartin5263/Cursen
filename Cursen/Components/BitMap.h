//
// Created by Brandon Martin on 9/25/19.
//

#ifndef CURSEN_BITMAP_H
#define CURSEN_BITMAP_H


#include "TextComponent.h"

namespace cursen
{

    class BitMap : public cursen::TextComponent
    {
    public:

        BitMap();
        BitMap(const cursen::Vect2 pos);
        BitMap(const cursen::Vect2 pos, const cursen::Vect2 size);

        void render() override;
        void initialize() override;

        void setSize(const cursen::Vect2& size) override;
        cursen::Vect2 getSize() const override;

        void setScale(const cursen::Vect2& scale);
        cursen::Vect2 getScale() const;

        cursen::Vect2 getCombinedSize();

        chtype*& operator [](int row);

    private:

        Content unscaled_content;
        cursen::Vect2 scale;
        cursen::Vect2 base_size;

    };

}


#endif //CURSEN_BITMAP_H
