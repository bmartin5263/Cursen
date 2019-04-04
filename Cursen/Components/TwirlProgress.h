//
// Created by Brandon Martin on 4/1/19.
//

#ifndef CURSEN_TWIRLPROGRESS_H
#define CURSEN_TWIRLPROGRESS_H

#include "Label.h"
#include "AggregateComponent.h"

class TwirlProgress : public AggregateComponent {

public:

    TwirlProgress();
    TwirlProgress(const Size &pos);

    void start();
    void stop();
    void toggle();
    void setState(const bool& on);

    void initialize() override;

    void setForeground(const Color &color) override;
    Color getForeground() override;
    void setBackground(const Color &color) override;
    Color getBackground() override;

    void setPosition(const Size &size) override;;

private:

    static const char TWIRL_LEN = 4;
    const char* TWIRL[TWIRL_LEN] = {"|", "/", "-", "\\"};

    void doTwirl();

    Label twirl_label;
    int twirlIndex;
    bool spinning;

};


#endif //CURSEN_TWIRLPROGRESS_H
