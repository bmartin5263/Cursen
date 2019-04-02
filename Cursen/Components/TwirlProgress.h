//
// Created by Brandon Martin on 4/1/19.
//

#ifndef CURSEN_TWIRLPROGRESS_H
#define CURSEN_TWIRLPROGRESS_H

#include "ColorComponent.h"
#include "Label.h"

class TwirlProgress : public ColorComponent {

public:

    TwirlProgress(const Vect2i &pos);

    void start();
    void stop();
    void toggle();

    void initialize() override;
    void render() override {};

private:

    static const char TWIRL_LEN = 4;
    const char* TWIRL[TWIRL_LEN] = {"|", "/", "-", "\\"};

    void doTwirl();

    Label* twirl_label;
    bool spinning;

};


#endif //CURSEN_TWIRLPROGRESS_H
