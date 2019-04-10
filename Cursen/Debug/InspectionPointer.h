//
// Created by Brandon Martin on 4/6/19.
//

#ifndef CURSEN_INSPECTORPOINTER_H
#define CURSEN_INSPECTORPOINTER_H


#include <Components/TextComponent.h>

class InspectionPointer : public TextComponent {

public:

    static const char POINTER = '@';

    InspectionPointer();
    ~InspectionPointer();

    void render() override;
    void initialize() override;

    void movePointer(const Event& event);
    void pressSpace(const Event& event);

    Size getBoxSize() { return boxSize; };
    Size getBoxLoc() { return boxLoc; };

private:

    Size boxSize;
    Size boxLoc;

};


#endif //CURSEN_INSPECTORPOINTER_H
