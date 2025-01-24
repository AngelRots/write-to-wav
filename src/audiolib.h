#include <stdint.h>


#ifndef AUDIOLIB_H
#define AUDIOLIB_H


typedef unsigned char BYTE;

#define CD_SMPLRATE 44100
#define WAV_LINEARPCM 1
#define WAV_STEREO 2
#define WAV_HEADER_SIZE 44 // WAV header size

//#pragma pack(push, 1) // Ensure no padding is added
struct WAVHeader_s // WAV Structure [44 Bytes]
{
    char RIFF[4]; // Identifier « RIFF »
    BYTE FTYPE[4]; // file type ("WAVE")
    BYTE FMT[4]; // ("fmt ")
    BYTE DATACHUNK[4]; // "data" chunk ID
    int32_t SIZE; // size of file - RIFF identifier
    int32_t LEN; // Length of format data
    int16_t AFORMAT; // Audio format
    int32_t SMPLRATE; // Sample rate
    int32_t BPERSEC; // Byte rate
    int16_t CHANNELS; // Number of channels
    int16_t BITDEPTH; // Bits per sample
    int32_t DATASZ; // Size of data chunk
}; 
//#pragma pack(pop)




#endif /* audiolib_h */
