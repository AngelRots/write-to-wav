#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include "audiolib.h"

#define PI 3.14159265358979323846

#define NOTE_C2 65.4
#define NOTE_C3 130.813
#define NOTE_C4 261.6
#define MAX_AMP 32767

int main(void)
{
    struct WAVHeader_s wav;

    wav.RIFF[0] = 'R';
    wav.RIFF[1] = 'I';
    wav.RIFF[2] = 'F';
    wav.RIFF[3] = 'F';

    wav.FTYPE[0] = 'W';
    wav.FTYPE[1] = 'A';
    wav.FTYPE[2] = 'V';
    wav.FTYPE[3] = 'E';

    wav.FMT[0] = 'f';
    wav.FMT[1] = 'm';
    wav.FMT[2] = 't';
    wav.FMT[3] = ' '; // NULL terminator
    
    wav.DATACHUNK[0] = 'd';
    wav.DATACHUNK[1] = 'a';
    wav.DATACHUNK[2] = 't';
    wav.DATACHUNK[3] = 'a';

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
        printf("Size of WAV Header: %lld\n", sizeof(wav));
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

  
    

    fclose(fp);
    free(audioData); 

    printf("WAV file created successfully!\n");
    return 0;
}