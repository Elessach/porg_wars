#ifndef GAME_H
#define GAME_H

#include "collision.h"

/* -----INITIALIZATION----- */
void initGameOverScreenText(GLuint text[]);
void initLoadingText(GLuint text[]);
void initScoreText(GLuint text[]);
void initStartScreenText(GLuint text[]);
void initSucceedScreenText(GLuint text[]);
void initVictoryScreenText(GLuint text[]);

/* -----GAME INFOS-----*/
/* decomposes score */
void tabScore(int (*tab)[5], int score);
/* draws score */
void drawScore(GLuint text[], int score[], int end);
/* draws health points' shooter */
void drawLife(int hp, GLuint heart);
/* draws infos */
void drawInfos();

/* -----SCREENS----- */
/* draws a screen with buttons */
void drawScreenAndButtons(GLuint text[], int activeButton);
/* draws a screen */
void drawScreen(GLuint text);

#endif