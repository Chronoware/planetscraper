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

uint16_t rgb(uint8_t red, uint8_t green, uint8_t blue){
    return ((red >> 4) << 8) | ((green >> 4) << 4) | (blue >> 4);
}

uint16_t rgbMix(uint16_t colorA, uint16_t colorB){
    uint8_t redA = (colorA >> 8)*17,
            greenA = ((colorA >> 4) & 0xF)*17,
            blueA = (colorA & 0xF)*17,
            redB = (colorB >> 8)*17,
            greenB = ((colorB >> 4) & 0xF)*17,
            blueB = (colorB & 0xF)*17;
    return rgb((redA+redB)/2, (greenA+greenB)/2, (blueA+blueB)/2);
}

uint16_t rgbBlend(uint16_t colorA, uint16_t colorB, double opacity){
    uint8_t redA = (colorA >> 8)*17,
            greenA = ((colorA >> 4) & 0xF)*17,
            blueA = (colorA & 0xF)*17,
            redB = (colorB >> 8)*17,
            greenB = ((colorB >> 4) & 0xF)*17,
            blueB = (colorB & 0xF)*17;
    if(opacity < 0) opacity = 0;
    if(opacity > 1) opacity = 1;
    return rgb((redA*(1-opacity)+redB*opacity)/2, (greenA*(1-opacity)+greenB*opacity)/2, (blueA*(1-opacity)+blueB*opacity)/2);
}

uint16_t rgbAdd(uint16_t colorA, uint16_t colorB){
    uint8_t redA = (colorA >> 8)*17,
            greenA = ((colorA >> 4) & 0xF)*17,
            blueA = (colorA & 0xF)*17,
            redB = (colorA >> 8)*17,
            greenB = ((colorA >> 4) & 0xF)*17,
            blueB = (colorA & 0xF)*17,
            redC = redA + redB,
            greenC = greenA + greenB,
            blueC = blueA + blueB;

    if(redC < redA || redC < redB) redC = 255;
    if(greenC < greenA || greenC < greenB) greenC = 255;
    if(blueC < blueA || blueC < blueB) blueC = 255;

    return rgb(redC, greenC, blueC);
}