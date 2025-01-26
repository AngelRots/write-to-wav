#include <stdio.h>
#include "vgui_base.h"


void vgui_base(const char* name, int w, int h, SDL_Window*win,SDL_Renderer*rend,Uint8 r,Uint8 g, Uint8 b)
{
  

    if(SDL_Init(SDL_INIT_VIDEO || SDL_INIT_EVENTS) != 1) /* Returns true on success, false otherwise. */
    {
        printf("SDL wasn't initialized correctly!\n");
        SDL_Log("SDL Error: %s",SDL_GetError());
        exit(-3);
    }

    win = SDL_CreateWindow(name,w,h,0);
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
        SDL_SetRenderDrawColor(rend,r,g,b,0xff);
        SDL_RenderClear(rend);
        SDL_RenderPresent(rend);
        SDL_Delay(1);

        
    }
    SDL_Log("SDL Shutdown!");
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();

}