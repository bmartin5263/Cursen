//
// Created by Brandon Martin on 4/3/19.
//

#ifndef CURSEN_AGGREGATECOMPONENT_H
#define CURSEN_AGGREGATECOMPONENT_H

#include "VisualComponent.h"

namespace cursen {

    class AggregateComponent : public VisualComponent {

    public:

        AggregateComponent();
        AggregateComponent(const Vect2& pos);

        virtual void setHidden(bool value) override;
        virtual void setEnabled(bool value) override;
        virtual void setPosition(const Vect2& pos) override;
        virtual void setForeground(const Color &color) override;
        virtual void setHighlight(const ColorPair& colorPair) override;

        void move(const Vect2& movement) override;
        void setSilenced(bool value) override;
        void setCursable(bool value) override;
        void setBackground(const Color& color) override;
        void setDisabled(const ColorPair& color) override;
        void setText(const std::string& text) override;

        void add(VisualComponent& component);
        void addRelative(VisualComponent& component);

        virtual void setDrawOrder(size_t order) override ;
        void drawOnTopOf(VisualComponent& component) override ;
        void addDrawOrder(size_t value) override ;

        size_t getDrawOrder() const override;
        size_t getMinOrder() const;
        size_t getMaxOrder() const;

    private:

        std::vector<VisualComponent*> children;
        size_t min_order;
        size_t max_order;

    };

}


#endif //CURSEN_AGGREGATECOMPONENT_H
