#ifndef BAGKGROUND_H
#define BACKGROUND_H

#include "graphics.h"

/* BACKGROUND : wallpaper for the game progress */
typedef struct bgimg{
	GLuint textID;		// texture of the background 
	float scrollSpeed;	// speed at which the background is scrolling
	float posX;			// position on abscissa axis
} Background;

/* -----INITIALIZATION----- */
/* initializes all the textures of background */
void initBgText(GLuint text[]);
/* initializes a background object */
void initBg(Background* bg, float pos, GLuint textID);

/* -----ACTION----- */
/* make a background scroll correctly */
void scrollBg(Background* bg);

/* ----- DISPLAY----- */
/* draws a background image considering the settings given */
void drawBg(Background bg);

#endif