#include <stdio.h>
#include "vgui_base.h"


/**
 * @brief          Creates a window using SDL3 with a structure's parameters.
 * 
 * @param win      The pointer to the SDL window. 
 * @param rend     The pointer to the SDL renderer.
 * @param vgui     The address of the VGUI structure.
 */
void vgui_base(SDL_Window*win,SDL_Renderer*rend,struct vgui* vgui)
{
  

    if(SDL_Init(SDL_INIT_VIDEO || SDL_INIT_EVENTS) != 1) /* Returns true on success, false otherwise. */
    {
        printf("SDL wasn't initialized correctly!\n");
        SDL_Log("SDL Error: %s",SDL_GetError());
        exit(-3);
    }

    win = SDL_CreateWindow(vgui->handle,vgui->w,vgui->h,0);
    if(win == NULL)
    {
        SDL_Log("SDL Window Error: %s",SDL_GetError());
        exit(-4);
    }

    rend = SDL_CreateRenderer(win,NULL);
    if(rend == NULL)
    {
        SDL_Log("SDL Renderer Error: %s",SDL_GetError());
        exit(-5);
    }
    
    SDL_Event LIB_EVENT;
    
    int noInit = 0;
    while(!noInit)
    {
        while(SDL_PollEvent(&LIB_EVENT)) 
        {
            switch(LIB_EVENT.type) 
            {
                case SDL_EVENT_QUIT:
                SDL_Log("SDL3 Event Exception!");
                noInit = 1;
                break;
            }
        }
        SDL_SetRenderDrawColor(rend,vgui->r,vgui->g,vgui->b,0xff);
        SDL_RenderClear(rend);
        SDL_RenderPresent(rend);
        SDL_Delay(1);

        
    }
    SDL_Log("SDL Shutdown!");
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();

}