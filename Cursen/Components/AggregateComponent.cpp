//
// Created by Brandon Martin on 4/3/19.
//

#include "AggregateComponent.h"

void AggregateComponent::initialize() {
    for (auto child : getChildren()) {
        child->initialize();
    }
}