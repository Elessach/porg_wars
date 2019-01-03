#ifndef LEVEL_H
#define LEVEL_H

#include "background.h"
#include "bonus.h"
#include "ennemy.h"
#include "wall.h"

/* LEVEL : niveau du jeu */
typedef struct level{
	WallList walls;			// obstacles
	EnnemyList ennemies;	// ennemies
	BonusList bonus;		// bonus
	float endPos;			// defines end of level position
	float bossPos;			// position of the eventual boss
	Background bg1, bg2;	// background
} Level;

/* -----INITIALIZATION----- */
/* initializes the level */
void initLevel(Level* level, Background bg1, Background bg2);
/* builds the level with the infos of the .ppm file */
int buildLevel(char* filename, Level* level, GLuint wallText[], GLuint ennemyText[], GLuint bonusText[]);

/* -----DELETION----- */
/* deletes level and its elements */
void deleteLevel(Level* level);

#endif