#include "main.h"

int MAIN_GAME()
{   
    //stop menu music
    oslStopSound(menu_music);
    
    //first we have to setup the player for the first time
    if(player.initialBoot){player.SetUp(DUDE); player.initialBoot = false;}
    
    //if its not the first time reset player stats
    else player.SetUp(player.id);
    player.quit = false;
    
    //then set up a level
    player.SpawnLevel(1);
    if(player.lives <= 0)player.lives = 2;
    
    /* main game loop */
    while(!player.quit)
    {
        oslStartDrawing();
        oslSetBkColor(RGBA(0,0,0,0)); 
        oslClearScreen(BLACK);
        
        //handle game
        use.UPDATER();
        
        if(currentLevel > LAST_LEVEL && spawned == 0) 
            use.COMPUTER_GENERATED_LEVELS();
        else 
            use.MANUALLY_CODED_LEVELS();
        
        
        //handle player
        player.ReadKeys();
        player.Handle();
        
        if(!player.toggle) {
          oslSetTextColor(BLACK); oslPrintf_xy(player.image->x, player.image->y -5, "Hp: %lld", player.health);
          oslSetTextColor(YELLOW); oslPrintf_xy(5, 35, "Power: %lld/%lld", player.power, player.maxPower);
          oslSetTextColor(BLACK); oslPrintf_xy(5, 5, "LEVEL %i: %i enemies left", currentLevel, totalNum);
          oslSetTextColor(BLACK); oslPrintf_xy(5, 15, "%d lives left", player.lives);
          oslSetTextColor(BLACK); oslPrintf_xy(5, 25, "$%lld", player.money);
        }
        
        oslEndDrawing();
        oslSyncFrame();
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
    powerUp = oslLoadSoundFile((char*)"sounds/powerUp.wav", OSL_FMT_NONE);
    error =     oslLoadSoundFileWAV((char*)"sounds/error.wav", OSL_FMT_NONE);
    bought =     oslLoadSoundFileBGM((char*)"sounds/selected.bgm", OSL_FMT_NONE);
    menu_music = oslLoadSoundFileWAV((char*)"sounds/battle1.wav", OSL_FMT_NONE);
    groan =      oslLoadSoundFileBGM((char*)"sounds/groan.bgm", OSL_FMT_NONE);
    groan2 =      oslLoadSoundFileWAV((char*)"sounds/groan2.wav", OSL_FMT_NONE);
    confuse =    oslLoadSoundFileBGM((char*)"sounds/confuse.bgm", OSL_FMT_NONE);
    stun =       oslLoadSoundFileBGM((char*)"sounds/stun.bgm", OSL_FMT_NONE);
    powerup =    oslLoadSoundFileBGM((char*)"sounds/powerup.bgm", OSL_FMT_NONE);
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


void pauseGame( void )
{
    //oslPauseSound(gameMusic, 1);
    
    //load and position pause picture
    OSL_IMAGE * pause_pic = oslLoadImageFile((char*)"img/data/paused.png", OSL_IN_RAM, OSL_PF_5551);
    pause_pic->x = 180;
    pause_pic->y = 100;
    
    //play a sound effect
    oslPlaySound(soft_punch, 7);
    
    //draw here to remove flicker
    oslStartDrawing();
    oslDrawImage(player.image);
    oslDrawImage(pause_pic);
    oslEndDrawing();
    oslSyncFrame();
        
    while(1)
    {
        oslReadKeys();
        if(osl_keys->pressed.start){break;}
        else if(osl_keys->pressed.select){player.quit = true; break;}
        else if(osl_keys->pressed.R){menu.Customize(); break;}
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

