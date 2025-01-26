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
    /*
    SDL_Window* winbase = NULL;
    SDL_Renderer* rendbase = NULL;

    struct VGUI vgui;
    vgui.handle = "Meow!";
    vgui.w = 800;
    vgui.h = 600;
    vgui.r = 255;
    vgui.g = 255;
    vgui.b = 255;

    struct VGUIButton button1;
    button1.b_x = 100;
    button1.b_y = 100;
    button1.b_w = 200;
    button1.b_h = 150;
    button1.b_r = 0;
    button1.b_g = 0;
    button1.b_b = 255;

    struct VGUIButton button2;
    button2.b_x = 400;
    button2.b_y = 300;
    button2.b_w = 200;
    button2.b_h = 150;
    button2.b_r = 255;
    button2.b_g = 0;
    button2.b_b = 0;

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
        vgui_button(rendbase,&button1);     
        vgui_button(rendbase,&button2);
        SDL_RenderPresent(rendbase);
        SDL_Delay(1);

        
    }
    SDL_Log("SDL Shutdown!");
    SDL_DestroyRenderer(rendbase);
    SDL_DestroyWindow(winbase);
    SDL_Quit();
    */


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
}