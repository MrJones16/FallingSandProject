#pragma once

#include "Liquid.h"
#include "ImmovableSolid.h"
#include "MovableSolid.h"
#include "Gas.h"
#include "Particle.h"


class EmptySource : public ImmovableSolid {
    public:
        EmptySource(int x, int y);
        //~EmptySource(){delete this;};
        Element* createElement(int x, int y);
        void actOnOther(Element* element, ElementMatrix* matrix);
        bool corrode(ElementMatrix* matrix);

};

class Sand : public MovableSolid {
    public:
        Sand(int x, int y);
        //~Sand(){delete this;};
        Element* createElement(int x, int y);
    
};

class Stone : public ImmovableSolid {
    public:
        Stone(int x, int y);
        //~Stone(){delete this;};
        Element* createElement(int x, int y);
        void actOnOther(Element* element, ElementMatrix* matrix);
};

class Water : public Liquid {
    public:
        Water(int x, int y);
        //~Water(){delete this;};
        Element* createElement(int x, int y);
        void actOnOther(Element* element, ElementMatrix* matrix);
        void ignitedAction();
        void onIgnite(ElementMatrix* matrix);

};

class WaterSource : public ImmovableSolid {
    public:
        //~WaterSource(){delete this;};
        WaterSource(int x, int y);
        Element* createElement(int x, int y);
        void actOnOther(Element* element, ElementMatrix* matrix);
        bool corrode(ElementMatrix* matrix);

};

class Wood : public ImmovableSolid {
    public:
        Wood (int x, int y);
        //~Wood(){delete this;};
        Element* createElement(int x, int y);
        void actOnOther(Element* element, ElementMatrix* matrix);
        void ignitedAction(ElementMatrix* matrix);
        void onCool(ElementMatrix* matrix);
};

class Fire : public Gas {
    public :
        Fire (int x, int y);
        //~Fire(){delete this;};
        Element* createElement(int x, int y);
        void actOnOther(Element* element, ElementMatrix* matrix);
        void ignitedAction(ElementMatrix* matrix);
        void onCool(ElementMatrix* matrix);
};

class FireSource : public ImmovableSolid {
    public:
        FireSource(int x, int y);
        //~FireSource(){delete this;};
        Element* createElement(int x, int y);
        void actOnOther(Element* element, ElementMatrix* matrix);
        bool corrode(ElementMatrix* matrix);

};

class Smoke : public Gas {
    public :
        Smoke (int x, int y);
        //~Smoke(){delete this;};
        Element* createElement(int x, int y);
        void actOnOther(Element* element, ElementMatrix* matrix);
        void ignitedAction(ElementMatrix* matrix);
};

class Steam : public Gas {
    public:
        Steam (int x, int y);
        //~Steam(){delete this;};
        Element* createElement(int x, int y);
        void actOnOther(Element* element, ElementMatrix* matrix);
        void onCool(ElementMatrix* matrix);
};

class Acid : public Liquid {
    public:
        Acid(int x, int y);
        Element* createElement(int x, int y);
        void actOnOther(Element* element, ElementMatrix* matrix);
        //void onCool(ElementMatrix* matrix);
        bool corrode(ElementMatrix* matrix);
};

class Titanium : public ImmovableSolid {
    public:
        Titanium(int x, int y);
        Element* createElement(int x, int y);
        //void actOnOther(Element* element, ElementMatrix* matrix);
        //void onCool(ElementMatrix* matrix);
        bool corrode(ElementMatrix* matrix);
};
