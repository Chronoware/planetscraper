#ifndef COLORS__H
#define COLORS__H

#define COLOR_RED       0xF00
#define COLOR_GREEN     0x0F0
#define COLOR_BLUE      0x00F
#define COLOR_YELLOW    0xFF0
#define COLOR_MAGENTA   0xF0F
#define COLOR_CYAN      0x0FF
#define COLOR_BLACK     0x000
#define COLOR_DARK_GRAY 0x444
#define COLOR_GRAY      0x888
#define COLOR_WHITE     0xFFF

uint8_t fgRed(uint8_t* src, uint32_t pos);                  //Foreground color from screen
uint8_t fgGreen(uint8_t* src, uint32_t pos);
uint8_t fgBlue(uint8_t* src, uint32_t pos);

uint8_t bgRed(uint8_t* src, uint32_t pos);                  //Background color from screen
uint8_t bgGreen(uint8_t* src, uint32_t pos);
uint8_t bgBlue(uint8_t* src, uint32_t pos);

uint8_t rgbSet(uint8_t red, uint8_t green, uint8_t blue);   //RGB operations
//uint8_t rgbMix(uint8_t* colorA, uint8_t colorB);
//uint8_t rgbAdd(uint8_t* colorA, uint8_t colorB);

#endif