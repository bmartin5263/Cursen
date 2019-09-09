//
// Created by Brandon Martin on 4/1/19.
//

#ifndef CURSEN_TWIRLPROGRESS_H
#define CURSEN_TWIRLPROGRESS_H

#include "Label.h"
#include "AggregateComponent.h"

namespace cursen {

    class TwirlProgress : public AggregateComponent {

    public:

        TwirlProgress();
        TwirlProgress(const Vect2 &pos);

        void start();
        void stop();
        void toggle();
        void setState(const bool on);
        bool isSpinning();
        void initialize() override;
        void setForeground(const Color &color) override;
        Color getForeground() const override;
        void setBackground(const Color &color) override;
        Color getBackground() const override;
        void setPosition(const Vect2 &size) override;

    private:

        Animation animation;
        Label twirl_label;

    };
}


#endif //CURSEN_TWIRLPROGRESS_H
