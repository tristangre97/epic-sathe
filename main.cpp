#include "main.h"

int MAIN_GAME()
{
    //stop menu music
    oslStopSound(menu_music);
    
    //first we have to setup the player for the first time
    if(player.initialBoot){player.SetUp(DUDE); player.initialBoot = false;}
    
    //if its not the first time reset player stats
    else player.SetUp(player.id);
    
    //then set up a level
    player.SpawnLevel(1);
    if(player.lives <= 0)player.lives = 2;
    
    /* main game loop */
    while(!player.quit)
    {
        oslStartDrawing();
        oslSetBkColor(RGBA(0,0,0,0)); 
        oslClearScreen(BLACK);
        oslDrawImage(level);
        if(cloud1 != NULL) oslDrawImageSimple(cloud1); 
        if(cloud2 != NULL) oslDrawImageSimple(cloud2); 
        if(cloud3 != NULL) oslDrawImageSimple(cloud3); 
        if(cloud4 != NULL) oslDrawImageSimple(cloud4); 
        if(cloud5 != NULL) oslDrawImageSimple(cloud5); 
        if(cloud6 != NULL) oslDrawImageSimple(cloud6); 
        if(cloud7 != NULL) oslDrawImageSimple(cloud7); 
        if(cloud8 != NULL) oslDrawImageSimple(cloud8); 
        
        //handle game
        use.UPDATER();
        
        if(currentLevel > LAST_LEVEL && spawned == 0) 
            use.COMPUTER_GENERATED_LEVELS();
        else 
            use.MANUALLY_CODED_LEVELS();
        
        
        //handle player
        player.ReadKeys(player.image);
        player.Handle(player.image);
        
        oslSetTextColor(BLACK); oslPrintf_xy(player.image->x, player.image->y -5, "Hp: %lld", player.health);
        
        oslSetTextColor(BLACK); oslPrintf_xy(5, 5, "LEVEL %i: %i enemies left", currentLevel, totalNum);
        oslSetTextColor(BLACK); oslPrintf_xy(5, 15, "%d lives left", player.lives);
        oslSetTextColor(BLACK); oslPrintf_xy(5, 25, "$%lld money", player.money);
        
        oslDrawImage(player.image);
        
        oslEndDrawing();
        oslSyncFrame();
    }
    
    //end music
    oslStopSound(battle1);
    oslStopSound(battle2);
    oslStopSound(battle3);
    oslStopSound(battle4);
    
    //turn menu music back on
    oslPlaySound(menu_music, 1); 
    oslSetSoundLoop(menu_music, 1);
    
    return 0;
}

int main(int argc, char* argv[])
{
    oslInit(0);
    oslInitGfx(OSL_PF_8888, 1);
    oslInitAudio();
    oslSetQuitOnLoadFailure(1);
    oslSetKeyAutorepeatInit(20);
    oslSetKeyAutorepeatInterval(5);
    oslSetTransparentColor(RGB(255,0,255));
    
    /* load sound files */
    select =     oslLoadSoundFileBGM((char*)"sounds/select.bgm", OSL_FMT_NONE);
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
    
    //start playing menu music
    oslPlaySound(menu_music, 1); oslSetSoundLoop(menu_music, 1);
    
    /* load image files */
    menu_background = oslLoadImageFilePNG((char*)"img/data/menu.png", OSL_IN_RAM, OSL_PF_5551);
    selector = oslLoadImageFilePNG((char*)"img/data/selector.png", OSL_IN_RAM, OSL_PF_5551);  
    
    //Show my logo
    VAUGHN_LOGO();
    
    //set up a menu animation
    PLAYER menuGuy;
    menuGuy.image = menuGuy.SetImage(-1);
    menuGuy.position = STILL_RIGHT;
    oslSetImageTileSize(menuGuy.image,1 * 53,menuGuy.position,53,76);
    menuGuy.image->x = 330;
    menuGuy.image->y = 140;
    
    //unlock two characters
    menu.DUDE_bought = true;
    menu.REPUBLIKEN_bought = true;
    
    for(;;)
	{  
       int menuChoice = 1;
       
	   while (1)
	   {	
		  oslReadKeys();
		
		  if(osl_keys->pressed.down){menuChoice++; oslPlaySound(select, 2);}
		  if(osl_keys->pressed.up)  {menuChoice--; oslPlaySound(select, 2);}
		  if(menuChoice > 4) menuChoice = 1;
          if(menuChoice < 1) menuChoice = 4;
		
		  if(menuChoice == START_GAME){
		    placeSelector(selector, 19,113);
		    if(osl_keys->pressed.cross) {oslPlaySound(select, 2); player.quit = false; MAIN_GAME();}                      
		  }
        
          else if(menuChoice == CUSTOMIZE){
			placeSelector(selector, 19, 149);
			if(osl_keys->pressed.cross){oslPlaySound(select, 2); menu.Customize(); }
		  }	
		
		  else if(menuChoice == CREDITS){
			placeSelector(selector, 19, 191);
			if(osl_keys->pressed.cross){oslPlaySound(select, 2); showCredits();}
		  }
		  
		  else if(menuChoice == EXIT_GAME){
			placeSelector(selector, 19, 228);
			if(osl_keys->pressed.cross){oslPlaySound(select, 2); oslQuit();}
		  }
		  
		  //Moves the sprite in the row that it is in
          menuGuy.manipulate++; if(menuGuy.manipulate > 9) {menuGuy.march++; menuGuy.manipulate = 0;}
          oslSetImageTileSize(menuGuy.image,menuGuy.march * 53,menuGuy.position,53,76);
          if(menuGuy.march == 3) menuGuy.march = 0;
		  
		  oslStartDrawing();
		  oslClearScreen(BLACK);
		  oslDrawImage(menu_background);
          oslDrawImage(selector);
          oslDrawImage(menuGuy.image);
		  oslEndDrawing();
		  oslSyncFrame();		
       }
    }
    
    oslEndGfx();
    sceKernelExitGame();
    
    return 0;
}

void showCredits( void )
{    
     while(1)
     {
    	  oslReadKeys();
    	  if(osl_keys->pressed.circle) {oslPlaySound(select, 2); break;}
    	  
          oslStartDrawing();
          oslClearScreen(BLACK);
          
          oslSetTextColor(RED);
          oslPrintf_xy(5, 15, "Credits: Epic Sathe v0.3");
          oslSetTextColor(WHITE);
          
          oslPrintf_xy(5, 25, "Epic Sathe, an epic game made by V@ughn");
          
          oslSetTextColor(RED);
          oslPrintf_xy(5, 45, "Tools used:");
          oslSetTextColor(WHITE);
          
          oslPrintf_xy(5, 55, "-Dev-C++ 4.9.9.2");
          oslPrintf_xy(5, 65, "-sfxr generator");
          oslPrintf_xy(5, 75, "-photoshop cs5");
          oslPrintf_xy(5, 85, "-oslib + gu of pspsdk");
          
          oslEndDrawing();
          oslSyncFrame();
     }
     
     return;
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

