
#include "ElementMatrix.h"
#include "MovableSolid.h"
#include <math.h>

MovableSolid::MovableSolid(int x, int y) : Element(x,y){
    this->x = x;
    this->y = y;
    red = 255;
    green = 255;
    blue = 0;
    alpha = 255;
    state = 0;
    mass = 500;
}
void MovableSolid::step(ElementMatrix* matrix){
    //update status check
    if (this->update_status == matrix->update_status){
        //std::cout << "Skipping Already Updated" << std::endl;
        return;
    }
    this->update_status = !(matrix->update_status);

    Element* element;

    //ignited check, if ignited add red to color
    if (isIgnited){
        ignitedAction(matrix);
    }
    //act on surrounding elements
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

    //for now just move down;
    element = matrix->getElement(this->x, this->y+1);
    if (element != NULL && element->state != 0){
        matrix->swapElements(this->x, this->y, this->x, this->y + 1);
        return;
    }
    
    if (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) > 0.5f){
        element = matrix->getElement(this->x-1, this->y+1);
        if (element != NULL && element->state != 0){
            element = matrix->getElement(x-1, y);
            if (element != NULL && element->state != 0){
                matrix->swapElements(this->x, this->y, this->x-1, this->y + 1);
                return;
            }
        }
        element = matrix->getElement(this->x+1, this->y+1);
        if (element != NULL && element->state != 0){
            element = matrix->getElement(x+1, y);
            if (element != NULL && element->state != 0){
                matrix->swapElements(this->x, this->y, this->x+1, this->y + 1);
                return;
            }
        }
    }else{
        element = matrix->getElement(this->x+1, this->y+1);
        if (element != NULL && element->state != 0){
            element = matrix->getElement(x+1, y);
            if (element != NULL && element->state != 0){
                matrix->swapElements(this->x, this->y, this->x+1, this->y + 1);
                return;
            }
        }
        element = matrix->getElement(this->x-1, this->y+1);
        if (element != NULL && element->state != 0){
            element = matrix->getElement(x-1, y);
            if (element != NULL && element->state != 0){
                matrix->swapElements(this->x, this->y, this->x-1, this->y + 1);
                return;
            }
        }
        
    }
    

}
void MovableSolid::actOnOther(Element* element, ElementMatrix* matrix){
    return;
}
void MovableSolid::ignitedAction(ElementMatrix* matrix){
    return;
}
void MovableSolid::onIgnite(ElementMatrix* matrix){
    return;
}
void MovableSolid::onCool(ElementMatrix* matrix){
    return;
}
