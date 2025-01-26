#ifndef VGUI_BASE_H
#define VGUI_BASE_H

#include <SDL3/SDL.h>

struct vgui 
{
    const char* handle; // Window Name
    int w;              // Window Height
    int h;              // Window Width
    Uint8 r;           
    Uint8 g;
    Uint8 b;
};

void vgui_base(SDL_Window*win,SDL_Renderer*rend,struct vgui* vgui);


#endif /* vgui_base_h */