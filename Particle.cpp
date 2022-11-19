#include "ElementMatrix.h"
#include "Particle.h"
#include <math.h>
#include "Elements.h"

Particle::Particle(int x, int y) : Element(x,y){
    this->x = x;
    this->y = y;

    red = 255;
    green = 0;
    blue = 255;
    alpha = 255;
    state = 0;
    mass = 1;
    element = NULL;
    //debugging
    xVel = -5;
    yVel = -15;
}

Element* Particle::createElement(int x, int y){
    Particle* p = new Particle(x,y);
    p->element = new Sand(x,y);
    return p;
}

void Particle::setContainedElement(Element* element){
    this->element = element;
    red = element->red;
    green = element->green;
    blue = element->blue;
    alpha = element->alpha;
}

void Particle::replaceWithContainedElement(ElementMatrix* matrix){
    element->x = x;
    element->y = y;
    matrix->setElement(x, y, this->element);
    //delete this;
}

void Particle::setVelocity(int xVel, int yVel){
    this->xVel = xVel;
    this->yVel = yVel;
}

void Particle::step(ElementMatrix* matrix){
    //update status check
    if (this->update_status == matrix->update_status){
        //std::cout << "Skipping Already Updated" << std::endl;
        return;
    }
    this->update_status = !(matrix->update_status);

    int x1 = x;
    int y1 = y;

    int x2 = x + xVel;
    int y2 = y + yVel;

    float slopeForX = (float)(y2 - y1)/(float)(x2 - x1);
    float slopeForY = (float)(x2 - x1)/(float)(y2 - y1);

    if (abs(x2 - x1) >= abs(y2 - y1)){
        //X distance is larger
        int xDistance = abs(x2 - x1) + 1;
        for (int i = 1; i < xDistance;i++){
            if (yVel > 0){
                y2 = y1 + abs(i*slopeForX);
            }else{
                y2 = y1 - abs(i*slopeForX);
            }
            if (xVel > 0){
                x2 = x1 + i;
            }else{
                x2 = x1 - i;
            }
            Element* element = matrix->getElement(x2,y2);
            if (element == NULL){
                replaceWithContainedElement(matrix);
                return;
            }else if (element->mass != 0){
                replaceWithContainedElement(matrix);
                return;
            }else{
                int prevY;
                int prevX;
                if (yVel > 0){
                    prevY = y1 + abs((i-1) * slopeForX);
                }else{
                    prevY = y1 - abs((i-1) * slopeForX);
                }
                if (xVel > 0){
                    prevX = x1 + (i-1);
                }else{
                    prevX = x1 - (i-1);
                }
                matrix->swapElements(prevX,prevY,x2,y2);
            }
        }
    }else{
        //Y distance is larger
        int yDistance = abs(y2 - y1) + 1;
        for (int i = 1; i < yDistance;i++){
            if (yVel > 0){
                y2 = y1 + i;
            }else{
                y2 = y1 - i;
            }
            if (xVel > 0){
                x2 = x1 + abs(i / slopeForX);
            }else{
                x2 = x1 - abs(i / slopeForX);
            }
            
            Element* element = matrix->getElement(x2,y2);
            if (element == NULL){
                replaceWithContainedElement(matrix);
                return;
            }else if (element->mass != 0){
                replaceWithContainedElement(matrix);
                return;
            }else{
                int prevY;
                int prevX;
                if (yVel > 0){
                    prevY = y1 + (i-1);
                }else{
                    prevY = y1 - (i-1);
                }
                if (xVel > 0){
                    prevX = x1 + abs((i-1) / slopeForX);
                }else{
                    prevX = x1 - abs((i-1) / slopeForX);
                }
                matrix->swapElements(prevX,prevY,x2,y2);
                //
            }
        }
    }

    //add gravity
    yVel += 2;
}

bool Particle::checkSuroundingsForElements(ElementMatrix* matrix){
    Element* element = matrix->getElement(x+1,y);
    if (element == NULL) return true;
    if (element->mass != 0) return true;
    element = matrix->getElement(x-1,y);
    if (element == NULL) return true;
    if (element->mass != 0) return true;
    element = matrix->getElement(x,y+1);
    if (element == NULL) return true;
    if (element->mass != 0) return true;
    element = matrix->getElement(x,y-1);
    if (element == NULL) return true;
    if (element->mass != 0) return true;
    return false;
}
