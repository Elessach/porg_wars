#include "level.h"

/* initializes level */
void initLevel(Level* level, Background bg1, Background bg2){
    level->bonus = NULL;
    level->ennemies = NULL;
    level->walls = NULL;
    level->endPos = 0;
    level->bossPos = -1;
    level->bg1 = bg1;
    level->bg2 = bg2;
}

/* builds level with .ppm file infos */
int buildLevel(char* filename, Level* level, GLuint wallText[], GLuint ennemyText[], GLuint bonusText[]){

    /* gets file */
    FILE* in = fopen(filename, "r");
    /* we vverify the file has been correctly loaded */
    if(in==NULL){
        printf("ERROR FILE\n");
        return 0;
    }

    char p, n;
    int width, height, colors, r, g, b;
    /* verifies if it's a convenient ppm file */
    if(fscanf(in, "%c", &p) == EOF || p != 'P') return 0;
    if(fscanf(in, "%c", &n) == EOF || (n != '6' && n != '3')) return 0;
    /* we retrieve the image dimensions and number of colors */
    if(fscanf(in, "%d", &width) == EOF) return 0;
    if(fscanf(in, "%d", &height) == EOF || height != 20) return 0;
    if(fscanf(in, "%d", &colors) == EOF || colors != 255) return 0;
    
    /* analyze of the file and creation of entities */
    int i, j;
    for(i = 0; i < height; i++){
        for(j = 0; j < width; j++){
            /* retrieve the color of the pixel */
            if(fscanf(in, "%d", &r) == EOF || r > 255 || r < 0)return 0;
            if(fscanf(in, "%d", &g) == EOF || g > 255 || g < 0) return 0;
            if(fscanf(in, "%d", &b) == EOF || b > 255 || b < 0)
                return 0;

            /* BONUS */
            /* shield */
            if(r == 0 && g == 255 && b == 0) addBonusToList(allocBonus(bonusText[0], j, 19-i, 's'), &level->bonus);
            /* heart */
            else if(r == 0 && g == 255 && b == 255) addBonusToList(allocBonus(bonusText[1], j, 19-i, 'h'), &level->bonus);
            /* attack */
            else if(r == 255 && g == 0 && b == 255) addBonusToList(allocBonus(bonusText[2], j, 19-i, 'a'), &level->bonus);

            /* WALL */
            else if(r == 0 && g == 0 && b == 255)
                addWallToList(allocWall(wallText, j, 19-i), &level->walls);

            /* ENNEMY */
            /* moving */
            else if(r == 255 && g == 0 && b == 0) addEnnemyToList(allocEnnemy(ennemyText[0], j, 'm'), &level->ennemies);
            /* tower */
            else if(r == 150 && g == 0 && b == 0){
                /* at the bottom */                
                if(19-i == 0) addEnnemyToList(allocEnnemy(ennemyText[1], j, 't'), &level->ennemies);
                else addEnnemyToList(allocEnnemy(ennemyText[1], j, 'T'), &level->ennemies);
            }
            /* boss */
            else if(r == 0 && g == 0 && b == 0){
                if(level->bossPos == -1){
                    addEnnemyToList(allocEnnemy(ennemyText[2], j, 'B'), &level->ennemies);
                    level->bossPos = j;
                }
            }
            /* END OF LEVEL */
            else if(r == 255 && g == 255 && b == 0) level->endPos = j;
        }
    }
    return 1;
}

/* deletes level and its elements */
void deleteLevel(Level* level){
    deleteAllBonus(&level->bonus);
    deleteAllEnnemies(&level->ennemies);
    deleteAllWalls(&level->walls);
}