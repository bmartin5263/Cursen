//
// Created by Brandon Martin on 3/11/19.
//

#ifndef CURSEN_LABEL_H
#define CURSEN_LABEL_H

#include "Cursen/Drawing/TextAlignment.h"
#include "StandardComponent.h"

namespace cursen {

    class Label : public StandardComponent {

    public:

        Label();
        Label(const Vect2& pos, const Vect2& dim);

        void initialize() override;
        void render() override;

        void emplaceText(const std::string& text);
        void setText(const std::string& text) override;

        void setTextAlignment(const TextAlignment new_alignment);
        TextAlignment getTextAlignment();

        std::string getText() const override;

    private:

        std::string text;
        TextAlignment alignment;

    };

}

#endif //CURSEN_LABEL_H
