#include <stdio.h>
#include "vgui_base.h"





void vgui_button(SDL_Renderer*rend,struct VGUIButton* vbutton)
{
    if(rend == NULL)
    {
        SDL_Log("SDL Renderer Error: %s",SDL_GetError());
        exit(-5);
    } 
   

   SDL_FRect quickref;
   quickref.x = vbutton->b_x;
   quickref.y = vbutton->b_y;
   quickref.w = vbutton->b_w;
   quickref.h = vbutton->b_h;


   SDL_SetRenderDrawColor(rend,vbutton->b_r,vbutton->b_g,vbutton->b_b,SDL_ALPHA_OPAQUE);

   SDL_RenderFillRect(rend,&quickref);
   
   SDL_Delay(1);

}
