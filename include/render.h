#ifndef RENDER__H
#define RENDER__H

#define SCREEN_W 64
#define SCREEN_H 32

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* tileset;

extern uint8_t tileW, tileH, zoom;

// [ tile0, fg0a, fg0b, bg0a, bg0b, tile1... ]
// tile(x, y) = screen[(y*SCREEN_W + x)*5]
// color = ????rrrr.ggggbbbb;
extern uint8_t screen[SCREEN_W * SCREEN_H * 5];

bool init();
void clearScreen();
void addTile(uint16_t x, uint16_t y, char  c, uint16_t fg, uint16_t bg);
void   write(uint16_t x, uint16_t y, char* s, uint16_t fg, uint16_t bg);
void  lwrite(uint16_t x, uint16_t y, char* s, uint16_t fg, uint16_t bg);
void  cwrite(uint16_t x, uint16_t y, char* s, uint16_t fg, uint16_t bg);
void drawBox(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t l, uint16_t fg, uint16_t bg);
void (*redraw)();
bool deinit();

#endif