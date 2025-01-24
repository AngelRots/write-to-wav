#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "audiolib.h"
#include "audiodef.h"
#include "os_dep.h"


#define PI      3.14159265358979323846
#define MAX_AMP 32767




int main(void)
{
    struct WAVHeader_s wav;

    memcpy(wav.RIFF, "RIFF", 4);

    memcpy(wav.FTYPE, "WAVE", 4);

    memcpy(wav.FMT, "fmt ", 4);

    memcpy(wav.DATACHUNK, "data", 4);

    wav.LEN = 16;                       // PCM
    wav.AFORMAT = WAV_LINEARPCM;        // PCM
    wav.SMPLRATE = CD_SMPLRATE;         // Sample rate
    wav.CHANNELS = WAV_STEREO;          // Stereo
    wav.BITDEPTH = 16;                  // Bits per sample
    wav.BPERSEC = wav.SMPLRATE * wav.CHANNELS * (wav.BITDEPTH / 8);     // Bytes per second
    wav.BLOCKALIGN = wav.CHANNELS * (wav.BITDEPTH / 8);                 // Block align

    int numSamples = CD_SMPLRATE;                                       // number of samples for 1 second of audio
    wav.DATASZ = numSamples * wav.CHANNELS * (wav.BITDEPTH / 8);        // Size of audio data

    // Calculate total file size
    wav.SIZE = 36 + wav.DATASZ; 

    printf("Checking WAV Header Size...\n");
    slp(1);
    if (sizeof(wav) != WAV_EXSIZE)
    {
        printf("WAV Header size doesn't match! (%zu)\n",sizeof(wav));
        printf("Exiting program!\n");
        exit(-1);
    }
    printf("WAV Header is %zu bytes.\n", sizeof(wav));

    FILE* fp = fopen("output.wav", "wb");
    if (fp == NULL)
    {
        printf("Error creating file!");
        exit(-1);
    }

    // Write the header to the file
    printf("Writing Header information to file...\n");
    fwrite(&wav, 1, WAV_EXSIZE, fp);
    

    SBYTE* audioData = (SBYTE*)calloc(wav.DATASZ, sizeof(SBYTE));
    for (int i = 0; i < numSamples; i++)
    {
        int sampleValue = MAX_AMP * cos((2 * PI * NOTE_C3 * i) / wav.SMPLRATE);

        audioData[i * 2] = (SBYTE)(sampleValue & 0xFF);              // Lower byte
        audioData[i * 2 + 1] = (SBYTE)((sampleValue >> 8) & 0xFF);   // Upper byte
    }
    printf("Writing Raw Data...\n");
    slp(1);
    fwrite(audioData, sizeof(SBYTE), wav.DATASZ, fp);
    printf("Data Written!\n");
    printf("WAV Size: %.1fKB\n", round(wav.DATASZ / 1024.0));

    fclose(fp);
    free(audioData);

    printf("WAV file created successfully!\n");
    return 0;
}