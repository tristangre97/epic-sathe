#include <oslib/oslib.h>
#include <pspkernel.h>
#include <vector>
#include <math.h>

/*********
 Build Id
**********/
const char * BUILD_ID = (char*)"v0.51";

/*******************************************************
 MAX number of enemies that can exist at one time
(WARNING the bigger value the slower the game becomes)
********************************************************/
const int MAX_ENEMIES = 20;

PSP_MODULE_INFO("Epic Sathe", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);
PSP_HEAP_SIZE_KB(-1024);

#include "main.h"


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
    menu_music = oslLoadSoundFileWAV((char*)"sounds/battle1.wav", OSL_FMT_NONE);
	jump = oslLoadSoundFileWAV((char*)"sounds/jump.wav", OSL_FMT_NONE);
    confuse = oslLoadSoundFileBGM((char*)"sounds/confuse.bgm", OSL_FMT_NONE);
    stun = oslLoadSoundFileBGM((char*)"sounds/stun.bgm", OSL_FMT_NONE);
    smashFist = oslLoadSoundFileBGM((char*)"sounds/smashFist.bgm", OSL_FMT_NONE);
    hard_punch = oslLoadSoundFileBGM((char*)"sounds/hard punch.bgm", OSL_FMT_NONE);
    soft_punch = oslLoadSoundFileBGM((char*)"sounds/soft punch.bgm", OSL_FMT_NONE);
    punch1 = oslLoadSoundFileBGM((char*)"sounds/punch1.bgm", OSL_FMT_NONE);
    punch2 = oslLoadSoundFileBGM((char*)"sounds/punch2.bgm", OSL_FMT_NONE);
	groan = oslLoadSoundFileBGM((char*)"sounds/groan.bgm", OSL_FMT_NONE);
    groan2 = oslLoadSoundFileWAV((char*)"sounds/groan2.wav", OSL_FMT_NONE);
    
    /* start playing menu music */
    oslPlaySound(menu_music, 1); 
    oslSetSoundLoop(menu_music, 1);
    
    /* Show V@ughn's logo */
    VAUGHN_LOGO();
    
    /* load use::CONTROLLER files */
    use.nextLevelSound = oslLoadSoundFileWAV((char*)"sounds/nextLevel.wav", OSL_FMT_NONE);
    use.battle1 = oslLoadSoundFileWAV((char*)"sounds/battle1.wav", OSL_FMT_NONE);
    use.battle2 = oslLoadSoundFileWAV((char*)"sounds/battle2.wav", OSL_FMT_NONE);
    use.battle3 = oslLoadSoundFileWAV((char*)"sounds/battle3.wav", OSL_FMT_NONE);
    use.battle4 = oslLoadSoundFileWAV((char*)"sounds/battle4.wav", OSL_FMT_NONE);
    use.battle5 = oslLoadSoundFileWAV((char*)"sounds/battle5.wav", OSL_FMT_NONE);
    use.level = oslLoadImageFilePNG((char*)"img/data/lx1.png", OSL_IN_RAM, OSL_PF_5551);
    
    /* load menu::MENU files */
    menu.select = oslLoadSoundFileBGM((char*)"sounds/select.bgm", OSL_FMT_NONE);
    menu.error = oslLoadSoundFileWAV((char*)"sounds/error.wav", OSL_FMT_NONE);
    menu.bought = oslLoadSoundFileBGM((char*)"sounds/selected.bgm", OSL_FMT_NONE);
    
	/* load fonts */
    oslIntraFontInit(INTRAFONT_CACHE_ALL | INTRAFONT_STRING_UTF8);
    ltn = oslLoadFontFile("flash0:/font/ltn0.pgf");
	oslIntraFontSetStyle(ltn, 1.0f,WHITE,WHITE,INTRAFONT_ALIGN_LEFT);
	oslSetFont(ltn);

    /* by default unlock two characters */
    menu.DUDE_bought = true;
    menu.REPUBLIKEN_bought = true;
    
    static int status = SHOW_MAIN_MENU;
   
    while(1){
	  if(status == SHOW_MAIN_MENU) status = menu.MainMenu();
       
	  if(status ==  SHOW_SECOND_MENU) status = menu.SecondaryMenu();
       
	  if(status ==  EXIT) break;
    }
    
    oslEndGfx();
    sceKernelExitGame();
    
    return 0;
}

int MAIN_GAME(const int MODE)
{   
    /* stop menu music */
    oslStopSound(menu_music);

	/* setup player */
    if(player.initialBoot){player.SetUp(DUDE); player.initialBoot = false;}
    else player.SetUp(player.id);
    if(player.lives <= 0)player.lives = 2;

    /* create powerups */
    ITEM powerup;
    powerup.missed = oslLoadSoundFileWAV((char*)"sounds/error.wav", OSL_FMT_NONE);
    powerup.image = oslLoadImageFilePNG((char*)"img/data/powerup.png", OSL_IN_RAM, OSL_PF_5551);
    powerup.collected = oslLoadSoundFileWAV((char*)"sounds/powerup.wav", OSL_FMT_NONE);

    while(!player.quit)
    {
      oslStartDrawing();
      oslSetBkColor(RGBA(0,0,0,0)); 
      oslClearScreen(BLACK);
    
      //update game
      use.UPDATER();
      
      //update game type
      if(MODE == 0)
      {
        if(use.currentLevel > LAST_LEVEL && use.spawned == 0) 
            use.COMPUTER_GENERATED_LEVELS();
        else 
            use.MANUALLY_CODED_LEVELS();
      }
      else if(MODE == 1)
        use.BOSS_LEVELS(player.quit);
         
      //update player
      player.UpdatePlayer(0, 0);
      if(!player.toggle) {
          oslSetTextColor(GREEN); oslPrintf_xy(player.image->x, player.image->y -10, "Hp: %lld", player.health);
          oslSetTextColor(WHITE); oslPrintf_xy(5, 5, "LEVEL %i: %i enemies left", use.currentLevel, totalNum);
          oslSetTextColor(WHITE); oslPrintf_xy(5, 35, "%d lives", player.lives);
          oslSetTextColor(WHITE); oslPrintf_xy(5, 25, "$%lld", player.money);
      }
      
      if(use.nextLevel) {
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
    powerup.UpdateItem(use.level);

    oslEndDrawing();
    oslSyncFrame();
  }
    
  //turn menu music back on
  oslPlaySound(menu_music, 1); 
  oslSetSoundLoop(menu_music, 1);
  
  player.quit = false;
  if(powerup.image != NULL)oslDeleteImage(powerup.image);
  if(powerup.collected != NULL)oslDeleteSound(powerup.collected);
  if(powerup.missed != NULL){oslStopSound(powerup.missed); oslDeleteSound(powerup.missed);}
    
  return 0;
}

//The client is connected and can send data:
void clientConnected(struct remotePsp *aPsp)
{
    //adhoc game starts here
    //stop menu music
    oslStopSound(menu_music);
    
    //create powerups
    ITEM powerup;
    
    //first we have to setup the player for the first time
    if(player.initialBoot){player.SetUp(DUDE); player.initialBoot = false;}
    
    //if its not the first time reset player stats
    else player.SetUp(player.id);
    player.quit = false;
    
    //then set up a level
    if(player.lives <= 0)player.lives = 2;
            
    /* main game loop */
    while(!player.quit)
    {
        oslStartDrawing();
        oslSetBkColor(RGBA(0,0,0,0)); 
        oslClearScreen(BLACK);
        
        //handle game
        u8 *macAddress = oslAdhocGetMacAddress();
        
        //update game
        use.UPDATER();
      
        //update game type
        if(use.currentLevel > LAST_LEVEL && use.spawned == 0) 
            use.COMPUTER_GENERATED_LEVELS();
        else 
            use.MANUALLY_CODED_LEVELS();
        
        
        //update player
        player.UpdatePlayer(0, aPsp);
        if(!player.toggle) {
          oslSetTextColor(GREEN); oslPrintf_xy(player.image->x, player.image->y -10, "Hp: %lld", player.health);
          oslSetTextColor(BLACK); oslPrintf_xy(5, 5, "LEVEL %i: %i enemies left", use.currentLevel, totalNum);
          oslSetTextColor(BLACK); oslPrintf_xy(5, 35, "%d lives", player.lives);
          oslSetTextColor(BLACK); oslPrintf_xy(5, 25, "$%lld", player.money);
          oslPrintf_xy(5, 55, "Current state: %s", oslAdhocGetState() == ADHOC_INIT ? "OK" : "KO");
	      oslPrintf_xy(5, 65, "Your MAC address: %02X:%02X:%02X:%02X:%02X:%02X", macAddress[0], macAddress[1], macAddress[2], macAddress[3], macAddress[4], macAddress[5]);
	      oslPrintf_xy(5, 75, "You are playing with: %s", aPsp->name);
        }
      
        if(use.nextLevel) {
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
        powerup.UpdateItem(use.level);
    }
    
    oslAdhocTerm();
    
    /* stop any possible playing music */
    oslStopSound(use.battle1); 
    oslStopSound(use.battle2); 
    oslStopSound(use.battle3); 
    oslStopSound(use.battle4); 
    oslStopSound(use.battle5);
    
    //turn menu music back on
    oslPlaySound(menu_music, 1); 
    oslSetSoundLoop(menu_music, 1);
    
    return;
}

//The server accepted the connection and it's ready to receive data:
void serverConnected(struct remotePsp *aPsp)
{
    //adhoc game starts here
    oslStopSound(menu_music);
    
    //setup friend
    //int dataLength = 0;
    
    //create powerups
    ITEM powerup;
    
    //first we have to setup the player for the first time
    if(player.initialBoot){player.SetUp(DUDE); player.initialBoot = false;}
    
    //if its not the first time reset player stats
    else player.SetUp(player.id);
    player.quit = false;
    
    //then set up a level
    if(player.lives <= 0)player.lives = 2;
            
    /* main game loop */
    while(!player.quit)
    {
        oslStartDrawing();
        oslSetBkColor(RGBA(0,0,0,0)); 
        oslClearScreen(BLACK);
        
        //handle game
        u8 *macAddress = oslAdhocGetMacAddress();
        
        //update game
        use.UPDATER();
      
        //update game type
        if(use.currentLevel > LAST_LEVEL && use.spawned == 0) 
            use.COMPUTER_GENERATED_LEVELS();
        else 
            use.MANUALLY_CODED_LEVELS();
        
        
        //update player
        player.UpdatePlayer(0, aPsp);
        if(!player.toggle) {
          oslSetTextColor(GREEN); oslPrintf_xy(player.image->x, player.image->y -10, "Hp: %lld", player.health);
          oslSetTextColor(BLACK); oslPrintf_xy(5, 5, "LEVEL %i: %i enemies left", use.currentLevel, totalNum);
          oslSetTextColor(BLACK); oslPrintf_xy(5, 35, "%d lives", player.lives);
          oslSetTextColor(BLACK); oslPrintf_xy(5, 25, "$%lld", player.money);
          oslPrintf_xy(5, 55, "Current state: %s", oslAdhocGetState() == ADHOC_INIT ? "OK" : "KO");
	      oslPrintf_xy(5, 65, "Your MAC address: %02X:%02X:%02X:%02X:%02X:%02X", macAddress[0], macAddress[1], macAddress[2], macAddress[3], macAddress[4], macAddress[5]);
	      oslPrintf_xy(5, 75, "You are playing with: %s", aPsp->name);
        }
      
        if(use.nextLevel) {
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
        powerup.UpdateItem(use.level);
    }
    
    oslAdhocTerm();
    
    /* stop any possible playing music */
    oslStopSound(use.battle1); 
    oslStopSound(use.battle2); 
    oslStopSound(use.battle3); 
    oslStopSound(use.battle4); 
    oslStopSound(use.battle5);
    
    //turn menu music back on
    oslPlaySound(menu_music, 1); 
    oslSetSoundLoop(menu_music, 1);
    
    return;
}

void PauseGame( void )
{
    //oslPauseSound(gameMusic, 1);
    
    //play a sound effect
    oslPlaySound(soft_punch, 7);
    
    //draw here to remove flicker
    oslStartDrawing();
    oslDrawImage(player.image);
    
	oslIntraFontSetStyle(ltn, 1.7f,WHITE,BLACK,INTRAFONT_ALIGN_LEFT);
	oslDrawString(19, 25, "Paused");
	oslIntraFontSetStyle(ltn, 1.0f,WHITE,BLACK,INTRAFONT_ALIGN_LEFT);
	oslDrawString(19, 63, "Press R to customize");
	oslDrawString(19, 93, "Press L to save game");
	oslDrawString(19, 123, "Press start to resume");
	oslDrawString(19, 153, "Press select to quit");

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
			oslIntraFontSetStyle(ltn, 1.7f,WHITE,BLACK,INTRAFONT_ALIGN_LEFT);
	        oslDrawString(19, 25, "Paused");
	        oslIntraFontSetStyle(ltn, 1.0f,WHITE,BLACK,INTRAFONT_ALIGN_LEFT);
	        oslDrawString(19, 63, "Press R to customize");
			oslDrawString(19, 93, "Press L to save game");
	        oslDrawString(19, 123, "Press start to resume");
	        oslDrawString(19, 153, "Press select to quit");
            oslEndDrawing();
            oslSyncFrame();}
	    }

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
     
     Wait();
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

