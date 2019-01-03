#include "bullet.h"

/* initializes the bullets textures */
void initBulletText(GLuint text[]){
	SDL_Surface* img[BULLET_IMG_NB];
	initBulletImg(img);
	initTextArray(img, text, BULLET_IMG_NB, 1);
	deleteImg(img, BULLET_IMG_NB);
}

/* initializes a bullet object */
Bullet* allocBullet(GLuint text, float posX, float posY, char type){
	/* allocates memory */
	Bullet* bullet = (Bullet*)malloc(sizeof(Bullet));
	if(bullet==NULL){
		fprintf(stderr, "Error alloc bullet");
		return NULL;
	}
	/* attributes */
	bullet->next = NULL;
	bullet->collision = 0;
	bullet->type = type;
	bullet->textID = text;
	initBoundingBox(&bullet->box, posX, posY, type);
	/* depending on type */
	if(type == 'M') bullet->speed =BULLET_BOSS_SPEED;
	else bullet->speed = BULLET_SPEED;
	return bullet;
}

/* adds a bullet to a list */
void addBulletToList(Bullet* bullet, BulletList* list){
	if(*list == NULL) *list = bullet;
	else addBulletToList(bullet, &(*list)->next);
}

/* draws bullets */
void drawBullets(BulletList list){
	while(list != NULL){
		glPushMatrix();
			if(list->type == 'v' || list->type == 'V')
				imgSettings((list->box).minX + 0.25, (list->box).minY, 1, 0.25, 90);
			else if(list->type == 'M')
				imgSettings((list->box).minX, (list->box).minY, 1, 0.5, 0);
			else
				imgSettings((list->box).minX, (list->box).minY, 1, 0.25, 0);
			draw(list->textID);
		glPopMatrix();
		//drawBoundingBox(list->box);
		list=list->next;
	}
}

/* makes bullets scroll depending on type */
void scrollBullets(BulletList list){
	/* scrolling different as not in same direction */
	while(list != NULL){
		switch(list->type){
			/* horizontal from left to right */
			case 'H':
				(list->box).minX += list->speed;
				(list->box).maxX += list->speed;
				break;
			/* horizontal from right to left */
		 	case 'h':
		 	case 'M':
				(list->box).minX -= list->speed;
				(list->box).maxX -= list->speed;
				break;
			/* vertical from top to bottom */
			case 'v':
				(list->box).minX -= OBJ_SPEED;
				(list->box).maxX -= OBJ_SPEED;
				(list->box).minY -= list->speed;
				(list->box).maxY -= list->speed;	
				break;
			/* vertical from bottom to top */
			case 'V':
				(list->box).minX -= OBJ_SPEED;
				(list->box).maxX -= OBJ_SPEED;
				(list->box).minY += list->speed;
				(list->box).maxY += list->speed;
				break;
			default:
				break;
		}
		list = list->next;
	}
}

/* deletes bullets off limits or collided  */
void deleteBullets(BulletList* list, BulletList prev, int size){
	if( *list != NULL ){
		BulletList tmp = *list;
		if( (tmp->box).maxX >= (float)size || tmp->collision == 1 ){
			if(prev == NULL){
				*list = tmp->next;
				free(tmp); 
				deleteBullets(list, NULL, size);
			}
			else{
				prev->next = tmp->next;
				free(tmp);
				tmp = NULL;
				deleteBullets(&prev->next, prev, size);
			}
		}
		else{
			prev = tmp;
			deleteBullets(&tmp->next, prev, size);	
		}	
	}
}

/* deletes all bullets from a list */
void deleteAllBullets(BulletList* list){
	if(*list != NULL){
		deleteAllBullets(&(*list)->next);
		free(*list);
		*list=NULL;
	}
}