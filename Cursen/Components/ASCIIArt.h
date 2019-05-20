//
// Created by Brandon Martin on 4/10/19.
//

#ifndef CURSEN_ASCIIART_H
#define CURSEN_ASCIIART_H


#include "TextComponent.h"

namespace cursen {

    class ASCIIArt : public TextComponent {

    public:

        ASCIIArt();
        ASCIIArt(const Vect2& pos);

        void render() override;

        void loadFromFile(const char* filename);

    private:

        std::vector<std::string> raw_data;
        int max_columns;

    };

}

#endif //CURSEN_ASCIIART_H
