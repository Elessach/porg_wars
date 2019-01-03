 #include "bonus.h"

/* initializes bonus textures */
void initBonusText(GLuint text[]){
	SDL_Surface* img[BONUS_IMG_NB];
	initBonusImg(img);
	initTextArray(img, text, BONUS_IMG_NB, 1);
	deleteImg(img, BONUS_IMG_NB);
}

/* initializes a bonus object */
Bonus* allocBonus(GLuint text, float posX, float posY, char type){
	/* allocates memory for the object */
	Bonus* bonus = (Bonus*)malloc(sizeof(Bonus));
	if(bonus == NULL){
		fprintf(stderr, "ERROR ALLOC BONUS");
		return NULL;
	}
	/* attributes */
	bonus->textID = text;
	bonus->type = type;
	bonus->collision = 0;
	bonus->next = NULL;
	initBoundingBox(&bonus->box, posX, posY, 'b');
	/* set attribute depending on the bonus type */
	switch(type){
		case 's':
			bonus->points = SHIELD_PTS;
			break;
		case 'h':
			bonus->points = HEART_PTS;
			break;
		case 'a':
			bonus->points = ATK_PTS;
			break;
		default:
			break;
	}
	return bonus;
}

/* adds a bonus to a list */
void addBonusToList(Bonus* bonus, BonusList* list){
	if(*list == NULL) *list = bonus;
	else addBonusToList(bonus, &(*list)->next);	
}

/* draws a bonus object */
void drawBonus(BonusList list){
	while(list != NULL){
		glPushMatrix();
			imgSettings((list->box).minX, (list->box).minY, 1, 1, 0);
			draw(list->textID);
		glPopMatrix();
		//drawBoundingBox(list->box);
		list=list->next;
	}
}

/* make a bonus object scroll */
void scrollBonus(BonusList list, float speed){
	while(list != NULL){
		(list->box).minX -= speed;
		(list->box).maxX -= speed;
		list = list->next;
	}
}

/* deletes a bonus object when it's off limits or collided */
void deleteBonus(BonusList* list, BonusList prev){
	if( *list != NULL ){
		BonusList tmp = *list;
		if( (tmp->box).maxX <= 0 || tmp->collision == 1 ){
			if(prev == NULL){
				*list = tmp->next;
				free(tmp); 
				deleteBonus(list, NULL);
			}
			else{
				prev->next = tmp->next;
				free(tmp);
				tmp = NULL;
				deleteBonus(&prev->next, prev);
			}
		}
		else{
			prev = tmp;
			deleteBonus(&tmp->next, prev);	
		}	
	}
}

/* delete all bonus of a list */
void deleteAllBonus(BonusList* list){
	if(*list != NULL){
		deleteAllBonus(&(*list)->next);
		free(*list);
		*list = NULL;
	}
}