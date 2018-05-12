//Gfx converted using Mollusk's PAGfx Converter

//This file contains all the .h, for easier inclusion in a project

#ifndef ALL_GFX_H
#define ALL_GFX_H

#ifndef PAGfx_struct
    typedef struct{
    void *Map;
    int MapSize;
    void *Tiles;
    int TileSize;
    void *Palette;
    int *Info;
} PAGfx_struct;
#endif


// Sprite files : 
extern const unsigned char buttons_Sprite[2048] __attribute__ ((aligned (4))) ;  // Pal : buttons_Pal
extern const unsigned char bigbutton_Sprite[8192] __attribute__ ((aligned (4))) ;  // Pal : bigbutton_Pal

// Background files : 
extern const unsigned char mandala_Bitmap[49152] __attribute__ ((aligned (4))) ;  // Pal : mandala_Pal

extern const unsigned char lotus_Bitmap[49152] __attribute__ ((aligned (4))) ;  // Pal : lotus_Pal


// Palette files : 
extern const unsigned short buttons_Pal[101] __attribute__ ((aligned (4))) ;
extern const unsigned short bigbutton_Pal[143] __attribute__ ((aligned (4))) ;
extern const unsigned short mandala_Pal[233] __attribute__ ((aligned (4))) ;
extern const unsigned short lotus_Pal[178] __attribute__ ((aligned (4))) ;


#endif

