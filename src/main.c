#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "fmt_wav.h"
#include "audiodef.h"
#include "os_dep.h"
#include "xclock.h"

#define SDL_MAIN_HANDLED // Avoid Main() method before sdl.h
#include <SDL3/SDL.h>

#include "vgui/vgui_base.h"


int main(void)
{
    struct VGUI vgui;
    struct VGUIButton vbutton;
    SDL_Window* winbase = NULL;
    SDL_Renderer* rendbase = NULL;

    
    vgui.handle = "Meow!";
    vgui.w = 800;
    vgui.h = 600;
    vgui.r = 0;
    vgui.g = 0;
    vgui.b = 150;

    vbutton.b_w = 64;
    vbutton.b_h = 64;
    vbutton.b_x = 100;
    vbutton.b_y = 100;
    
    vbutton.b_r = 255;
    vbutton.b_g = 255;
    vbutton.b_b = 255;


    



    if(SDL_Init(SDL_INIT_VIDEO || SDL_INIT_EVENTS) != 1) /* Returns true on success, false otherwise. */
    {
        printf("SDL wasn't initialized correctly!\n");
        SDL_Log("SDL Error: %s",SDL_GetError());
        exit(-3);
        
    }

    winbase = SDL_CreateWindow(vgui.handle,vgui.w,vgui.h,0);
    if(winbase == NULL)
    {
        SDL_Log("SDL Window Error: %s",SDL_GetError());
        exit(-4);
    }

    rendbase = SDL_CreateRenderer(winbase,NULL);
    if(rendbase == NULL)
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
            if(SDL_EVENT_MOUSE_MOTION == LIB_EVENT.type)
            {
                float mouse_x, mouse_y; 

                SDL_GetMouseState(&mouse_x,&mouse_y);
                printf("Mouse X:%f\n",mouse_x);

            }
        }
        SDL_SetRenderDrawColor(rendbase, vgui.r, vgui.g, vgui.b, 0xff);
        SDL_RenderClear(rendbase);
          vgui_button(rendbase,&vbutton);     
        SDL_RenderPresent(rendbase);
        SDL_Delay(1);

        
    }
    SDL_Log("SDL Shutdown!");
    SDL_DestroyRenderer(rendbase);
    SDL_DestroyWindow(winbase);
    SDL_Quit();








    

   
    

    struct WAVHeader_s wav;
    char filename[OS_PATHMAX]; 
    char fullFilename[OS_PATHMAX + 4]; 
    SBYTE* PCMD = NULL;


    memcpy(wav.RIFF, "RIFF", 4);

    memcpy(wav.FTYPE, "WAVE", 4);

    memcpy(wav.FMT, "fmt ", 4);

    memcpy(wav.DATACHUNK, "data", 4);

    InitRIFF(&wav, WAV_LINEARPCM, CD_SMPLRATE, WAV_STEREO, 16);


    printf("Enter a filename: ");
    scanf("%s", filename);
    
    snprintf(fullFilename, sizeof(fullFilename), "%s%s", filename,WAV_FMTEX);
    
    if(strlen(filename) > OS_PATHMAX - 4)
    {
        printf("Filename was too long!\n");
        exit(-2);
    }

    printf("Checking WAV Header Size...\n");
    xsleep(1);
    if (sizeof(wav) != WAV_EXSIZE)
    {
        printf("WAV Header size doesn't match! (%zu)\n",sizeof(wav));
        printf("Exiting program!\n");
        exit(-1);
    }
    printf("WAV Header is %zu bytes.\n", sizeof(wav));

    FILE* fp = fopen(fullFilename, "wb");
    if (fp == NULL)
    {
        printf("Error creating file!");
        exit(-1);
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
    return 0;
}