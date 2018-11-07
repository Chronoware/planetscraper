#include <stdint.h>
#include "colors.h"

uint8_t fgRed(uint8_t* src, uint32_t pos){
    return (src[pos+1] & 0x0F)*17;
}

uint8_t fgGreen(uint8_t* src, uint32_t pos){
    return (src[pos+2] >> 4)*17;
}

uint8_t fgBlue(uint8_t* src, uint32_t pos){
    return (src[pos+2] & 0x0F)*17;
}

uint8_t bgRed(uint8_t* src, uint32_t pos){
    return (src[pos+3] & 0x0F)*17;
}

uint8_t bgGreen(uint8_t* src, uint32_t pos){
    return (src[pos+4] >> 4)*17;
}

uint8_t bgBlue(uint8_t* src, uint32_t pos){
    return (src[pos+4] & 0x0F)*17;
}