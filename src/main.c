#include "main.h"

/* window's dimensions */
static unsigned int WINDOW_WIDTH = 1000;
static unsigned int WINDOW_HEIGHT = 1000;

/* window's settings */
static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

/* window's resize */
void resizeViewport() {
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIDTH, -1., HEIGHT);
    SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE);
}

/* initializes sdl and window */
int initWindow(){
    /* -----INITIALISATION DE LA SDL----- */
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return 0;
    }

    /* -----OUVERTURE FENETRE ET CONTEXTE OPENGL----- */
    if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE)) {
        fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        return 0;
    }
    SDL_WM_SetCaption("PORG WARS", NULL);
    resizeViewport();

    return 1;
}

/* initializes music */
int initMusic(){
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1){
        printf("ERROR MUSIC : %s\n", Mix_GetError());
        return 0;
    }
    return 1;
}

int main(int argc, char** argv) {

    /* initialization of sdl and window */
    if(initWindow() == 0) return EXIT_FAILURE;
    /* initialization music */
    if(initMusic() == 0) printf("ERROR MUSIC INIT\n");

    /* -----VARIABLES----- */
    /* current level */
    int nbLevel = 0;
    /* tells if scrolling is activated */
    int mvt = 1;
    /* tells the position of the window */
    float countX = 0;
    /* screen number */
    int screen = -1;
    /* scores */
    int prevScore = 0;
    int score = 0;
    /* frequency at which the ennemies shoot */
    int bulletsTime = BULLETS_PERIOD;
    /* which button is activve */
    int activeButton = 1;
    /* step on story */
    int storyStep = 0;

    /* -----OBJECTS INITIALIZATION----- */
    /* TEXTURES */
    GLuint bgText[LEVEL_NB], bonusText[BONUS_IMG_NB], bulletText[BULLET_IMG_NB], ennemyText[ENNEMY_IMG_NB], shooterText[SHOOTER_IMG_NB], wallText[WALL_IMG_NB], startScreenText[SCREEN_IMG_NB], succeedScreenText[SCREEN_IMG_NB], victoryScreenText[SCREEN_IMG_NB], loadingText[LOADING_IMG_NB], gameOverScreenText[SCREEN_IMG_NB], scoreText[11], firstLevelStoryText[FIRST_LVL_IMG_NB], otherLevelStoryText[OTHER_LVL_IMG_NB];
    
    initBgText(bgText);       
    initLoadingText(loadingText);
    initGameOverScreenText(gameOverScreenText);
    initStartScreenText(startScreenText);
    initSucceedScreenText(succeedScreenText);
    initVictoryScreenText(victoryScreenText);
    initScoreText(scoreText);
    initBonusText(bonusText);
    initBulletText(bulletText);
    initEnnemyText(ennemyText);
    initShooterText(shooterText);
    initWallText(wallText);
    initFirstLevelStoryText(firstLevelStoryText);
    initOtherLevelStoryText(otherLevelStoryText);

    /* NIVEAU */
    Level level;  
    Background bg1, bg2;
    Shooter shooter;

    /* MUSIC */
    Mix_Music *music;
    music = Mix_LoadMUS("audio/music.mp3");
    Mix_PlayMusic(music, -1);

    /* SOUNDS */
    Mix_AllocateChannels(3);
    Mix_Volume(1, MIX_MAX_VOLUME/2);
    Mix_Chunk* sound;
    sound = Mix_LoadWAV("audio/sound.wav");
    Mix_VolumeChunk(sound, MIX_MAX_VOLUME);

    glClearColor(0, 0, 0, 1.0);
    int loop = 1;
    while(loop) {
        Uint32 startTime = SDL_GetTicks();
        glClear(GL_COLOR_BUFFER_BIT);

        /* ECRAN -1 : écran de crédit */
        if(screen == -1)
            drawScreen(otherLevelStoryText[3]);
        /* ECRAN 0 : début de jeu */
        else if(screen == 0){
            score = 0;
            drawScreenAndButtons(startScreenText, activeButton);
        }
        /* ECRAN 1 : story */
        else if(screen == 1){
            switch(nbLevel){
                case 1:
                    if(storyStep == FIRST_LVL_IMG_NB + 1) screen = 3; 
                    else drawFirstLevelStory(firstLevelStoryText, storyStep);
                    break;
                case 2:
                    drawScreen(otherLevelStoryText[0]);
                    break;
                case 3:
                    drawScreen(otherLevelStoryText[1]);
                    break;
                case 4:
                    drawScreen(otherLevelStoryText[2]);
                    break;
                case 5:
                    screen = 2;
                default:
                    break;
            }
        }
        /* ECRAN 2 : chargement du niveau */
        else if(screen == 2){
            /* (ré)initialisation */
            initBg(&bg1, 0, bgText[nbLevel-1]); 
            initBg(&bg2, WIDTH * 4, bgText[nbLevel-1]); 
            initLevel(&level, bg1, bg2);
            initShooter(&shooter, shooterText[0], shooterText[1]);
            countX = 0;
            mvt = 1;
            /* construction du niveau */
            char levelName[20];
            sprintf(levelName, "levels/level_%d.ppm", nbLevel);
            if(buildLevel(levelName, &level, wallText, ennemyText, bonusText) == 0) printf("ERROR LEVEL.\n");
            else screen = 3;
        }
        /* ECRAN 2 : déroulement du niveau */
        else if(screen == 3){
            storyStep = 0;

            /*-----DISPLAY-----*/
            /* ARRIERE-PLAN */
            drawBg(level.bg1);
            drawBg(level.bg2);

            /* VAISSEAU */
            drawShooter(shooter);
            /* OBSTACLES */
            drawWalls(level.walls);
            /* PROJECTILES VAISSEAU & ENNEMIS */
            drawBullets(shooter.bullets);
            drawEnnemiesBullets(level.ennemies);
            /* BONUS */
            drawBonus(level.bonus);
            /* ENNEMIS */
            drawEnnemies(level.ennemies);
            
            /* REPERE (debug) */
            //drawLandmark(WIDTH);

            /*-----ACTIONS-----*/

            /* CREATION OF ENNEMIES BULLETS */
            /* if time has spent we add another bullet */
            if(bulletsTime == 0){
                addBulletsToEnnemies(&level.ennemies, bulletText);
                bulletsTime = BULLETS_PERIOD;
            }
            else bulletsTime -= 1;

            /* SHOOTER MOVEMENTS */
            if(shooter.up == 1) moveUp(&shooter.box, shooter.speed, WIDTH);
            else if(shooter.up == 0) moveDown(&shooter.box, shooter.speed);
            /* BULLETS */
            scrollBullets(shooter.bullets);
            scrollEnnemiesBullets(level.ennemies);

            /* -----SCROLLING----- */ 
            if(mvt == 1){
                scrollBg(&level.bg1);
                scrollBg(&level.bg2);  
                scrollWalls(level.walls, OBJ_SPEED); 
                scrollBonus(level.bonus, OBJ_SPEED);
                scrollEnnemies(level.ennemies, OBJ_SPEED, WIDTH);    
            }

            /* -----COLLISIONS----- */

            /* the shooter have damage if there's cillision and the shield isn't activated */
            if(collisionShooterWalls(shooter, &level.walls) == 1 || collisionShooterEnnemies(shooter, &level.ennemies, &mvt) == 1){
                if(shooter.shield == 0){
                    shooter.collision = 10;
                    shooter.hp -= 1;
                }
                /* otherwise the shield take damage */
                else shooter.shield -= 1;
            }
            /* collisions mounting score */
            score += collisionBulletsWalls(&shooter.bullets, &level.walls);
            collisionBulletsEnnemies(&shooter.bullets, &level.ennemies, &mvt, &score);
            /* bonus collision */
            Bonus* bonusTmp = collisionShooterBonus(shooter, &level.bonus);
            if(bonusTmp != NULL){
                switch(bonusTmp->type){
                    case 'a':;
                        BulletList bulletTmp = shooter.bullets;
                        while(bulletTmp != NULL){
                            bulletTmp->speed = bonusTmp->points;   
                            bulletTmp = bulletTmp->next;
                        }
                        break;
                    case 'h':
                        if(shooter.hp + HEART_PTS > SHOOTER_HP) shooter.hp = SHOOTER_HP;
                        else shooter.hp += bonusTmp->points;
                        break;
                    case 's':
                        shooter.shield = bonusTmp->points;
                        break;
                    default:
                        break;
                }
            }

            /* -----VERIFICATIONS----- */
            /* if shooter hp are down it's a game over then */
            if(shooter.hp == 0) screen = 4;
            /* the count continues if the movement goes on */
            if(mvt == 1) countX += OBJ_SPEED; 
            /* if the shooter reaches level's end, it's a success */
            if(countX >= level.endPos) screen = 5;
            /* if the count reaches the boss the movement stops */
            if(countX + 10 >= level.bossPos && level.bossPos != -1){
                mvt = 0;
                level.bossPos = -1;
            }
            /* count for damage appeareance */
            if(shooter.collision >= 1) shooter.collision -= 1;

            /* -----GAME INFOS----- */
            drawInfos();
            drawLife(shooter.hp, bonusText[1]);
            int tab[5];
            tabScore(&tab, score);
            drawScore(scoreText, tab, 0);

            /*-----DELETION-----*/
            deleteBullets(&shooter.bullets, NULL, WIDTH);
            deleteWalls(&level.walls, NULL);
            deleteBonus(&level.bonus, NULL);
            deleteEnnemies(&level.ennemies, NULL);
            deleteEnnemiesBullets(&level.ennemies);

        }
        /* ECRAN 4 : GAME OVER */
        else if(screen == 4){
            drawScreenAndButtons(gameOverScreenText, activeButton);
            int tab[5];
            tabScore(&tab, score);
            drawScore(scoreText, tab, 1);
        }
        /* ECRAN 5 : SUCCESS / VICTORY */
        else if(screen == 5){
            /* if the success was at the last level it's a victory */
            if(nbLevel == 5) drawScreenAndButtons(victoryScreenText, activeButton);
            else drawScreenAndButtons(succeedScreenText, activeButton);
            int tab[5];
            tabScore(&tab, score);
            drawScore(scoreText, tab, 1);
            prevScore = score;
        }
    
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            switch(e.type) {
                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym){
                        case SDLK_RETURN:
                                if(screen != 3 && screen != 1) drawScreen(loadingText[0]);
                                switch(screen){
                                    case -1:
                                        screen = 0;
                                        break;
                                    case 0:
                                        if(activeButton == 1){
                                            nbLevel += 1;
                                            screen = 1;
                                        }
                                        else loop = 0;
                                        break;
                                    case 1:
                                        if(nbLevel == 1){
                                            if(storyStep == FIRST_LVL_IMG_NB - 1) screen = 2;
                                            else storyStep += 1;
                                        }
                                        else screen = 2;
                                        break;
                                    case 5:
                                        if(nbLevel == 5){
                                            if(activeButton == 1){
                                                nbLevel = 0;
                                                screen = 0;
                                            } 
                                            else{
                                                deleteLevel(&level);
                                                deleteShooter(&shooter);
                                                loop = 0;
                                            }
                                            break;
                                        } else nbLevel += 1;
                                    case 4:
                                        if(activeButton == 1){          
                                            score = prevScore;
                                            screen = 1;
                                        }
                                        else{
                                            deleteLevel(&level);
                                            deleteShooter(&shooter);
                                            loop = 0;
                                        }
                                        break;
                                    default:
                                        break;
                                }
                            break;
                        /* quit */
                        case SDLK_ESCAPE:
                            if(screen == 3){
                                glClear(GL_COLOR_BUFFER_BIT);
                                deleteLevel(&level);
                                deleteShooter(&shooter);
                                loop = 0;   
                            }
                            break;
                        case SDLK_UP:
                            if(screen == 3) shooter.up = 1;
                            else activeButton = 1;
                            break;
                        case SDLK_DOWN:
                            if(screen == 3) shooter.up = 0;
                            else activeButton = 2;
                            break;

                        /* bullet */
                        case SDLK_SPACE:
                            if(shooter.bullets == NULL){
                                Mix_PlayChannel(1, sound, 0);
                                addBulletToList(allocBullet(bulletText[0], 2.75, (shooter.box).minY, 'H'), &shooter.bullets);
                            }
                            break;
                        default:
                            break;
                    }
                    break;

                case SDL_KEYUP:
                    switch(e.key.keysym.sym){
                        /* désactive le déplacement vers le haut */
                        case SDLK_UP:
                            shooter.up = -1;
                            break;
                        /* désactive le déplacement vers le bas */
                        case SDLK_DOWN:
                            shooter.up = -1;
                            break;
                        default:
                            break;
                    }
                    break;

                case SDL_QUIT:
                    loop = 0;
                    break;

                case SDL_VIDEORESIZE:
                    WINDOW_WIDTH = e.resize.w;
                    WINDOW_HEIGHT = e.resize.h;
                    resizeViewport();
                    break;

                default:
                    break;
            }
        }

        SDL_GL_SwapBuffers();
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        if(elapsedTime < FRAMERATE_MILLISECONDS) {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }

    /* -----SUPPRESSION DES TEXTURES----- */
    deleteTextures(LEVEL_NB, bgText);
    deleteTextures(LOADING_IMG_NB, loadingText);
    deleteTextures(SCREEN_IMG_NB, gameOverScreenText);
    deleteTextures(SCREEN_IMG_NB, startScreenText);
    deleteTextures(SCREEN_IMG_NB, succeedScreenText);
    deleteTextures(SCREEN_IMG_NB, victoryScreenText);
    deleteTextures(11, scoreText);
    deleteTextures(BONUS_IMG_NB, bonusText);
    deleteTextures(BULLET_IMG_NB, bulletText);
    deleteTextures(ENNEMY_IMG_NB, ennemyText);
    deleteTextures(SHOOTER_IMG_NB, shooterText);
    deleteTextures(WALL_IMG_NB, wallText);

    Mix_FreeChunk(sound);
    Mix_FreeMusic(music);
    Mix_CloseAudio();

    // Liberation des ressources associées à la SDL
    SDL_Quit();

    return EXIT_SUCCESS;
}