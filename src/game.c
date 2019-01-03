#include "game.h"

/* initializes textures arrays */
void initGameOverScreenText(GLuint text[]){
    SDL_Surface* img[SCREEN_IMG_NB];
    initGameOverScreenImg(img);
    initTextArray(img, text, SCREEN_IMG_NB, 0);
    deleteImg(img, SCREEN_IMG_NB);
}
void initLoadingText(GLuint text[]){
    SDL_Surface* img[LOADING_IMG_NB];
    initLoadingImg(img);
    initTextArray(img, text, LOADING_IMG_NB, 0);
    deleteImg(img, LOADING_IMG_NB);
}
void initScoreText(GLuint text[]){
    SDL_Surface* img[11];
    initScoreImg(img);
    initTextArray(img, text, 11, 1);
    deleteImg(img, 11);
}
void initStartScreenText(GLuint text[]){
    SDL_Surface* img[SCREEN_IMG_NB];
    initStartScreenImg(img);
    initTextArray(img, text,SCREEN_IMG_NB, 0);
    deleteImg(img, SCREEN_IMG_NB);
}
void initSucceedScreenText(GLuint text[]){
    SDL_Surface* img[SCREEN_IMG_NB];
    initSucceedScreenImg(img);
    initTextArray(img, text, SCREEN_IMG_NB, 0);
    deleteImg(img, SCREEN_IMG_NB);    
}
void initVictoryScreenText(GLuint text[]){
    SDL_Surface* img[SCREEN_IMG_NB];
    initVictoryScreenImg(img);
    initTextArray(img, text, SCREEN_IMG_NB, 0);
    deleteImg(img, SCREEN_IMG_NB);
}

/* decomposes the score */
void tabScore(int (*tab)[5], int score){
    (*tab)[4]= score % 10;
    (*tab)[3]= (score % 100 - score % 10) / 10;
    (*tab)[2]= (score % 1000 - score % 100) / 100;
    (*tab)[1]= (score % 10000 - score % 1000) / 1000;
    (*tab)[0]= score / 10000;
}
/* draws the score */
void drawScore(GLuint text[], int score[], int end){
    /* "score" */
    glPushMatrix();
        if(end == 0) imgSettings(14, 20.25, 2, 0.5, 0);
        else imgSettings(WIDTH/2 - 3, HEIGHT/2 - 3, 2, 0.5, 0);
        draw(text[10]);
    glPopMatrix();
    /* numbers */
    int i;
    for(i = 0; i < 5; i++){
        glPushMatrix();
            if(end == 0) imgSettings(i * 0.55 + 17.1, 20.25, 0.5, 0.5, 0);
            else imgSettings(WIDTH/2 + i * 0.55, HEIGHT/2 - 3, 0.5, 0.5, 0);
            draw(text[score[i]]);
        glPopMatrix();   
    }
}
/* draws health points */
void drawLife(int hp, GLuint heart){
    int i;
    for(i = 0; i < hp ; i++){
        glPushMatrix();
            imgSettings(i * (HEART_SIZE + 0.05) + 0.1, 20 + HEART_SIZE / 2, HEART_SIZE, HEART_SIZE, 0);
            draw(heart);
        glPopMatrix();
    }
}
/* draws infos */
void drawInfos(){
    glColor3ub(50, 50, 50);
    glBegin(GL_QUADS);
        glVertex2f(0, HEIGHT - 1);
        glVertex2f(0, HEIGHT);
        glVertex2f(WIDTH, HEIGHT);
        glVertex2f(WIDTH, HEIGHT - 1);
    glEnd();
    glColor3ub(255, 255, 255);
}


/* draws a screen */
void drawScreen(GLuint text){
    glPushMatrix();
        imgSettings(0, 0, WIDTH, HEIGHT, 0);
        draw(text);
    glPopMatrix();
}

/* draws screens with buttonss */
void drawScreenAndButtons(GLuint text[] , int button){
    GLuint id;
    if(button == 1) id = text[0];
    else id = text[1];

    drawScreen(id);
}