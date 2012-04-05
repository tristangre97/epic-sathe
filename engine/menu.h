/* 
 * class MENU ~V@ughn
 * -------------------
 * ->menu container for the game
 * 
 * @virtual void BuyCharacters() - character buy menu
 * @virtual void BuyItems() - buy items menu
 * @virtual void BuyLives() - buy lives menu
 * @virtual void UpgradeCharacter() - updgrade menu
 * @virtual int Customize() - customize directory
 * @virtual int MainMenu() - main menu
 * @virtual int SecondaryMenu() - second main menu
 * @virtual short BossMenu(...) - Boss selector menu
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
        
		//behaviors
        virtual void BuyCharacters();
        virtual void BuyItems();
        virtual void BuyLives();
        virtual void UpgradeCharacter();
        virtual int Customize();
        virtual int MainMenu();
        virtual int SecondaryMenu();
        virtual short BossMenu(const int currentLevel, int &trackLevel);

		MENU();
        ~MENU();
    
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
    menuChoice = 1;
    IMAGE * background = oslLoadImageFilePNG((char*)"img/data/lx1.png", OSL_IN_RAM, OSL_PF_5551);
    
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
		  if(osl_keys->pressed.cross) {oslPlaySound(select, 2); return SHOW_SECOND_MENU;}                      
		}
        
        else if(menuChoice == HELP)
        {
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
                  oslPrintf_xy(5, 25, "Programming: V@ughn");
				  oslPrintf_xy(5, 35, "Art: Devin and V@ughn");
                  oslSetTextColor(RED);
                  oslPrintf_xy(5, 55, "Tools used:");
                  oslSetTextColor(WHITE);
                  oslPrintf_xy(5, 65, "-Dev-C++ 4.9.9.2");
				  oslPrintf_xy(5, 75, "-Microsoft Visual C++ Express 2010");
                  oslPrintf_xy(5, 85, "-sfxr and cfxr sound generators");
                  oslPrintf_xy(5, 95, "-MS paint");
				  oslPrintf_xy(5, 105, "-Paint.NET");
                  oslPrintf_xy(5, 115, "-oslib");
				  oslSetTextColor(RED);
                  oslPrintf_xy(5, 135, "Latest Changes:");
				  oslSetTextColor(WHITE);
				  oslPrintf_xy(5, 145, "-changed background image");
				  oslPrintf_xy(5, 155, "-replaced all menus with a new look");
				  oslPrintf_xy(5, 165, "-did a complete rewrite on the game engine");
				  oslPrintf_xy(5, 175, "      ~documented code as well");
				  oslPrintf_xy(5, 185, "-fixed jumping (no second jump lag)");
				  oslPrintf_xy(5, 195, "-created jumping sound effect");
				  oslPrintf_xy(5, 205, "-enemies are now created dynamically");
				  oslPrintf_xy(5, 215, "      ~there is not a fixed number of enemies");
				  oslPrintf_xy(5, 225, "      ~enemy levels rise with level number now");
				  oslPrintf_xy(5, 235, "-fixed some minor animation glitches");
				  oslPrintf_xy(5, 245, "-player can now upgrade character!");
          
                  oslEndDrawing();
                  oslSyncFrame();
                }
          }
		}
		  
		else if(menuChoice == EXIT_GAME){
			if(osl_keys->pressed.cross) {oslPlaySound(select, 2); return EXIT;}
		}
		  
		oslStartDrawing();
		oslClearScreen(BLACK);
		oslDrawImage(background);

		oslIntraFontSetStyle(ltn, 1.7f,WHITE,BLACK,INTRAFONT_ALIGN_LEFT);
		oslDrawString(19, 25, "Epic Sathe");

		if(menuChoice == START_GAME) oslIntraFontSetStyle(ltn, 1.3f,RED,BLACK,INTRAFONT_ALIGN_LEFT);
		else oslIntraFontSetStyle(ltn, 1.0f,WHITE,BLACK,INTRAFONT_ALIGN_LEFT);
		oslDrawString(19, 63, "Start");

		if(menuChoice == HELP) oslIntraFontSetStyle(ltn, 1.3f,RED,BLACK,INTRAFONT_ALIGN_LEFT);
		else oslIntraFontSetStyle(ltn, 1.0f,WHITE,BLACK,INTRAFONT_ALIGN_LEFT);
		oslDrawString(19, 93, "Help");

		if(menuChoice == CREDITS) oslIntraFontSetStyle(ltn, 1.3f,RED,BLACK,INTRAFONT_ALIGN_LEFT);
		else oslIntraFontSetStyle(ltn, 1.0f,WHITE,BLACK,INTRAFONT_ALIGN_LEFT);
		oslDrawString(19, 123, "Credits");

		if(menuChoice == EXIT_GAME) oslIntraFontSetStyle(ltn, 1.3f,RED,BLACK,INTRAFONT_ALIGN_LEFT);
		else oslIntraFontSetStyle(ltn, 1.0f,WHITE,BLACK,INTRAFONT_ALIGN_LEFT);
		oslDrawString(19, 153, "Quit");
            
		oslEndDrawing();
		oslSyncFrame();		
    }
    
    if(background != NULL){oslDeleteImage(background); background = NULL;}
    
    return 1;
}

int MENU::SecondaryMenu()
{
    menuChoice = 1;
	IMAGE * background = oslLoadImageFilePNG((char*)"img/data/lx1.png", OSL_IN_RAM, OSL_PF_5551);

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
		  if(osl_keys->pressed.cross) {oslPlaySound(select, 2); MAIN_GAME(0); return SHOW_MAIN_MENU;}                      
		}
        
        else if(menuChoice == LOAD_OLD_STATS){
		  if(osl_keys->pressed.cross){
                oslPlaySound(select, 2); 
                int check = LoadGame();
                if(check == 0)oslDebug("ERROR! NO SAVE DATA CAN BE LOADED!"); 
                return SHOW_SECOND_MENU;
            }
		}	
		
		else if(menuChoice == BOSS_MODE){
		  if(osl_keys->pressed.cross){oslPlaySound(select, 2); MAIN_GAME(1); return SHOW_MAIN_MENU; }
		}
		  
		else if(menuChoice == MULTIPLAYER){
	      if(osl_keys->pressed.cross) {oslPlaySound(select, 2); InitAdhocGame(); return SHOW_MAIN_MENU;}
		}
		
		else if(menuChoice == BACK){
	      if(osl_keys->pressed.cross) {oslPlaySound(select, 2); return SHOW_MAIN_MENU;}
		}
		  
		oslStartDrawing();
		oslClearScreen(BLACK);
		oslDrawImage(background);

		oslIntraFontSetStyle(ltn, 1.7f,WHITE,BLACK,INTRAFONT_ALIGN_LEFT);
		oslDrawString(19, 25, "Epic Sathe");

		if(menuChoice == SOLO_MODE) oslIntraFontSetStyle(ltn, 1.3f,RED,BLACK,INTRAFONT_ALIGN_LEFT);
		else oslIntraFontSetStyle(ltn, 1.0f,WHITE,BLACK,INTRAFONT_ALIGN_LEFT);
		oslDrawString(19, 63, "Solo mode");

		if(menuChoice == LOAD_OLD_STATS) oslIntraFontSetStyle(ltn, 1.3f,RED,BLACK,INTRAFONT_ALIGN_LEFT);
		else oslIntraFontSetStyle(ltn, 1.0f,WHITE,BLACK,INTRAFONT_ALIGN_LEFT);
		oslDrawString(19, 93, "Load");

		if(menuChoice == BOSS_MODE) oslIntraFontSetStyle(ltn, 1.3f,RED,BLACK,INTRAFONT_ALIGN_LEFT);
		else oslIntraFontSetStyle(ltn, 1.0f,WHITE,BLACK,INTRAFONT_ALIGN_LEFT);
		oslDrawString(19, 123, "Boss mode");

		if(menuChoice == MULTIPLAYER) oslIntraFontSetStyle(ltn, 1.3f,RED,BLACK,INTRAFONT_ALIGN_LEFT);
		else oslIntraFontSetStyle(ltn, 1.0f,WHITE,BLACK,INTRAFONT_ALIGN_LEFT);
		oslDrawString(19, 153, "Multiplayer");

		if(menuChoice == BACK) oslIntraFontSetStyle(ltn, 1.3f,RED,BLACK,INTRAFONT_ALIGN_LEFT);
		else oslIntraFontSetStyle(ltn, 1.0f,WHITE,BLACK,INTRAFONT_ALIGN_LEFT);
		oslDrawString(19, 183, "Back");
            
		oslEndDrawing();
		oslSyncFrame();			
    }
    
	if(background != NULL){oslDeleteImage(background); background = NULL;}

    return 1;
}

int MENU::Customize()
{
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
		    if(osl_keys->pressed.cross || osl_keys->pressed.start) {oslPlaySound(select, 2); BuyCharacters();}                      
		}
        
        else if(menuChoice == BUY_NEW_ITEMS){
			if(osl_keys->pressed.cross || osl_keys->pressed.start){oslPlaySound(select, 2); BuyItems();}
		}	
		
		else if(menuChoice == BUY_MORE_LIVES){
			if(osl_keys->pressed.cross || osl_keys->pressed.start){oslPlaySound(select, 2); BuyLives();}
		}
		  
		else if(menuChoice == UPGRADE_CHARACTER){
			if(osl_keys->pressed.cross || osl_keys->pressed.start){oslPlaySound(select, 2); UpgradeCharacter();}
		}
		
		else if(menuChoice == BACK){
			if(osl_keys->pressed.cross || osl_keys->pressed.start){oslPlaySound(select, 2); return SHOW_MAIN_MENU;}
		}
		
		/* draw everything */
        oslStartDrawing();
        oslClearScreen(BLACK);
        
		oslIntraFontSetStyle(ltn, 1.7f,WHITE,BLACK,INTRAFONT_ALIGN_LEFT);
		oslDrawString(19, 25, "Customize");

		if(menuChoice == BUY_NEW_CHARACTER) oslIntraFontSetStyle(ltn, 1.3f,RED,BLACK,INTRAFONT_ALIGN_LEFT);
		else oslIntraFontSetStyle(ltn, 1.0f,WHITE,BLACK,INTRAFONT_ALIGN_LEFT);
		oslDrawString(19, 63, "Buy New Characters");

		if(menuChoice == BUY_NEW_ITEMS) oslIntraFontSetStyle(ltn, 1.3f,RED,BLACK,INTRAFONT_ALIGN_LEFT);
		else oslIntraFontSetStyle(ltn, 1.0f,WHITE,BLACK,INTRAFONT_ALIGN_LEFT);
		oslDrawString(19, 93, "Buy New Items");

		if(menuChoice == BUY_MORE_LIVES) oslIntraFontSetStyle(ltn, 1.3f,RED,BLACK,INTRAFONT_ALIGN_LEFT);
		else oslIntraFontSetStyle(ltn, 1.0f,WHITE,BLACK,INTRAFONT_ALIGN_LEFT);
		oslDrawString(19, 123, "Buy more Lives");

		if(menuChoice == UPGRADE_CHARACTER) oslIntraFontSetStyle(ltn, 1.3f,RED,BLACK,INTRAFONT_ALIGN_LEFT);
		else oslIntraFontSetStyle(ltn, 1.0f,WHITE,BLACK,INTRAFONT_ALIGN_LEFT);
		oslDrawString(19, 153, "Upgrade Character");

		if(menuChoice == BACK) oslIntraFontSetStyle(ltn, 1.3f,RED,BLACK,INTRAFONT_ALIGN_LEFT);
		else oslIntraFontSetStyle(ltn, 1.0f,WHITE,BLACK,INTRAFONT_ALIGN_LEFT);
		oslDrawString(19, 183, "Back");

        oslEndDrawing();
        oslSyncFrame();
    }
    
    return SHOW_MAIN_MENU;
}

void MENU::BuyItems()
{
    cost = 99999;
    menuChoice = 1;

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
		    if(osl_keys->pressed.cross) {oslPlaySound(select, 2);}  
            else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);                         
		}
        
        else if(menuChoice == FREEZING_PUNCH){
			if(osl_keys->pressed.cross){oslPlaySound(select, 2);}
			else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);     
		}	
		
		else if(menuChoice == SWIFTNESS){
            cost = 1000;
			if(osl_keys->pressed.cross && player.money > cost){
                oslPlaySound(select, 2);
                player.speed *= 2;
                player.money -= cost;
            }
			else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);     
		}
		  
		else if(menuChoice == SATHES_BRUTE){
			if(osl_keys->pressed.cross){oslPlaySound(select, 2);}
			else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);     
		}
		
		else if(menuChoice == BACK){
			if(osl_keys->pressed.cross){oslPlaySound(select, 2); break;}
		}
		
        oslStartDrawing();
        oslClearScreen(BLACK);
        
		oslIntraFontSetStyle(ltn, 1.7f,WHITE,BLACK,INTRAFONT_ALIGN_LEFT);
		oslDrawString(19, 25, "Customize");

		if(menuChoice == FLYING_PUNCH) oslIntraFontSetStyle(ltn, 1.3f,RED,BLACK,INTRAFONT_ALIGN_LEFT);
		else oslIntraFontSetStyle(ltn, 1.0f,WHITE,BLACK,INTRAFONT_ALIGN_LEFT);
		oslDrawString(19, 63, "Flying Punch $250");

		if(menuChoice == FREEZING_PUNCH) oslIntraFontSetStyle(ltn, 1.3f,RED,BLACK,INTRAFONT_ALIGN_LEFT);
		else oslIntraFontSetStyle(ltn, 1.0f,WHITE,BLACK,INTRAFONT_ALIGN_LEFT);
		oslDrawString(19, 93, "Freezing Punch $500");

		if(menuChoice == SWIFTNESS) oslIntraFontSetStyle(ltn, 1.3f,RED,BLACK,INTRAFONT_ALIGN_LEFT);
		else oslIntraFontSetStyle(ltn, 1.0f,WHITE,BLACK,INTRAFONT_ALIGN_LEFT);
		oslDrawString(19, 123, "Swiftness $1000");

		if(menuChoice == UPGRADE_CHARACTER) oslIntraFontSetStyle(ltn, 1.3f,RED,BLACK,INTRAFONT_ALIGN_LEFT);
		else oslIntraFontSetStyle(ltn, 1.0f,WHITE,BLACK,INTRAFONT_ALIGN_LEFT);
		oslDrawString(19, 153, "Upgrade Character");

		if(menuChoice == BACK) oslIntraFontSetStyle(ltn, 1.3f,RED,BLACK,INTRAFONT_ALIGN_LEFT);
		else oslIntraFontSetStyle(ltn, 1.0f,WHITE,BLACK,INTRAFONT_ALIGN_LEFT);
		oslDrawString(19, 183, "Back");

        
        //display player money
        oslSetTextColor(WHITE); oslPrintf_xy(250, 20, "Player money left: $%lld", player.money);
        
        oslEndDrawing();
        oslSyncFrame();
    }
    
    return;
}

void MENU::BuyLives()
{
    menuChoice = 1;
    cost = 0;
    
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
		    cost = 100;
		    if(osl_keys->pressed.cross && player.money >= cost){oslPlaySound(bought, 7); player.money -= cost; player.lives++;}    
              else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);                     
		}
        
        else if(menuChoice == BUY3){
			cost = 250;
		    if(osl_keys->pressed.cross && player.money >= cost){oslPlaySound(bought, 7); player.money -= cost; player.lives+=3;}       
              else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);                  
		}	
		
		else if(menuChoice == BUY9){
			cost = 500;
		    if(osl_keys->pressed.cross && player.money >= cost){oslPlaySound(bought, 7); player.money -= cost; player.lives+=9;}  
              else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);                       
		}
		  
		else if(menuChoice == BUY15){
			cost = 890;
		    if(osl_keys->pressed.cross && player.money >= cost){oslPlaySound(bought, 7); player.money -= cost; player.lives+=15;}  
            else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);                       
		}
		
		else if(menuChoice == BACK){
			if(osl_keys->pressed.cross){oslPlaySound(select, 2); break;}
		}
		
        oslStartDrawing();
        oslClearScreen(BLACK);
        
		oslIntraFontSetStyle(ltn, 1.7f,WHITE,BLACK,INTRAFONT_ALIGN_LEFT);
		oslDrawString(19, 25, "Customize");

		if(menuChoice == BUY1) oslIntraFontSetStyle(ltn, 1.3f,RED,BLACK,INTRAFONT_ALIGN_LEFT);
		else oslIntraFontSetStyle(ltn, 1.0f,WHITE,BLACK,INTRAFONT_ALIGN_LEFT);
		oslDrawString(19, 63, "Buy 1 life $100");

		if(menuChoice == BUY3) oslIntraFontSetStyle(ltn, 1.3f,RED,BLACK,INTRAFONT_ALIGN_LEFT);
		else oslIntraFontSetStyle(ltn, 1.0f,WHITE,BLACK,INTRAFONT_ALIGN_LEFT);
		oslDrawString(19, 93, "Buy 3 lives $250");

		if(menuChoice == BUY9) oslIntraFontSetStyle(ltn, 1.3f,RED,BLACK,INTRAFONT_ALIGN_LEFT);
		else oslIntraFontSetStyle(ltn, 1.0f,WHITE,BLACK,INTRAFONT_ALIGN_LEFT);
		oslDrawString(19, 123, "Buy 9 lives $500");

		if(menuChoice == BUY15) oslIntraFontSetStyle(ltn, 1.3f,RED,BLACK,INTRAFONT_ALIGN_LEFT);
		else oslIntraFontSetStyle(ltn, 1.0f,WHITE,BLACK,INTRAFONT_ALIGN_LEFT);
		oslDrawString(19, 153, "Buy 15 lives $890");

		if(menuChoice == BACK) oslIntraFontSetStyle(ltn, 1.3f,RED,BLACK,INTRAFONT_ALIGN_LEFT);
		else oslIntraFontSetStyle(ltn, 1.0f,WHITE,BLACK,INTRAFONT_ALIGN_LEFT);
		oslDrawString(19, 183, "Back");

        
        //display player money
        oslSetTextColor(WHITE); oslPrintf_xy(250, 20, "Player money left: $%lld", player.money);
        
        oslEndDrawing();
        oslSyncFrame();
    }
    
    return;
}

void MENU::UpgradeCharacter()
{
    cost = 99999;
    menuChoice = 1;

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
        
        if(menuChoice == UPGRADE_HEALTH)
		{
			//set price of item
			if(healthLevel == 0)     cost = 800;
			else if(healthLevel == 1)cost = 1500;
			else if(healthLevel == 2)cost = 3000;
			else cost = 0;

		    if(osl_keys->pressed.cross && player.money >= cost && healthLevel < 3){
				player.money -= cost;
				healthLevel++;
			    if(healthLevel == 1)     healthManip = 1.3;
				else if(healthLevel == 2)healthManip = 1.6;
				else if(healthLevel == 3)healthManip = 2.1;
				player.SetUp(player.id);

				oslPlaySound(bought, 2);
			}
			else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);                         
		}
        
        else if(menuChoice == UPGRADE_ATTACK)
		{
			//set price of item
			if(attackLevel == 0)     cost = 1000;
			else if(attackLevel == 1)cost = 2800;
			else if(attackLevel == 2)cost = 5600;
			else cost = 0;

			if(osl_keys->pressed.cross && player.money >= cost){
				player.money -= cost;
				attackLevel++;
				if(attackLevel == 1)     attackManip = 1.2;
				else if(attackLevel == 2)attackManip = 1.5;
				else if(attackLevel == 3)attackManip = 1.9;
				player.SetUp(player.id);

				oslPlaySound(bought, 2);
			}
			else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);       
		}	
		
		else if(menuChoice == UPGRADE_JUMP_HEIGHT)
		{
			//set price of item
			if(jumpLevel == 0)     cost = 800;
			else if(jumpLevel == 1)cost = 900;
			else if(jumpLevel == 2)cost = 1000;
			else cost = 0;

			if(osl_keys->pressed.cross && player.money >= cost && jumpLevel < 3){
				player.money -= cost;
				jumpLevel++;
				if(jumpLevel == 1)      jumpManip = 1.1;
				else if(jumpLevel == 2) jumpManip = 1.2;
				else if(jumpLevel == 3) jumpManip = 1.35;
				player.SetUp(player.id);

				oslPlaySound(bought, 2);
			}
			else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);    
		}
		  
		else if(menuChoice == UPGRADE_MAX_POWER){
			//set price of item
			if(powerLevel == 0)cost = 3000;
			else if(powerLevel == 1)cost = 8000;
			else if(powerLevel == 2)cost = 14000;
			else cost = 0;

			if(osl_keys->pressed.cross && player.money >= cost && powerLevel < 3){
				player.money -= cost;
				powerLevel++;
				if(powerLevel == 1)     powerManip = 1.6;
				else if(powerLevel == 2)powerManip = 2.1;
				else if(powerLevel == 3)powerManip = 3.4;
				player.SetUp(player.id);

				oslPlaySound(bought, 2);
			}
			else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);     
		}
		
		else if(menuChoice == BACK){
			if(osl_keys->pressed.cross){oslPlaySound(select, 2); break;}  
		}
		
        oslStartDrawing();
        oslClearScreen(BLACK);
        
		oslIntraFontSetStyle(ltn, 1.7f,WHITE,BLACK,INTRAFONT_ALIGN_LEFT);
		oslDrawString(19, 25, "Customize");

		if(menuChoice == UPGRADE_HEALTH) oslIntraFontSetStyle(ltn, 1.3f,RED,BLACK,INTRAFONT_ALIGN_LEFT);
		else oslIntraFontSetStyle(ltn, 1.0f,WHITE,BLACK,INTRAFONT_ALIGN_LEFT);

		if(healthLevel == 0)     oslDrawString(19, 63, "Upgrade Health to Lv1 $800");
		else if(healthLevel == 1)oslDrawString(19, 63, "Upgrade Health to Lv2 $1500");
		else if(healthLevel == 2)oslDrawString(19, 63, "Upgrade Health to Lv3 $3000");
		else if(healthLevel == 3)oslDrawString(19, 63, "Health Maxed Out");

		if(menuChoice == UPGRADE_ATTACK) oslIntraFontSetStyle(ltn, 1.3f,RED,BLACK,INTRAFONT_ALIGN_LEFT);
		else oslIntraFontSetStyle(ltn, 1.0f,WHITE,BLACK,INTRAFONT_ALIGN_LEFT);

		if(attackLevel == 0)     oslDrawString(19, 93, "Upgrade Attack to Lv1 $1000");
		else if(attackLevel == 1)oslDrawString(19, 93, "Upgrade Attack to Lv2 $2800");
		else if(attackLevel == 2)oslDrawString(19, 93, "Upgrade Attack to Lv3 $5600");
		else if(attackLevel == 3)oslDrawString(19, 93, "Attack Maxed Out");

		if(menuChoice == UPGRADE_JUMP_HEIGHT) oslIntraFontSetStyle(ltn, 1.3f,RED,BLACK,INTRAFONT_ALIGN_LEFT);
		else oslIntraFontSetStyle(ltn, 1.0f,WHITE,BLACK,INTRAFONT_ALIGN_LEFT);
		
		if(jumpLevel == 0)     oslDrawString(19, 123, "Upgrade Jump to Lv1 $800");
		else if(jumpLevel == 1)oslDrawString(19, 123, "Upgrade Jump to Lv2 $900");
		else if(jumpLevel == 2)oslDrawString(19, 123, "Upgrade Jump to Lv3 $1000");
		else if(jumpLevel == 3)oslDrawString(19, 123, "Jump Height Maxed Out");

		if(menuChoice == UPGRADE_MAX_POWER) oslIntraFontSetStyle(ltn, 1.3f,RED,BLACK,INTRAFONT_ALIGN_LEFT);
		else oslIntraFontSetStyle(ltn, 1.0f,WHITE,BLACK,INTRAFONT_ALIGN_LEFT);
		
		if(powerLevel == 0)     oslDrawString(19, 153, "Upgrade Power to Lv1 $3000");
		else if(powerLevel == 1)oslDrawString(19, 153, "Upgrade Power to Lv2 $8000");
		else if(powerLevel == 2)oslDrawString(19, 153, "Upgrade Power to Lv3 $14000");
		else if(powerLevel == 3)oslDrawString(19, 153, "Power Maxed Out");

		if(menuChoice == BACK) oslIntraFontSetStyle(ltn, 1.3f,RED,BLACK,INTRAFONT_ALIGN_LEFT);
		else oslIntraFontSetStyle(ltn, 1.0f,WHITE,BLACK,INTRAFONT_ALIGN_LEFT);
		oslDrawString(19, 183, "Back");

        
        //display player money
        oslSetTextColor(WHITE); oslPrintf_xy(250, 20, "Player money left: $%lld", player.money);
        
        oslEndDrawing();
        oslSyncFrame();
    }
    
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
        
		oslIntraFontSetStyle(ltn, 1.7f,WHITE,BLACK,INTRAFONT_ALIGN_LEFT);
		oslDrawString(19, 25, "Customize");

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
