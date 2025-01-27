#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "fmt_wav.h"
#include "audiodef.h"
#include "os_dep.h"
#include "xclock.h"


#include "vgui/vgui_base.h"
#include "vgui/vgui_def.hpp"
#include "imgui/include/imgui.h"
#include "imgui/include/imgui_impl_sdl3.h"
#include "imgui/include/imgui_impl_sdlrenderer3.h"
#include <SDL3/SDL.h>

using namespace CGUI;


enum EXITCODES 
{
  EC_SUCCESS,
  EC_NOPTR,
  EC_ERRNRENDER,
  EC_ERRWIN,
  EC_ERRINIT,
  EC_USRERR,
  EC_SZNMATCH

};


int main(void)
{
     
    SDL_Window*   winbase  = NULL;
    SDL_Renderer* rendbase = NULL;

    Panel vpan;
    App   app;

    
    struct VGUI vgui;
    vgui.handle = "Meow!";
    vgui.w = 800;
    vgui.h = 600;
    vgui.r = 70;
    vgui.g = 70;
    vgui.b = 70;


    if(SDL_Init(SDL_INIT_VIDEO || SDL_INIT_EVENTS) != 1) // Returns true on success, false otherwise. 
    {
        printf("SDL wasn't initialized correctly!\n");
        SDL_Log("SDL Error: %s",SDL_GetError());
        exit(EC_ERRINIT);
        
    }

    winbase = SDL_CreateWindow(vgui.handle,vgui.w,vgui.h,0);
    if(winbase == NULL)
    {
        SDL_Log("SDL Window Error: %s",SDL_GetError());
        exit(EC_ERRWIN);
    }

    rendbase = SDL_CreateRenderer(winbase,NULL);
    if(rendbase == NULL)
    {
        SDL_Log("SDL Renderer Error: %s",SDL_GetError());
        exit(EC_ERRNRENDER);
    }
    
    SDL_Event LIB_EVENT;
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplSDL3_InitForSDLRenderer(winbase,rendbase);
    ImGui_ImplSDLRenderer3_Init(rendbase);


    int noInit = 0;
    while(!noInit && vpan.WinActive)
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
            ImGui_ImplSDL3_ProcessEvent(&LIB_EVENT);
        }
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();

        ImGui::StyleColorsDark();
        ImGui::NewFrame();
        if(app.WinStyleEdit)
        {
            ImGui::Begin("Dear ImGui Style Editor", &app.WinStyleEdit);
            ImGui::ShowStyleEditor();
            ImGui::End();
        }
        ImGui::Begin("ImGui Menu",&vpan.WinActive,ImGuiWindowFlags_MenuBar);
        ImGui::Text("ImGui Version: (%s)",IMGUI_VERSION);
        ImGui::Spacing();
        
        if(ImGui::BeginMainMenuBar())
        {
            if(ImGui::Button("Quit"))         { vpan.WinActive   = false;  }
            if(ImGui::Button("Style Editor")) { app.WinStyleEdit = true;   } 
          
            ImGui::EndMainMenuBar();
        }
        
        ImGui::ColorEdit3("Color Picker",vpan.WinColors);
       
        ImGui::End();

        ImGui::Render();

        SDL_SetRenderDrawColor(rendbase, vgui.r, vgui.g, vgui.b, 0xff);
        SDL_RenderClear(rendbase);
        
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(),rendbase);

        SDL_RenderPresent(rendbase);
        SDL_Delay(1);

        
    }
    SDL_Log("SDL Shutdown!\n");
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
    SDL_DestroyRenderer(rendbase);
    SDL_DestroyWindow(winbase);
    SDL_Quit();
    return EC_SUCCESS;
    
}