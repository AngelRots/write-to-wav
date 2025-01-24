#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include "audiolib.h"
#include "audiodef.h"

#define PI 3.14159265358979323846


#define MAX_AMP 32767

int main(void)
{
    struct WAVHeader_s wav;
    strncpy(wav.RIFF,"RIFF",4);
            wav.RIFF[4] = '\0'; // Manually null-terminate

    strncpy(wav.FTYPE,"WAVE",4);
        wav.FTYPE[4] = '\0'; // Manually null-terminate

    strncpy(wav.FMT,"fmt ",4);
            wav.FMT[4] = '\0'; // Manually null-terminate

    strncpy(wav.DATACHUNK,"data",4);
            wav.DATACHUNK[4] = '\0'; // Manually null-terminate


 

    wav.BITDEPTH = 16; // Bits per sample

    wav.LEN = 16; // PCM
    wav.AFORMAT = WAV_LINEARPCM; // PCM
    wav.SMPLRATE = CD_SMPLRATE; // Sample rate
    wav.BPERSEC = wav.SMPLRATE * WAV_STEREO * (wav.BITDEPTH / 8); // Bytes per second
    wav.CHANNELS = WAV_STEREO; // Stereo

    int numSamples = CD_SMPLRATE; // number of samples for 1 second of audio
    wav.DATASZ = numSamples * wav.CHANNELS * (wav.BITDEPTH / 8); // Size of audio data

    // Calculate total file size
    wav.SIZE = sizeof(wav) + wav.DATASZ - 8; // 8 bytes for the RIFF header

    if(sizeof(wav) != 44)
    {
        printf("WAV Header size doesn't match!\n");
        exit(-1);
    }
    
    FILE* fp = fopen("output.wav", "wb");
    if (fp == NULL)
    {
        printf("Error creating file!");
        exit(-1);
    }
    
    // Write the header to the file
    fwrite(&wav, sizeof(struct WAVHeader_s), 1, fp);
    if (sizeof(wav) != 0 || NULL)
    {
        printf("Size of WAV Header: %lld Bytes\n", sizeof(wav));
        printf("WAVE Header was written!\n");
    }
    else 
    {
        printf("Error while writing WAV Header!\n");
    }

    BYTE* audioData = (BYTE*)calloc(wav.DATASZ, sizeof(BYTE));
    for (int i = 0; i < numSamples; i++)
    {
        int sampleValue = MAX_AMP * (sin(2 / 2) + sin(3 / 3) * NOTE_C3 * i) / wav.SMPLRATE;
        
        audioData[i * 2] = (BYTE)(sampleValue & 0xFF); // Lower byte
        audioData[i * 2 + 1] = (BYTE)((sampleValue >> 8) & 0xFF); // Upper byte

        
    }
    printf("Writing Raw Data...\n");
    sleep(1);
    fwrite(audioData, sizeof(BYTE), wav.DATASZ, fp);
    printf("Data Written!\n");
    printf("WAV Size: %.1fKB\n", round(wav.DATASZ));

  printf("%s\n",wav.RIFF);
    

    fclose(fp);
    free(audioData); 

    printf("WAV file created successfully!\n");
    return 0;
}