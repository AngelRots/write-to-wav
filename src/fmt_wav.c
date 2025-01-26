#include "fmt_wav.h"
#include <stdio.h>

/**
 * @brief Initializes the values of the WAV Header with the specified information.
 * 
 * @param wav The address of the file header.
 * @param PCM The audio format (PCM).
 * @param kHz The sample rate in kHz.
 * @param chnum The number of channels (e.g. stereo).
 * @param bitdepth The bit depth (e.g., 16 bits per sample).
 */
void InitRIFF(struct WAVHeader_s* wav, int PCM, int kHz, int chnum, int bitdepth)
{
    int numSamples = kHz;                // number of samples for 1 second of audio
    wav->LEN = 16;                       // PCM
    wav->AFORMAT = PCM;                  // PCM
    wav->SMPLRATE = kHz;                 // Sample rate
    wav->CHANNELS = chnum;               // Stereo
    wav->BITDEPTH = bitdepth;            // Bits per sample
    wav->BPERSEC = wav->SMPLRATE * wav->CHANNELS * (wav->BITDEPTH / 8);    // Bytes per second
    wav->BLOCKALIGN = wav->CHANNELS * (wav->BITDEPTH / 8);                 // Block align
    wav->DATASZ = numSamples * wav->CHANNELS * (wav->BITDEPTH / 8);        // Size of audio data

    wav->SIZE = wav->DATASZ - 8; // RIFF Chunk Size
}
