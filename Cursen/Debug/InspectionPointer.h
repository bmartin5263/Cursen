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

private:


};


#endif //CURSEN_INSPECTORPOINTER_H
