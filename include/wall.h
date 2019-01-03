#ifndef WALL_H
#define WALL_H

#include "box.h"

/* WALL : obstacles that can be destroyed */
typedef struct wall{
	GLuint textID;		// texture
	BoundingBox box;	// bounding box & position
	int collision;		// tells if it's hit
	struct wall* next;
} Wall, *WallList;

/* -----INITIALIZATION----- */
/* initializes textures */
void initWallText(GLuint text[]);
/* initializes wall */
Wall* allocWall(GLuint text[], float posX, float posY);
/* adds obstacle to list */
void addWallToList(Wall* wall, WallList* list);

/* -----DISPLAY----- */
/* draws obstacles */
void drawWalls(WallList list);

/* -----MOUVEMENT----- */
/* make obstacles scroll */
void scrollWalls(WallList list, float speed);

/* -----DELETION----- */
/* deletes walls off limits and hit */
void deleteWalls(WallList* list, WallList prev);
/* delete all walls from list */
void deleteAllWalls(WallList* list);

#endif