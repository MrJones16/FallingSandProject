#include "ElementMatrix.h"
#include "ImmovableSolid.h"
#include <iostream>

ImmovableSolid::ImmovableSolid(int x, int y) : Element(x, y){
    state = 0;
    mass = 1000;
}
// Element* ImmovableSolid::createElement(int x, int y){
//     return new ImmovableSolid(x,y);
// }
void ImmovableSolid::step(ElementMatrix* matrix){
    //update status check
    if (this->update_status == matrix->update_status){
        //std::cout << "Skipping Already Updated" << std::endl;
        return;
    }
    this->update_status = !(matrix->update_status);

    Element* element;

    //ignited check, if ignited add red to color
    if (isIgnited){
        //std::cout << "calling ingitedAction on Immovable Solid" << std::endl;
        ignitedAction(matrix);
    }else{
        cooledAction(matrix);
    }

    //affect surrounding elements
    element = matrix->getElement(x+1, y);
    if (element != NULL){
        actOnOther(element, matrix);
    }
    element = matrix->getElement(x-1, y);
    if (element != NULL){
        actOnOther(element, matrix);
    }
    element = matrix->getElement(x, y+1);
    if (element != NULL){
        actOnOther(element, matrix);
    }
    element = matrix->getElement(x, y-1);
    if (element != NULL){
        actOnOther(element, matrix);
    }
}
void ImmovableSolid::actOnOther(Element* element, ElementMatrix* matrix){
    return;
}
void ImmovableSolid::ignitedAction(ElementMatrix* matrix){
    return;
}
void ImmovableSolid::onIgnite(ElementMatrix* matrix){
    return;
}
void ImmovableSolid::onCool(ElementMatrix* matrix){
    return;
}