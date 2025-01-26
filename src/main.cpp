#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "fmt_wav.h"
#include "audiodef.h"
#include "os_dep.h"
#include "xclock.h"


#include "vgui/vgui_base.h"
#include "imgui/include/imgui.h"
#include "imgui/include/imgui_impl_sdl3.h"
#include "imgui/include/imgui_impl_sdlrenderer3.h"
#include <SDL3/SDL.h>

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

     
    SDL_Window* winbase = NULL;
    SDL_Renderer* rendbase = NULL;

    struct VGUI vgui;
    vgui.handle = "Meow!";
    vgui.w = 800;
    vgui.h = 600;
    vgui.r = 255;
    vgui.g = 255;
    vgui.b = 255;


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
            if(SDL_EVENT_MOUSE_MOTION == LIB_EVENT.type)
            {
                float mouse_x, mouse_y; 

                SDL_GetMouseState(&mouse_x,&mouse_y);
                printf("Mouse X:%f\n",mouse_x);

            }
            ImGui_ImplSDL3_ProcessEvent(&LIB_EVENT);

        }
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();

        ImGui::NewFrame();

        ImGui::Begin("IMGUI");
        ImGui::Text("Cruel World!");
        ImGui::End();
        ImGui::Render();

        SDL_SetRenderDrawColor(rendbase, vgui.r, vgui.g, vgui.b, 0xff);
        SDL_RenderClear(rendbase);
        
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(),rendbase);

        SDL_RenderPresent(rendbase);
        SDL_Delay(1);

        
    }
    SDL_Log("SDL Shutdown!");
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
    SDL_DestroyRenderer(rendbase);
    SDL_DestroyWindow(winbase);
    SDL_Quit();
    

    /*

    struct WAVHeader_s wav;
    char filename[OS_PATHMAX]; 
    char fullFilename[OS_PATHMAX + 4]; 
    SBYTE* PCMD = NULL;




    InitRIFF(&wav, WAV_LINEARPCM, CD_SMPLRATE, WAV_STEREO, 16);


    printf("Enter a filename: ");
    scanf("%s", filename);
    
    snprintf(fullFilename, sizeof(fullFilename), "%s%s", filename,WAV_FMTEX);
    
    if(strlen(filename) > OS_PATHMAX - 4)
    {
        printf("Filename was too long!\n");
        exit(EC_USRERR);
    }

    printf("Checking WAV Header Size...\n");
    xsleep(1);
    if (sizeof(wav) != WAV_EXSIZE)
    {
        printf("WAV Header size doesn't match! (%zu)\n",sizeof(wav));
        printf("Exiting program!\n");
        exit(EC_SZNMATCH);
    }
    printf("WAV Header is %zu bytes.\n", sizeof(wav));

    FILE* fp = fopen(fullFilename, "wb");
    if (fp == NULL)
    {
        printf("Error creating file!");
        exit(EC_NOPTR);
    }

    // Write the header to the file
    printf("Writing Header information to file...\n");
    fwrite(&wav, 1, WAV_EXSIZE, fp);
    


    printf("Writing Raw Data...\n");
    xsleep(1);
    CreatePCM(&wav,PCMD,fp,0);

    printf("Data Written!\n");
    printf("WAV Size: %.1fKB\n", round(wav.DATASZ / 1024.0));

    fclose(fp);
    free(PCMD);

    printf("WAV file created successfully!\n");
    return EC_SUCCESS;
    */
}