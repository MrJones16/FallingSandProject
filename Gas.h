#pragma once

#include "Element.h"

class matrix;

class Gas : public Element {
    public:
        int flowRate = 2;
        Gas(int x, int y);
        void step(ElementMatrix* matrix);
        virtual void actOnOther(Element* element, ElementMatrix* matrix);
        virtual void ignitedAction(ElementMatrix* matrix);
        virtual void onIgnite(ElementMatrix* matrix);
        virtual void onCool(ElementMatrix* matrix);

};