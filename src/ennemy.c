#include "ennemy.h"

/* initialise les images des projectiles */
void initEnnemyText(GLuint text[]){
	SDL_Surface* img[ENNEMY_IMG_NB];
	initEnnemyImg(img);
	initTextArray(img, text, ENNEMY_IMG_NB, 1);
	deleteImg(img, ENNEMY_IMG_NB);
}
/* aloue de la mémoire pour un ennemi et l'initialise */
Ennemy* allocEnnemy(GLuint text, float posX, char type){
	/* allocation mémoire */
	Ennemy* ennemy = (Ennemy*)malloc(sizeof(Ennemy));
	if(ennemy == NULL){
		printf("ERROR ALLOC ENNEMY\n");
		return NULL;
	}
	/* attributs */
	ennemy->speed = ENNEMY_SPEED;
	ennemy->type = type;
	ennemy->bullets = NULL;
	ennemy->textID = text;
	ennemy->next = NULL;

	/* hauteur aléaoire */
	float posY = 0;
	switch(type){
		case 'm':
			posY = rand()%HEIGHT;
			break;
		case 't':
			posY = 0;
			break;
		case 'T':
			posY = HEIGHT - 2;
			break;
		case 'B':
			break;
		default:
			break;
	}
	initBoundingBox(&ennemy->box, posX, posY, type);

	if(type == 'B') ennemy->hp = BOSS_HP;
	else ennemy->hp = ENNEMY_HP;

	if(type == 'm') ennemy->up = 1;
	else ennemy->up = -1;

	return ennemy;
}

/* ajoute un annemi à la liste */
void addEnnemyToList(Ennemy* ennemy, EnnemyList* list){
	if(*list == NULL) *list = ennemy;
	else addEnnemyToList(ennemy, &(*list)->next);
}

/* affiche les ennemis */
void drawEnnemies(EnnemyList list){
	while(list != NULL){
		glPushMatrix();
			if(list->type == 'T')
				imgSettings((list->box).minX + 1.5, (list->box).minY + 1, 1.5, 1.5, 180);
			else if(list->type == 'B')
				imgSettings((list->box).minX, (list->box).minY, 10, 10, 0);
			else
				imgSettings((list->box).minX, (list->box).minY, 1.5, 1.5, 0);
			draw(list->textID);
		glPopMatrix();
		//drawBoundingBox(list->box);
		list=list->next;
	}
}

/* permet de faire défiler les ennemis sur axe Y */
void scrollEnnemies(EnnemyList list, float speedX, int size){
	while(list != NULL){
		/* déplacement axe X */
		(list->box).minX -= speedX;
		(list->box).maxX -= speedX;
		/* déplacement axe Y */
		if(list->up == 1){
			(list->box).minY += list->speed;
			(list->box).maxY += list->speed;
			if((list->box).maxY >= size)
				list->up = 0;
		}
		else if(list->up == 0){
			(list->box).minY -= list->speed;
			(list->box).maxY -= list->speed;	
			if((list->box).minY <= 0)
				list->up = 1;
		}
		list = list->next;
	}
}

/* permet de supprimes les ennemis */
void deleteEnnemies(EnnemyList* list, EnnemyList prev){
	if( *list != NULL ){
		EnnemyList tmp = *list;
		/* on supprime quand il y a eu collision */
		/* on supprime quand l'obstacle n'est plus affiché */
		if( (tmp->box).maxX <= 0 || tmp->hp == 0 ){
			/* cas où tête de liste */
			if(prev == NULL){
				*list = tmp->next;
				free(tmp); 
				deleteEnnemies(list, NULL);
			}
			else{
				prev->next = tmp->next;
				free(tmp);
				tmp = NULL;
				deleteEnnemies(&prev->next, prev);
			}
		}
		else{
			prev = tmp;
			deleteEnnemies(&tmp->next, prev);	
		}	
	}
}

/* permet de supprimer tous les enenmis */
void deleteAllEnnemies(EnnemyList* list){
	if(*list != NULL){
		deleteAllEnnemies(&(*list)->next);
		deleteAllBullets(&(*list)->bullets);
	}
}

/* ajoute un projectile a chaque liste de projectiles des ennemies */
void addBulletsToEnnemies(EnnemyList* ennemies, GLuint text[]){
	EnnemyList tmp = *ennemies;
	while(tmp != NULL){
		if((tmp->box).minX <= WIDTH){
			switch(tmp->type){
				case 'm':
		 			addBulletToList(allocBullet(text[1], (tmp->box).minX, (tmp->box).minY, 'h'), &tmp->bullets);
		 			break;
		 		case 't':
		 			addBulletToList(allocBullet(text[2], (tmp->box).minX, (tmp->box).minY, 'V'), &tmp->bullets);
		 			break;
		 		case 'T':
	 				addBulletToList(allocBullet(text[2], (tmp->box).minX, (tmp->box).minY, 'v'), &tmp->bullets);
	 				break;
	 			case 'B':;
	 				int y1 = rand()%(15-5) + 5, y2 = rand()%(15-5) + 5;
	 				addBulletToList(allocBullet(text[1], (tmp->box).minX, y1, 'M'), &tmp->bullets);
	 				addBulletToList(allocBullet(text[1], (tmp->box).minX, y2, 'M'), &tmp->bullets);
	 			default:
	 				break;
	 		}
		}
		tmp = tmp -> next;
	}
}

void drawEnnemiesBullets(EnnemyList ennemies){
	while(ennemies != NULL){
		drawBullets(ennemies->bullets);		
		ennemies = ennemies->next;
	}
}

/* fait défiler les projectiles ennemies */
void scrollEnnemiesBullets(EnnemyList ennemies){
	while(ennemies != NULL){
		scrollBullets(ennemies->bullets);
		ennemies = ennemies->next;
	}
}

/* supprime les projectiles des ennemies */
void deleteEnnemiesBullets(EnnemyList* ennemies){
	EnnemyList tmp = *ennemies;
	while(tmp != NULL){
		deleteBullets(&tmp->bullets, NULL, WIDTH);
		tmp = tmp->next;
	}
}