#include "ElementMatrix.h"
#include "Element.h"
#include <iostream>

Element::Element(int x, int y){
    this->x = x;
    this->y = y;
    this->red = 10;
    this->green = 10;
    this->blue = 10;
    this->alpha = 255;
    this->mass = 0;
    
}
// Element::~Element(){
//     std::cout << "Deleting Element" << std::endl;
//     delete this;
//     }
void Element::step(ElementMatrix* matrix){
    if (this->update_status == matrix->update_status){
        //std::cout << "Skipping Already Updated" << std::endl;
        return;
    }
    this->update_status = !matrix->update_status;
    if (temperature > 0) temperature--;
    if (temperature < 0) temperature++;
}
void Element::actOnOther(Element* element, ElementMatrix* matrix){
    return;
}
//Element* Element::createElement(){}
//Element* Element::addElement(){}
uint32_t Element::getColor(){
    //std::cout << "value: " << (this->alpha | this->red>>24 | this->green>>16 | this->blue>>8) << std::endl;
    return (this->alpha<<24 | this->red<<16 | this->green<<8 | this->blue);
}
void Element::setPosition(int x, int y){
    this->x = x;
    this->y = y;
}
Element* Element::createElement(int x, int y){
    return new Element(x,y);
}

void Element::takeDamage(int damage){
    health -= damage;
}
void Element::tryIgnite(ElementMatrix* matrix){
    if (temperature > heatingPoint){
        if (!isIgnited) onIgnite(matrix);
        isIgnited = true;
    }
}
void Element::ignitedAction(ElementMatrix* matrix){
    return;
}

void Element::onIgnite(ElementMatrix* matrix){
    return;
}

void Element::tryCool(ElementMatrix* matrix){
    if (temperature < heatingPoint){
        if (isIgnited){
            onCool(matrix);
        }
        isIgnited = false;
    }
}

void Element::cooledAction(ElementMatrix* matrix){
    return;
}

void Element::onCool(ElementMatrix* matrix){
    return;
}

bool Element::corrode(ElementMatrix* matrix){
    if (this->mass == 0) return false; // do nothing to empty
    this->health -= 100;
    if (matrix->checkIfDead(x,y)){
        matrix->DieAndReplace(x,y, "Empty");
        return true;
    }
    return false;
}
