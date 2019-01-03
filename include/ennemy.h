#ifndef ENNEMY_H
#define ENNEMY_H

#include "bullet.h"

/* ENNEMY : hurts the shooter and throws bullets */
typedef struct ennemy{
	GLuint textID;		// texture
	BoundingBox box;	// bounding box & position
	int hp;				// health points
	BulletList bullets;	// bullets
	int up;				// tells if the ennemy moves up or down
	float speed;		// speed on ordinate axis
	char type;	// m : moving ennemies shooting horizontal bullets
				// t : towers not moving shooting vertical bullets
				// B : boss
	struct ennemy* next;
} Ennemy, *EnnemyList;

/* -----INITIALIZATION----- */
/* initializes ennemies textures */
void initEnnemyText(GLuint text[]);
/* initializes ennemy object */
Ennemy* allocEnnemy(GLuint, float posX, char type);
/* adds an ennmy to a list */
void addEnnemyToList(Ennemy* ennemy, EnnemyList* list);

/* -----DISPLAY----- */
/* draws ennemies */
void drawEnnemies(EnnemyList list);

/* -----ACTION----- */
/* makes ennemies scroll */
void scrollEnnemies(EnnemyList list, float speedX, int size);

/* -----DELETION----- */
/* deletes ennemies off limits and collided */
void deleteEnnemies(EnnemyList* list, EnnemyList prev);
/* deletes all ennemies of a list and their bullets */
void deleteAllEnnemies(EnnemyList* list);

/* -----BULLETS-----*/
/* adds bullets to the ennemies' bullets list */
void addBulletsToEnnemies(EnnemyList* ennemies, GLuint text[]);
/* draws ennemies' bullets */
void drawEnnemiesBullets(EnnemyList ennemies);
/* maes the bullets' ennemies scroll */
void scrollEnnemiesBullets(EnnemyList ennemies);
/* deletes ennemies bullets */
void deleteEnnemiesBullets(EnnemyList* ennemies);

#endif