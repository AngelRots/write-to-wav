#include "fmt_wav.h"
#include "audiodef.h"


/**
 * @brief          Initializes the values of the WAV Header with the specified information.
 * 
 * @param wav      The address of the file structure.
 * @param PCM      The audio format (PCM).
 * @param kHz      The sample rate in kHz.
 * @param chnum    The number of channels (e.g. stereo).
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

/** 
* @brief         Allocates dynamic memory and writes audio in a WAV file before freeing it. 
* @param wav     The address of the file structure.
* @param fptr    A pointer to the file.
* @param PMD     A pointer to PCM Data.
* @param memflag If true it frees the buffer right after, false if it has to be handled manually.
*/
void CreatePCM(struct WAVHeader_s* wav,SBYTE* PMD,FILE*fptr,int memflag)
{
    PMD = (SBYTE*)calloc(wav->DATASZ, sizeof(SBYTE));
    for (int i = 0; i < wav->SMPLRATE; i++)
    {
        int sampleValue = MAX_AMP * cos((2 * PI * NOTE_C3 * i) / wav->SMPLRATE);

        PMD[i * 2] = (SBYTE)(sampleValue & 0xFF);              // Lower byte
        PMD[i * 2 + 1] = (SBYTE)((sampleValue >> 8) & 0xFF);   // Upper byte
    }
        fwrite(PMD, sizeof(SBYTE), wav->DATASZ, fptr);
        if(memflag != 0)
        {
            free(PMD);
            printf("CreatePCM was freed automatically.\n");
        }

}


