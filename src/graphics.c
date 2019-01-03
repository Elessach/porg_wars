#include "graphics.h"
 
/* links an image to a texture with RGBA settings */
void imgToTextRGBA(GLuint text, SDL_Surface* img){
    glBindTexture(GL_TEXTURE_2D, text);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        img->w,
        img->h,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        img->pixels
    );
    glBindTexture(GL_TEXTURE_2D, 0);
}
/* links an image to a texture with RGB settings */
void imgToTextRGB(GLuint text, SDL_Surface* img){
    glBindTexture(GL_TEXTURE_2D, text);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        img->w,
        img->h,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        img->pixels
    );
    glBindTexture(GL_TEXTURE_2D, 0);
}
/* links images to textures */
void initTextArray(SDL_Surface* img[], GLuint text[], int nb, int rgba){
    glGenTextures(nb, text);
    int i;
    for(i = 0; i < nb; i++){
        if(rgba == 1) imgToTextRGBA(text[i], img[i]);
        else imgToTextRGB(text[i], img[i]);
    }
}

/* verifies if all images have been correctly loaded */
int verifyImg(SDL_Surface* img[], int nb){
    int i;
    for(i = 0; i < nb; i++){
        if(img[1] == NULL) return 0;
    }
    return 1;
}
/* deletes sdl surface */
void deleteImg(SDL_Surface* img[], int nb){
    int i;
    for(i = 0; i < nb; i++){
        SDL_FreeSurface(img[i]);
    }
}
/* deletes textures */
void deleteTextures(int nb, GLuint text[]){
    int i;
    for(i = 0; i < nb; i++){
        glDeleteTextures(1, &text[i]);
    }
}

/* draws grid */ 
void drawLandmark(int size){
    /* white grid */
    /* line width */
    glLineWidth(0.75);
    /* line color */
    glColor3ub(255, 255, 255);
    int i;
    /* vertical lines */
    for(i =- size;i < size; i++){
        glBegin(GL_LINES);
            glVertex2f(i, -size);
            glVertex2f(i, size);
        glEnd();    
    }
    /* horizontal lines */
    for(i=-size;i<size;i++){
        glBegin(GL_LINES);
            glVertex2f(-size, i);
            glVertex2f(size, i);
        glEnd();    
    }

    /* axis */
    /* line width */
    glLineWidth(5);
    /* abscissa color */
    glColor3ub(255, 0, 0);
    glBegin(GL_LINES);
        glVertex2f(-size, 0);
        glVertex2f(size, 0);
    glEnd();
    /* ordinate color */
    glColor3ub(0, 255, 0);
    glBegin(GL_LINES);
        glVertex2f(0, -size);
        glVertex2f(0, size);
    glEnd();

    /* sets color back to normal */
    glColor3ub(255,255,255);
}
/* define settings of translation, rotation and scale */
void imgSettings(float posX, float posY, float sizeX, float sizeY, float angle){
    glTranslatef(posX, posY, 0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    glScalef(sizeX, sizeY, 1);
}
/* draws a texture on a 1-width sqaure */
void draw(GLuint textureID){
    glEnable(GL_TEXTURE_2D);
    /* transparency */
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, textureID);
        glBegin(GL_QUADS);
            glTexCoord2f(0,0);
            glVertex2f(0, 1);
            glTexCoord2f(1,0);
            glVertex2f(1, 1);
            glTexCoord2f(1,1);
            glVertex2f(1, 0);
            glTexCoord2f(0,1);
            glVertex2f(0, 0);
        glEnd();
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);   
}

void initBgImg(SDL_Surface* img[]){
    img[0] = IMG_Load("img/backgrounds/background_1.png");
    img[1] = IMG_Load("img/backgrounds/background_2.png");
    img[2] = IMG_Load("img/backgrounds/background_3.png");
    img[3] = IMG_Load("img/backgrounds/background_4.png");
    img[4] = IMG_Load("img/backgrounds/background_5.png");

    if(verifyImg(img, LEVEL_NB) == 0)
        printf("ERROR BG IMG\n");
}
void initShooterImg(SDL_Surface* img[]){
    img[0] = IMG_Load("img/shooter/shooter.png");
    img[1] = IMG_Load("img/shooter/shield.png");

    if(verifyImg(img, SHOOTER_IMG_NB) == 0)
        printf("ERROR SHOOTER IMG\n");
}
void initBonusImg(SDL_Surface* img[]){
    img[0] = IMG_Load("img/bonus/bonus_1.png");
    img[1] = IMG_Load("img/bonus/bonus_2.png");
    img[2] = IMG_Load("img/bonus/bonus_3.png");

    if(verifyImg(img, BONUS_IMG_NB) == 0)
        printf("ERROR BONUS IMG \n");
}
void initBulletImg(SDL_Surface* img[]){
    img[0] = IMG_Load("img/bullets/shooter_bullet.png");
    img[1] = IMG_Load("img/bullets/ennemy_bullet_h.png");
    img[2] = IMG_Load("img/bullets/ennemy_bullet_v.png");  
    
    if(verifyImg(img, BULLET_IMG_NB) == 0)
        printf("ERROR BULLET IMG\n");
}
void initEnnemyImg(SDL_Surface* img[]){
    img[0] = IMG_Load("img/ennemies/ennemy_1.png");
    img[1] = IMG_Load("img/ennemies/ennemy_2.png");
    img[2] = IMG_Load("img/ennemies/boss.png");

    if(verifyImg(img, ENNEMY_IMG_NB) == 0)
        printf("ERROR IMG ENNEMY\n");
}
void initWallImg(SDL_Surface* img[]){
    img[0] = IMG_Load("img/walls/asteroid_1.png");
    img[1] = IMG_Load("img/walls/asteroid_2.png");
    img[2] = IMG_Load("img/walls/asteroid_3.png");
    img[3] = IMG_Load("img/walls/asteroid_4.png");   

    if(verifyImg(img, WALL_IMG_NB) == 0)
        printf("ERROR IMG WALL\n");
}
void initStartScreenImg(SDL_Surface* img[]){
    img[0] = IMG_Load("img/screens/start/startPlay.png");
    img[1] = IMG_Load("img/screens/start/startQuit.png");

    if(verifyImg(img, SCREEN_IMG_NB) == 0)
        printf("ERROR IMG START SCREEN\n");
}
void initVictoryScreenImg(SDL_Surface* img[]){
    img[0] = IMG_Load("img/screens/victory/victoryMain.png");
    img[1] = IMG_Load("img/screens/victory/victoryQuit.png");

    if(verifyImg(img, SCREEN_IMG_NB) == 0)
        printf("ERROR IMG VICTORY SCREEN\n");
}
void initSucceedScreenImg(SDL_Surface* img[]){
    img[0] = IMG_Load("img/screens/succeed/succeedNext.png");
    img[1] = IMG_Load("img/screens/succeed/succeedQuit.png");

    if(verifyImg(img, SCREEN_IMG_NB) == 0)
        printf("ERROR IMG LOADING SCREEN\n");
}
void initLoadingImg(SDL_Surface* img[]){
    img[0] = IMG_Load("img/screens/loading/loading_1.png");

    if(verifyImg(img, SCREEN_IMG_NB) == 0)
        printf("ERROR IMG LOADING SCREEN\n");
}
void initGameOverScreenImg(SDL_Surface* img[]){
    img[0] = IMG_Load("img/screens/game_over/game_overRetry.png");
    img[1] = IMG_Load("img/screens/game_over/game_overQuit.png");

    if(verifyImg(img, SCREEN_IMG_NB) == 0)
        printf("ERROR IMG GAME OVER SCREEN\n");
}
void initScoreImg(SDL_Surface* img[]){
    img[0] = IMG_Load("img/score/number_0.png");
    img[1] = IMG_Load("img/score/number_1.png");
    img[2] = IMG_Load("img/score/number_2.png");
    img[3] = IMG_Load("img/score/number_3.png");
    img[4] = IMG_Load("img/score/number_4.png");
    img[5] = IMG_Load("img/score/number_5.png");
    img[6] = IMG_Load("img/score/number_6.png");
    img[7] = IMG_Load("img/score/number_7.png");
    img[8] = IMG_Load("img/score/number_8.png");
    img[9] = IMG_Load("img/score/number_9.png");
    img[10] = IMG_Load("img/score/score.png");

    if(verifyImg(img, SCREEN_IMG_NB) == 0)
        printf("ERROR IMG SCORE SCREEN\n");
}
void initFirstLevelStoryImg(SDL_Surface* img[]){
    img[0] = IMG_Load("img/story/level_1/level_1_story_1.png");
    img[1] = IMG_Load("img/story/level_1/level_1_story_2.png");
    img[2] = IMG_Load("img/story/level_1/tutorial.png");

    if(verifyImg(img, FIRST_LVL_IMG_NB) == 0)
        printf("ERROR IMG FIRST LEVEL STORY \n");
}
void initLevelStoriesImg(SDL_Surface* img[]){
    img[0] = IMG_Load("img/story/level_2/level_2_story_1.png");
    img[1] = IMG_Load("img/story/level_3/level_3_story_1.png");
    img[2] = IMG_Load("img/story/level_4/level_4_story_1.png");
    img[3] = IMG_Load("img/screens/credits/credits.png");

    if(verifyImg(img, OTHER_LVL_IMG_NB) == 0)
        printf("ERROR IMG OTHER LEVEL STORY \n");
}