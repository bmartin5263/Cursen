//
// Created by Brandon Martin on 4/3/19.
//

#ifndef CURSEN_AGGREGATECOMPONENT_H
#define CURSEN_AGGREGATECOMPONENT_H

#include "Component.h"

namespace cursen {

    class AggregateComponent : public Component {

    public:

        AggregateComponent();
        AggregateComponent(const Vect2& pos);

        void setHidden(bool value) override;
        void setEnabled(bool value) override;
        void setPosition(const Vect2& pos) override;
        void setForeground(const Color &color) override;

        void setDrawOrder(int order) override;


    };

}


#endif //CURSEN_AGGREGATECOMPONENT_H
