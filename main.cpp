#include "main.h"

int MAIN_GAME(const int MODE)
{   
    //stop menu music
    oslStopSound(menu_music);
    
    //load level background
    if(level != NULL){oslDeleteImage(level); level = NULL;}
    level = oslLoadImageFilePNG((char*)"img/data/lx1.png", OSL_IN_RAM, OSL_PF_5551);
    
    //first we have to setup the player for the first time
    if(player.initialBoot){player.SetUp(DUDE); player.initialBoot = false;}
    
    //if its not the first time reset player stats
    else player.SetUp(player.id);
    
    //reset lives
    if(player.lives <= 0)player.lives = 2;
    
    //preparte powerups
    ITEM powerup;
    powerup.image = oslLoadImageFilePNG((char*)"img/data/powerup.png", OSL_IN_RAM, OSL_PF_5551);
    powerup.collected = oslLoadSoundFileWAV((char*)"sounds/powerup.wav", OSL_FMT_NONE);
    
    /* solo mode game loop */
    if(MODE == 0)
    {
      while(!player.quit)
      {
        oslStartDrawing();
        oslSetBkColor(RGBA(0,0,0,0)); 
        oslClearScreen(BLACK);
        
        //update game
        use.UPDATER();
        
        if(currentLevel > LAST_LEVEL && spawned == 0) 
            use.COMPUTER_GENERATED_LEVELS();
        else 
            use.MANUALLY_CODED_LEVELS();
        
        
        //update player
        player.ReadKeys(0, 0);
        player.Update();
        if(!player.toggle) {
          oslSetTextColor(GREEN); oslPrintf_xy(player.image->x, player.image->y -10, "Hp: %lld", player.health);
          oslSetTextColor(BLACK); oslPrintf_xy(5, 5, "LEVEL %i: %i enemies left", currentLevel, totalNum);
          oslSetTextColor(BLACK); oslPrintf_xy(5, 35, "%d lives", player.lives);
          oslSetTextColor(BLACK); oslPrintf_xy(5, 25, "$%lld", player.money);
        }
        if(use.nextLevel) 
        {
            //play cool effect for next level
            use.q++;
            if(use.q > 5){use.i++; use.q = 0;}
            if(use.i > 2)oslSetTextColor(YELLOW);
            if(use.i > 4)oslSetTextColor(LIGHTGRAY);
            if(use.i > 6)oslSetTextColor(BLACK);
            if(use.i > 8)oslSetTextColor(AZURE);
            if(use.i > 10)oslSetTextColor(VIOLET);
            if(use.i > 12)oslSetTextColor(ROSE);
            if(use.i > 14)oslSetTextColor(ORANGE);
            if(use.i > 16)oslSetTextColor(CHARTREUSE);
            if(use.i > 18)oslSetTextColor(SPRING_GREEN);
            if(use.i > 20)oslSetTextColor(CYAN);
            if(use.i > 22)oslSetTextColor(MAGENTA);
            if(use.i > 24)oslSetTextColor(BLUE);
            if(use.i > 26)oslSetTextColor(WHITE);
            if(use.i > 28)oslSetTextColor(RED);
            if(use.i > 30){use.nextLevel = false; use.i = 0; use.q = 0;}
            oslPrintf_xy(player.image->x, (player.image->y - 10) - use.i, "NEXT LEVEL");
        }
        
        //update items
        powerup.Update();

        oslEndDrawing();
        oslSyncFrame();
      }
    }
    
    /* boss mode game loop */
    else if(MODE == 1)
    {
        while(!player.quit)
        {
           oslStartDrawing();
           oslSetBkColor(RGBA(0,0,0,0)); 
        
           //update game
           use.BOSS_LEVELS();
        
           //update player
           player.ReadKeys(0, 0);
           player.Update();
           if(!player.toggle) {
             oslSetTextColor(GREEN); oslPrintf_xy(player.image->x, player.image->y -10, "Hp: %lld", player.health);
             oslSetTextColor(BLACK); oslPrintf_xy(5, 5, "LEVEL %i: %i enemies left", currentLevel, totalNum);
             oslSetTextColor(BLACK); oslPrintf_xy(5, 35, "%d lives", player.lives);
             oslSetTextColor(BLACK); oslPrintf_xy(5, 25, "$%lld", player.money);
           }
         }
    }
    
    /* stop any possible playing music */
    oslStopSound(battle1); 
    oslStopSound(battle2); 
    oslStopSound(battle3); 
    oslStopSound(battle4); 
    oslStopSound(battle5);
    
    //turn menu music back on
    oslPlaySound(menu_music, 1); 
    oslSetSoundLoop(menu_music, 1);
    
    //reset
    player.quit = false;
    
    return 0;
}

int main(int argc, char* argv[])
{
    /* init graphics and sound library */
    oslInit(0);
    oslInitGfx(OSL_PF_8888, 1);
    oslInitAudio();
    oslSetQuitOnLoadFailure(1);
    oslSetKeyAutorepeatInit(20);
    oslSetKeyAutorepeatInterval(5);
    oslSetTransparentColor(RGB(255,0,255));
    
    /* load sound files */
    select =     oslLoadSoundFileBGM((char*)"sounds/select.bgm", OSL_FMT_NONE);
    error =     oslLoadSoundFileWAV((char*)"sounds/error.wav", OSL_FMT_NONE);
    nextLevelSound =     oslLoadSoundFileWAV((char*)"sounds/nextLevel.wav", OSL_FMT_NONE);
    bought =     oslLoadSoundFileBGM((char*)"sounds/selected.bgm", OSL_FMT_NONE);
    menu_music = oslLoadSoundFileWAV((char*)"sounds/battle1.wav", OSL_FMT_NONE);
    groan =      oslLoadSoundFileBGM((char*)"sounds/groan.bgm", OSL_FMT_NONE);
    groan2 =      oslLoadSoundFileWAV((char*)"sounds/groan2.wav", OSL_FMT_NONE);
    confuse =    oslLoadSoundFileBGM((char*)"sounds/confuse.bgm", OSL_FMT_NONE);
    stun =       oslLoadSoundFileBGM((char*)"sounds/stun.bgm", OSL_FMT_NONE);
    smashFist =  oslLoadSoundFileBGM((char*)"sounds/smashFist.bgm", OSL_FMT_NONE);
    hard_punch = oslLoadSoundFileBGM((char*)"sounds/hard punch.bgm", OSL_FMT_NONE);
    soft_punch = oslLoadSoundFileBGM((char*)"sounds/soft punch.bgm", OSL_FMT_NONE);
    punch1 =     oslLoadSoundFileBGM((char*)"sounds/punch1.bgm", OSL_FMT_NONE);
    punch2 =     oslLoadSoundFileBGM((char*)"sounds/punch2.bgm", OSL_FMT_NONE);
    battle1 =    oslLoadSoundFileWAV((char*)"sounds/battle1.wav", OSL_FMT_NONE);
    battle2 =    oslLoadSoundFileWAV((char*)"sounds/battle2.wav", OSL_FMT_NONE);
    battle3 =    oslLoadSoundFileWAV((char*)"sounds/battle3.wav", OSL_FMT_NONE);
    battle4 =    oslLoadSoundFileWAV((char*)"sounds/battle4.wav", OSL_FMT_NONE);
    battle5 =    oslLoadSoundFileWAV((char*)"sounds/battle5.wav", OSL_FMT_NONE);
    
    //start playing menu music
    oslPlaySound(menu_music, 1); 
    oslSetSoundLoop(menu_music, 1);

    //Show my logo
    VAUGHN_LOGO();
    
    //unlock two characters
    menu.DUDE_bought = true;
    menu.REPUBLIKEN_bought = true;
    
    int status = SHOW_MAIN_MENU;
    
    while(1) {  
       if(status == SHOW_MAIN_MENU) status = menu.MainMenu();
       
       else if(status == SHOW_SECOND_MENU) status = menu.SecondaryMenu();
       
       else if(status == EXIT) break;
    }
    
    oslEndGfx();
    sceKernelExitGame();
    
    return 0;
}

void PauseGame( void )
{
    //oslPauseSound(gameMusic, 1);
    
    //load and position pause picture
    IMAGE * pause_pic = oslLoadImageFilePNG((char*)"img/data/paused.png", OSL_IN_RAM, OSL_PF_5551);
    IMAGE * second_pic = oslLoadImageFilePNG((char*)"img/data/paused2.png", OSL_IN_RAM, OSL_PF_5551);
    pause_pic->x = 180;
    pause_pic->y = 90;
    second_pic->x = 180;
    second_pic->y = 190;
    
    //play a sound effect
    oslPlaySound(soft_punch, 7);
    
    //draw here to remove flicker
    oslStartDrawing();
    oslDrawImage(player.image);
    oslDrawImage(pause_pic);
    oslDrawImage(second_pic);
    oslEndDrawing();
    oslSyncFrame();
        
    while(1)
    {
        oslReadKeys();
        if(osl_keys->pressed.start){break;}
        else if(osl_keys->pressed.select){player.quit = true; break;}
        else if(osl_keys->pressed.R){menu.Customize(); break;}
        else if(osl_keys->pressed.L){
            SaveGame();
            oslStartDrawing();
            oslDrawImage(player.image);
            oslDrawImage(pause_pic);
            oslDrawImage(second_pic);
            oslEndDrawing();
            oslSyncFrame();}
    }
    
    if(pause_pic != NULL){oslDeleteImage(pause_pic); pause_pic = NULL;}

    return;
}

//my custom logo ;)
void VAUGHN_LOGO( void )
{
     OSL_IMAGE *logo;
     logo = oslLoadImageFilePNG((char*)"img/data/logo.png", OSL_IN_RAM, OSL_PF_5551);
     
     oslStartDrawing();
     oslDrawImage(logo);
     oslEndDrawing();
     oslSyncFrame();
     
     Wait;
     oslDeleteImage(logo);
     
}

int collision(OSL_IMAGE *img1,float img1posX, float img1posY, OSL_IMAGE *img2, float img2posX, float img2posY ) 
{
   int collisio;
   collisio = 0;
   float img1width  = img1->stretchX;
   float img1height = img1->stretchY;
   float img2width  = img2->stretchX;
   float img2height = img2->stretchY;
   
   if ((img1posX + img1width > img2posX) &&
       (img1posX < img2posX + img2width) &&
       (img1posY + img1height > img2posY) &&
       (img1posY < img2posY + img2height) ) 
{
         collisio = 1;               
   }     
   return collisio;
}

