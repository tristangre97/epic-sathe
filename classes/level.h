class LEVEL
{
    public:
        void MANUALLY_CODED_LEVELS();
        
        void COMPUTER_GENERATED_LEVELS();
        
        void UPDATER();
        
    private:
        
}use;

void LEVEL::MANUALLY_CODED_LEVELS()
{   
    /* manually coded levels */
    if(currentLevel == 1 && spawned == 0){
        spawned = 1;
        spawn.SetUpSlot1(DUDE, 360, 50);
        
    }
    else if(currentLevel == 2 && spawned == 0){
        spawned = 1;
        spawn.SetUpSlot1(DUDE, 360, 50);
        spawn.SetUpSlot2(REPUBLIKEN, 0, 50);
    }
    else if(currentLevel == 3 && spawned == 0){
        spawned = 1;
        spawn.SetUpSlot1(DUDE, 360, 50);
        spawn.SetUpSlot3(DUDE, -2, 50);
        
    }
    else if(currentLevel == 4 && spawned == 0){
        spawned = 1;
        spawn.SetUpSlot1(REPUBLIKEN, 360, 50);
        spawn.SetUpSlot2(REPUBLIKEN, 0, 50);
        spawn.SetUpSlot3(REPUBLIKEN, 426, 50);
        spawn.SetUpSlot4(REPUBLIKEN, 360, 0);
        spawn.SetUpSlot5(REPUBLIKEN, 360, -30);
    }
    else if(currentLevel == 5 && spawned == 0){
        spawned = 1;
        spawn.SetUpSlot1(DUDE, 360, 50);
        spawn.SetUpSlot3(DUDE, 426, 50);
    }
    else if(currentLevel == 6 && spawned == 0){
        spawned = 1;
        spawn.SetUpSlot1(DUDE, 360, 50);
        spawn.SetUpSlot3(REPUBLIKEN, 426, 50);
        spawn.SetUpSlot4(DUDE, 360, 0);
        spawn.SetUpSlot5(REPUBLIKEN, 360, -30);
    }
    else if(currentLevel == 7 && spawned == 0){
        spawned = 1;
        spawn.SetUpSlot1(DUDE, 360, 50);
    }
    else if(currentLevel == 8 && spawned == 0){
        spawned = 1;
        spawn.SetUpSlot1(DUDE, 360, 50);
        spawn.SetUpSlot2(DUDE, 0, 50);
        spawn.SetUpSlot3(DUDE, 426, 50);
        spawn.SetUpSlot4(DUDE, 360, 0);
        spawn.SetUpSlot5(DUDE, 360, -30);
        spawn.SetUpSlot6(DUDE, 0, 50);
        spawn.SetUpSlot7(DUDE, 17, -80);
        spawn.SetUpSlot8(REPUBLIKEN, 190, 0);
    }
    
    //this moves the game along
    if(totalNum == 0)
    {   
        /* set game to next level */
        currentLevel++; 
        spawned = 0;
        
        //spawn some random clouds
        int rcloud1, rcloud2, rcloud3, rcloud4, rcloud5, rcloud6, rcloud7, rcloud8;
        srand((unsigned)time(0)); rcloud1 = (rand()%6)+1;
        srand((unsigned)time(0)); rcloud2 = (rand()%6)+1;
        srand((unsigned)time(0)); rcloud3 = (rand()%6)+1;
        srand((unsigned)time(0)); rcloud4 = (rand()%6)+1;
        srand((unsigned)time(0)); rcloud5 = (rand()%6)+1;
        srand((unsigned)time(0)); rcloud6 = (rand()%6)+1;
        srand((unsigned)time(0)); rcloud7 = (rand()%6)+1;
        srand((unsigned)time(0)); rcloud8 = (rand()%6)+1;
        
        if(rcloud1 == 2){
            if(cloud1 != NULL){oslDeleteImage(cloud1); cloud1 = NULL;}
            cloud1 = oslLoadImageFilePNG((char*)"img/data/cloud.png", OSL_IN_RAM, OSL_PF_5551);
            cloud1->x = 240;
        }
        if(rcloud2 == 2){
            if(cloud2 != NULL){oslDeleteImage(cloud2); cloud2 = NULL;}
            cloud2 = oslLoadImageFilePNG((char*)"img/data/cloud.png", OSL_IN_RAM, OSL_PF_5551);
            cloud2->x = 280;
        }
        if(rcloud3 == 2){
            if(cloud3 != NULL){oslDeleteImage(cloud3); cloud3 = NULL;}
            cloud3 = oslLoadImageFilePNG((char*)"img/data/cloud.png", OSL_IN_RAM, OSL_PF_5551);
            cloud3->x = 210;
        }
        if(rcloud4 == 2){
            if(cloud4 != NULL){oslDeleteImage(cloud4); cloud4 = NULL;}
            cloud4 = oslLoadImageFilePNG((char*)"img/data/cloud.png", OSL_IN_RAM, OSL_PF_5551);
            cloud4->x = 340;
        }
        if(rcloud5 == 2){
            if(cloud5 != NULL){oslDeleteImage(cloud5); cloud5 = NULL;}
            cloud5 = oslLoadImageFilePNG((char*)"img/data/cloud.png", OSL_IN_RAM, OSL_PF_5551);
            cloud5->x = 360;
        }
        if(rcloud6 == 2){
            if(cloud6 != NULL){oslDeleteImage(cloud6); cloud6 = NULL;}
            cloud6 = oslLoadImageFilePNG((char*)"img/data/cloud.png", OSL_IN_RAM, OSL_PF_5551);
            cloud6->x = 350;
        }
        if(rcloud7 == 2){
            if(cloud7 != NULL){oslDeleteImage(cloud7); cloud7 = NULL;}
            cloud7 = oslLoadImageFilePNG((char*)"img/data/cloud.png", OSL_IN_RAM, OSL_PF_5551);
            cloud7->x = 180;
        }
        if(rcloud8 == 2){
            if(cloud8 != NULL){oslDeleteImage(cloud8); cloud8 = NULL;}
            cloud8 = oslLoadImageFilePNG((char*)"img/data/cloud.png", OSL_IN_RAM, OSL_PF_5551);
            cloud8->x = 50;
        }
        
        /* stop any possible playing music */
        oslStopSound(battle2); oslStopSound(battle3); oslStopSound(battle4); oslStopSound(battle5);
        
        if(currentLevel <= 10){oslPlaySound(battle3, 1);}
        else if(currentLevel > 10 && currentLevel <= 20)  {oslPlaySound(battle2, 1); oslSetSoundLoop(battle2, 1);}
        else if(currentLevel > 20 && currentLevel <= 30)  {oslPlaySound(battle3, 1); oslSetSoundLoop(battle3, 1);}
        else if(currentLevel > 30 && currentLevel <= 40)  {oslPlaySound(battle4, 1); oslSetSoundLoop(battle4, 1);}
        else if(currentLevel > 40 && currentLevel <= 50)  {oslPlaySound(battle5, 1); oslSetSoundLoop(battle5, 1);}
        else if(currentLevel > 50 && currentLevel <= 60)  {oslPlaySound(battle2, 1); oslSetSoundLoop(battle2, 1);}
        else if(currentLevel > 60 && currentLevel <= 70)  {oslPlaySound(battle3, 1); oslSetSoundLoop(battle3, 1);}
        else if(currentLevel > 70 && currentLevel <= 80)  {oslPlaySound(battle4, 1); oslSetSoundLoop(battle4, 1);}
        else if(currentLevel > 80 && currentLevel <= 90)  {oslPlaySound(battle5, 1); oslSetSoundLoop(battle5, 1);}
        else if(currentLevel > 90 && currentLevel <= 100) {oslPlaySound(battle2, 1); oslSetSoundLoop(battle2, 1);}
        else if(currentLevel > 100 && currentLevel <= 110){oslPlaySound(battle3, 1); oslSetSoundLoop(battle3, 1);}
        else if(currentLevel > 110 && currentLevel <= 120){oslPlaySound(battle4, 1); oslSetSoundLoop(battle4, 1);}
        else if(currentLevel > 120 && currentLevel <= 130){oslPlaySound(battle5, 1); oslSetSoundLoop(battle5, 1);}
        else if(currentLevel > 50 && currentLevel <= 60)  {oslPlaySound(battle2, 1); oslSetSoundLoop(battle2, 1);}
        else if(currentLevel > 130 && currentLevel <= 140){oslPlaySound(battle3, 1); oslSetSoundLoop(battle3, 1);}
        else oslPlaySound(battle3, 1);
    }
    
    return;
    
}

void LEVEL::UPDATER()
{
    /* handle clouds */
    if(cloud1 != NULL)
    {
        cloud1->y = -5;
        cloud1->x++;
        if(cloud1->x > 500) cloud1->x = 0;
    }
    if(cloud2 != NULL)
    {
        cloud2->y = 5;
        cloud2->x++;
        if(cloud2->x > 500) cloud2->x = 0;
    }
    if(cloud3 != NULL)
    {
        cloud3->y = 0;
        cloud3->x++;
        if(cloud3->x > 500) cloud3->x = 0;
    }
    if(cloud4 != NULL)
    {
        cloud4->y = -10;
        cloud4->x++;
        if(cloud4->x > 500) cloud4->x = 0;
    }
    if(cloud5 != NULL)
    {
        cloud5->y = 0;
        cloud5->x++;
        if(cloud5->x > 500) cloud5->x = 0;
    }
    if(cloud6 != NULL)
    {
        cloud6->y = 10;
        cloud6->x++;
        if(cloud6->x > 500) cloud6->x = 0;
    }
    if(cloud7 != NULL)
    {
        cloud7->y = 20;
        cloud7->x++;
        if(cloud7->x > 500) cloud7->x = 0;
    }
    if(cloud8 != NULL)
    {
        cloud8->y = -3;
        cloud8->x++;
        if(cloud8->x > 500) cloud8->x = 0;
    }
    
    oslDrawImage(level);
    if(cloud1 != NULL) oslDrawImageSimple(cloud1); 
    if(cloud2 != NULL) oslDrawImageSimple(cloud2); 
    if(cloud3 != NULL) oslDrawImageSimple(cloud3); 
    if(cloud4 != NULL) oslDrawImageSimple(cloud4); 
    if(cloud5 != NULL) oslDrawImageSimple(cloud5); 
    if(cloud6 != NULL) oslDrawImageSimple(cloud6); 
    if(cloud7 != NULL) oslDrawImageSimple(cloud7); 
    if(cloud8 != NULL) oslDrawImageSimple(cloud8); 
    
    /****************************************handle enemies if they are alive*********************************/
        if(enemy1.alive){
            enemy1.SpriteAnimate(enemy1.image, enemy1.manipulate, enemy1.march, enemy1.position);
            enemy1.Handle(enemy1.image, enemy1.health, enemy1.attack, enemy1.power, enemy1.maxPower, enemy1.touchingGround, enemy1.attacking, enemy1.sy, enemy1.position, enemy1.special);
            if(enemy1.health <= 0) {totalNum--; oslPlaySound(groan, 6); enemy1.alive = false; enemy1.Reward(enemy1.id);}
        }
        if(enemy2.alive){
            enemy2.SpriteAnimate(enemy2.image, enemy2.manipulate, enemy2.march, enemy2.position);
            enemy2.Handle(enemy2.image, enemy2.health, enemy2.attack, enemy2.power, enemy2.maxPower, enemy2.touchingGround, enemy2.attacking, enemy2.sy, enemy2.position, enemy2.special);
            if(enemy2.health <= 0) {totalNum--; oslPlaySound(groan2, 6); enemy2.alive = false; enemy2.Reward(enemy2.id);}
        }
        if(enemy3.alive){
            enemy3.SpriteAnimate(enemy3.image, enemy3.manipulate, enemy3.march, enemy3.position);
            enemy3.Handle(enemy3.image, enemy3.health, enemy3.attack, enemy3.power, enemy3.maxPower, enemy3.touchingGround, enemy3.attacking,  enemy3.sy, enemy3.position, enemy3.special);
            if(enemy3.health <= 0) {totalNum--; oslPlaySound(groan, 6); enemy3.alive = false; enemy3.Reward(enemy3.id);}
        }
        if(enemy4.alive){
            enemy4.SpriteAnimate(enemy4.image, enemy4.manipulate, enemy4.march, enemy4.position);
            enemy4.Handle(enemy4.image, enemy4.health, enemy4.attack, enemy4.power, enemy4.maxPower, enemy4.touchingGround, enemy4.attacking,  enemy4.sy, enemy4.position, enemy4.special);
            if(enemy4.health <= 0) {totalNum--;  oslPlaySound(groan2, 6); enemy4.alive = false; enemy4.Reward(enemy4.id);}
        }
        if(enemy5.alive){
            enemy5.SpriteAnimate(enemy5.image, enemy5.manipulate, enemy5.march, enemy5.position);
            enemy5.Handle(enemy5.image, enemy5.health, enemy5.attack, enemy5.power, enemy5.maxPower, enemy5.touchingGround, enemy5.attacking,  enemy5.sy, enemy5.position, enemy5.special);
            if(enemy5.health <= 0) {totalNum--; oslPlaySound(groan, 6); enemy5.alive = false; enemy5.Reward(enemy5.id);}
        }
        if(enemy6.alive){
            enemy6.SpriteAnimate(enemy6.image, enemy6.manipulate, enemy6.march, enemy6.position);
            enemy6.Handle(enemy6.image, enemy6.health, enemy6.attack, enemy6.power, enemy6.maxPower, enemy6.touchingGround, enemy6.attacking,  enemy6.sy, enemy6.position, enemy6.special);
            if(enemy6.health <= 0) {totalNum--;  oslPlaySound(groan2, 6); enemy6.alive = false; enemy6.Reward(enemy6.id);}
        }
        if(enemy7.alive){
            enemy7.SpriteAnimate(enemy7.image, enemy7.manipulate, enemy7.march, enemy7.position);
            enemy7.Handle(enemy7.image, enemy7.health, enemy7.attack, enemy7.power, enemy7.maxPower, enemy7.touchingGround, enemy7.attacking,  enemy7.sy, enemy7.position, enemy7.special);
            if(enemy7.health <= 0) {totalNum--;  oslPlaySound(groan, 6); enemy7.alive = false; enemy7.Reward(enemy7.id);}
        }
        if(enemy8.alive){
            enemy8.SpriteAnimate(enemy8.image, enemy8.manipulate, enemy8.march, enemy8.position);
            enemy8.Handle(enemy8.image, enemy8.health, enemy8.attack, enemy8.power, enemy8.maxPower, enemy8.touchingGround, enemy8.attacking,  enemy8.sy, enemy8.position, enemy8.special);
            if(enemy8.health <= 0) {totalNum--; oslPlaySound(groan2, 6); enemy8.alive = false; enemy8.Reward(enemy8.id);}
        }
        if(enemy9.alive){
            enemy9.SpriteAnimate(enemy9.image, enemy9.manipulate, enemy9.march, enemy9.position);
            enemy9.Handle(enemy9.image, enemy9.health, enemy9.attack, enemy9.power, enemy9.maxPower, enemy9.touchingGround, enemy9.attacking,  enemy9.sy, enemy9.position, enemy9.special);
            if(enemy9.health <= 0) {totalNum--; oslPlaySound(groan, 6); enemy9.alive = false; enemy9.Reward(enemy9.id);}
        }
        if(enemy10.alive){
            enemy10.SpriteAnimate(enemy10.image, enemy10.manipulate, enemy10.march, enemy10.position);
            enemy10.Handle(enemy10.image, enemy10.health, enemy10.attack, enemy10.power, enemy10.maxPower, enemy10.touchingGround, enemy10.attacking,  enemy10.sy, enemy10.position, enemy10.special);
            if(enemy10.health <= 0) {totalNum--; oslPlaySound(groan2, 6); enemy10.alive = false; enemy10.Reward(enemy10.id);}
        }
        /****************************************handle enemies if they are alive*********************************/
        
    return;
}


void LEVEL::COMPUTER_GENERATED_LEVELS()
{
    /* COMPUTER GENERATOR...THESE LINES OF CODE WILL INFINITELY SPAWN LEVELS...FOREVER */
    if(currentLevel > LAST_LEVEL && spawned == 0)
    {
        //this is the computer generator...needs testing
        spawned = 1;
        
        //spawn some random clouds
        int rcloud1, rcloud2, rcloud3, rcloud4, rcloud5, rcloud6, rcloud7, rcloud8;
        srand((unsigned)time(0)); rcloud1 = (rand()%6)+1;
        srand((unsigned)time(0)); rcloud2 = (rand()%6)+1;
        srand((unsigned)time(0)); rcloud3 = (rand()%6)+1;
        srand((unsigned)time(0)); rcloud4 = (rand()%6)+1;
        srand((unsigned)time(0)); rcloud5 = (rand()%6)+1;
        srand((unsigned)time(0)); rcloud6 = (rand()%6)+1;
        srand((unsigned)time(0)); rcloud7 = (rand()%6)+1;
        srand((unsigned)time(0)); rcloud8 = (rand()%6)+1;
        
        if(rcloud1 == 2){
            if(cloud1 != NULL){oslDeleteImage(cloud1); cloud1 = NULL;}
            cloud1 = oslLoadImageFilePNG((char*)"img/data/cloud.png", OSL_IN_RAM, OSL_PF_5551);
            cloud1->x = 240;
        }
        if(rcloud2 == 2){
            if(cloud2 != NULL){oslDeleteImage(cloud2); cloud2 = NULL;}
            cloud2 = oslLoadImageFilePNG((char*)"img/data/cloud.png", OSL_IN_RAM, OSL_PF_5551);
            cloud2->x = 280;
        }
        if(rcloud3 == 2){
            if(cloud3 != NULL){oslDeleteImage(cloud3); cloud3 = NULL;}
            cloud3 = oslLoadImageFilePNG((char*)"img/data/cloud.png", OSL_IN_RAM, OSL_PF_5551);
            cloud3->x = 210;
        }
        if(rcloud4 == 2){
            if(cloud4 != NULL){oslDeleteImage(cloud4); cloud4 = NULL;}
            cloud4 = oslLoadImageFilePNG((char*)"img/data/cloud.png", OSL_IN_RAM, OSL_PF_5551);
            cloud4->x = 340;
        }
        if(rcloud5 == 2){
            if(cloud5 != NULL){oslDeleteImage(cloud5); cloud5 = NULL;}
            cloud5 = oslLoadImageFilePNG((char*)"img/data/cloud.png", OSL_IN_RAM, OSL_PF_5551);
            cloud5->x = 360;
        }
        if(rcloud6 == 2){
            if(cloud6 != NULL){oslDeleteImage(cloud6); cloud6 = NULL;}
            cloud6 = oslLoadImageFilePNG((char*)"img/data/cloud.png", OSL_IN_RAM, OSL_PF_5551);
            cloud6->x = 350;
        }
        if(rcloud7 == 2){
            if(cloud7 != NULL){oslDeleteImage(cloud7); cloud7 = NULL;}
            cloud7 = oslLoadImageFilePNG((char*)"img/data/cloud.png", OSL_IN_RAM, OSL_PF_5551);
            cloud7->x = 180;
        }
        if(rcloud8 == 2){
            if(cloud8 != NULL){oslDeleteImage(cloud8); cloud8 = NULL;}
            cloud8 = oslLoadImageFilePNG((char*)"img/data/cloud.png", OSL_IN_RAM, OSL_PF_5551);
            cloud8->x = 50;
        }
        
        //r1 = amount of enemies r... = id of enemy
        int NUM_OF_ENEMIES; srand((unsigned)time(0)); NUM_OF_ENEMIES = (rand()%10)+1;
        if(NUM_OF_ENEMIES == 1){
            int r2; srand((unsigned)time(0)); r2 = (rand()%7)+1;
            spawn.SetUpSlot1(r2, 360, 50);
        }
        else if(NUM_OF_ENEMIES == 2){
            int r2; srand((unsigned)time(0)); r2 = (rand()%7)+1;
            spawn.SetUpSlot1(r2, 360, 50);
            int r3; srand((unsigned)time(0)); r3 = (rand()%7)+1;
            spawn.SetUpSlot2(r3, 0, 50);
        }
        else if(NUM_OF_ENEMIES == 3){
            int r2; srand((unsigned)time(0)); r2 = (rand()%7)+1;
            spawn.SetUpSlot1(r2, 360, 50);
            int r3; srand((unsigned)time(0)); r3 = (rand()%7)+1;
            spawn.SetUpSlot2(r3, 0, 50);
            int r4; srand((unsigned)time(0)); r4 = (rand()%7)+1;
            spawn.SetUpSlot3(r4, 426, 50);
        }
        else if(NUM_OF_ENEMIES == 4){
            int r2; srand((unsigned)time(0)); r2 = (rand()%7)+1;
            spawn.SetUpSlot1(r2, 360, 50);
            int r3; srand((unsigned)time(0)); r3 = (rand()%7)+1;
            spawn.SetUpSlot2(r3, 0, 50);
            int r4; srand((unsigned)time(0)); r4 = (rand()%7)+1;
            spawn.SetUpSlot3(r4, 426, 50);
            int r5; srand((unsigned)time(0)); r5 = (rand()%7)+1;
            spawn.SetUpSlot4(r5, 360, 0);
        }
        else if(NUM_OF_ENEMIES == 5){
            int r2; srand((unsigned)time(0)); r2 = (rand()%7)+1;
            spawn.SetUpSlot1(r2, 360, 50);
            int r3; srand((unsigned)time(0)); r3 = (rand()%7)+1;
            spawn.SetUpSlot2(r3, 0, 50);
            int r4; srand((unsigned)time(0)); r4 = (rand()%7)+1;
            spawn.SetUpSlot3(r4, 426, 50);
            int r5; srand((unsigned)time(0)); r5 = (rand()%7)+1;
            spawn.SetUpSlot4(r5, 360, 0);
            int r6; srand((unsigned)time(0)); r6 = (rand()%8)+1;
            spawn.SetUpSlot5(r6, 360, -30);
        }
        else if(NUM_OF_ENEMIES == 6){
            int r2; srand((unsigned)time(0)); r2 = (rand()%8)+1;
            spawn.SetUpSlot1(r2, 360, 50);
            int r3; srand((unsigned)time(0)); r3 = (rand()%8)+1;
            spawn.SetUpSlot2(r3, 0, 50);
            int r4; srand((unsigned)time(0)); r4 = (rand()%8)+1;
            spawn.SetUpSlot3(r4, 426, 50);
            int r5; srand((unsigned)time(0)); r5 = (rand()%8)+1;
            spawn.SetUpSlot4(r5, 360, 0);
            int r6; srand((unsigned)time(0)); r6 = (rand()%8)+1;
            spawn.SetUpSlot5(r6, 360, -30);
            int r7; srand((unsigned)time(0)); r7 = (rand()%8)+1;
            spawn.SetUpSlot6(r7, 0, 50);
        }
        else if(NUM_OF_ENEMIES == 7){
            int r2; srand((unsigned)time(0)); r2 = (rand()%8)+1;
            spawn.SetUpSlot1(r2, 360, 50);
            int r3; srand((unsigned)time(0)); r3 = (rand()%8)+1;
            spawn.SetUpSlot2(r3, 0, 50);
            int r4; srand((unsigned)time(0)); r4 = (rand()%8)+1;
            spawn.SetUpSlot3(r4, 426, 50);
            int r5; srand((unsigned)time(0)); r5 = (rand()%8)+1;
            spawn.SetUpSlot4(r5, 360, 0);
            int r6; srand((unsigned)time(0)); r6 = (rand()%8)+1;
            spawn.SetUpSlot5(r6, 360, -30);
            int r7; srand((unsigned)time(0)); r7 = (rand()%8)+1;
            spawn.SetUpSlot6(r7, 0, 50);
            int r8; srand((unsigned)time(0)); r8 = (rand()%8)+1;
            spawn.SetUpSlot7(r8, 17, -80);
        }
        else if(NUM_OF_ENEMIES == 8){
            int r2; srand((unsigned)time(0)); r2 = (rand()%8)+1;
            spawn.SetUpSlot1(r2, 360, 50);
            int r3; srand((unsigned)time(0)); r3 = (rand()%8)+1;
            spawn.SetUpSlot2(r3, 0, 50);
            int r5; srand((unsigned)time(0)); r5 = (rand()%8)+1;
            spawn.SetUpSlot3(r5, 426, 50);
            int r6; srand((unsigned)time(0)); r6 = (rand()%8)+1;
            spawn.SetUpSlot4(r6, 360, 0);
            int r7; srand((unsigned)time(0)); r7 = (rand()%8)+1;
            spawn.SetUpSlot5(r7, 360, -30);
            int r8; srand((unsigned)time(0)); r8 = (rand()%8)+1;
            spawn.SetUpSlot6(r8, 0, 50);
            int r9; srand((unsigned)time(0)); r9 = (rand()%8)+1;
            spawn.SetUpSlot7(r9, 17, -80);
            int r10; srand((unsigned)time(0)); r10 = (rand()%8)+1;
            spawn.SetUpSlot8(r10, 190, 0);   
        }
        else if(NUM_OF_ENEMIES == 9){
            int r2; srand((unsigned)time(0)); r2 = (rand()%8)+1;
            spawn.SetUpSlot1(r2, 360, 50);
            int r3; srand((unsigned)time(0)); r3 = (rand()%8)+1;
            spawn.SetUpSlot2(r3, 0, 50);
            int r5; srand((unsigned)time(0)); r5 = (rand()%8)+1;
            spawn.SetUpSlot3(r5, 426, 50);
            int r6; srand((unsigned)time(0)); r6 = (rand()%8)+1;
            spawn.SetUpSlot4(r6, 360, 0);
            int r7; srand((unsigned)time(0)); r7 = (rand()%8)+1;
            spawn.SetUpSlot5(r7, 360, -30);
            int r8; srand((unsigned)time(0)); r8 = (rand()%8)+1;
            spawn.SetUpSlot6(r8, 0, 50);
            int r9; srand((unsigned)time(0)); r9 = (rand()%8)+1;
            spawn.SetUpSlot7(r9, 17, -80);
            int r10; srand((unsigned)time(0)); r10 = (rand()%8)+1;
            spawn.SetUpSlot8(r10, 190, 0);  
            int r11; srand((unsigned)time(0)); r11 = (rand()%8)+1;
            spawn.SetUpSlot9(r11, 190, 0);  
        }
        else if(NUM_OF_ENEMIES == 10){
            int r2; srand((unsigned)time(0)); r2 = (rand()%8)+1;
            spawn.SetUpSlot1(r2, 360, 50);
            int r3; srand((unsigned)time(0)); r3 = (rand()%8)+1;
            spawn.SetUpSlot2(r3, 0, 50);
            int r5; srand((unsigned)time(0)); r5 = (rand()%8)+1;
            spawn.SetUpSlot3(r5, 426, 50);
            int r6; srand((unsigned)time(0)); r6 = (rand()%8)+1;
            spawn.SetUpSlot4(r6, 360, 0);
            int r7; srand((unsigned)time(0)); r7 = (rand()%8)+1;
            spawn.SetUpSlot5(r7, 360, -30);
            int r8; srand((unsigned)time(0)); r8 = (rand()%8)+1;
            spawn.SetUpSlot6(r8, 0, 50);
            int r9; srand((unsigned)time(0)); r9 = (rand()%8)+1;
            spawn.SetUpSlot7(r9, 17, -80);
            int r10; srand((unsigned)time(0)); r10 = (rand()%8)+1;
            spawn.SetUpSlot8(r10, 190, 0);   
            int r11; srand((unsigned)time(0)); r11 = (rand()%8)+1;
            spawn.SetUpSlot9(r11, 190, 0); 
            int r12; srand((unsigned)time(0)); r12 = (rand()%8)+1;
            spawn.SetUpSlot10(r12, 190, 0);   
        }
        else oslWarning("ERROR! THE COMPUTER MESSED UP! HOPE YOUR GAME DOES NOT CRASH!!");  
    }
        
    //this moves the game along
    if(totalNum == 0)
    {
        currentLevel++; 
        spawned = 0;
        
        oslStopSound(battle2); oslStopSound(battle3); oslStopSound(battle4); oslStopSound(battle5);
        
        if(currentLevel <= 10){oslPlaySound(battle3, 1);}
        else if(currentLevel > 10 && currentLevel <= 20)  {oslPlaySound(battle2, 1); oslSetSoundLoop(battle2, 1);}
        else if(currentLevel > 20 && currentLevel <= 30)  {oslPlaySound(battle3, 1); oslSetSoundLoop(battle3, 1);}
        else if(currentLevel > 30 && currentLevel <= 40)  {oslPlaySound(battle4, 1); oslSetSoundLoop(battle4, 1);}
        else if(currentLevel > 40 && currentLevel <= 50)  {oslPlaySound(battle5, 1); oslSetSoundLoop(battle5, 1);}
        else if(currentLevel > 50 && currentLevel <= 60)  {oslPlaySound(battle2, 1); oslSetSoundLoop(battle2, 1);}
        else if(currentLevel > 60 && currentLevel <= 70)  {oslPlaySound(battle3, 1); oslSetSoundLoop(battle3, 1);}
        else if(currentLevel > 70 && currentLevel <= 80)  {oslPlaySound(battle4, 1); oslSetSoundLoop(battle4, 1);}
        else if(currentLevel > 80 && currentLevel <= 90)  {oslPlaySound(battle5, 1); oslSetSoundLoop(battle5, 1);}
        else if(currentLevel > 90 && currentLevel <= 100) {oslPlaySound(battle2, 1); oslSetSoundLoop(battle2, 1);}
        else if(currentLevel > 100 && currentLevel <= 110){oslPlaySound(battle3, 1); oslSetSoundLoop(battle3, 1);}
        else if(currentLevel > 110 && currentLevel <= 120){oslPlaySound(battle4, 1); oslSetSoundLoop(battle4, 1);}
        else if(currentLevel > 120 && currentLevel <= 130){oslPlaySound(battle5, 1); oslSetSoundLoop(battle5, 1);}
        else if(currentLevel > 50 && currentLevel <= 60)  {oslPlaySound(battle2, 1); oslSetSoundLoop(battle2, 1);}
        else if(currentLevel > 130 && currentLevel <= 140){oslPlaySound(battle3, 1); oslSetSoundLoop(battle3, 1);}
        else oslPlaySound(battle3, 1);
    }
    
    return;
}
