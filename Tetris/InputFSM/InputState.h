//
// Created by Brandon Martin on 10/12/19.
//

#ifndef CURSEN_INPUTSTATE_H
#define CURSEN_INPUTSTATE_H

class GameForm;
class InputState
{

public:

    virtual void pressDrop(const GameForm& game_form) const = 0;
    virtual void pressRotate(const GameForm& game_form) const = 0;
    virtual void pressLeft(const GameForm& game_form) const = 0;
    virtual void pressRight(const GameForm& game_form) const = 0;
    virtual void update(GameForm& game_form) const = 0;

    virtual ~InputState() = default;

};


#endif //CURSEN_INPUTSTATE_H
