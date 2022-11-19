#include <iostream>
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include "ElementMatrix.h"
//#include "MovableSolid.h"
#include "Elements.h"
#include <math.h>


using namespace std;

int Width = 192, Height = 108;

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("My Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, 0);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    float scaleX = 10;
    float scaleY = 10;

    SDL_RenderSetLogicalSize(renderer, Width*10, Height*10);
    //int SDL_RenderSetScale(SDL_Renderer * renderer, float scaleX, float scaleY);

    //setting background color to black
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    SDL_Event event;

    SDL_Texture * texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, Width, Height);

    uint32_t * pixels = new Uint32[Width * Height];
    memset(pixels, 0, Width * Height * sizeof(Uint32));
    cout << "Making the matrix" << endl;
    ElementMatrix *matrix = new ElementMatrix(Width, Height);
    cout << "Matrix Made Successfully" << endl;


    //input variables
    int mouseX = 0, mouseY = 0;
    bool LMB = false;
    bool RMB = false;
    bool SMB = false;
    bool BMB = false;
    bool FMB = false;
    bool ScrollingUp = false;
    bool Scrollingdown = false;

    //Game Variables
    bool constant_update = false;
    int elementNumber = 0;
    int brush_size = 1;
    std::string curr_element = "Sand";


    
    bool quit = false;
    while (!quit){
        while (SDL_PollEvent(&event)){
            switch (event.type)
            {
            case SDL_QUIT://quitting the program
                quit = true;
                break;
            case SDL_KEYDOWN://on key downs
                if (SDLK_RIGHT == event.key.keysym.sym){
                    matrix->stepAll();
                }
                if (SDLK_SPACE == event.key.keysym.sym){
                    constant_update = !constant_update;
                }
                if (SDLK_c == event.key.keysym.sym){
                    memset(pixels, 0, Width * Height * sizeof(Uint32));
                }
                break;
            case SDL_KEYUP:// key ups
                if (SDLK_a == event.key.keysym.sym){
                    
                }
                break;
            case SDL_MOUSEMOTION:
                SDL_GetMouseState(&mouseX, &mouseY);
                mouseX/=10;
                mouseY/=10;
                cout << mouseX << " : " << mouseY << endl;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (SDL_BUTTON_LEFT == event.button.button){
                    LMB = true;
                    cout << "Left Mouse Button Down" << endl;
                }
                else if (SDL_BUTTON_RIGHT == event.button.button){
                    RMB = true;
                    cout << "Right Mouse Button Down" << endl;
                }
                else if (SDL_BUTTON_MIDDLE == event.button.button){
                    SMB = true;
                    cout << "Middle Mouse Button Down" << endl;
                }
                else if (SDL_BUTTON_X1 == event.button.button){
                    BMB = true;
                    cout << "Back Mouse Button Down" << endl;
                    brush_size--;
                    if (brush_size < 1) brush_size = 1;
                }
                else if (SDL_BUTTON_X2 == event.button.button){
                    FMB = true;
                    cout << "Forward Mouse Button Down" << endl;
                    brush_size++;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (SDL_BUTTON_LEFT == event.button.button){
                    LMB = false;
                    cout << "Left Mouse Button Up" << endl;
                }
                else if (SDL_BUTTON_RIGHT == event.button.button){
                    RMB = false;
                    cout << "Right Mouse Button Up" << endl;
                }
                else if (SDL_BUTTON_MIDDLE == event.button.button){
                    SMB = false;
                    cout << "Middle Mouse Button Up" << endl;
                }
                else if (SDL_BUTTON_X1 == event.button.button){
                    BMB = false;
                    cout << "Back Mouse Button Up" << endl;
                }
                else if (SDL_BUTTON_X2 == event.button.button){
                    FMB = false;
                    cout << "Forward Mouse Button Up" << endl;
                }
                break;
            case SDL_MOUSEWHEEL:
                if (event.wheel.y > 0){
                    ScrollingUp = true;
                    cout << "Mouse Wheel Scrolling Up" << endl;
                    elementNumber++;
                }else{ScrollingUp = false;}
                if (event.wheel.y < 0){
                    Scrollingdown = true;
                    cout << "Mouse Wheel Scrolling Down" << endl;
                    elementNumber--;
                }else {Scrollingdown = false;}
                break;
            default:
                break;
            }
            //Make the mouse positions locked to the window size - 1 (since array is 0 - 999):
            
        }
        int elementCount = matrix->elementMap->size(); // change this later

        if (elementNumber< 0) elementNumber = 0;
        if (elementNumber > elementCount - 1) elementNumber = elementCount - 1;

        switch (elementNumber)
        {
        case 0: // Empty
            curr_element = "Empty";
            break;
        case 1: // stone
            curr_element = "Stone";
            break;
        case 2: // Sand
            curr_element = "Sand";
            break;
        case 3:
            curr_element = "Water";
            break;
        case 4: // Wood
            curr_element = "Wood";
            break;
        case 5:
            curr_element = "Fire";
            break;
        case 6:
            curr_element = "Smoke";
            break;
        case 7:
            curr_element = "Steam";
            break;
        case 8:
            curr_element = "WaterSource";
            break;
        case 9:
            curr_element = "FireSource";
            break;
        case 10:
            curr_element = "EmptySource";
            break;
        case 11:
            curr_element = "Acid";
            break;
        case 12:
            curr_element = "Titanium";
            break;
        case 13:
            curr_element = "Particle";
            break;
        default:
            break;
        }
        

        //UPDATE LOOP START

        //drawing elements with mouse:
        if (mouseX > Width-1) mouseX = Width-1;
        if (mouseX < 0) mouseX = 0;
        if (mouseY > Height-1) mouseY = Height-1;
        if (mouseY < 0) mouseY = 0;
        if (LMB){
            //pixels[mouseY * Width + mouseX] = 0xFFFFFFFF;
            if (curr_element == "Particle"){
                matrix->pushElements(mouseX, mouseY, brush_size, 1);
            }else{
                for (int x = -brush_size; x < brush_size + 1; x++){
                    int x2 = mouseX + x;
                    for (int y = -brush_size; y < brush_size + 1; y++){
                        int y2 = mouseY + y;
                        if (sqrt(pow((x2 - mouseX), 2) + pow(y2 - mouseY,2)) < brush_size){
                            matrix->setElementByString(x2, y2, curr_element);
                        }
                    }
                }
            }
            //bool placed = matrix->setElementByString(mouseX, mouseY, curr_element);
            //cout << "placed?: " << placed << endl;
        }

        //step through the matrixx
        if (constant_update) matrix->stepAll();

        //get the matrix pixels to render
        matrix->getMatrixPixels(pixels);

        //replace brush pixels to show the brush
        for (int x = -brush_size; x < brush_size + 1; x++){
            int x2 = mouseX + x;
            for (int y = -brush_size; y < brush_size + 1; y++){
                int y2 = mouseY + y;
                if (sqrt(pow((x2-mouseX), 2) + pow(y2 - mouseY,2)) < brush_size){
                    if (x2 < 0 || x2 >= Width) continue;
                    if (y2 < 0 || y2 >= Height) continue;
                    //cout << "Coloring Pixel" << endl;
                    pixels[y2 * Width + x2] = matrix->elementMap->find(curr_element)->second->getColor();
                }
            }
        }
        //pixels[mouseY * Width + mouseX] = matrix->elementMap->find(curr_element)->second->getColor();
        

        //rendering to the screen

        SDL_UpdateTexture(texture, NULL, pixels, Width * sizeof(Uint32));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);

        //UPDATE LOOP END

    }
    




    delete[] pixels;
    delete matrix;
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
