#include "background.h"
 
/* initializes the background textures */
void initBgText(GLuint text[]){
    SDL_Surface* img[LEVEL_NB];
    initBgImg(img);
    initTextArray(img, text, LEVEL_NB, 1);
    deleteImg(img, LEVEL_NB);
}

/* initializes a background object */
void initBg(Background* bg, float pos, GLuint textID)
{
	bg->scrollSpeed = SCROLL_SPEED;
	bg->posX = pos;
    bg->textID = textID;
}

/* makes a background object scroll correctly */
void scrollBg(Background* bg){
	/* if the background is off limits, it gets back to the end of the window to appear again */
	if(bg->posX <= -WIDTH * 4) bg->posX = WIDTH * 4 - 0.25;
    /* otherwise the background scrolls, position changes */
    else bg->posX -= bg->scrollSpeed;
}

/* draws a background objects */
void drawBg(Background bg){
    glPushMatrix();
        imgSettings(bg.posX, 0, WIDTH, WIDTH, 0);
        glEnable(GL_TEXTURE_2D);
        /* for transparency */
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBindTexture(GL_TEXTURE_2D, bg.textID);
            /* the quad must be adapted to the proportions of the background image */
            glBegin(GL_QUADS);
                glTexCoord2f(0,0);
                glVertex2f(0, 1);
                glTexCoord2f(1,0);
                glVertex2f(4, 1);
                glTexCoord2f(1,1);
                glVertex2f(4, 0);
                glTexCoord2f(0,1);
                glVertex2f(0, 0);
            glEnd();
        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);  
    glPopMatrix();
}