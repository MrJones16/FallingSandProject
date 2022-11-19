#pragma once

#include "Element.h"
#include <string>

class Particle : public Element{
    private:

    public:
        Element* element;
        int xVel = 0;
        int yVel = 0;
        Particle(int x, int y);
        Element* createElement(int x, int y);
        void step(ElementMatrix* matrix);
        void setContainedElement(Element* element);
        void replaceWithContainedElement(ElementMatrix* matrix);
        void setVelocity(int xVel, int yVel);
        bool checkSuroundingsForElements(ElementMatrix* matrix);
};