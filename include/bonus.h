#ifndef BONUS_H
#define BONUS_H

#include "box.h"

/* BONUS : once hit by the shooter, gives advantage to it */
typedef struct bonus{
	GLuint textID;		// texture of the bonus
	BoundingBox box;	// delineate the object
	int collision;		// tells if the bonus have been hit
	char type;	// h : the shooter gains health points
				// s : the shooter gains a shield
				// a : the shooter's bullets gain speed
	int points; // how consequent is the gain
	struct bonus* next;
} Bonus, *BonusList;

/* -----INITIALIZATION----- */
/* initializes bonus textures */
void initBonusText(GLuint text[]);
/* initializes a bonus object */
Bonus* allocBonus(GLuint text, float posX, float posY, char type);
/* adds a bonus object to a bonus list */
void addBonusToList(Bonus* bonus, BonusList* list);

/* -----DISPLAY----- */
/* draws a bonus */
void drawBonus(BonusList list);

/* -----ACTION----- */
/* makes a bonus scroll */
void scrollBonus(BonusList list, float speed);

/* -----DELETION----- */
/* deletes bonus off limits or collided */
void deleteBonus(BonusList* list, BonusList prev);
/* deletes all bonus in the list */
void deleteAllBonus(BonusList* list);

#endif