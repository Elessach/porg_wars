#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "settings.h"

/* -----LINKS IMAGES AND TEXTURES----- */
/* RGBA settings */
void imgToTextRGBA(GLuint text, SDL_Surface* img);
/* RGB settings */
void imgToTextRGB(GLuint text, SDL_Surface* img);
/* links sdl_surfaces to textures */
void initTextArray(SDL_Surface* img[], GLuint text[], int nb, int rgba);

/* -----FUNCTIONS FOR SDL_SURFACE ARRAYS----- */
/* verifies all images have been correctly loaded */
int verifyImg(SDL_Surface* img[], int nb);
/* deletes sdl_surfaces */
void deleteImg(SDL_Surface* img[], int nb);
/* deletes textures */
void deleteTextures(int nb, GLuint text[]);

/* -----DISPLAY----- */
/* draws grid */
void drawLandmark(int size);
/* defines in which ways the image will be transformed */
void imgSettings(float posX, float posY, float sizeX, float sizeY, float angle);
/* draws a texture simply on a 1-width square */
void draw(GLuint id);

/* -----IMAGE LOADING----- */
/* background images */
void initBgImg(SDL_Surface* img[]);
/* shooter images */
void initShooterImg(SDL_Surface* img[]);
/* bonus images */
void initBonusImg(SDL_Surface* img[]);
/* bullets images */
void initBulletImg(SDL_Surface* img[]);
/* ennemies images */
void initEnnemyImg(SDL_Surface* img[]);
/* walls images */
void initWallImg(SDL_Surface* img[]);
/* starts screen images */
void initStartScreenImg(SDL_Surface* img[]);
/* victory screen images */
void initVictoryScreenImg(SDL_Surface* img[]);
/* succeed screen images */
void initSucceedScreenImg(SDL_Surface* img[]);
/* loading screen images */
void initLoadingImg(SDL_Surface* img[]);
/* game over screen images */
void initGameOverScreenImg(SDL_Surface* img[]);
/* score and numbers images */
void initScoreImg(SDL_Surface* img[]);
/* story of first level */
void initFirstLevelStoryImg(SDL_Surface* img[]);
/* other images for story */
void initLevelStoriesImg(SDL_Surface* img[]);

#endif