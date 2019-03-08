//
// Created by Brandon Martin on 3/8/19.
//

#ifndef CURSEN_COMPONENT_H
#define CURSEN_COMPONENT_H

#include <functional>

class Component {

public:

    void ForKeyPress(std::function<void(const Event&)> fun);

private:

    friend class EventManager;

    std::function<void(const Event&)> onKeyPress;

};


#endif //CURSEN_COMPONENT_H
