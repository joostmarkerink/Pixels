//
//  pixels.h
//  pixels
/*
 MIT License
 
 Copyright (c) 2017 Joost Markerink
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#ifndef PIXELS_h
#define PIXELS_h


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
