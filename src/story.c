#include "story.h"

/* intiializes textures for story of beginning of the game */
void initFirstLevelStoryText(GLuint text[]){
	SDL_Surface* img[FIRST_LVL_IMG_NB];
    initFirstLevelStoryImg(img);
    initTextArray(img, text, FIRST_LVL_IMG_NB, 1);
    deleteImg(img, FIRST_LVL_IMG_NB);
}
/* draws story for start of game */
void drawFirstLevelStory(GLuint text[], int step){
	drawScreen(text[step]);
}

/* initializes textuures of storues between levels */
void initOtherLevelStoryText(GLuint text[]){
	SDL_Surface* img[OTHER_LVL_IMG_NB];
    initLevelStoriesImg(img);
    initTextArray(img, text, OTHER_LVL_IMG_NB, 1);
    deleteImg(img, OTHER_LVL_IMG_NB);
}