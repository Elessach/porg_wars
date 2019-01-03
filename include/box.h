#ifndef BOX_H
#define BOX_H

#include "graphics.h"

/* BOUNDING BOX : delineates an object and defines its position */
typedef struct boundingbox {
	float minX, minY;
	float maxX, maxY;
} BoundingBox;

/* -----INITIALIZATION----- */
/* initializes a bounding box object */
void initBoundingBox(BoundingBox* bb, float posX, float posY, char type);

/* -----DISPLAY----- */
/* (debug) draws a bounding box */
void drawBoundingBox(BoundingBox box);

#endif