
#include "circularBuffer.h"

#ifdef USE_DYNAMIC_ALLOCATION
    sCircBuff8bit_t * New_8BitCircularBuffer(int maxLen){
        sCircBuff8bit_t * buf = (sCircBuff8bit_t *) malloc(sizeof(sCircBuff8bit_t));
        buf->arr = (uint8_t*)malloc(sizeof(uint8_t) * maxLen);    
        buf->maxLen = maxLen;
        buf->writeIndx = 0;
        buf->readIndx = 0;
        buf->flags = 0x04;
        return buf;
    }

    int Delete_8BitCircularBuffer(sCircBuff8bit_t * buf){
        // Free memory of array
        free(buf->arr);
        // Free memory of structure
        free(buf);
        return 0;
    }
#endif


int Init_8BitCircularBuffer(sCircBuff8bit_t * buf, uint8_t * arr, int maxLen){
    buf->arr = arr; // buffer array points to a global array somewhere
    buf->maxLen = maxLen;
    buf->writeIndx = 0;
    buf->readIndx = 0;
    buf->flags = 0x04;
    return 0;
}


int Reset_8BitCircularBuffer(sCircBuff8bit_t * buf){
    buf->writeIndx = 0;
    buf->readIndx = 0;
    buf->flags = 0x04;
    for(int i = 0; i < buf->maxLen; i++){
        buf->arr[i] = 0;
    }
    // memset(buf->arr, 0, sizeof(buf->arr[0])); // undefined reference fix it.
    return 0;
}

uint8_t Full_8BitCircularBuffer(sCircBuff8bit_t * buf){
    return MASK_FULL(buf->flags);
}

uint8_t Overflow_8BitCircularBuffer(sCircBuff8bit_t * buf){
    return MASK_OVERFLOW(buf->flags);
}

uint8_t Empty_8BitCircularBuffer(sCircBuff8bit_t * buf){
    return MASK_EMPTY(buf->flags);
}

int Capacity_8BitCircularBuffer(sCircBuff8bit_t * buf){
    return buf->maxLen;
}

int Size_8BitCircularBuffer(sCircBuff8bit_t * buf){
    return (buf->writeIndx - buf->readIndx);
}

int Push_8BitCircularBuffer(sCircBuff8bit_t * buf, uint8_t data){
    // if pushing data at start, lower empty flag
    if(MASK_EMPTY(buf->flags)){
        buf->flags &= ~(CIRCULAR_BUFFER_FLAG_EMPTY);
    }
    // If the buffer is full and data is pushed. Raise the overflow flag
    if(MASK_FULL(buf->flags)){
        buf->flags |= CIRCULAR_BUFFER_FLAG_OVERFLOW;
        return 1;
    }
    // If nextElem wrapped around and met the read index, buff is full.
    if((buf->writeIndx + 1) % buf->maxLen == buf->readIndx){
        buf->flags |= CIRCULAR_BUFFER_FLAG_FULL;
    } 
    buf->arr[buf->writeIndx] = data;
    buf->writeIndx = (buf->writeIndx + 1) % buf->maxLen;    

    return 0;
}

int Pop_8BitCircularBuffer(sCircBuff8bit_t * buf, uint8_t * ret){
    // - if data has overflowed or buffer is empty, return 1
    // - At the start, the buffer has no data to pop, so we use
    // the empty flag to avoid that error case. It also helps us
    // when the writer rolls back into the reader.
    if(
        MASK_OVERFLOW(buf->flags) || 
        MASK_EMPTY(buf->flags) ||
    ((buf->readIndx == buf->writeIndx) && MASK_EMPTY(buf->flags))
    ) {
        return 1;
    }

    // if the buffer is full, popping data will drop flag
    // keep flag raised if there was an overflow
    if(MASK_FULL(buf->flags) && !(MASK_OVERFLOW(buf->flags))){
        buf->flags &= ~(CIRCULAR_BUFFER_FLAG_FULL);
    }

    *ret = buf->arr[buf->readIndx];
    buf->readIndx = (buf->readIndx + 1) % buf->maxLen;
    return 0;
}


