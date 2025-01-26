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
    //SDL_Window* winbase = NULL;
    //SDL_Renderer* rendbase = NULL;

    //vgui_base("Oh my SDL!",1024,768,winbase,rendbase,255,255,0);
    

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