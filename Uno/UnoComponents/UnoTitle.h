//
// Created by Brandon Martin on 4/10/19.
//

#ifndef CURSEN_UNOTITLE_H
#define CURSEN_UNOTITLE_H

#include "Components/TextComponent.h"

class UnoTitle : public cursen::TextComponent {

public:

    UnoTitle();
    UnoTitle(const cursen::Vect2& pos);

    void initialize() override;
    void render() override;

private:


};


#endif //CURSEN_UNOTITLE_H
