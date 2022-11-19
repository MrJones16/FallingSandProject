#pragma once

#include <vector>
#include <map>
#include <string>
#include "Element.h"
#include "Elements.h"

class ElementMatrix{
    private:
        int Width, Height;
        
        std::vector<Element*> *matrix;
        
    public:
        std::map<std::string, Element*> *elementMap;
        bool update_status = false;
        // friend class Element;
        ElementMatrix(int Width, int Height);
        ~ElementMatrix();
        Element* getElement(int x, int y);
        void setElement(int x, int y, Element* element);
        bool setElementByString(int x, int y, std::string element_name);
        bool swapElements(int x1, int y1, int x2, int y2);
        void stepAll();
        void getMatrixPixels(uint32_t *pixels);
        bool checkIfDead(int x, int y);
        void DieAndReplace(int x, int y, std::string element_name);
        //void DieAndReplaceWithElement(int x, int y, Element* element);
        void pushElements(int xPos, int yPos, int radius, float forceMultiplier);
        
    
};


