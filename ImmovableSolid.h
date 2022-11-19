#pragma once

#include "Element.h"
class ImmovableSolid : public Element{
    public:
    ImmovableSolid(int x, int y);
    //Element* createElement(int x, int y);
    void step(ElementMatrix* matrix);
    virtual void actOnOther(Element* element, ElementMatrix* matrix);
    virtual void ignitedAction(ElementMatrix* matrix);
    virtual void onIgnite(ElementMatrix* matrix);
    virtual void onCool(ElementMatrix* matrix);

};