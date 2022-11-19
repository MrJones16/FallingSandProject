#include "ElementMatrix.h"
#include "Gas.h"
#include <math.h>
#include <iostream>
using namespace std;

Gas::Gas(int x, int y) : Element(x,y){
    this->x = x;
    this->y = y;
    red = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*10) + 230;
    green = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*10) + 0;
    blue = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*10) + 230;
    mass = 200;
    flowRate =  2;
    isIgnited = false;
}
void Gas::step(ElementMatrix* matrix){
    //update status check
    if (this->update_status == matrix->update_status){
        //std::cout << "Skipping Already Updated" << std::endl;
        return;
    }
    this->update_status = !(matrix->update_status);

    Element* element;

    if (isIgnited){
        //cout << "Calling Ignited Action" << endl;
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

    //50/50 chance to check above first:
    if (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) > 0.5f){
        element = matrix->getElement(x, y-1);
        if (element != NULL){ // check if it exists
            if (element->state != 0){ // check if it is not a solid
                if (element->mass < mass){//check the mass / density
                    matrix->swapElements(x,y,x,y-1);
                    return;
                }
            }
        }
    }
    //randomly pick a side to try to move to
    if (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) > 0.5f){//left
        for (int i = 0; i < flowRate; i++){//loop the move over the flow rate
            if (i != 0){ // try to move up again!
                Element* element = matrix->getElement(x, y-1);
                if (element != NULL){ // check if it exists
                    if (element->state != 0){ // check if it is not a solid
                        if (element->mass < mass){//check the mass / density
                            matrix->swapElements(x,y,x,y-1);
                            return;
                        }
                    }
                }
            }
            element = matrix->getElement(x-1,y);
            if (element != NULL){//check if it exists
                if (element->state != 0){ // check if not solid
                    matrix->swapElements(x,y,x-1,y);
                }else{
                    return;
                }
            }
        }
    }else{//right
        for (int i = 0; i < flowRate; i++){//loop the move over the flow rate
                if (i != 0){ // try to move up again!
                Element* element = matrix->getElement(x, y-1);
                if (element != NULL){ // check if it exists
                    if (element->state != 0){ // check if it is not a solid
                        if (element->mass < mass){//check the mass / density
                            matrix->swapElements(x,y,x,y-1);
                            return;
                        }
                    }
                }
                }
                element = matrix->getElement(x+1,y);
                if (element != NULL){//check if it exists
                    if (element->state != 0){ // check if not solid
                        matrix->swapElements(x,y,x+1,y);
                    }else{
                        return;
                    }
                }
            }
        }
    return;
}
void Gas::actOnOther(Element* element, ElementMatrix* matrix){
    return;
}
void Gas::ignitedAction(ElementMatrix* matrix){
    return;
}
void Gas::onIgnite(ElementMatrix* matrix){
    return;
}
void Gas::onCool(ElementMatrix* matrix){
    return;
}
