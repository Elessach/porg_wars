#include "box.h"

/* draws an object's bounding box */
void drawBoundingBox(BoundingBox box){
	/* permet d'avoir une forme sans remplissage */
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
		glVertex2f(box.minX, box.maxY);
		glVertex2f(box.maxX, box.maxY);
		glVertex2f(box.maxX, box.minY);
		glVertex2f(box.minX, box.minY);
	glEnd();
	/* rétablit le remplissage */
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

/* depending on the object, its position, defines the bounding box correctly */
void initBoundingBox(BoundingBox* bb, float posX, float posY, char type)
{
	/* default width of a bounding box is 1 */
	bb->minX = posX;	
	bb->maxX = posX+1;

	switch(type){
		/* for the vertical bullets */
		case 'v':
		case 'V':
			bb->minX += 0.5 - BULLET_HEIGHT / 2;
			bb->maxX -= 0.5 - BULLET_HEIGHT / 2;
		/* for bonus */
		case 'b':
			bb->minY = posY;
			bb->maxY = posY + BONUS_SIZE;	
			break;
		/* for the obstacles */
		case 'w':
			bb->minY = posY;
			bb->maxY = posY + WALL_SIZE;
			break;
		/* for the shooter */
		case 's':
			bb->maxX += SHOOTER_SIZE - 1;
			bb->minY = posY;
			bb->maxY = posY + SHOOTER_SIZE;			
			break;
		/* for the ennemies */
		case 'm':
		case 't':
		case 'T':
			bb->maxX += ENNEMY_SIZE - 1;
			bb->minY = posY;
			bb->maxY = posY + ENNEMY_SIZE;
			break;
		/* for the boss */
		case 'B':
			bb->maxX += 10;
			bb->minY = (HEIGHT - BOSS_SIZE - 1) / 2;
			bb->maxY = HEIGHT - bb->minY;
			break;
		/* for the horizontal bullets */
		case 'H':
		case 'h':
			bb->maxY = posY + 1 - BULLET_HEIGHT / 2;
			bb->minY = bb->maxY - BULLET_HEIGHT;
			break;
		/* for the boss bullets */
		case 'M':
			bb->minY = posY;
			bb->maxY = bb->minY + BOSS_BULLETS_HEIGHT;
			break;
		default:
			break;
	}
}
