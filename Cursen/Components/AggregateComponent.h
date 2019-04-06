//
// Created by Brandon Martin on 4/3/19.
//

#ifndef CURSEN_AGGREGATECOMPONENT_H
#define CURSEN_AGGREGATECOMPONENT_H

#include "Components/Component.h"

class AggregateComponent : public Component {

public:

    AggregateComponent();
    AggregateComponent(const Size& pos);

    void render() override {};                         // Aggregates don't render any content
    Content * getContent() override {return nullptr;}
    void initialize() override {}
};


#endif //CURSEN_AGGREGATECOMPONENT_H
