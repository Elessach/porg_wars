#include "wall.h"

/* initializes wall textures */
void initWallText(GLuint text[]){
	SDL_Surface* img[WALL_IMG_NB];
	initWallImg(img);
	initTextArray(img, text, WALL_IMG_NB, 1);
	deleteImg(img, WALL_IMG_NB);
}
/* initializes wall object */
Wall* allocWall(GLuint text[], float posX, float posY){
	Wall* wall = (Wall*)malloc(sizeof(Wall));
	if(wall == NULL){
		printf("ERROR ALLOC WALL\n");
		return NULL;
	}
	wall->collision = 0;
	wall->next = NULL;
	initBoundingBox(&wall->box, posX, posY, 'w');
	/* defines texture randomly */
	int i = rand()%3;
	wall->textID = text[i];
	return wall;
}
/* add wall to list */
void addWallToList(Wall* wall, WallList* list){
	if(*list == NULL) *list = wall;
	else addWallToList(wall, &(*list)->next);
}
/* draw walls */
void drawWalls(WallList list){
	while(list != NULL){
		if((list->box).minX < WIDTH){
			glPushMatrix();
				imgSettings((list->box).minX, (list->box).minY, 1, 1, 0);
				draw(list->textID);
			glPopMatrix();
		}
		//drawBoundingBox(list->box);
		list = list->next;
	}
}
/* make obstacles scroll */
void scrollWalls(WallList list, float speed){
	while(list != NULL){
		(list->box).minX -= speed;
		(list->box).maxX -= speed;
		list=list->next;
	}
}

/* delete walls */
void deleteWalls(WallList* list, WallList prev){
	if( *list != NULL ){
		WallList tmp = *list;
		if((tmp->box).maxX <= 0 || tmp->collision == 1 ){
			if(prev == NULL){
				*list = tmp->next;
				free(tmp); 
				deleteWalls(list, NULL);
			}
			else{
				prev->next = tmp->next;
				free(tmp);
				tmp = NULL;
				deleteWalls(&prev->next, prev);
			}
		}
		else{
			prev = tmp;
			deleteWalls(&tmp->next, prev);	
		}	
	}
}
/* delete all walls from list */
void deleteAllWalls(WallList* list){
	if(*list != NULL){
		deleteAllWalls(&(*list)->next);
		free(*list);
		*list = NULL;
	}
}