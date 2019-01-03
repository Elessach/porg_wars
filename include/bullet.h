#ifndef BULLET_H
#define BULLET_H

#include "box.h"

/* BULLET : objects able to destroy objects */
typedef struct bullet{
	GLuint textID;		// texture
	float speed;		// speed it's thrown
	BoundingBox box;	// delineates and defines position 
	int collision;		// tells if it's been hit
	char type; 	// h : horizontal from right to left
				// v : vertical from top to bottom
				// V : vertical from bottom to to
				// H : horizontal from left to right
				// M : multiple bullets for the boss
	struct bullet* next;
} Bullet, *BulletList;

/* -----INITIALIZATION----- */
/* initializes bullets textures */
void initBulletText(GLuint text[]);
/* initializes a bullet object */
Bullet* allocBullet(GLuint text, float posX, float posY, char type);
/* adds a bullet to a list */
void addBulletToList(Bullet* bullet, BulletList* list);

/* -----DISPLAY----- */
/* draw bullets */
void drawBullets(BulletList list);

/* -----ACTION-----*/
/* makes bullets scroll */
void scrollBullets(BulletList list);

/* -----DELETION----- */
/* deletes bullets off limits and collided */
void deleteBullets(BulletList* list, BulletList prev, int size);
/* deletes all bullets from a list */
void deleteAllBullets(BulletList* list);

#endif