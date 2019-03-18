//
// Created by Brandon Martin on 3/11/19.
//

#ifndef CURSEN_VISUALCOMPONENT_H
#define CURSEN_VISUALCOMPONENT_H


#include "Component.h"

using namespace cursen;

class TextComponent : public Component {

public:

    TextComponent();
    TextComponent(const Vect2i& pos);
    TextComponent(const Vect2i& pos, const Vect2i& dim);

    // Virtual Methods
    virtual void render() = 0;

    // Methods
    void move(const Vect2i& movement);
    void invalidate();
    void refresh();

    /**
     * Called when a virtual Cursor hovers over this component
     * @param f
     */
    void onCursor(std::function<void()> f);

    /**
     * Called when a virtual Cursor hovers away from this component
     * @param f
     */
    void offCursor(std::function<void()> f);

    /**
     * Called when a virtual Cursor clicks on this component
     * @param f
     */
    void onClick(std::function<void()> f);

private:

    ClearRequest clearRequest;

    friend class Cursor;
    friend class CursesManager;

    void CallOnCursor();
    void CallOffCursor();
    void CallOnClick();

    std::function<void()> f_onCursor;
    std::function<void()> f_offCursor;
    std::function<void()> f_onClick;

protected:

    TextBody body;
    Vect2i position;

};


#endif //CURSEN_VISUALCOMPONENT_H
