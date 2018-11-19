#include <stdint.h>
#include "colors.h"

// color = ????rrrr.ggggbbbb; 2 bytes, 4-bit colors, first 4 bits reserved

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

uint8_t rgbSet(uint8_t red, uint8_t green, uint8_t blue){
    return ((red >> 4) << 8) | ((green >> 4) << 4) | (blue >> 4);
}