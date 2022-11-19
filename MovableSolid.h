#pragma once

#include "Element.h"
//#include "ElementMatrix.h"
class matrix;

class MovableSolid : public Element{
    private:

    public:
        MovableSolid(int x, int y);
        void step(ElementMatrix* matrix);
        virtual void actOnOther(Element* element, ElementMatrix* matrix);
        virtual void ignitedAction(ElementMatrix* matrix);
        virtual void onIgnite(ElementMatrix* matrix);
        virtual void onCool(ElementMatrix* matrix);
};
