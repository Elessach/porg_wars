#ifndef SETTINGS_H
#define SETTINGS_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* GRILLE */
#define HEIGHT 21
#define WIDTH 20

/* ECRANS */
#define LOADING_IMG_NB 1
#define SCREEN_IMG_NB 2

/* NIVEAUX */
#define LEVEL_NB 5

/* VITESSES DE DEFILEMENT*/
#define SCROLL_SPEED 0.2
#define OBJ_SPEED 0.15

/* PROJECTILES */
#define BULLETS_PERIOD 50
#define BULLET_HEIGHT 0.25
#define BULLET_IMG_NB 3
#define BULLET_SPEED 0.7 
#define BULLET_BOSS_SPEED 0.3

/* INFOS */
#define HEART_SIZE 0.5

/* SHOOTER */
#define SHOOTER_HP 15
#define SHOOTER_SPEED 0.2
#define SHOOTER_SIZE 1.5
#define SHOOTER_IMG_NB 2

/* ENNEMIES */
#define ENNEMY_HP 1
#define ENNEMY_SPEED 0.1
#define ENNEMY_SIZE 1.5
#define ENNEMY_IMG_NB 3

/* BOSS */
#define BOSS_HP 10
#define BOSS_SIZE 10
#define BOSS_BULLETS_HEIGHT 0.5

/* BONUS */
#define BONUS_SIZE 1
#define BONUS_IMG_NB 3
#define HEART_PTS 5
#define SHIELD_PTS 5
#define ATK_PTS 1

/* OBSTACLES */
#define WALL_SIZE 1
#define WALL_IMG_NB 4

/* STORY */
#define FIRST_LVL_IMG_NB 3
#define OTHER_LVL_IMG_NB 4

#endif