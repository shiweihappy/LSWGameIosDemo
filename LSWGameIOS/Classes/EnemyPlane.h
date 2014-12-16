//
//  EnemyPlane.h
//  LSWGameIOS
//
//  Created by lsw on 14-10-20.
//
//

#ifndef LSWGameIOS_EnemyPlane_h
#define LSWGameIOS_EnemyPlane_h

#include "cocos2d.h"

#define ENEMY1_MAXLIFE 1
#define ENEMY2_MAXLIFE 2
#define ENEMY3_MAXLIFE 3
#define ENEMY1_MAXSCORE 1
#define ENEMY2_MAXSCORE 2
#define ENEMY3_MAXSCORE 3

enum enemyType {
    Enemy1 = 1,
    Enemy2,
    Enemy3,
    Enemy4
};

class EnemyPlane : public cocos2d::Sprite {
public:
    EnemyPlane();
    ~EnemyPlane();
    
    virtual bool init();
    CREATE_FUNC(EnemyPlane);
public:
    static EnemyPlane *createEnemy(enemyType type);
    int getLife();
    void loseLife();
    void increaseLife(int life);
    int getScore();
    bool isDie();
    cocos2d::Rect getBoundingBox();
protected:
    bool initEnemyPlaneByType(enemyType type);
    
private:
    int nlife;
    int maxLife;
    int maxScore;
};

#endif
