/**
 * class CONTROLLER ~V@ughn
 * ------------------------
 * ->handles the levels (spawns and updates clouds/background/enemies
 *
 * @virtual void BOSS_LEVELS(bool &quit) - updates a boss
 * @virtual void MANUALLY_CODED_LEVELS() - levels manually coded by yours truly
 * @virtual void COMPUTER_GENERATED_LEVELS() - infinitely creates levels
 * @virtual void UPDATER() - updates enemies/levels/clouds
 *
 */
class CONTROLLER 
{
    public:
        
        //properties
        bool nextLevel;
        bool startedBossBattle;
        int spawned;
        int currentLevel;
        int currentBossLevel;
        int trackLevel;
        int i;
        int q;

        //images
        IMAGE * cloud1;
        IMAGE * cloud2;
        IMAGE * cloud3;
        IMAGE * cloud4;
        IMAGE * cloud5;
        IMAGE * cloud6;
        IMAGE * cloud7;
        IMAGE * cloud8;
        IMAGE * level;
        
        //sounds
        SOUND * nextLevelSound;
        SOUND * battle1;
        SOUND * battle2;
        SOUND * battle3;
        SOUND * battle4;
        SOUND * battle5;
        
        CONTROLLER();
        ~CONTROLLER();
        
        //behaviors
        virtual void BOSS_LEVELS(bool &quit);
        virtual void MANUALLY_CODED_LEVELS();
        virtual void COMPUTER_GENERATED_LEVELS();
        virtual void UPDATER();
        
    private:
        
}use;

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
//CONTROLLER methods://///////////////////////////////////////////////////////////////////////////

void CONTROLLER::BOSS_LEVELS(bool &quit)
{
    oslDrawImage(level);
    
    if(!startedBossBattle){
        //choose boss
		boss.id = menu.BossMenu(use.currentBossLevel, use.trackLevel);
        quit = true;
        return;
        
        //set up boss
        boss.attack =    boss.SetAttack(boss.id);
        boss.maxPower =  boss.SetPower(boss.id);
        boss.jumpHeight =boss.SetJumpHeight(boss.id);
        boss.alive = true;
        if(boss.image != NULL){oslDeleteImage(boss.image); boss.image = NULL;}
        boss.image = boss.SetImage(boss.id);
        boss.image->x = 380;
        boss.image->y = 50;
        boss.waitToAttack = 250;
        
        //add extra health to make it more "boss" like
        boss.health =    boss.SetHealth(boss.id);
        boss.health *= 3;
        boss.maxHealth = boss.health;
        
        startedBossBattle = true;
    }
    
    if(boss.alive)boss.UpdateEnemy();
    if(boss.health <= 0){
        startedBossBattle = false;
        if(trackLevel > currentBossLevel)currentBossLevel++;
        boss.alive = false;
    }
    
    return;
}


void CONTROLLER::MANUALLY_CODED_LEVELS()
{   
    if(currentLevel == 1 && spawned == 0){
        spawned = 1;
        spawn.SetUpEnemy(DUDE, 360, 50);   
    }
    else if(currentLevel == 2 && spawned == 0){
        spawned = 1;
        spawn.SetUpEnemy(DUDE, 360, 50);
        spawn.SetUpEnemy(REPUBLIKEN, 0, 50);
    }
    else if(currentLevel == 3 && spawned == 0){
        spawned = 1;
        spawn.SetUpEnemy(DUDE, 360, 50);
        spawn.SetUpEnemy(DUDE, -2, 50);
    }
    else if(currentLevel == 4 && spawned == 0){
        spawned = 1;
        spawn.SetUpEnemy(REPUBLIKEN, 360, 50);
        spawn.SetUpEnemy(REPUBLIKEN, 0, 50);
        spawn.SetUpEnemy(REPUBLIKEN, 426, 50);
        spawn.SetUpEnemy(REPUBLIKEN, 360, 0);
        spawn.SetUpEnemy(REPUBLIKEN, 360, -30);
    }
    else if(currentLevel == 5 && spawned == 0){
        spawned = 1;
        spawn.SetUpEnemy(DUDE, 360, 50);
        spawn.SetUpEnemy(DUDE, 426, 50);
    }
    else if(currentLevel == 6 && spawned == 0){
        spawned = 1;
        spawn.SetUpEnemy(DUDE, 360, 50);
        spawn.SetUpEnemy(REPUBLIKEN, 426, 50);
        spawn.SetUpEnemy(DUDE, 360, 0);
        spawn.SetUpEnemy(REPUBLIKEN, 360, -30);
    }
    else if(currentLevel == 7 && spawned == 0){
        spawned = 1;
        spawn.SetUpEnemy(DUDE, 360, 50);
    }
    else if(currentLevel == 8 && spawned == 0){
        spawned = 1;
        spawn.SetUpEnemy(DUDE, 360, 50);
        spawn.SetUpEnemy(DUDE, 0, 50);
        spawn.SetUpEnemy(DUDE, 426, 50);
        spawn.SetUpEnemy(DUDE, 360, 0);
        spawn.SetUpEnemy(DUDE, 360, -30);
        spawn.SetUpEnemy(DUDE, 0, 50);
        spawn.SetUpEnemy(DUDE, 17, -80);
        spawn.SetUpEnemy(REPUBLIKEN, 190, 0);
    }
    
    //this moves the game along
    if(totalNum == 0)
    {   
        /* set game to next level */
        currentLevel++; 
        spawned = 0;
        nextLevel = true;
        oslStopSound(nextLevelSound);
        oslPlaySound(nextLevelSound, 5);
            
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

void CONTROLLER::UPDATER()
{
	/* draw/update level */
	if(!level) level = oslLoadImageFilePNG((char*)"img/data/lx1.png", OSL_IN_RAM, OSL_PF_5551);
	oslDrawImage(level);

    /* update clouds */
    if(cloud1 != NULL)
    {
        cloud1->y = -5;
        cloud1->x++;
        if(cloud1->x > 500) cloud1->x = -110;
    }
    if(cloud2 != NULL)
    {
        cloud2->y = 5;
        cloud2->x++;
        if(cloud2->x > 500) cloud2->x = -110;
    }
    if(cloud3 != NULL)
    {
        cloud3->y = 0;
        cloud3->x++;
        if(cloud3->x > 500) cloud3->x = -110;
    }
    if(cloud4 != NULL)
    {
        cloud4->y = -10;
        cloud4->x++;
        if(cloud4->x > 500) cloud4->x = -110;
    }
    if(cloud5 != NULL)
    {
        cloud5->y = 0;
        cloud5->x++;
        if(cloud5->x > 500) cloud5->x = -110;
    }
    if(cloud6 != NULL)
    {
        cloud6->y = 10;
        cloud6->x++;
        if(cloud6->x > 500) cloud6->x = -110;
    }
    if(cloud7 != NULL)
    {
        cloud7->y = 20;
        cloud7->x++;
        if(cloud7->x > 500) cloud7->x = -110;
    }
    if(cloud8 != NULL)
    {
        cloud8->y = -3;
        cloud8->x++;
        if(cloud8->x > 500) cloud8->x = -110;
    }
 
	//draw clouds
    if(cloud1 != NULL) oslDrawImageSimple(cloud1); 
    if(cloud2 != NULL) oslDrawImageSimple(cloud2); 
    if(cloud3 != NULL) oslDrawImageSimple(cloud3); 
    if(cloud4 != NULL) oslDrawImageSimple(cloud4); 
    if(cloud5 != NULL) oslDrawImageSimple(cloud5); 
    if(cloud6 != NULL) oslDrawImageSimple(cloud6); 
    if(cloud7 != NULL) oslDrawImageSimple(cloud7); 
    if(cloud8 != NULL) oslDrawImageSimple(cloud8); 

	//update all enemies
	for(int i = 0; i < MAX_ENEMIES; i++)
	{
      if(enemy[i].alive)
		  enemy[i].UpdateEnemy();

        if(enemy[i].health <= 0 && enemy[i].alive) {
			enemy[i].Reward(enemy[i].id, player.money);
			enemy[i].alive = false;
        }
	}

    return;
}


void CONTROLLER::COMPUTER_GENERATED_LEVELS()
{
    /* COMPUTER GENERATOR...THESE LINES OF CODE WILL INFINITELY SPAWN LEVELS...FOREVER */
    if(currentLevel > LAST_LEVEL && spawned == 0)
    {
        //reset
        spawned = 1;
        nextLevel = true;
        oslStopSound(nextLevelSound);
        oslPlaySound(nextLevelSound, 5);
            
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
            int r2; srand((unsigned)time(0)); r2 = (rand()%10)+1;
            spawn.SetUpEnemy(r2, 360, 50);
        }
        else if(NUM_OF_ENEMIES == 2){
            int r2; srand((unsigned)time(0)); r2 = (rand()%9)+1;
            spawn.SetUpEnemy(r2, 360, 50);
            int r3; srand((unsigned)time(0)); r3 = (rand()%7)+1;
            spawn.SetUpEnemy(r3, 0, 50);
        }
        else if(NUM_OF_ENEMIES == 3){
            int r2; srand((unsigned)time(0)); r2 = (rand()%9)+1;
            spawn.SetUpEnemy(r2, 360, 50);
            int r3; srand((unsigned)time(0)); r3 = (rand()%9)+1;
            spawn.SetUpEnemy(r3, 0, 50);
            int r4; srand((unsigned)time(0)); r4 = (rand()%9)+1;
            spawn.SetUpEnemy(r4, 426, 50);
        }
        else if(NUM_OF_ENEMIES == 4){
            int r2; srand((unsigned)time(0)); r2 = (rand()%9)+1;
            spawn.SetUpEnemy(r2, 360, 50);
            int r3; srand((unsigned)time(0)); r3 = (rand()%9)+1;
            spawn.SetUpEnemy(r3, 0, 50);
            int r4; srand((unsigned)time(0)); r4 = (rand()%9)+1;
            spawn.SetUpEnemy(r4, 426, 50);
            int r5; srand((unsigned)time(0)); r5 = (rand()%9)+1;
            spawn.SetUpEnemy(r5, 360, 0);
        }
        else if(NUM_OF_ENEMIES == 5){
            int r2; srand((unsigned)time(0)); r2 = (rand()%9)+1;
            spawn.SetUpEnemy(r2, 360, 50);
            int r3; srand((unsigned)time(0)); r3 = (rand()%9)+1;
            spawn.SetUpEnemy(r3, 0, 50);
            int r4; srand((unsigned)time(0)); r4 = (rand()%7)+1;
            spawn.SetUpEnemy(r4, 426, 50);
            int r5; srand((unsigned)time(0)); r5 = (rand()%9)+1;
            spawn.SetUpEnemy(r5, 360, 0);
            int r6; srand((unsigned)time(0)); r6 = (rand()%8)+1;
            spawn.SetUpEnemy(r6, 360, -30);
        }
        else if(NUM_OF_ENEMIES == 6){
            int r2; srand((unsigned)time(0)); r2 = (rand()%9)+1;
            spawn.SetUpEnemy(r2, 360, 50);
            int r3; srand((unsigned)time(0)); r3 = (rand()%9)+1;
            spawn.SetUpEnemy(r3, 0, 50);
            int r4; srand((unsigned)time(0)); r4 = (rand()%9)+1;
            spawn.SetUpEnemy(r4, 426, 50);
            int r5; srand((unsigned)time(0)); r5 = (rand()%8)+1;
            spawn.SetUpEnemy(r5, 360, 0);
            int r6; srand((unsigned)time(0)); r6 = (rand()%8)+1;
            spawn.SetUpEnemy(r6, 360, -30);
            int r7; srand((unsigned)time(0)); r7 = (rand()%8)+1;
            spawn.SetUpEnemy(r7, 0, 50);
        }
        else if(NUM_OF_ENEMIES == 7){
            int r2; srand((unsigned)time(0)); r2 = (rand()%9)+1;
            spawn.SetUpEnemy(r2, 360, 50);
            int r3; srand((unsigned)time(0)); r3 = (rand()%8)+1;
            spawn.SetUpEnemy(r3, 0, 50);
            int r4; srand((unsigned)time(0)); r4 = (rand()%9)+1;
            spawn.SetUpEnemy(r4, 426, 50);
            int r5; srand((unsigned)time(0)); r5 = (rand()%8)+1;
            spawn.SetUpEnemy(r5, 360, 0);
            int r6; srand((unsigned)time(0)); r6 = (rand()%9)+1;
            spawn.SetUpEnemy(r6, 360, -30);
            int r7; srand((unsigned)time(0)); r7 = (rand()%8)+1;
            spawn.SetUpEnemy(r7, 0, 50);
            int r8; srand((unsigned)time(0)); r8 = (rand()%9)+1;
            spawn.SetUpEnemy(r8, 17, -80);
        }
        else if(NUM_OF_ENEMIES == 8){
            int r2; srand((unsigned)time(0)); r2 = (rand()%15)+1;
            spawn.SetUpEnemy(r2, 360, 50);
            int r3; srand((unsigned)time(0)); r3 = (rand()%8)+1;
            spawn.SetUpEnemy(r3, 0, 50);
            int r5; srand((unsigned)time(0)); r5 = (rand()%8)+1;
            spawn.SetUpEnemy(r5, 426, 50);
            int r6; srand((unsigned)time(0)); r6 = (rand()%9)+1;
            spawn.SetUpEnemy(r6, 360, 0);
            int r7; srand((unsigned)time(0)); r7 = (rand()%8)+1;
            spawn.SetUpEnemy(r7, 360, -30);
            int r8; srand((unsigned)time(0)); r8 = (rand()%9)+1;
            spawn.SetUpEnemy(r8, 0, 50);
            int r9; srand((unsigned)time(0)); r9 = (rand()%8)+1;
            spawn.SetUpEnemy(r9, 17, -80);
            int r10; srand((unsigned)time(0)); r10 = (rand()%9)+1;
            spawn.SetUpEnemy(r10, 190, 0);   
        }
        else if(NUM_OF_ENEMIES == 9){
            int r2; srand((unsigned)time(0)); r2 = (rand()%8)+1;
            spawn.SetUpEnemy(r2, 360, 50);
            int r3; srand((unsigned)time(0)); r3 = (rand()%8)+1;
            spawn.SetUpEnemy(r3, 0, 50);
            int r5; srand((unsigned)time(0)); r5 = (rand()%8)+1;
            spawn.SetUpEnemy(r5, 426, 50);
            int r6; srand((unsigned)time(0)); r6 = (rand()%9)+1;
            spawn.SetUpEnemy(r6, 360, 0);
            int r7; srand((unsigned)time(0)); r7 = (rand()%9)+1;
            spawn.SetUpEnemy(r7, 360, -30);
            int r8; srand((unsigned)time(0)); r8 = (rand()%8)+1;
            spawn.SetUpEnemy(r8, 0, 50);
            int r9; srand((unsigned)time(0)); r9 = (rand()%8)+1;
            spawn.SetUpEnemy(r9, 17, -80);
            int r10; srand((unsigned)time(0)); r10 = (rand()%8)+1;
            spawn.SetUpEnemy(r10, 190, 0);  
            int r11; srand((unsigned)time(0)); r11 = (rand()%9)+1;
            spawn.SetUpEnemy(r11, 190, 0);  
        }
        else if(NUM_OF_ENEMIES == 10){
            int r2; srand((unsigned)time(0)); r2 = (rand()%9)+1;
            spawn.SetUpEnemy(r2, 360, 50);
            int r3; srand((unsigned)time(0)); r3 = (rand()%9)+1;
            spawn.SetUpEnemy(r3, 0, 50);
            int r5; srand((unsigned)time(0)); r5 = (rand()%9)+1;
            spawn.SetUpEnemy(r5, 426, 50);
            int r6; srand((unsigned)time(0)); r6 = (rand()%9)+1;
            spawn.SetUpEnemy(r6, 360, 0);
            int r7; srand((unsigned)time(0)); r7 = (rand()%9)+1;
            spawn.SetUpEnemy(r7, 360, -30);
            int r8; srand((unsigned)time(0)); r8 = (rand()%9)+1;
            spawn.SetUpEnemy(r8, 0, 50);
            int r9; srand((unsigned)time(0)); r9 = (rand()%9)+1;
            spawn.SetUpEnemy(r9, 17, -80);
            int r10; srand((unsigned)time(0)); r10 = (rand()%9)+1;
            spawn.SetUpEnemy(r10, 190, 0);   
            int r11; srand((unsigned)time(0)); r11 = (rand()%9)+1;
            spawn.SetUpEnemy(r11, 190, 0); 
            int r12; srand((unsigned)time(0)); r12 = (rand()%9)+1;
            spawn.SetUpEnemy(r12, 190, 0);   
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

CONTROLLER::CONTROLLER()
{ 
    currentLevel = 1; 
    currentBossLevel = 1; 
	trackLevel = 1;
    nextLevel = false;
    startedBossBattle = false;
    spawned = 0;
    
    return;
}

CONTROLLER::~CONTROLLER()
{     
    return;
}
