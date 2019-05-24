//
// Created by Brandon Martin on 4/3/19.
//

#ifndef CURSEN_TEXTCOMPONENT_H
#define CURSEN_TEXTCOMPONENT_H

#include "Cursen/Components/Component.h"

namespace cursen {

    class TextComponent : public Component {

    public:

        TextComponent();
        TextComponent(const Vect2& pos);
        TextComponent(const Vect2& pos, const Vect2& dim);
        ~TextComponent();

        virtual void setSize(const Vect2 &size);
        virtual Vect2 getSize();

        virtual Content& getContent();
        virtual void render() = 0;
        void setDrawOrder(int order) override;

    private:

        Content content;

    };
}

#endif //CURSEN_TEXTCOMPONENT_H
