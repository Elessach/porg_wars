#ifndef SHOOTER_H
#define SHOOTER_H

#include "bullet.h"

/* SHOOTER : player's character */
typedef struct shooter{
	GLuint textID, shieldTextID;// textures (normal and shielded)
	float speed;				// speed on ordinate axis
	BoundingBox box;			// bounding box & position
	int hp;						// health points
	int shield;					// tells if shooter is shielded
	int up;						// tells if the shooter is moving
	int collision;				// tells if the shooter's been hit
	BulletList bullets;			// bullets
} Shooter;

/* -----INITIALIZATION----- */
/* initializes textures */
void initShooterText(GLuint text[]);
/* initializes shooter object */
void initShooter(Shooter* shooter, GLuint text, GLuint shield);

/* -----ACTION----- */
/* makes shooter move down */
void moveDown(BoundingBox* box, float speed);
/* makes shooter move up */
void moveUp(BoundingBox* box, float speed, int size);

/* -----DISPLAY----- */
/* draws the shooter */
void drawShooter(Shooter shooter);

/* -----DELETION----- */
/* deletes shooter */
void deleteShooter(Shooter* shooter);

#endif