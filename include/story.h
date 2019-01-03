#ifndef STORY_H
#define STORY_H

#include "game.h"

/* initializes textures for the start of the game */
void initFirstLevelStoryText(GLuint text[]);
/* draws textures for beginning of game */
void drawFirstLevelStory(GLuint text[], int time);

/* initializes textures for story between the levels */
void initOtherLevelStoryText(GLuint text[]);

#endif