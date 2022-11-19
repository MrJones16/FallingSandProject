#include "ElementMatrix.h"
#include "Elements.h"
#include <iostream>
#include <math.h>


//SAND
Sand::Sand(int x, int y) : MovableSolid(x,y){
    red = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*10) + 230;
    green = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*10) + 230;
    temperature = 0;
    blue = 0;
    alpha = 255;
    mass = 520;
    state = 0;
}
Element* Sand::createElement (int x, int y){
    return new Sand(x,y);
}

//STONE
Stone::Stone(int x, int y) : ImmovableSolid(x,y){
    red = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*10) + 100;
    green = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*10) + 100;
    blue = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*10) + 100;
    health = 1000;
    mass = 1000;
    state = 0;
    temperature = 0;
    conductivity = 2;
    heatingPoint = 1000;
}
void Stone::actOnOther(Element* element, ElementMatrix* matrix){
    //stone passive cooling:
    if (element->temperature > 0) element->temperature--;
    //transfer heat
    if (element->temperature > temperature){
        element->temperature -= conductivity;
        element->tryCool(matrix);
        temperature += conductivity;
    }else if (element->temperature < temperature){
        element->temperature += conductivity;
        element->tryIgnite(matrix);
        temperature -= conductivity;
    }
}

Element* Stone::createElement(int x, int y){
    return new Stone(x,y);
}

//WATER
Water::Water(int x, int y) : Liquid(x,y){
    red = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*10) + 0;
    green = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*10) + 0;
    blue = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*10) + 230;
    mass = 300;
    state = 1; // liquid
    flowRate = 3;
    temperature = -80;
    heatingPoint = 100;
    conductivity = 20;
}
Element* Water::createElement(int x, int y){
    return new Water(x,y);
}

void Water::actOnOther(Element* element, ElementMatrix* matrix){
    if (element->temperature > temperature){
        element->temperature -= conductivity;
        temperature += conductivity;
        tryIgnite(matrix);
    }
    element->tryCool(matrix);
    //std::cout << "Trying to cool!" << std::endl;
}

void Water::onIgnite(ElementMatrix* matrix){
    matrix->DieAndReplace(x,y, "Steam");
}

//ACID
Acid::Acid(int x, int y) : Liquid(x,y){
    red = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*10) + 20;
    green = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*10) + 230;
    blue = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*10) + 20;
    mass = 255;
    state = 1; // liquid
    flowRate = 3;
    temperature = 0;
    heatingPoint = 100;
    conductivity = 20;
}
Element* Acid::createElement(int x, int y){
    return new Acid(x,y);
}
void Acid::actOnOther(Element* element, ElementMatrix* matrix){
    if (element->corrode(matrix)){
        matrix->DieAndReplace(x,y, "Empty");
    }
}
bool Acid::corrode(ElementMatrix* matrix){
    return false;
}

//LAVA

//WOOD
Wood::Wood(int x, int y) : ImmovableSolid(x,y){
    red = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*10) + 150;
    green = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*10) + 90;
    blue = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*10) + 27;
    health = 400;
    mass = 600;
    state = 0;
    temperature = 0;
    heatingPoint = 100;
    conductivity = 1;
    isIgnited = false;
}
Element* Wood::createElement(int x, int y){
    return new Wood(x,y);
}
void Wood::actOnOther(Element* element, ElementMatrix* matrix){
    if (element->temperature < temperature){
        element->temperature += conductivity;
        temperature -= conductivity;
    }else if(element->temperature > temperature){
        element->temperature -= conductivity;
        temperature += conductivity;
    }
    if (isIgnited){
        element->tryIgnite(matrix);
    }
}
void Wood::ignitedAction(ElementMatrix* matrix){
    //create heat since it is burning wood!
    if (temperature < heatingPoint * 2);
    temperature += 5;

    //add a lot of variable red to the color
    red = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*10) + 240;
    green = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*150) + 0;
    blue = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*10) + 27;
    health -= 1;
    if (matrix->checkIfDead(x,y)){
        matrix->DieAndReplace(x,y, "Empty");
    }
    Element* element;
    //chance to place fire surrounding the wood
    if ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) > 0.9f){
        element = matrix->getElement(x,y-1);
        if (element != NULL){
            if (element->mass == 0){
                matrix->setElementByString(x,y-1, "Fire");
            }
        }
        element = matrix->getElement(x+1,y);
        if (element != NULL){
            if (element->mass == 0){
                matrix->setElementByString(x+1,y, "Fire");
            }
        }
        element = matrix->getElement(x,y+1);
        if (element != NULL){
            if (element->mass == 0){
                matrix->setElementByString(x,y+1, "Fire");
            }
        }
        element = matrix->getElement(x-1,y);
        if (element != NULL){
            if (element->mass == 0){
                matrix->setElementByString(x-1,y, "Fire");
            }
        }
    }
}

void Wood::onCool(ElementMatrix* matrix){
    red = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*10) + 130;
    green = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*10) + 70;
    blue = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*10) + 7;
}

//FIRE

Fire::Fire(int x, int y) : Gas(x,y){
    red = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*10) + 240;
    green = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*10) + 0;
    blue = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*10) + 0;
    health = 10;
    mass = 10;
    state = 2;
    flowRate = 1;
    temperature = 1000;
    heatingPoint = 800;
    conductivity = 10;
    isIgnited = true;
}
Element* Fire::createElement(int x, int y){
    return new Fire(x,y);
}
void Fire::actOnOther(Element* element, ElementMatrix* matrix){
    if (element->temperature < temperature){
        element->temperature += conductivity;
        temperature -= conductivity;
        element->tryIgnite(matrix);
    }
}
void Fire::ignitedAction(ElementMatrix* matrix){
    //add a lot of variable red to the color
    red = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*10) + 240;
    green = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*150) + 0;
    blue = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*10) + 27;
    health -= 1;
    if (matrix->checkIfDead(x,y)){
        if ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) > 0.9f){
            matrix->DieAndReplace(x,y, "Smoke");
        }else{
            matrix->DieAndReplace(x,y, "Empty");
        }
        
    }
}

void Fire::onCool(ElementMatrix* matrix){
    matrix->DieAndReplace(x,y, "Empty");
}

//SMOKE
Smoke::Smoke(int x, int y) : Gas(x,y){
    red = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*10) + 190;
    green = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*10) + 190;
    blue = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*10) + 190;
    health = 10;
    mass = 8;
    state = 2;
    flowRate = 2;
    temperature = 200;
    heatingPoint = 150;
    conductivity = 1;
    isIgnited = true;
}
Element* Smoke::createElement(int x, int y){
    return new Smoke(x,y);
}
void Smoke::actOnOther(Element* element, ElementMatrix* matrix){
    return;
}
void Smoke::ignitedAction(ElementMatrix* matrix){
    return;
}

//Steam
Steam::Steam(int x, int y) : Gas(x,y){
    red = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*10) + 220;
    green = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*10) + 220;
    blue = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*10) + 220;
    health = 100;
    mass = 9;
    state = 2;
    flowRate = 2;
    temperature = 100;
    heatingPoint = 80;
    conductivity = 10;
    isIgnited = true;
}
Element* Steam::createElement(int x, int y){
    return new Steam(x,y);
}
void Steam::actOnOther(Element* element, ElementMatrix* matrix){
    if (element->temperature < temperature){
        element->temperature += conductivity;
        temperature -= conductivity;
        element->tryIgnite(matrix);
    }
}
void Steam::onCool(ElementMatrix* matrix){
    matrix->DieAndReplace(x,y, "Water");
    matrix->getElement(x,y)->temperature = 100;
}

//WATER SOURCE
WaterSource::WaterSource(int x, int y) : ImmovableSolid(x,y){
    red = 0;
    green = 100;
    blue = 240;
    mass = -1;
    temperature = 0;
}
Element* WaterSource::createElement(int x, int y){
    return new WaterSource(x,y);
}
void WaterSource::actOnOther(Element* element, ElementMatrix* matrix){
    if (element->mass == 0){
        matrix->setElementByString (element->x, element->y, "Water");
    }
}
bool WaterSource::corrode(ElementMatrix* matrix){
    return false;
}

//FIRE SOURCE
FireSource::FireSource(int x, int y) : ImmovableSolid(x,y){
    red = 255;
    green = 20;
    blue = 0;
    mass = -1;
    temperature = 0;
}
Element* FireSource::createElement(int x, int y){
    return new FireSource(x,y);
}
void FireSource::actOnOther(Element* element, ElementMatrix* matrix){
    if (element->mass == 0){
        matrix->setElementByString (element->x, element->y, "Fire");
    }
}
bool FireSource::corrode(ElementMatrix* matrix){
    return false;
}

//EMPTY SOURCE
EmptySource::EmptySource(int x, int y) : ImmovableSolid(x,y){
    red = 30;
    green = 30;
    blue = 30;
    mass = -1;
    temperature = 0;
}
Element* EmptySource::createElement(int x, int y){
    return new EmptySource(x,y);
}
void EmptySource::actOnOther(Element* element, ElementMatrix* matrix){
    if (element->mass != -1){
        matrix->setElementByString (element->x, element->y, "Empty");
    }
}
bool EmptySource::corrode(ElementMatrix* matrix){
    return false;
}

Titanium::Titanium(int x, int y) : ImmovableSolid(x,y){
    red = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*10) + 155;
    green = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*10) + 154;
    blue = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*10) + 149;
    health = 1000;
    mass = 1500;
    state = 0;
    temperature = 0;
    conductivity = 0;
    heatingPoint = 1200;
}
Element* Titanium::createElement(int x, int y){
    return new Titanium(x,y);
}

bool Titanium::corrode(ElementMatrix* matrix){
    return false;
}
