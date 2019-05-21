//
// Created by Brandon Martin on 4/6/19.
//

#ifndef CURSEN_INSPECTORPOINTER_H
#define CURSEN_INSPECTORPOINTER_H


#include "Cursen/Components/TextComponent.h"

namespace cursen {

    class InspectionPointer : public TextComponent {

    public:

        static const char POINTER = '@';

        InspectionPointer();
        ~InspectionPointer();

        void render() override;
        void initialize() override;

        void movePointer(const Event& event);
        void pressSpace(const Event& event);

        Vect2 getBoxSize() { return boxSize; };
        Vect2 getBoxLoc() { return boxLoc; };

    private:

        Vect2 boxSize;
        Vect2 boxLoc;

    };

}


#endif //CURSEN_INSPECTORPOINTER_H
