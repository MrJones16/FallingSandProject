#pragma once

#include <map>
#include <string>
#include <iostream>


class ElementMatrix;

class Element{
    private:

    public:
    //Add basic element attributes like health, mass, ect
    bool update_status = false;
    uint8_t state = 5;
    int temperature = 0;
    int heatingPoint = 100;
    int coolingPoint = -100;
    int conductivity = 1;
    bool isIgnited = false;
    int mass = 0;
    int health = 100;
    int x;
    int y;

    uint8_t red = 1;
    uint8_t green = 1;
    uint8_t blue = 1;
    uint8_t alpha = 255;

    Element(int x, int y);

    //virtual ~Element();
    virtual void step(ElementMatrix* matrix);
    virtual void actOnOther(Element* element, ElementMatrix* matrix);

    virtual Element* createElement(int x, int y);
    static Element* addElement();
    uint32_t getColor();
    void setPosition(int x, int y);
    void takeDamage(int x);
    void tryIgnite(ElementMatrix* matrix);
    void tryCool(ElementMatrix* matrix);
    void ignitedAction(ElementMatrix* matrix);
    virtual void onIgnite(ElementMatrix* matrix);
    void cooledAction(ElementMatrix* matrix);
    virtual void onCool(ElementMatrix* matrix);
    virtual bool corrode(ElementMatrix* matrix);
    

};
