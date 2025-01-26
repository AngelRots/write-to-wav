#include <stdint.h>
#include "os_dep.h"
#include <stdio.h>
#include <math.h>

#ifndef FMT_WAV_H
#define FMT_WAV_H


#define CD_SMPLRATE     44100
#define WAV_LINEARPCM   1
#define WAV_STEREO      2
#define WAV_EXSIZE      44 
#define WAV_FMTEX       ".wav"

                        // Source: https://docs.fileformat.com/audio/wav/
#pragma pack(push, 1)   // Ensure no padding is added
struct WAVHeader_s      // WAV Structure [44 Bytes]
{
    SBYTE RIFF[4];      // Identifier "RIFF"
    int32_t SIZE;       // size of file - 8 bytes
    SBYTE FTYPE[4];     // file type ("WAVE")
    SBYTE FMT[4];       // "fmt " sub-chunk
    int32_t LEN;        // Length of format data
    int16_t AFORMAT;    // Audio format
    int16_t CHANNELS;   // Number of channels
    int32_t SMPLRATE;   // Sample rate
    int32_t BPERSEC;    // Byte rate
    int16_t BLOCKALIGN; // Block align
    int16_t BITDEPTH;   // Bits per sample
    char DATACHUNK[4];  // "data" sub-chunk
    int32_t DATASZ;     // Size of data chunk
};
#pragma pack(pop)


void InitRIFF(struct WAVHeader_s* wav,int PCM, int kHz, int chnum, int bitdepth);

void CreatePCM(struct WAVHeader_s* wav,FILE*fptr);

#endif /* fmt_wav_h */
