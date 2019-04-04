//
// Created by Brandon Martin on 4/3/19.
//

#include "AggregateComponent.h"

AggregateComponent::AggregateComponent()
{

}

AggregateComponent::AggregateComponent(const Size &pos) :
    Component(pos)
{

}

void AggregateComponent::initialize() {
    for (auto child : getChildren()) {
        child->initialize();
    }
}