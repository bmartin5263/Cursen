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

        virtual void setHidden(bool value) override;
        virtual void setEnabled(bool value) override;
        virtual void setPosition(const Vect2& pos) override;
        virtual void setForeground(const Color &color) override;
        virtual void setDrawOrder(int order) override;
        virtual void setHighlight(const ColorPair& colorPair) override;
        void move(const Vect2& movement) override;
        void setSilenced(bool value) override;
        void setCursable(bool value) override;
        void setBackground(const Color& color) override;
        void setDisabled(const ColorPair& color) override;
        void setText(const std::string& text) override;


    };

}


#endif //CURSEN_AGGREGATECOMPONENT_H
