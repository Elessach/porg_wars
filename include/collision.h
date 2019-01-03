#ifndef COLLISION_H
#define COLLISION_H

#include "level.h"
#include "shooter.h"

/* compares two bounding boxes and returns whether there's a collision */
int collision(BoundingBox box1, BoundingBox box2);

/* detects collision between shooter and walls */
int collisionShooterWalls(Shooter shooter, WallList* list);
/* detects collision between shooter and ennemies */
int collisionShooterEnnemies(Shooter shooter, EnnemyList* list, int* mvt);
/* detects collisioin between shooter and ennemies bullets */
int collisionShooterBullets(Shooter shooter, BulletList* bullets);
/* detects collision between shooter and bonus */
Bonus* collisionShooterBonus(Shooter shooter, BonusList* list);

/* detects collisions between shooter's bullets and walls */
int collisionBulletsWalls(BulletList* bullets, WallList* walls);
/* detects collision between shooter's bullets and ennemies */
void collisionBulletsEnnemies(BulletList* bullets, EnnemyList* ennemies, int* mvt, int* score);


#endif