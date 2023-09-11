#ifndef _CIRCULARBUFFER_H
#define _CIRCULARBUFFER_H
/**
 * Circular Buffer
 * - At overflow occurance, the readIndx contents will not be updated
 * - It is up to the program to empty the contents of the buffer when 
 * it has overflowed.
 * - It is recommended to use powers of 2 for the buffer size to ensure
 * the data fits nicely in the pages of memory.
 * - define dynamic allocation if you want to D.A memory. This will
 * introduce misalignements if you are not careful. (Something to add in future)
*/
#include <stdint.h>
#include <assert.h>
// #include <string.h> // memset

typedef enum {
    CIRCULAR_BUFFER_FLAG_FULL = 0x01,
    CIRCULAR_BUFFER_FLAG_OVERFLOW = 0x02,
    CIRCULAR_BUFFER_FLAG_EMPTY = 0x04,
} eCircularBufferFlag_t;

#define MASK_FULL(x)            (x & CIRCULAR_BUFFER_FLAG_FULL)
#define MASK_OVERFLOW(x)        ((x & CIRCULAR_BUFFER_FLAG_OVERFLOW) >> 1)
#define MASK_EMPTY(x)           ((x & CIRCULAR_BUFFER_FLAG_EMPTY) >> 2)

typedef struct {
    uint8_t * arr;
    int writeIndx;
    int readIndx;
    int maxLen;
    uint8_t flags;
} sCircBuff8bit_t;

// #define USE_DYNAMIC_ALLOCATION
#ifdef USE_DYNAMIC_ALLOCATION
    #include <stdlib.h> // free 
    sCircBuff8bit_t * New_8BitCircularBuffer(int maxLen);
    int Delete_8BitCircularBuffer(sCircBuff8bit_t * buf);
#endif


int Init_8BitCircularBuffer(sCircBuff8bit_t * buf, uint8_t * arr, int maxLen);

int Reset_8BitCircularBuffer(sCircBuff8bit_t * buf);

uint8_t Full_8BitCircularBuffer(sCircBuff8bit_t * buf);

uint8_t Overflow_8BitCircularBuffer(sCircBuff8bit_t * buf);

uint8_t Empty_8BitCircularBuffer(sCircBuff8bit_t * buf);

int Capacity_8BitCircularBuffer(sCircBuff8bit_t * buf);

int Size_8BitCircularBuffer(sCircBuff8bit_t * buf);

int Push_8BitCircularBuffer(sCircBuff8bit_t * buf, uint8_t data);

int Pop_8BitCircularBuffer(sCircBuff8bit_t * buf, uint8_t * ret);


#endif