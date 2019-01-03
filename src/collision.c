#include "collision.h"

/* compares two bounding box and tells if there's a collision */
int collision(BoundingBox box1, BoundingBox box2){
    /* first object data */
    float minX1 = box1.minX,
    maxX1 = box1.maxX,
    minY1 = box1.minY,
    maxY1 = box1.maxY,
    /* second object data */
    minX2 = box2.minX,
    maxX2 = box2.maxX,
    minY2 = box2.minY,
    maxY2 = box2.maxY;
    /* comparison */
    if(!((maxX1 < minX2)||(minY1 > maxY2)||(maxY1 < minY2)||(minX1 > maxX2))) return 1;
    else return 0;
}

/* detects collision between shooter and walls */
int collisionShooterWalls(Shooter shooter, WallList* list){
    WallList tmp = *list;
	while(tmp != NULL){
        if(collision(shooter.box, tmp->box) == 1){
            tmp->collision = 1;
            return 1;
        }
		tmp=tmp->next;
	}
    return 0;
}

/* detects collision between shooter and ennemies */
int collisionShooterEnnemies(Shooter shooter, EnnemyList* list, int* mvt){
    EnnemyList tmp = *list;
    while(tmp != NULL){
        if(collision(shooter.box, tmp->box) == 1){
            tmp->hp -= 1;
            /* if it's the boss and he's dead, then the scrolling comes back */
            if(tmp->type == 'B' && tmp->hp == 0) *mvt = 1;
            return 1;
        }
        if(collisionShooterBullets(shooter, &tmp->bullets) == 1)return 1;
        tmp=tmp->next;
    }
    return 0;
}

/* detects collision between shooter and bullets */
int collisionShooterBullets(Shooter shooter, BulletList* bullets){
    BulletList tmp = *bullets;
    while(tmp != NULL){
        if(collision(shooter.box, tmp->box) == 1){
            tmp->collision = 1;
            return 1;
        }
        tmp = tmp->next;
    }
    return 0;
}

/* detects collision between shooter and bonus */
Bonus* collisionShooterBonus(Shooter shooter, BonusList* list){
    /* returns the collided bonus to know what does the shooter gain */
    BonusList tmp = *list;
    while(tmp != NULL){
        if(collision(shooter.box, tmp->box) == 1){
            tmp->collision = 1;
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}


/* detects the collision between the shooter's bullets and walls */
int collisionBulletsWalls(BulletList* bullets, WallList* walls){
    /* returns the score to add */
    int val = 0;
    if(*bullets != NULL){
        BulletList bulletsTmp = *bullets;
        if(*walls != NULL){
            WallList wallsTmp = *walls;
            if(collision(bulletsTmp->box, wallsTmp->box) == 1){
                bulletsTmp->collision = 1;
                wallsTmp->collision = 1;
                return 10;
            }
            val += collisionBulletsWalls(&bulletsTmp, &wallsTmp->next);
        }
        val += collisionBulletsWalls(&bulletsTmp->next, walls);
    }
    return val;
}

/* detects collision between bullets and ennemies */
void collisionBulletsEnnemies(BulletList* bullets, EnnemyList* ennemies, int* mvt, int* score){
    if(*bullets != NULL){
        BulletList bulletsTmp = *bullets;
        if(*ennemies != NULL){
            EnnemyList ennemiesTmp = *ennemies;
            if(collision(bulletsTmp->box, ennemiesTmp->box) == 1){
                bulletsTmp->collision = 1;
                ennemiesTmp->hp -= 1;
                if(ennemiesTmp->type == 'B' && ennemiesTmp->hp <= 0){
                    *mvt = 1;
                    *score += 200;
                }
                else *score += 100;
            }
            collisionBulletsEnnemies(&bulletsTmp, &ennemiesTmp->next, mvt, score);
        }
        collisionBulletsEnnemies(&bulletsTmp->next, ennemies, mvt, score);
    }
}