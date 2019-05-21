//
// Created by Brandon Martin on 3/11/19.
//

#ifndef CURSEN_LABEL_H
#define CURSEN_LABEL_H

#include "Cursen/Components/Component.h"
#include "Cursen/Drawing/TextAlignment.h"
#include "TextComponent.h"

namespace cursen {

    class Label : public TextComponent {

    public:

        Label();
        Label(const Vect2& pos, const Vect2& dim);

        void initialize() override;
        void render() override;

        void emplaceText(const std::string& text);
        void setText(const std::string& text) override;

        void setTextAlignment(const TextAlignment new_alignment);
        TextAlignment getTextAlignment();

        std::string getText() override;

    private:

        std::string text;
        TextAlignment alignment;

    };

}

#endif //CURSEN_LABEL_H
