//
// Created by Brandon Martin on 3/11/19.
//

#ifndef CURSEN_LABEL_H
#define CURSEN_LABEL_H


#include <Components/Component.h>
#include <Components/TextComponent.h>
#include <string>

class Label : public TextComponent {

public:

    Label(const Vect2d& pos, const Vect2d& dim);

    void Initialize() override;
    void Destroy() override;
    void draw() override;

    void emplaceText(const std::string& text);
    void setText(const std::string& text);

private:

    std::string text;

    void onKey(const Event &event);
};


#endif //CURSEN_LABEL_H
