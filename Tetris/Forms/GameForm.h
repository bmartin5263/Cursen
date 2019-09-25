//
// Created by Brandon Martin on 9/25/19.
//

#ifndef CURSEN_GAMEFORM_H
#define CURSEN_GAMEFORM_H


#include <Cursen/Components/Form.h>
#include <Cursen/Components/BitMap.h>

class GameForm : public cursen::Form
{
public:

    GameForm();

    void initialize() override;

private:

    cursen::BitMap bitmap;

};


#endif //CURSEN_GAMEFORM_H
