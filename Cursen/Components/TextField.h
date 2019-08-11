//
// Created by Brandon Martin on 4/15/19.
//

#ifndef CURSEN_TEXTFIELD_H
#define CURSEN_TEXTFIELD_H

#include "StandardComponent.h"

namespace cursen {

    class TextField : public StandardComponent {

    public:

        TextField();

        TextField(const Vect2 &size);

        virtual ~TextField();

        void initialize() override;
        void render() override;
        void keyPress(const Event &e);
        void deletePress(const Event &e);
        void moveCursor(const Event &event);
        void setMaxLength(int len);
        void cursorOn() override;
        void setSize(const Vect2 &size) override;
        void setText(const std::string &text) override;
        std::string getText() override;
        void setEnabled(bool value) override;

        void setActiveBackgroundColor(Color color);


    private:

        Color active_bg_color;
        std::string text;
        int max_len;
        int cursor_x;
        bool stretch;

    };
}

#endif //CURSEN_TEXTFIELD_H
