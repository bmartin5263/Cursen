//
// Created by Brandon Martin on 4/15/19.
//

#ifndef CURSEN_TEXTFIELD_H
#define CURSEN_TEXTFIELD_H


#include "TextComponent.h"

class TextField : public TextComponent {

public:

    TextField();
    TextField(const Size& size);
    virtual ~TextField();

    void initialize() override;
    void render() override;

    void keyPress(const Event& e);
    void deletePress(const Event& e);

    void setMaxLength(const int& len);

    void cursorOn() override;

    void setSize(const Size &size) override;

    void setText(const std::string &text) override;

    std::string getText() override;

private:

    std::string text;
    int max_len;

};


#endif //CURSEN_TEXTFIELD_H
