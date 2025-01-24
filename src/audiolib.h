#include <stdint.h>

#ifndef AUDIOLIB_H
#define AUDIOLIB_H

typedef unsigned char BYTE;

#define CD_SMPLRATE     44100
#define WAV_LINEARPCM   1
#define WAV_STEREO      2
#define WAV_EXSIZE      44 

#pragma pack(push, 1)   // Ensure no padding is added
struct WAVHeader_s      // WAV Structure [44 Bytes]
{
    char RIFF[4];       // Identifier "RIFF"
    int32_t SIZE;       // size of file - 8 bytes
    char FTYPE[4];      // file type ("WAVE")
    char FMT[4];        // "fmt " sub-chunk
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

#endif /* audiolib_h */
