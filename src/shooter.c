#include "shooter.h"

/* initializes textures */
void initShooterText(GLuint text[]){
	SDL_Surface* img[SHOOTER_IMG_NB];
	initShooterImg(img);
	initTextArray(img, text, SHOOTER_IMG_NB, 1);
	deleteImg(img, SHOOTER_IMG_NB);
}
/* initializes shooter */
void initShooter(Shooter* shooter, GLuint text, GLuint shield)
{
	shooter->speed = SHOOTER_SPEED;
	shooter->hp = SHOOTER_HP;
	shooter->shield = 0;
	shooter->up = -1;
	shooter->collision = 0;
	shooter->bullets = NULL;
	initBoundingBox(&shooter->box, 2, HEIGHT/2, 's');
	shooter->textID = text;
	shooter->shieldTextID = shield;
}

/* movement on ordinate axis */
void moveDown(BoundingBox* box, float speed){
	if(box->minY - speed >= 0){
        box->minY -= speed;
        box->maxY = box->minY + 1.5;
	}
}
void moveUp(BoundingBox* box, float speed, int size){
	if(box->maxY + speed <= size){
        box->minY += speed;
        box->maxY = box->minY + 1.5;
	}
}

/* draws shooter */
void drawShooter(Shooter shooter){
	GLuint text;
	if(shooter.shield >= 1) text = shooter.shieldTextID;
	else text = shooter.textID;

	float angle;
	if(shooter.up == 1) angle = 10;
	else if(shooter.up == 0) angle = -10;
	else angle = 0;

    if(shooter.collision >= 1) glColor3ub(255, 0, 0);
	glPushMatrix();
		imgSettings((shooter.box).minX, (shooter.box).minY, 1.5, 1.5, angle);
       	draw(text);
	    glColor3ub(255, 255, 255);
    glPopMatrix();
    //drawBoundingBox(shooter.box);
}

/* deletes shooter */
void deleteShooter(Shooter* shooter){
	deleteAllBullets(&shooter->bullets);
	glDeleteTextures(1, &shooter->textID);
	glDeleteTextures(1, &shooter->shieldTextID);
}