//
//  BitMap.h
//  BitMap
//
//  Created by Joost Markerink on 29-10-17.
//  Copyright © 2017 Joost Markerink. All rights reserved.
//

#ifndef BitMap_h
#define BitMap_h


typedef unsigned int pixelcolor;

typedef struct{
    unsigned short width,height;
    pixelcolor *pixels;
}pixels;



typedef struct{
    pixels framebuffer;
    unsigned short map_x,map_y;
    pixels *map;
}pixelsdisplay;

pixels *    pixels_create           (unsigned short width,unsigned short height);

void        pixels_free             (       pixels *);
void        pixels_clear            (       pixels *,pixelcolor);
void        pixels_getRowpixels     (const  pixels *,unsigned short x,unsigned short y,unsigned short numOfpixels,        pixelcolor *);
void        pixels_setRowpixels     (       pixels *,unsigned short x,unsigned short y,unsigned short numOfpixels,const   pixelcolor *);
void        pixels_fillRectangle    (       pixels *,unsigned short x,unsigned short y,unsigned short width,unsigned short height,pixelcolor);




pixelsdisplay * pixelsdisplay_create            (unsigned short width,unsigned short height);

void            pixelsdisplay_free              (pixelsdisplay *);
void            pixelsdisplay_setMap            (pixelsdisplay *,pixels *);
void            pixelsdisplay_scrollVertical    (pixelsdisplay *,int deltay);
void            pixelsdisplay_scrollHorizontal  (pixelsdisplay *,int deltax);
void            pixelsdisplay_render            (pixelsdisplay *);


#endif /* BitMap_h */
