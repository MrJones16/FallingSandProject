#include "ElementMatrix.h"
#include <vector>
#include <iostream>
#include <math.h>
#include "Element.h"
#include "Elements.h"
#include "Particle.h"


ElementMatrix::ElementMatrix(int Width, int Height){
    this->Width = Width;
    this->Height = Height;
    this->update_status = false;
    this->matrix = new std::vector<Element*>(Width * Height, 0);
    int x = 0;
    for (int y = 0; y < Height;y++){
        int x = 0;
        for (; x < this->Width;){
            //std::cout << "Calling setElement" << std::endl;
            setElement(x, y, new Element(x, y));
            ++x;
        }
        // std::cout << "for loop y: " << y << std::endl;
    }
    //create the element map
    this->elementMap = new std::map<std::string, Element*>();
    this->elementMap->insert(std::pair<std::string, Element*>("Empty", new Element(-1, -1)));
    this->elementMap->insert(std::pair<std::string, Element*>("Sand", new Sand(-1, -1)));
    this->elementMap->insert(std::pair<std::string, Element*>("Stone", new Stone(-1, -1)));
    this->elementMap->insert(std::pair<std::string, Element*>("Water", new Water(-1, -1)));
    this->elementMap->insert(std::pair<std::string, Element*>("Wood", new Wood(-1, -1)));
    this->elementMap->insert(std::pair<std::string, Element*>("Fire", new Fire(-1, -1)));
    this->elementMap->insert(std::pair<std::string, Element*>("Smoke", new Smoke(-1, -1)));
    this->elementMap->insert(std::pair<std::string, Element*>("Steam", new Steam(-1, -1)));
    this->elementMap->insert(std::pair<std::string, Element*>("WaterSource", new WaterSource(-1, -1)));
    this->elementMap->insert(std::pair<std::string, Element*>("FireSource", new FireSource(-1, -1)));
    this->elementMap->insert(std::pair<std::string, Element*>("EmptySource", new EmptySource(-1, -1)));
    this->elementMap->insert(std::pair<std::string, Element*>("Acid", new Acid(-1, -1)));
    this->elementMap->insert(std::pair<std::string, Element*>("Titanium", new Titanium(-1, -1)));
    this->elementMap->insert(std::pair<std::string, Element*>("Particle", new Particle(-1, -1)));
    std::cout << "Size: " << this->elementMap->size() << std::endl;
    std::cout << "Map: " << this->elementMap->find("Sand")->second->mass << std::endl;
}
ElementMatrix::~ElementMatrix(){
    delete this->matrix;
    delete this->elementMap;
}
Element* ElementMatrix::getElement(int x, int y){
    if (x < 0) return NULL;
    if (x > this->Width-1) return NULL;
    if (y < 0) return NULL;
    if (y > this->Height-1) return NULL;
    return (*this->matrix)[(y * this->Width) + x];
}
void ElementMatrix::setElement(int x, int y, Element* element){
    //Element* oldElement = (*this->matrix)[(y * this->Width) + x];
    //if (oldElement != NULL) delete oldElement;
    (*this->matrix)[(y * this->Width) + x] = element;
}
bool ElementMatrix::setElementByString(int x, int y, std::string element_name){
    if (x < 0 || x >= Width) return false;
    if (y < 0 || y >= Height) return false;
    if (this->elementMap->find(element_name) == elementMap->end()){
        std::cout << "Couldn't find element: " << element_name << std::endl;
        return false;
    }
    Element* element = this->elementMap->find(element_name)->second;
    element = element->createElement(x,y);
    //std::cout << "Mass: " << element->mass << std::endl;
    Element* oldElement = (*this->matrix)[(y * this->Width) + x];
    if (oldElement != NULL) delete oldElement;
    (*this->matrix)[(y * this->Width) + x] = element;
    return true;
}

bool ElementMatrix::swapElements(int x1, int y1, int x2, int y2){
    Element* element = getElement(x2,y2);
    if (element == NULL) return false;
    setElement(x2, y2, getElement(x1, y1));
    setElement(x1, y1, element);
    //set their x/y values
    getElement(x1, y1)->setPosition(x1, y1);
    getElement(x2, y2)->update_status = this->update_status;
    getElement(x2, y2)->setPosition(x2, y2);
    return true;
}

void ElementMatrix::stepAll(){
    // std::vector<std::pair<int, int>> *coordinates = new std::vector<std::pair<int,int>>(this->Width * this->Height);
    // if (this->update_status) {this->update_status = false;}
    // else {this->update_status = true;}
    // //std::cout << "Update Status: " << this->update_status << std::endl;

    // //initialize the coordinate vector with all possible coordinates
    // for (int y = 0; y < this->Height; y++){
    //     for (int x = 0; x < this->Width; x++){
    //         std::pair<int,int> pair = *(new std::pair<int,int>(x,y));
    //         (*coordinates)[y * Width + x] = pair;
    //     }
    // }
    // //shuffle the coordinate vector;
    // for (int i = coordinates->size() - 1; i > 0; i--){
    //     int randomIndex = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*i;
    //     //std::cout << "rand: " << randomIndex  << std::endl;
    //     std::pair<int,int> temp = (*coordinates)[i];
    //     (*coordinates)[i] = (*coordinates)[randomIndex];
    //     (*coordinates)[randomIndex] = temp;
    // }
    // for(int i = 0; i < coordinates->size(); i++){
    //     //std::cout << "x: " << (*coordinates)[i].first << " y: " << (*coordinates)[i].second << std::endl;
    //     (*this->matrix)[((*coordinates)[i].second * Width) + (*coordinates)[i].first]->step(this);
    // }

    // coordinates->clear();
    // delete coordinates;

    if (this->update_status) {this->update_status = false;}
    else {this->update_status = true;}

    for (int y = 0; y < this->Height; y++){
        for (int x = 0; x < this->Width; x++){
            (*this->matrix)[(y * Width) + x]->step(this);
        }
    }
    
}

void ElementMatrix::getMatrixPixels(uint32_t *pixels){
    for (int x = 0; x < this->Width; x++){
        for (int y = 0; y < this->Height; y++){
            //std::cout << "going to get element" << std::endl;
            uint32_t color = this->getElement(x,y)->getColor();
            //std::cout << "x: " << x << " y: " << y << std::endl;
            pixels[(y * this->Width) + x] = color;
        }
    }
}

bool ElementMatrix::checkIfDead(int x, int y){
    //std::cout << "Checking if dead" << std::endl;
    if ((*this->matrix)[(y * this->Width) + x]->health <= 0){
        //std::cout << "Its Dead!" << std::endl;
        return true;
    }
    //std::cout << "not dead yet!" << std::endl;
    return false;
}
void ElementMatrix::DieAndReplace(int x, int y, std::string element_name){
    //std::cout << "Going to replace element by string" << std::endl;
    //delete (*this->matrix)[(y * this->Width) + x];
    if (setElementByString(x, y, element_name)){
        return;
    }
    //std::cout << "Setting by empty instead, cant find: " << element_name << std::endl;
    setElementByString(x,y,"Empty");
}

void ElementMatrix::pushElements(int xPos, int yPos, int radius, float forceMultiplier){
    for (int x = xPos - radius; x < xPos + radius + 1; x++){
        //bounds checking
        if (x < 0) continue;
        if (x > this->Width - 1) continue;
        for (int y = yPos - radius; y < yPos + radius + 1; y++){
            //bounds checking
            if (y < 0) continue;
            if (y > this->Height - 1) continue;
            if (sqrt(pow((x - xPos), 2) + pow(y - yPos,2)) < radius){
                //check distance from center to make it a circle
                Element* element = getElement(x,y);
                if (element->mass == 1) return;
                Particle* p = new Particle(x, y);
                p->setContainedElement(element);
                p->setVelocity((x - xPos) * forceMultiplier, (y - yPos)*forceMultiplier);
                setElement(x,y, p);
            }
        }
    }
}
