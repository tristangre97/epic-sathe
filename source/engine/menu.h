/* 
 * class MENU ~V@ughn
 * -------------------
 * ->contains bought items
 *       -all items are expressed in boolean values if bought the value is set to true
 *               if not bought, the value is set to false
 * ->contains all menus wihtin the game
 *       -this class defines all the menus and can be used to launch a menu at any time
 *      
 */
class MENU  
{
    public:
        
        //sounds
        SOUND * select;
        SOUND * bought;
        SOUND * error;
        
        //properties
        bool DUDE_bought;
        bool SATHE_NORMAL_bought;
        bool REPUBLIKEN_bought;
        bool ORRE_bought;
        bool BARON_bought;
        bool BLADE_bought;
        bool RYAN_bought;
        bool EARTH_bought;
        bool ATLANTIS_bought;
        bool VEXUS_bought;
        bool ZAMUS_NORMAL_bought;
        bool SUPER_SATHE_bought;
        bool GENAMI_bought;
        bool ORPHEUS_bought;
        bool SATHIMUS_bought;
        bool WEAK_KROM_bought;
        bool WEAK_WRAITH_bought;
        bool WRAITH_bought;
        bool KRITH_bought;
        bool ULTRA_SATHE_bought;
        bool ULTRA_ZAMUS_bought;
        bool KROM_bought;
        bool SATHIS_bought;
        bool PHALEM_bought;
        bool FOURTH_ELDER_bought;
        bool FIFTH_ELDER_bought;
        bool SIXTH_ELDER_bought;
        bool ELDER_SATHE_bought;
        bool ETHAS_bought;
        
        MENU();
        ~MENU();
        
        virtual void BuyCharacters();

        virtual void BuyItems();

        virtual void BuyLives();

        virtual void UpgradeCharacter();

        virtual int Customize();
        
        virtual int MainMenu();
        
        virtual int SecondaryMenu();
        
        virtual short BossMenu(const int currentLevel, int &trackLevel);
    
    private:
        int menuChoice;
        int cost;
}menu;

/* menu macros */
#define SHOW_MAIN_MENU 1
#define SHOW_SECOND_MENU 2
#define EXIT 0

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
//MENU methods://///////////////////////////////////////////////////////////////////////////

int MENU::MainMenu()
{
    OBJECT menuGuy[4];
    
    menuChoice = 1;
    IMAGE * background = oslLoadImageFilePNG((char*)"img/data/menu.png", OSL_IN_RAM, OSL_PF_5551);
    IMAGE * selector = oslLoadImageFilePNG((char*)"img/data/selector.png", OSL_IN_RAM, OSL_PF_5551);  
    
    //set up a menu animation
    int x = 190;
    for(int i = 0; i < 4; i++){
      menuGuy[i].id = MDUDE;
      menuGuy[i].image = menuGuy[i].SetImage(menuGuy[i].id);
      menuGuy[i].position = ATTACKING_RIGHT;
      menuGuy[i].image->x = x;
      menuGuy[i].image->y = 202;
      x += 60; 
    }
    menuGuy[0].position = STILL_LEFT;
    menuGuy[1].position = ATTACKING_RIGHT;
    menuGuy[2].position = ATTACKING_LEFT;
    menuGuy[3].position = STILL_RIGHT;
    
    #define START_GAME 1
    #define HELP 2
    #define CREDITS 3
    #define EXIT_GAME 4

	while (1)
	{	
		oslReadKeys();
		
		if(osl_keys->pressed.down){menuChoice++; oslPlaySound(select, 2);}
		if(osl_keys->pressed.up)  {menuChoice--; oslPlaySound(select, 2);}
		if(menuChoice > 4) menuChoice = 1;
        if(menuChoice < 1) menuChoice = 4;
		
		if(menuChoice == START_GAME){
		  placeSelector(selector, 19,113);
		  if(osl_keys->pressed.cross) {oslPlaySound(select, 2); return SHOW_SECOND_MENU;}                      
		}
        
        else if(menuChoice == HELP)
        {
		  placeSelector(selector, 19, 149);
		  if(osl_keys->pressed.cross)
          {
                oslPlaySound(select, 2); 
                IMAGE * help = oslLoadImageFilePNG((char*)"img/data/help.png", OSL_IN_RAM, OSL_PF_5551);
                
                while(1)
                {
                    oslStartDrawing();
                    oslClearScreen(BLACK);
                    oslDrawImage(help);
                    oslEndDrawing();
                    oslSyncFrame();
                    
                    oslReadKeys();
                    if(osl_keys->pressed.circle || osl_keys->pressed.select) break;
                }
                
                oslPlaySound(select, 2); 
                oslDeleteImage(help);
          }
		}	
		
		else if(menuChoice == CREDITS)
        {
		  placeSelector(selector, 19, 191);
		  if(osl_keys->pressed.cross)
          {
                oslPlaySound(select, 2);
                while(1)
                {
    	          oslReadKeys();
    	          if(osl_keys->pressed.circle) {oslPlaySound(select, 2); break;}
    	  
                  oslStartDrawing();
                  oslClearScreen(BLACK);
          
                  oslSetTextColor(RED);
                  oslPrintf_xy(5, 15, "Credits: Epic Sathe %s", BUILD_ID);
                  oslSetTextColor(WHITE);
          
                  oslPrintf_xy(5, 25, "Epic Sathe, an epic game made by V@ughn");
          
                  oslSetTextColor(RED);
                  oslPrintf_xy(5, 45, "Tools used:");
                  oslSetTextColor(WHITE);
          
                  oslPrintf_xy(5, 55, "-Dev-C++ 4.9.9.2");
				  oslPrintf_xy(5, 65, "Microsoft Visual C++ Express");
                  oslPrintf_xy(5, 75, "-sfxr sound generator");
                  oslPrintf_xy(5, 85, "-MS paint");
                  oslPrintf_xy(5, 95, "-oslib + gu of pspsdk");
          
                  oslEndDrawing();
                  oslSyncFrame();
                }
          }
		}
		  
		else if(menuChoice == EXIT_GAME){
		  placeSelector(selector, 19, 228);
	      if(osl_keys->pressed.cross) return EXIT;
		}
		  
		oslStartDrawing();
		oslClearScreen(BLACK);
		oslDrawImage(background);
        oslDrawImage(selector);
        
        //update animation
        for(int i = 0; i < 4; i++){
            oslDrawImage(menuGuy[i].image);
            menuGuy[i].SpriteAnimate();
        }
            
		oslEndDrawing();
		oslSyncFrame();		
    }
    
    if(background != NULL){oslDeleteImage(background); background = NULL;}
    if(selector != NULL){oslDeleteImage(selector); selector = NULL;}
    
    return 1;
}

int MENU::SecondaryMenu()
{
    menuChoice = 1;
    IMAGE * background = oslLoadImageFilePNG((char*)"img/data/menu2.png", OSL_IN_RAM, OSL_PF_5551);
    IMAGE * selector = oslLoadImageFilePNG((char*)"img/data/selector2.png", OSL_IN_RAM, OSL_PF_5551);  
    
    #define SOLO_MODE 1
    #define LOAD_OLD_STATS 2
    #define BOSS_MODE 3
    #define MULTIPLAYER 4
    #define BACK 5

	while (1)
	{	
		oslReadKeys();
		
		if(osl_keys->pressed.down){menuChoice++; oslPlaySound(select, 2);}
		if(osl_keys->pressed.up)  {menuChoice--; oslPlaySound(select, 2);}
		if(menuChoice > 5) menuChoice = 1;
        if(menuChoice < 1) menuChoice = 5;
		
		if(menuChoice == SOLO_MODE){
		  placeSelector(selector, 19,106);
		  if(osl_keys->pressed.cross) {oslPlaySound(select, 2); MAIN_GAME(0); return SHOW_MAIN_MENU;}                      
		}
        
        else if(menuChoice == LOAD_OLD_STATS){
		  placeSelector(selector, 19, 143);
		  if(osl_keys->pressed.cross){
                oslPlaySound(select, 2); 
                int check = LoadGame();
                if(check == 0)oslWarning("ERROR! NO SAVE DATA CAN BE LOADED!"); 
                return SHOW_SECOND_MENU;
            }
		}	
		
		else if(menuChoice == BOSS_MODE){
		  placeSelector(selector, 19, 177);
		  if(osl_keys->pressed.cross){oslPlaySound(select, 2); MAIN_GAME(1); return SHOW_MAIN_MENU; }
		}
		  
		else if(menuChoice == MULTIPLAYER){
		  placeSelector(selector, 19, 213);
	      if(osl_keys->pressed.cross) {oslPlaySound(select, 2); InitAdhocGame(); return SHOW_MAIN_MENU;}
		}
		
		else if(menuChoice == BACK){
		  placeSelector(selector, 19, 250);
	      if(osl_keys->pressed.cross) {oslPlaySound(select, 2); return SHOW_MAIN_MENU;}
		}
		  
		oslStartDrawing();
		oslClearScreen(BLACK);
		oslDrawImage(background);
        oslDrawImage(selector);
        
		oslEndDrawing();
		oslSyncFrame();		
    }
    
    if(background != NULL){oslDeleteImage(background); background = NULL;}
    if(selector != NULL){oslDeleteImage(selector); selector = NULL;}
    
    return 1;
}

int MENU::Customize()
{
    //load images
    IMAGE * background = oslLoadImageFile((char*)"img/data/customize1.png", OSL_IN_RAM, OSL_PF_5551);
    IMAGE * selector = oslLoadImageFile((char*)"img/data/selector2.png", OSL_IN_RAM, OSL_PF_5551);
    
    //menu manipulators
    int menuChoice = 1;
    
    //menu macros
    #define BUY_NEW_CHARACTER 1
    #define BUY_NEW_ITEMS 2
    #define BUY_MORE_LIVES 3
    #define UPGRADE_CHARACTER 4
    #define BACK 5
    
    while(1)
    {
        oslReadKeys();
        
        /* handle menu input */
        if(osl_keys->pressed.down){menuChoice++; oslPlaySound(select, 2);}
		else if(osl_keys->pressed.up)  {menuChoice--; oslPlaySound(select, 2);}
		if(menuChoice > 5) menuChoice = 1;
        if(menuChoice < 1) menuChoice = 5;
        
        if(menuChoice == BUY_NEW_CHARACTER){
		    placeSelector(selector, 19,116);
		    if(osl_keys->pressed.cross || osl_keys->pressed.start) {oslPlaySound(select, 2); BuyCharacters();}                      
		}
        
        else if(menuChoice == BUY_NEW_ITEMS){
			placeSelector(selector, 19, 148);
			if(osl_keys->pressed.cross || osl_keys->pressed.start){oslPlaySound(select, 2); BuyItems();}
		}	
		
		else if(menuChoice == BUY_MORE_LIVES){
			placeSelector(selector, 20, 177);
			if(osl_keys->pressed.cross || osl_keys->pressed.start){oslPlaySound(select, 2); BuyLives();}
		}
		  
		else if(menuChoice == UPGRADE_CHARACTER){
			placeSelector(selector, 20, 205);
			if(osl_keys->pressed.cross || osl_keys->pressed.start){oslPlaySound(select, 2); UpgradeCharacter();}
		}
		
		else if(menuChoice == BACK){
			placeSelector(selector, 20, 232);
			if(osl_keys->pressed.cross || osl_keys->pressed.start){oslPlaySound(select, 2); return SHOW_MAIN_MENU;}
		}
		
		/* draw everything */
        oslStartDrawing();
        oslClearScreen(BLACK);
        oslDrawImage(background);
        oslDrawImage(selector);
        oslEndDrawing();
        oslSyncFrame();
    }
    
    //free memory
    if(background != NULL){oslDeleteImage(background); background = NULL;}
    if(selector != NULL){oslDeleteImage(selector); selector = NULL;}
    
    return SHOW_MAIN_MENU;
}

void MENU::BuyItems()
{
    cost = 99999;
    menuChoice = 1;
    IMAGE * selectorb = oslLoadImageFilePNG((char*)"img/data/selector2.png", OSL_IN_RAM, OSL_PF_5551);
    IMAGE * backgroundb = oslLoadImageFilePNG((char*)"img/data/customize3.png", OSL_IN_RAM, OSL_PF_5551);
    
    //menu macros
    #define FLYING_PUNCH 1
    #define FREEZING_PUNCH 2
    #define SWIFTNESS 3
    #define SATHES_BRUTE 4
    #define BACK 5
    
    while(1)
    {
        oslReadKeys();
        
        if(osl_keys->pressed.down){menuChoice++; oslPlaySound(select, 2);}
		else if(osl_keys->pressed.up)  {menuChoice--; oslPlaySound(select, 2);}
		if(menuChoice > 5) menuChoice = 1;
        if(menuChoice < 1) menuChoice = 5;
        
        if(menuChoice == FLYING_PUNCH){
		    placeSelector(selectorb, 19,116);
		    if(osl_keys->pressed.cross) {oslPlaySound(select, 2);}  
            else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);                         
		}
        
        else if(menuChoice == FREEZING_PUNCH){
			placeSelector(selectorb, 19, 148);
			if(osl_keys->pressed.cross){oslPlaySound(select, 2);}
			else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);     
		}	
		
		else if(menuChoice == SWIFTNESS){
            cost = 1000;
			placeSelector(selectorb, 20, 177);
			if(osl_keys->pressed.cross && player.money > cost){
                oslPlaySound(select, 2);
                player.speed *= 2;
                player.money -= cost;
            }
			else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);     
		}
		  
		else if(menuChoice == SATHES_BRUTE){
			placeSelector(selectorb, 20, 205);
			if(osl_keys->pressed.cross){oslPlaySound(select, 2);}
			else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);     
		}
		
		else if(menuChoice == BACK){
			placeSelector(selectorb, 20, 232);
			if(osl_keys->pressed.cross){oslPlaySound(select, 2); break;}
		}
		
        oslStartDrawing();
        oslClearScreen(BLACK);
        oslDrawImage(backgroundb);
        oslDrawImage(selectorb);
        
        //display player money
        oslSetTextColor(WHITE); oslPrintf_xy(250, 20, "Player money left: $%lld", player.money);
        
        oslEndDrawing();
        oslSyncFrame();
    }
    
    //free memory
    if(selectorb != NULL)  {oslDeleteImage(selectorb);}
    if(backgroundb != NULL){oslDeleteImage(backgroundb);}
    
    return;
}

void MENU::BuyLives()
{
    menuChoice = 1;
    cost = 0;
    IMAGE * selectorl = oslLoadImageFilePNG((char*)"img/data/selector2.png", OSL_IN_RAM, OSL_PF_5551);
    IMAGE * backgroundl = oslLoadImageFilePNG((char*)"img/data/customize4.png", OSL_IN_RAM, OSL_PF_5551);
    
    //menu macros
    #define BUY1 1
    #define BUY3 2
    #define BUY9 3
    #define BUY15 4
    #define BACK 5
    
    while(1)
    {
        oslReadKeys();
        
        if(osl_keys->pressed.down){menuChoice++; oslPlaySound(select, 2);}
		else if(osl_keys->pressed.up)  {menuChoice--; oslPlaySound(select, 2);}
		if(menuChoice > 5) menuChoice = 1;
        if(menuChoice < 1) menuChoice = 5;
        
        if(menuChoice == BUY1){
		    placeSelector(selectorl, 19,116);
		    cost = 100;
		    if(osl_keys->pressed.cross && player.money >= cost){oslPlaySound(bought, 7); player.money -= cost; player.lives++;}    
              else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);                     
		}
        
        else if(menuChoice == BUY3){
			placeSelector(selectorl, 19, 148);
			cost = 250;
		    if(osl_keys->pressed.cross && player.money >= cost){oslPlaySound(bought, 7); player.money -= cost; player.lives+=3;}       
              else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);                  
		}	
		
		else if(menuChoice == BUY9){
			placeSelector(selectorl, 20, 177);
			cost = 500;
		    if(osl_keys->pressed.cross && player.money >= cost){oslPlaySound(bought, 7); player.money -= cost; player.lives+=9;}  
              else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);                       
		}
		  
		else if(menuChoice == BUY15){
			placeSelector(selectorl, 20, 205);
			cost = 890;
		    if(osl_keys->pressed.cross && player.money >= cost){oslPlaySound(bought, 7); player.money -= cost; player.lives+=15;}  
            else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);                       
		}
		
		else if(menuChoice == BACK){
			placeSelector(selectorl, 20, 232);
			if(osl_keys->pressed.cross){oslPlaySound(select, 2); break;}
		}
		
        oslStartDrawing();
        oslClearScreen(BLACK);
        oslDrawImage(backgroundl);
        oslDrawImage(selectorl);
        
        //display player money
        oslSetTextColor(WHITE); oslPrintf_xy(250, 20, "Player money left: $%lld", player.money);
        
        oslEndDrawing();
        oslSyncFrame();
    }
    
    //free memory
    if(selectorl != NULL) {oslDeleteImage(selectorl); selectorl = NULL;}
    if(backgroundl != NULL){oslDeleteImage(backgroundl); backgroundl = NULL;}
    
    return;
}

void MENU::UpgradeCharacter()
{
    cost = 99999;
    menuChoice = 1;
    IMAGE * selectoru = oslLoadImageFilePNG((char*)"img/data/selector2.png", OSL_IN_RAM, OSL_PF_5551);
    IMAGE * backgroundu = oslLoadImageFilePNG((char*)"img/data/customize5.png", OSL_IN_RAM, OSL_PF_5551);
    
    //menu macros
    #define UPGRADE_HEALTH 1
    #define UPGRADE_ATTACK 2
    #define UPGRADE_JUMP_HEIGHT 3
    #define UPGRADE_MAX_POWER 4
    #define BACK 5
    
    while(1)
    {
        oslReadKeys();
        
        if(osl_keys->pressed.down)       {oslPlaySound(select, 2); menuChoice++; }
		else if(osl_keys->pressed.up)    {oslPlaySound(select, 2); menuChoice--; }
		if(menuChoice > 5) menuChoice = 1;
        if(menuChoice < 1) menuChoice = 5;
        
        if(menuChoice == UPGRADE_HEALTH){
		    placeSelector(selectoru, 19,116);
		    if(osl_keys->pressed.cross) {oslPlaySound(bought, 2);}   
            else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);                        
		}
        
        else if(menuChoice == UPGRADE_ATTACK){
			placeSelector(selectoru, 19, 148);
			if(osl_keys->pressed.cross){oslPlaySound(bought, 2);}
			else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);     
		}	
		
		else if(menuChoice == UPGRADE_JUMP_HEIGHT){
			placeSelector(selectoru, 20, 177);
			if(osl_keys->pressed.cross){oslPlaySound(bought, 2);}
			else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);     
		}
		  
		else if(menuChoice == UPGRADE_MAX_POWER){
			placeSelector(selectoru, 20, 205);
			if(osl_keys->pressed.cross){oslPlaySound(bought, 2);}
			else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);     
		}
		
		else if(menuChoice == BACK){
			placeSelector(selectoru, 20, 232);
			if(osl_keys->pressed.cross){oslPlaySound(select, 2); break;}  
		}
		
        oslStartDrawing();
        oslClearScreen(BLACK);
        oslDrawImage(backgroundu);
        oslDrawImage(selectoru);
        
        //display player money
        oslSetTextColor(WHITE); oslPrintf_xy(250, 20, "Player money left: $%lld", player.money);
        
        oslEndDrawing();
        oslSyncFrame();
    }
    
    //free memory
    if(selectoru != NULL) {oslDeleteImage(selectoru); selectoru = NULL;}
    if(backgroundu != NULL){oslDeleteImage(backgroundu); backgroundu = NULL;}
    
    return;
}

short MENU::BossMenu(const int currentLevel, int &trackLevel)
{
    menuChoice = 1;
    IMAGE * BossChoice = oslLoadImageFilePNG((char*)"img/data/boss1.png", OSL_IN_RAM, OSL_PF_5551);
    IMAGE * BossSelector = oslLoadImageFilePNG((char*)"img/data/bossSelector.png", OSL_IN_RAM, OSL_PF_5551);

    //load and position locked images
    IMAGE * lock[35];
    int posx = 25;
    int posy = 21;
    int manipRow = 1;
    for(int i = 0; i < 35; i++){
      lock[i] = oslLoadImageFilePNG((char*)"img/data/lock.png", OSL_IN_RAM, OSL_PF_5551);
      lock[i]->stretchX /= 2;
      lock[i]->stretchY /= 2;
      lock[i]->x = posx;
      lock[i]->y = posy;
      manipRow++;
      if(manipRow > 7){manipRow = 1; posx = 25; posy += 57;}
      posx += 60;
    }
    
    while(1)
    {
        oslReadKeys();
        if(osl_keys->pressed.right && menuChoice < 35){oslPlaySound(select, 2); menuChoice++; }
        else if(osl_keys->pressed.left && menuChoice > 1) {oslPlaySound(select, 2); menuChoice--; }
        else if(osl_keys->pressed.down && menuChoice < 28){oslPlaySound(select, 2); menuChoice += 7;}
        else if(osl_keys->pressed.up && menuChoice > 7){oslPlaySound(select, 2); menuChoice -= 7;}
        
        if(menuChoice == 1){
            placeSelector(BossSelector, 11,5); trackLevel = menuChoice;
            if(osl_keys->pressed.cross)
            {
              oslPlaySound(select, 2);
              boss.id = DUDE;
              boss.line1 = "Welcome to BOSS mode!";
              boss.line2 = "Here each enemy will refer to use as 'Sathe'. Defeat each";
              boss.line3 = "boss to unlock a new one!";
              break;
            }
        }
        
        else if(menuChoice == 2){
            placeSelector(BossSelector, 77,5); trackLevel = menuChoice;
            if(osl_keys->pressed.cross && currentLevel >= menuChoice)
            {
              oslPlaySound(select, 2);
              boss.id = DUDE;
              boss.line1 = "Welcome to BOSS mode!";
              boss.line2 = "Here each enemy will refer to use as 'Sathe'. Defeat each";
              boss.line3 = "boss to unlock a new one!";
              break;
            }
        }
        
        else if(menuChoice == 3){
            placeSelector(BossSelector, 143,5); trackLevel = menuChoice;
            if(osl_keys->pressed.cross && currentLevel >= menuChoice)
            {
              oslPlaySound(select, 2);
              boss.id = ORRE;
              boss.line1 = "Hey Sathe!";
              boss.line2 = "Ready for some hardcore training?";
              boss.line3 = "Well ready or not, because here I come!";
            }
        }
        
        else if(menuChoice == 4){
            placeSelector(BossSelector, 209,5); trackLevel = menuChoice;
            if(osl_keys->pressed.cross && currentLevel >= menuChoice)
            {
              oslPlaySound(select, 2);
            }
        }
        
        else if(menuChoice == 5){
            placeSelector(BossSelector, 275,5); trackLevel = menuChoice;
            if(osl_keys->pressed.cross && currentLevel >= menuChoice)
            {
              oslPlaySound(select, 2);
            }
        }
        
        else if(menuChoice == 6){
            placeSelector(BossSelector, 342,5); trackLevel = menuChoice;
            if(osl_keys->pressed.cross && currentLevel >= menuChoice)
            {
              oslPlaySound(select, 2);
            }
        }
        
        else if(menuChoice == 7){
            placeSelector(BossSelector, 408,5); trackLevel = menuChoice;
            if(osl_keys->pressed.cross && currentLevel >= menuChoice)
            {
              oslPlaySound(select, 2);
            }
        }
        
        else if(menuChoice == 8){
            placeSelector(BossSelector, 11,59); trackLevel = menuChoice;
            if(osl_keys->pressed.cross && currentLevel >= menuChoice)
            {
              oslPlaySound(select, 2);
            }
        }
        
        else if(menuChoice == 9){
            placeSelector(BossSelector, 77,59); trackLevel = menuChoice;
            if(osl_keys->pressed.cross && currentLevel >= menuChoice)
            {
              oslPlaySound(select, 2);
            }
        }
        
        else if(menuChoice == 10){
            placeSelector(BossSelector, 143,59); trackLevel = menuChoice;
            if(osl_keys->pressed.cross && currentLevel >= menuChoice)
            {
              oslPlaySound(select, 2);
            }
        }
        
        else if(menuChoice == 11){
            placeSelector(BossSelector, 209,59); trackLevel = menuChoice;
            if(osl_keys->pressed.cross && currentLevel >= menuChoice)
            {
              oslPlaySound(select, 2);
            }
        }
        
        else if(menuChoice == 12){
            placeSelector(BossSelector, 275,59); trackLevel = menuChoice;
            if(osl_keys->pressed.cross && currentLevel >= menuChoice)
            {
              oslPlaySound(select, 2);
            }
        }
        
        else if(menuChoice == 13){
            placeSelector(BossSelector, 342,59); trackLevel = menuChoice;
            if(osl_keys->pressed.cross && currentLevel >= menuChoice)
            {
              oslPlaySound(select, 2);
            }
        }
        
        else if(menuChoice == 14){
            placeSelector(BossSelector, 408,59); trackLevel = menuChoice;
            if(osl_keys->pressed.cross && currentLevel >= menuChoice)
            {
              oslPlaySound(select, 2);
            }
        }
        
        else if(menuChoice == 15){
            placeSelector(BossSelector, 11,113); trackLevel = menuChoice;
            if(osl_keys->pressed.cross && currentLevel >= menuChoice)
            {
              oslPlaySound(select, 2);
            }
        }
        
        else if(menuChoice == 16){
            placeSelector(BossSelector, 77,113); trackLevel = menuChoice;
            if(osl_keys->pressed.cross && currentLevel >= menuChoice)
            {
              oslPlaySound(select, 2);
            }
        }
        
        else if(menuChoice == 17){
            placeSelector(BossSelector, 143,113); trackLevel = menuChoice;
            if(osl_keys->pressed.cross && currentLevel >= menuChoice)
            {
              oslPlaySound(select, 2);
            }
        }
        
        else if(menuChoice == 18){
            placeSelector(BossSelector, 209,113); trackLevel = menuChoice;
            if(osl_keys->pressed.cross && currentLevel >= menuChoice)
            {
              oslPlaySound(select, 2);
            }
        }
        
        else if(menuChoice == 19){
            placeSelector(BossSelector, 275,113); trackLevel = menuChoice;
            if(osl_keys->pressed.cross && currentLevel >= menuChoice)
            {
              oslPlaySound(select, 2);
            }
        }
        
        else if(menuChoice == 20){
            placeSelector(BossSelector, 342,113); trackLevel = menuChoice;
            if(osl_keys->pressed.cross && currentLevel >= menuChoice)
            {
              oslPlaySound(select, 2);
            }
        }
        
        else if(menuChoice == 21){
            placeSelector(BossSelector, 408,113); trackLevel = menuChoice;
            if(osl_keys->pressed.cross && currentLevel >= menuChoice)
            {
              oslPlaySound(select, 2);
            }
        }
        
        else if(menuChoice == 22){
            placeSelector(BossSelector, 11,167); trackLevel = menuChoice;
            if(osl_keys->pressed.cross && currentLevel >= menuChoice)
            {
              oslPlaySound(select, 2);
            }
        }
        
        else if(menuChoice == 23){
            placeSelector(BossSelector, 77,167); trackLevel = menuChoice;
            if(osl_keys->pressed.cross && currentLevel >= menuChoice)
            {
              oslPlaySound(select, 2);
            }
        }
        
        else if(menuChoice == 24){
            placeSelector(BossSelector, 143,167); trackLevel = menuChoice;
            if(osl_keys->pressed.cross && currentLevel >= menuChoice)
            {
              oslPlaySound(select, 2);
            }
        }
        
        else if(menuChoice == 25){
            placeSelector(BossSelector, 209,167); trackLevel = menuChoice;
            if(osl_keys->pressed.cross && currentLevel >= menuChoice)
            {
              oslPlaySound(select, 2);
            }
        }
        
        else if(menuChoice == 26){
            placeSelector(BossSelector, 275,167); trackLevel = menuChoice;
            if(osl_keys->pressed.cross && currentLevel >= menuChoice)
            {
              oslPlaySound(select, 2);
            }
        }
        
        else if(menuChoice == 27){
            placeSelector(BossSelector, 342,167); trackLevel = menuChoice;
            if(osl_keys->pressed.cross && currentLevel >= menuChoice)
            {
              oslPlaySound(select, 2);
            }
        }
        
        else if(menuChoice == 28){
            placeSelector(BossSelector, 408,167); trackLevel = menuChoice;
            if(osl_keys->pressed.cross && currentLevel >= menuChoice)
            {
              oslPlaySound(select, 2);
            }
        }
        
        else if(menuChoice == 29){
            placeSelector(BossSelector, 11,221); trackLevel = menuChoice;
            if(osl_keys->pressed.cross && currentLevel >= menuChoice)
            {
              oslPlaySound(select, 2);
            }
        }
        
        else if(menuChoice == 30){
            placeSelector(BossSelector, 77,221); trackLevel = menuChoice;
            if(osl_keys->pressed.cross && currentLevel >= menuChoice)
            {
              oslPlaySound(select, 2);
            }
        }
        
        else if(menuChoice == 31){
            placeSelector(BossSelector, 143,221); trackLevel = menuChoice;
            if(osl_keys->pressed.cross && currentLevel >= menuChoice)
            {
              oslPlaySound(select, 2);
            }
        }
        
        else if(menuChoice == 32){
            placeSelector(BossSelector, 209,221); trackLevel = menuChoice;
            if(osl_keys->pressed.cross && currentLevel >= menuChoice)
            {
              oslPlaySound(select, 2);
            }
        }
        
        else if(menuChoice == 33){
            placeSelector(BossSelector, 275,221); trackLevel = menuChoice;
            if(osl_keys->pressed.cross && currentLevel >= menuChoice)
            {
              oslPlaySound(select, 2);
            }
        }
        
        else if(menuChoice == 34){
            placeSelector(BossSelector, 342,221); trackLevel = menuChoice;
            if(osl_keys->pressed.cross && currentLevel >= menuChoice)
            {
              oslPlaySound(select, 2);
            }
        }
        
        else if(menuChoice == 35){
            placeSelector(BossSelector, 408,221); trackLevel = menuChoice;
            if(osl_keys->pressed.cross && currentLevel >= menuChoice)
            {
              oslPlaySound(select, 2);
            }
        }
            
        oslStartDrawing();
        oslDrawImage(BossChoice);
        oslDrawImage(BossSelector);
        
        //draw lock images
        for(int i = (currentLevel); i < 35; i++){
            oslDrawImage(lock[i]);
        }
        
        oslEndDrawing();
        oslSyncFrame();
    }
    
    //free RAM
    for(int i = 0; i < 35; i++)
      if(lock[i] != NULL)oslDeleteImage(lock[i]);
    if(BossSelector != NULL)oslDeleteImage(BossSelector);
    if(BossChoice != NULL)oslDeleteImage(BossChoice);
    
    return boss.id;
}

void MENU::BuyCharacters()
{  
    OSL_IMAGE * backgroundBC, *background2BC, *background3BC, *background4BC, *selectBC, *lock1, *lock2,
    *lock3, *lock4, *lock5, *lock6, *lock7, *lock8;
    
    menuChoice = 1;
    int pageOn = 1;
    cost = 0;
    
    //load and configure images
    selectBC = oslLoadImageFilePNG((char*)"img/data/sqselector.png", OSL_IN_RAM, OSL_PF_5551);
    backgroundBC = oslLoadImageFilePNG((char*)"img/data/customize2.png", OSL_IN_RAM, OSL_PF_5551);
    background2BC = oslLoadImageFilePNG((char*)"img/data/customize6.png", OSL_IN_RAM, OSL_PF_5551);
    background3BC = oslLoadImageFilePNG((char*)"img/data/customize7.png", OSL_IN_RAM, OSL_PF_5551);
    background4BC = oslLoadImageFilePNG((char*)"img/data/customize8.png", OSL_IN_RAM, OSL_PF_5551);
    lock1 = oslLoadImageFilePNG((char*)"img/data/lock.png", OSL_IN_RAM, OSL_PF_5551);
    lock2 = oslLoadImageFilePNG((char*)"img/data/lock.png", OSL_IN_RAM, OSL_PF_5551);
    lock3 = oslLoadImageFilePNG((char*)"img/data/lock.png", OSL_IN_RAM, OSL_PF_5551);
    lock4 = oslLoadImageFilePNG((char*)"img/data/lock.png", OSL_IN_RAM, OSL_PF_5551);
    lock5 = oslLoadImageFilePNG((char*)"img/data/lock.png", OSL_IN_RAM, OSL_PF_5551);
    lock6 = oslLoadImageFilePNG((char*)"img/data/lock.png", OSL_IN_RAM, OSL_PF_5551);
    lock7 = oslLoadImageFilePNG((char*)"img/data/lock.png", OSL_IN_RAM, OSL_PF_5551);
    lock8 = oslLoadImageFilePNG((char*)"img/data/lock.png", OSL_IN_RAM, OSL_PF_5551);
    lock1->x = 75;
    lock1->y = 103;
    lock2->x = 171;
    lock2->y = 103;
    lock3->x = 268;
    lock3->y = 103;
    lock4->x = 380;
    lock4->y = 103;
    lock5->x = 75;
    lock5->y = 205;
    lock6->x = 171;
    lock6->y = 205;
    lock7->x = 268;
    lock7->y = 205;
    lock8->x = 380;
    lock8->y = 205;
    
    
    while(1)
    {
        oslReadKeys();
        if(osl_keys->pressed.circle){oslPlaySound(select, 2); break;}
        
        else if(osl_keys->pressed.R && pageOn < 4){oslPlaySound(select, 2); pageOn++;}
        else if(osl_keys->pressed.L && pageOn > 1){oslPlaySound(select, 2); pageOn--;}
        else if(osl_keys->pressed.right && menuChoice < 8){oslPlaySound(select, 2); menuChoice++; }
        else if(osl_keys->pressed.left && menuChoice > 1) {oslPlaySound(select, 2); menuChoice--; }
        else if(osl_keys->pressed.down && menuChoice == 1){oslPlaySound(select, 2); menuChoice = 5;}
        else if(osl_keys->pressed.down && menuChoice == 2){oslPlaySound(select, 2); menuChoice = 6;}
        else if(osl_keys->pressed.down && menuChoice == 3){oslPlaySound(select, 2); menuChoice = 7;}
        else if(osl_keys->pressed.down && menuChoice == 4){oslPlaySound(select, 2); menuChoice = 8;}
        else if(osl_keys->pressed.up && menuChoice == 5){oslPlaySound(select, 2); menuChoice = 1;}
        else if(osl_keys->pressed.up && menuChoice == 6){oslPlaySound(select, 2); menuChoice = 2;}
        else if(osl_keys->pressed.up && menuChoice == 7){oslPlaySound(select, 2); menuChoice = 3;}
        else if(osl_keys->pressed.up && menuChoice == 8){oslPlaySound(select, 2); menuChoice = 4;}
        
		if(menuChoice > 8) menuChoice = 1;
        if(menuChoice < 1) menuChoice = 8;
        
        if(menuChoice == 1)
        {
		    placeSelector(selectBC, 28,75); 
		    
		    if(pageOn == 1){  
              cost = 0;
		      if(osl_keys->pressed.cross && player.money >= cost && menu.DUDE_bought == false) 
              {oslPlaySound(bought, 7); player.SetUp(DUDE); menu.DUDE_bought = true; player.money -= cost;} 
              else if(osl_keys->pressed.cross && menu.DUDE_bought == true){oslPlaySound(bought, 7); player.SetUp(DUDE);}   
              else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);                                  }
            
            else if(pageOn == 2){  
              cost = 2400;
		      if(osl_keys->pressed.cross && player.money >= cost && menu.ATLANTIS_bought == false) 
              {oslPlaySound(bought, 7); player.SetUp(ATLANTIS); menu.ATLANTIS_bought = true; player.money -= cost;} 
              else if(osl_keys->pressed.cross && menu.ATLANTIS_bought == true){oslPlaySound(bought, 7); player.SetUp(ATLANTIS);}    
              else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);                      
            }   
            
            else if(pageOn == 3){  
              cost = 12000;
		      if(osl_keys->pressed.cross && player.money >= cost && menu.WEAK_WRAITH_bought == false) 
              {oslPlaySound(bought, 7); player.SetUp(WEAK_WRAITH); menu.WEAK_WRAITH_bought = true; player.money -= cost;} 
              else if(osl_keys->pressed.cross && menu.WEAK_WRAITH_bought == true){oslPlaySound(bought, 7); player.SetUp(WEAK_WRAITH);}      
              else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);                       
            }      
            
            else if(pageOn == 4){  
              cost = 35000;
		      if(osl_keys->pressed.cross && player.money >= cost && menu.FOURTH_ELDER_bought == false) 
              {oslPlaySound(bought, 7); player.SetUp(FOURTH_ELDER); menu.FOURTH_ELDER_bought = true; player.money -= cost;} 
              else if(osl_keys->pressed.cross && menu.FOURTH_ELDER_bought == true){oslPlaySound(bought, 7); player.SetUp(FOURTH_ELDER);}     
              else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);                   
            }  
            
		}
		
		else if(menuChoice == 2)
        {
		    placeSelector(selectBC, 131,75); 
		    
		    if(pageOn == 1){  
              cost = 400;
              if(osl_keys->pressed.cross && player.money >= cost && menu.SATHE_NORMAL_bought == false) 
              {oslPlaySound(bought, 7); player.SetUp(SATHE_NORMAL); menu.SATHE_NORMAL_bought = true; player.money -= cost;} 
              else if(osl_keys->pressed.cross && menu.SATHE_NORMAL_bought == true){oslPlaySound(bought, 7); player.SetUp(SATHE_NORMAL);} 
              else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);       
            }
            
            else if(pageOn == 2){  
              cost = 3500;
              if(osl_keys->pressed.cross && player.money >= cost && menu.VEXUS_bought == false) 
              {oslPlaySound(bought, 7); player.SetUp(VEXUS); menu.VEXUS_bought = true; player.money -= cost;} 
              else if(osl_keys->pressed.cross && menu.VEXUS_bought == true){oslPlaySound(bought, 7); player.SetUp(VEXUS);} 
              else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);     
            }
            
            else if(pageOn == 3){  
              cost = 18000;
              if(osl_keys->pressed.cross && player.money >= cost && menu.WRAITH_bought == false) 
              {oslPlaySound(bought, 7); player.SetUp(WRAITH); menu.WRAITH_bought = true; player.money -= cost;} 
              else if(osl_keys->pressed.cross && menu.WRAITH_bought == true){oslPlaySound(bought, 7); player.SetUp(WRAITH);} 
             else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);       
            }
            
            else if(pageOn == 4){  
              cost = 40000;
              if(osl_keys->pressed.cross && player.money >= cost && menu.FIFTH_ELDER_bought == false) 
              {oslPlaySound(bought, 7); player.SetUp(FIFTH_ELDER); menu.FIFTH_ELDER_bought = true; player.money -= cost;} 
              else if(osl_keys->pressed.cross && menu.FIFTH_ELDER_bought == true){oslPlaySound(bought, 7); player.SetUp(FIFTH_ELDER);} 
              else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);        
            }
                                 
		}
		
		else if(menuChoice == 3)
        {
		    placeSelector(selectBC, 234,75);              
            
            if(pageOn == 1){  
              cost = 0;
              if(osl_keys->pressed.cross && player.money >= cost && menu.REPUBLIKEN_bought == false) 
              {oslPlaySound(bought, 7); player.SetUp(REPUBLIKEN); menu.REPUBLIKEN_bought = true; player.money -= cost;} 
              else if(osl_keys->pressed.cross && menu.REPUBLIKEN_bought == true){oslPlaySound(bought, 7); player.SetUp(REPUBLIKEN);}  
              else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);        
            }  
            
            else if(pageOn == 2){  
              cost = 900;
              if(osl_keys->pressed.cross && player.money >= cost && menu.ZAMUS_NORMAL_bought == false) 
              {oslPlaySound(bought, 7); player.SetUp(ZAMUS_NORMAL); menu.ZAMUS_NORMAL_bought = true; player.money -= cost;} 
              else if(osl_keys->pressed.cross && menu.ZAMUS_NORMAL_bought == true){oslPlaySound(bought, 7); player.SetUp(ZAMUS_NORMAL);}  
              else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);       
            }      
            
            else if(pageOn == 3){  
              cost = 20000;
              if(osl_keys->pressed.cross && player.money >= cost && menu.KRITH_bought == false) 
              {oslPlaySound(bought, 7); player.SetUp(KRITH); menu.KRITH_bought = true; player.money -= cost;} 
              else if(osl_keys->pressed.cross && menu.KRITH_bought == true){oslPlaySound(bought, 7); player.SetUp(KRITH);}  
              else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);       
            }  
            
            else if(pageOn == 4){  
              cost = 60000;
              if(osl_keys->pressed.cross && player.money >= cost && menu.SIXTH_ELDER_bought == false) 
              {oslPlaySound(bought, 7); player.SetUp(SIXTH_ELDER); menu.SIXTH_ELDER_bought = true; player.money -= cost;} 
              else if(osl_keys->pressed.cross && menu.SIXTH_ELDER_bought == true){oslPlaySound(bought, 7); player.SetUp(SIXTH_ELDER);}  
              else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);       
            }  
		}
		
		else if(menuChoice == 4)
        {
		    placeSelector(selectBC, 338,75); 
		    
		    if(pageOn == 1){  
              cost = 870;
              if(osl_keys->pressed.cross && player.money >= cost && menu.ORRE_bought == false) 
              {oslPlaySound(bought, 7); player.SetUp(ORRE); menu.ORRE_bought = true; player.money -= cost;} 
              else if(osl_keys->pressed.cross && menu.ORRE_bought == true){oslPlaySound(bought, 7); player.SetUp(ORRE);}      
              else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);     
            }     
            
            else if(pageOn == 2){  
              cost = 5800;
              if(osl_keys->pressed.cross && player.money >= cost && menu.SUPER_SATHE_bought == false) 
              {oslPlaySound(bought, 7); player.SetUp(SUPER_SATHE); menu.SUPER_SATHE_bought = true; player.money -= cost;} 
              else if(osl_keys->pressed.cross && menu.SUPER_SATHE_bought == true){oslPlaySound(bought, 7); player.SetUp(SUPER_SATHE);}  
              else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);            
            }      
            
            else if(pageOn == 3){  
              cost = 16000;
              if(osl_keys->pressed.cross && player.money >= cost && menu.ULTRA_SATHE_bought == false) 
              {oslPlaySound(bought, 7); player.SetUp(ULTRA_SATHE); menu.ULTRA_SATHE_bought = true; player.money -= cost;} 
              else if(osl_keys->pressed.cross && menu.ULTRA_SATHE_bought == true){oslPlaySound(bought, 7); player.SetUp(ULTRA_SATHE);}   
              else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);         
            }    
            
            else if(pageOn == 4){  
              cost = 100000;
              if(osl_keys->pressed.cross && player.money >= cost && menu.ELDER_SATHE_bought == false) 
              {oslPlaySound(bought, 7); player.SetUp(ELDER_SATHE); menu.ELDER_SATHE_bought = true; player.money -= cost;} 
              else if(osl_keys->pressed.cross && menu.ELDER_SATHE_bought == true){oslPlaySound(bought, 7); player.SetUp(ELDER_SATHE);}   
              else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);           
            }      
		}
		
		else if(menuChoice == 5)
        {
		    placeSelector(selectBC, 28,169); 
		    
		    if(pageOn == 1){  
              cost = 1430;
              if(osl_keys->pressed.cross && player.money >= cost && menu.BARON_bought == false) 
              {oslPlaySound(bought, 7); player.SetUp(BARON); menu.BARON_bought = true; player.money -= cost;} 
              else if(osl_keys->pressed.cross && menu.BARON_bought == true){oslPlaySound(bought, 7); player.SetUp(BARON);}   
              else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);       
            }       
            
            else if(pageOn == 2){  
              cost = 4700;
              if(osl_keys->pressed.cross && player.money >= cost && menu.GENAMI_bought == false) 
              {oslPlaySound(bought, 7); player.SetUp(GENAMI); menu.GENAMI_bought = true; player.money -= cost;} 
              else if(osl_keys->pressed.cross && menu.GENAMI_bought == true){oslPlaySound(bought, 7); player.SetUp(GENAMI);}   
              else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);        
            }     
            
            else if(pageOn == 3){  
              cost = 11000;
              if(osl_keys->pressed.cross && player.money >= cost && menu.ULTRA_ZAMUS_bought == false) 
              {oslPlaySound(bought, 7); player.SetUp(ULTRA_ZAMUS); menu.ULTRA_ZAMUS_bought = true; player.money -= cost;} 
              else if(osl_keys->pressed.cross && menu.ULTRA_ZAMUS_bought == true){oslPlaySound(bought, 7); player.SetUp(ULTRA_ZAMUS);} 
              else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);          
            }  
            
            else if(pageOn == 4){  
              cost = 79000;
              if(osl_keys->pressed.cross && player.money >= cost && menu.ETHAS_bought == false) 
              {oslPlaySound(bought, 7); player.SetUp(ETHAS); menu.ETHAS_bought = true; player.money -= cost;} 
              else if(osl_keys->pressed.cross && menu.ETHAS_bought == true){oslPlaySound(bought, 7); player.SetUp(ETHAS);}   
              else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);       
            }  
		} 
		
		else if(menuChoice == 6)
        {
		    placeSelector(selectBC, 131,169); 
	        
	        if(pageOn == 1){  
              cost = 2000;
              if(osl_keys->pressed.cross && player.money >= cost && menu.BLADE_bought == false) 
              {oslPlaySound(bought, 7); player.SetUp(BLADE); menu.BLADE_bought = true; player.money -= cost;} 
               else if(osl_keys->pressed.cross && menu.BLADE_bought == true){oslPlaySound(bought, 7); player.SetUp(BLADE);}   
               else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);       
            }  
               
            
            else if(pageOn == 2){  
              cost = 8000;
              if(osl_keys->pressed.cross && player.money >= cost && menu.ORPHEUS_bought == false) 
              {oslPlaySound(bought, 7); player.SetUp(ORPHEUS); menu.ORPHEUS_bought = true; player.money -= cost;} 
              else if(osl_keys->pressed.cross && menu.ORPHEUS_bought == true){oslPlaySound(bought, 7); player.SetUp(ORPHEUS);}   
              else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);       
            }       
            
            else if(pageOn == 3){  
              cost = 26000;
              if(osl_keys->pressed.cross && player.money >= cost && menu.KROM_bought == false) 
              {oslPlaySound(bought, 7); player.SetUp(KROM); menu.KROM_bought = true; player.money -= cost;} 
              else if(osl_keys->pressed.cross && menu.KROM_bought == true){oslPlaySound(bought, 7); player.SetUp(KROM);}   
              else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);         
            }     
            
            else if(pageOn == 4){}     
		}
		
		else if(menuChoice == 7)
        {
		    placeSelector(selectBC, 234,169);   
            
            if(pageOn == 1){       
              cost = 2500;
              if(osl_keys->pressed.cross && player.money >= cost && menu.RYAN_bought == false) 
              {oslPlaySound(bought, 7); player.SetUp(RYAN); menu.RYAN_bought = true; player.money -= cost;} 
              else if(osl_keys->pressed.cross && menu.RYAN_bought == true){oslPlaySound(bought, 7); player.SetUp(RYAN);} 
              else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);       
            }      
            
            else if(pageOn == 2){       
              cost = 7350;
              if(osl_keys->pressed.cross && player.money >= cost && menu.SATHIMUS_bought == false) 
              {oslPlaySound(bought, 7); player.SetUp(SATHIMUS); menu.SATHIMUS_bought = true; player.money -= cost;} 
              else if(osl_keys->pressed.cross && menu.SATHIMUS_bought == true){oslPlaySound(bought, 7); player.SetUp(SATHIMUS);} 
              else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);       
            }      
            
            else if(pageOn == 3){       
              cost = 26000;
              if(osl_keys->pressed.cross && player.money >= cost && menu.SATHIS_bought == false) 
              {oslPlaySound(bought, 7); player.SetUp(SATHIS); menu.SATHIS_bought = true; player.money -= cost;} 
              else if(osl_keys->pressed.cross && menu.SATHIS_bought == true){oslPlaySound(bought, 7); player.SetUp(SATHIS);} 
              else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);        
            }       
            
            else if(pageOn == 4){}         
		}
		
		else if(menuChoice == 8)
        {
		    placeSelector(selectBC, 338,169); 
            
            if(pageOn == 1){    
              cost = 3400;
              if(osl_keys->pressed.cross && player.money >= cost && menu.EARTH_bought == false) 
              {oslPlaySound(bought, 7); player.SetUp(EARTH); menu.EARTH_bought = true; player.money -= cost;}
              else if(osl_keys->pressed.cross && menu.EARTH_bought == true){oslPlaySound(bought, 7); player.SetUp(EARTH);} 
              else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);            
            }
            
            else if(pageOn == 2){    
              cost = 10000;
              if(osl_keys->pressed.cross && player.money >= cost && menu.WEAK_KROM_bought == false) 
              {oslPlaySound(bought, 7); player.SetUp(WEAK_KROM); menu.WEAK_KROM_bought = true; player.money -= cost;}
              else if(osl_keys->pressed.cross && menu.WEAK_KROM_bought == true){oslPlaySound(bought, 7); player.SetUp(WEAK_KROM);}  
              else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);           
            }
            
            else if(pageOn == 3){    
              cost = 26000;
              if(osl_keys->pressed.cross && player.money >= cost && menu.PHALEM_bought == false) 
              {oslPlaySound(bought, 7); player.SetUp(PHALEM); menu.PHALEM_bought = true; player.money -= cost;}
              else if(osl_keys->pressed.cross && menu.PHALEM_bought == true){oslPlaySound(bought, 7); player.SetUp(PHALEM);}       
              else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);      
            }
            
            else if(pageOn == 4){}    
                             
		}
            
        oslStartDrawing();
        
        /* draw background */
        if(pageOn == 1)      oslDrawImage(backgroundBC);
        else if(pageOn == 2) oslDrawImage(background2BC);
        else if(pageOn == 3) oslDrawImage(background3BC);
        else if(pageOn == 4) oslDrawImage(background4BC);
        
        oslDrawImage(selectBC);
        
        /* draw lock symbols */
        oslSetTextColor(RED);
        
        if(pageOn == 1){
            if(DUDE_bought == false)         {oslDrawImage(lock1); oslPrintf_xy((lock1->x - 15),(lock1->y + 5), "$0");}
            if(SATHE_NORMAL_bought == false) {oslDrawImage(lock2); oslPrintf_xy((lock2->x - 15),(lock2->y + 5), "$400");}
            if(REPUBLIKEN_bought == false)   {oslDrawImage(lock3); oslPrintf_xy((lock3->x - 15),(lock3->y + 5), "$0");}
            if(ORRE_bought == false)         {oslDrawImage(lock4); oslPrintf_xy((lock4->x - 15),(lock4->y + 5), "$870");}
            if(BARON_bought == false)        {oslDrawImage(lock5); oslPrintf_xy((lock5->x - 15),(lock5->y + 5), "$1430");}
            if(BLADE_bought == false)        {oslDrawImage(lock6); oslPrintf_xy((lock6->x - 15),(lock6->y + 5), "$2000");}
            if(RYAN_bought == false)         {oslDrawImage(lock7); oslPrintf_xy((lock7->x - 15),(lock7->y + 5), "$2500");}
            if(EARTH_bought == false)        {oslDrawImage(lock8); oslPrintf_xy((lock8->x - 15),(lock8->y + 5), "$3400");}
        }
        else if(pageOn == 2){
            if(ATLANTIS_bought == false)     {oslDrawImage(lock1); oslPrintf_xy((lock1->x - 15),(lock1->y + 5), "$2400");}
            if(VEXUS_bought == false)        {oslDrawImage(lock2); oslPrintf_xy((lock2->x - 15),(lock2->y + 5), "$3500");}
            if(ZAMUS_NORMAL_bought == false) {oslDrawImage(lock3); oslPrintf_xy((lock3->x - 15),(lock3->y + 5), "$900");}
            if(SUPER_SATHE_bought == false)  {oslDrawImage(lock4); oslPrintf_xy((lock4->x - 15),(lock4->y + 5), "$5800");}
            if(GENAMI_bought == false)       {oslDrawImage(lock5); oslPrintf_xy((lock5->x - 15),(lock5->y + 5), "$4700");}
            if(ORPHEUS_bought == false)      {oslDrawImage(lock6); oslPrintf_xy((lock6->x - 15),(lock6->y + 5), "$8000");}
            if(SATHIMUS_bought == false)     {oslDrawImage(lock7); oslPrintf_xy((lock7->x - 15),(lock7->y + 5), "$7350");}
            if(WEAK_KROM_bought == false)    {oslDrawImage(lock8); oslPrintf_xy((lock8->x - 15),(lock8->y + 5), "$10000");}
        }
        else if(pageOn == 3){
            if(WEAK_WRAITH_bought == false) {oslDrawImage(lock1); oslPrintf_xy((lock1->x - 15),(lock1->y + 5), "$12000");}
            if(WRAITH_bought == false)      {oslDrawImage(lock2); oslPrintf_xy((lock2->x - 15),(lock2->y + 5), "$18000");}
            if(KRITH_bought == false)       {oslDrawImage(lock3); oslPrintf_xy((lock3->x - 15),(lock3->y + 5), "$20000");}
            if(ULTRA_SATHE_bought == false) {oslDrawImage(lock4); oslPrintf_xy((lock4->x - 15),(lock4->y + 5), "$16000");}
            if(ULTRA_ZAMUS_bought == false) {oslDrawImage(lock5); oslPrintf_xy((lock5->x - 15),(lock5->y + 5), "$11000");}
            if(KROM_bought == false)        {oslDrawImage(lock6); oslPrintf_xy((lock6->x - 15),(lock6->y + 5), "$26000");}
            if(SATHIS_bought == false)      {oslDrawImage(lock7); oslPrintf_xy((lock7->x - 15),(lock7->y + 5), "$26000");}
            if(PHALEM_bought == false)      {oslDrawImage(lock8); oslPrintf_xy((lock8->x - 15),(lock8->y + 5), "$26000");}
        }
        else if(pageOn == 4){
            if(FOURTH_ELDER_bought == false) {oslDrawImage(lock1); oslPrintf_xy((lock1->x - 15),(lock1->y + 5), "$35000");}
            if(FIFTH_ELDER_bought == false)  {oslDrawImage(lock2); oslPrintf_xy((lock2->x - 15),(lock2->y + 5), "$40000");}
            if(SIXTH_ELDER_bought == false)  {oslDrawImage(lock3); oslPrintf_xy((lock3->x - 15),(lock3->y + 5), "$60000");}
            if(ELDER_SATHE_bought == false)  {oslDrawImage(lock4); oslPrintf_xy((lock4->x - 15),(lock4->y + 5), "$100000");}
            if(ETHAS_bought == false)        {oslDrawImage(lock5); oslPrintf_xy((lock5->x - 15),(lock5->y + 5), "$79000");}
        }
        
        //display player money
        oslSetTextColor(WHITE); oslPrintf_xy(240, 40, "Player money left: $%lld", player.money);
        
        oslEndDrawing();
        oslSyncFrame();
    }
    
    //free memory
    if(selectBC != NULL){oslDeleteImage(selectBC); selectBC = NULL;}
    if(backgroundBC != NULL){oslDeleteImage(backgroundBC); backgroundBC = NULL;}
    if(background2BC != NULL){oslDeleteImage(background2BC); background2BC = NULL;}
    if(background3BC != NULL){oslDeleteImage(background3BC); background3BC = NULL;}
    if(background4BC != NULL){oslDeleteImage(background4BC); background4BC = NULL;}
    if(lock1 != NULL){oslDeleteImage(lock1); lock1 = NULL;}
    if(lock2 != NULL){oslDeleteImage(lock2); lock2 = NULL;}
    if(lock3 != NULL){oslDeleteImage(lock3); lock3 = NULL;}
    if(lock4 != NULL){oslDeleteImage(lock4); lock4 = NULL;}
    if(lock5 != NULL){oslDeleteImage(lock5); lock5 = NULL;}
    if(lock6 != NULL){oslDeleteImage(lock6); lock6 = NULL;}
    if(lock7 != NULL){oslDeleteImage(lock7); lock7 = NULL;}
    if(lock8 != NULL){oslDeleteImage(lock8); lock8 = NULL;}
    
    return;
}

MENU::MENU()
{
    return;
}

MENU::~MENU()
{
    
    return;
}