//
//  BitMap.c
//  BitMap
//
//  Created by Joost Markerink on 29-10-17.
//  Copyright © 2017 Joost Markerink. All rights reserved.
//

#include "pixels.h"
#include <stdlib.h>
#include <string.h>




void pixelcolor_getRGBA(pixelcolor c,unsigned char *RGBA){
    int bitPerSample=(sizeof(pixelcolor)*8)/4;
    int i,num=0;
    for(i=0;i<bitPerSample;i++){
        num<<=1;
        num|=1;
    }
    
    RGBA[0]=(c)&num;
    RGBA[1]=(c>>bitPerSample)&num;
    RGBA[2]=(c>>(bitPerSample*2))&num;
    RGBA[3]=(c>>(bitPerSample*3))&num;
}

void pixels_clear(pixels *p,pixelcolor clearColor){
    unsigned char RGBA[4];
    pixelcolor_getRGBA(clearColor,RGBA);
    int linesize=sizeof(pixelcolor)*p->width;
    
    if(RGBA[0]==RGBA[1] && RGBA[0]==RGBA[2] && RGBA[0]==RGBA[3]){
        memset(p->pixels,RGBA[0],p->width*p->height*sizeof(pixelcolor));
    }else{
        int i;
        for(i=0;i<p->width;i++) memcpy(&p->pixels[i],RGBA,sizeof(RGBA));
        for(i=1;i<p->height;i++) memcpy(&p->pixels[i*p->width],&p->pixels[0],linesize);
    }
}
pixels *pixels_create(unsigned short width,unsigned short height){
    pixels *p=malloc(sizeof(pixels));
    p->width=width;
    p->height=height;
    p->pixels=malloc(width*height*sizeof(pixelcolor));
    return p;
}

void pixels_free(pixels *p){
    free(p->pixels);
    free(p);
}

void pixels_getRowpixels(const pixels *pix,unsigned short x,unsigned short y,unsigned short pixels,pixelcolor *result){
    memcpy(result,&pix->pixels[(y*pix->width)+x],pixels*sizeof(pixelcolor));
}

void pixels_setRowpixels(pixels *target,unsigned short x,unsigned short y,unsigned short len,const pixelcolor *pixels){
    memcpy(&target->pixels[ (y*target->width)+x], pixels, len*sizeof(pixelcolor));
}
void pixels_fillRowpixels(pixels *target,unsigned short x,unsigned short y,unsigned short width,pixelcolor color){
    int i;
    for(i=0;i<width;i++) target->pixels[(y*target->width)+x+i]=color;
}

void pixels_fillRectangle(pixels *target,unsigned short x,unsigned short y,unsigned short width,unsigned short height,pixelcolor color){
    int i;
    pixels_fillRowpixels(target,x,y,width,color);
    for(i=1;i<height;i++) pixels_setRowpixels(target, x, y+i, width, &target->pixels[(y*target->width)+x]);
}









pixelsdisplay *pixelsdisplay_create(unsigned short width,unsigned short height){
    pixelsdisplay *d=malloc(sizeof(pixelsdisplay));
    d->framebuffer.width=width;
    d->framebuffer.height=height;
    d->framebuffer.pixels=malloc(width*height*sizeof(pixelcolor));
    d->map=0;
    d->map_x=0;
    d->map_y=0;
    return d;
}

void pixelsdisplay_free(pixelsdisplay *d){
    free(d->framebuffer.pixels);
    if(d->map) free(d->map);
    free(d);
}

void pixelsdisplay_render(pixelsdisplay *display){
    if(!display->map) return;
    
    int i;
    for(i=0;i<display->framebuffer.height;i++)
        pixels_getRowpixels(display->map, display->map_x,display->map_y+i, display->framebuffer.width, &display->framebuffer.pixels[i*display->framebuffer.width]);
}

void pixelsdisplay_scrollHorizontal(pixelsdisplay *display,int num){
    int x=display->map_x;
    x+=num;
    if(x<0) x=0;
    else if((x+display->framebuffer.width)>=display->map->width)
        x=display->map->width-display->framebuffer.width;
    display->map_x=x;
}


void pixelsdisplay_scrollVertical(pixelsdisplay *display,int num){
    int y=display->map_y;
    y+=num;
    
    if(y<0) y=0;
    else if((y+display->framebuffer.height)>=display->map->height)
        y=display->map->height-display->framebuffer.height;
    
    display->map_y=y;
}



void pixelsdisplay_setMap(pixelsdisplay *display,pixels *map){
    display->map=map;
    display->map_x=0;
    display->map_y=0;
}

