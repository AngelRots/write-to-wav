#ifndef VGUI_BASE_H
#define VGUI_BASE_H

#include <SDL3/SDL.h>

struct VGUI 
{
    const char* handle; // Window Name
    int w;              // Window Height
    int h;              // Window Width
    Uint8 r;            // Red
    Uint8 g;            // Green
    Uint8 b;            // Blue
    
    // TODO: Implement Inheritance
    
   struct VGUIButton  
    {
        const char* BID;  // Button ID 
        int b_w;          // Button Width
        int b_h;          // Button Height
        int b_x;          // Button X Coord 
        int b_y;          // Button Y Coord
        Uint8 b_r;        // Red
        Uint8 b_g;        // Green
        Uint8 b_b;        // Blue

    };
 
};


void vgui_button(SDL_Renderer*rend,struct VGUIButton*vbutton);


#endif /* vgui_base_h */