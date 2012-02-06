class MENU
{
    public:
        MENU();
        ~MENU();
        
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
        
        void BuyCharacters();

        void BuyItems();

        void BuyLives();

        void UpgradeCharacter();

        void Customize();
        
        int MainMenu();
        
        int SecondaryMenu();
    
    private:
        OSL_IMAGE * selector;
        OSL_IMAGE * background;
        int menuChoice;
        int cost;
}menu;

int MENU::MainMenu()
{
    menuChoice = 1;
    background = oslLoadImageFilePNG((char*)"img/data/menu.png", OSL_IN_RAM, OSL_PF_5551);
    selector = oslLoadImageFilePNG((char*)"img/data/selector.png", OSL_IN_RAM, OSL_PF_5551);  
    
    //set up a menu animation
    PLAYER menuGuy;
    menuGuy.image = menuGuy.SetImage(-1);
    menuGuy.position = STILL_RIGHT;
    oslSetImageTileSize(menuGuy.image,1 * 53,menuGuy.position,53,76);
    menuGuy.image->x = 330;
    menuGuy.image->y = 140;
    
    #define START_GAME 1
    #define CUSTOMIZE 2
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
        
        else if(menuChoice == CUSTOMIZE){
		  placeSelector(selector, 19, 149);
		  if(osl_keys->pressed.cross){oslPlaySound(select, 2); menu.Customize(); }
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
                  oslPrintf_xy(5, 15, "Credits: Epic Sathe v0.4");
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
          }
		}
		  
		else if(menuChoice == EXIT_GAME){
		  placeSelector(selector, 19, 228);
	      if(osl_keys->pressed.cross) return EXIT;
		}
		  
		//Moves the sprite in the row that it is in
        menuGuy.manipulate++; if(menuGuy.manipulate > 9) {menuGuy.march++; menuGuy.manipulate = 0;}
        oslSetImageTileSize(menuGuy.image,menuGuy.march * 53,menuGuy.position,53,76);
        if(menuGuy.march == 3) menuGuy.march = 0;
		  
		oslStartDrawing();
		oslClearScreen(BLACK);
		oslDrawImage(background);
        oslDrawImage(selector);
        oslDrawImage(menuGuy.image);
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
    background = oslLoadImageFilePNG((char*)"img/data/menu2.png", OSL_IN_RAM, OSL_PF_5551);
    selector = oslLoadImageFilePNG((char*)"img/data/selector.png", OSL_IN_RAM, OSL_PF_5551);  
    
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
		  placeSelector(selector, 19,104);
		  if(osl_keys->pressed.cross) {oslPlaySound(select, 2); MAIN_GAME(); return SHOW_MAIN_MENU;}                      
		}
        
        else if(menuChoice == LOAD_OLD_STATS){
		  placeSelector(selector, 19, 141);
		  if(osl_keys->pressed.cross){oslPlaySound(select, 2);}
		}	
		
		else if(menuChoice == BOSS_MODE){
		  placeSelector(selector, 19, 175);
		  if(osl_keys->pressed.cross){oslPlaySound(select, 2);}
		}
		  
		else if(menuChoice == MULTIPLAYER){
		  placeSelector(selector, 19, 212);
	      if(osl_keys->pressed.cross) {oslPlaySound(select, 2); online.InitAdhocGame(); return SHOW_MAIN_MENU;}
		}
		
		else if(menuChoice == BACK){
		  placeSelector(selector, 19, 248);
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

void MENU::Customize()
{
    //load images
    background = oslLoadImageFilePNG((char*)"img/data/customize1.png", OSL_IN_RAM, OSL_PF_5551);
    selector = oslLoadImageFilePNG((char*)"img/data/selector2.png", OSL_IN_RAM, OSL_PF_5551);
    
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
		else if(osl_keys->pressed.circle){oslPlaySound(select, 2); break;}
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
			if(osl_keys->pressed.cross || osl_keys->pressed.start){oslPlaySound(select, 2); break;}
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
    
    return;
}

void MENU::BuyItems()
{
    cost = 99999;
    menuChoice = 1;
    selector = oslLoadImageFilePNG((char*)"img/data/selector2.png", OSL_IN_RAM, OSL_PF_5551);
    background = oslLoadImageFilePNG((char*)"img/data/customize3.png", OSL_IN_RAM, OSL_PF_5551);
    
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
		else if(osl_keys->pressed.circle){oslPlaySound(select, 2); break;}
		if(menuChoice > 5) menuChoice = 1;
        if(menuChoice < 1) menuChoice = 5;
        
        if(menuChoice == FLYING_PUNCH){
		    placeSelector(selector, 19,116);
		    if(osl_keys->pressed.cross) {oslPlaySound(select, 2);}  
            else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);                         
		}
        
        else if(menuChoice == FREEZING_PUNCH){
			placeSelector(selector, 19, 148);
			if(osl_keys->pressed.cross){oslPlaySound(select, 2);}
			else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);     
		}	
		
		else if(menuChoice == SWIFTNESS){
			placeSelector(selector, 20, 177);
			if(osl_keys->pressed.cross){oslPlaySound(select, 2);}
			else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);     
		}
		  
		else if(menuChoice == SATHES_BRUTE){
			placeSelector(selector, 20, 205);
			if(osl_keys->pressed.cross){oslPlaySound(select, 2);}
			else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);     
		}
		
		else if(menuChoice == BACK){
			placeSelector(selector, 20, 232);
			if(osl_keys->pressed.cross){oslPlaySound(select, 2); break;}
		}
		
        oslStartDrawing();
        oslClearScreen(BLACK);
        oslDrawImage(background);
        oslDrawImage(selector);
        
        //display player money
        oslSetTextColor(WHITE); oslPrintf_xy(250, 20, "Player money left: $%lld", player.money);
        
        oslEndDrawing();
        oslSyncFrame();
    }
    
    //free memory
    if(selector != NULL)  {oslDeleteImage(selector); selector = NULL;}
    if(background != NULL){oslDeleteImage(background); background = NULL;}
    
    return;
}

void MENU::BuyLives()
{
    menuChoice = 1;
    cost = 0;
    selector = oslLoadImageFilePNG((char*)"img/data/selector2.png", OSL_IN_RAM, OSL_PF_5551);
    background = oslLoadImageFilePNG((char*)"img/data/customize4.png", OSL_IN_RAM, OSL_PF_5551);
    
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
		else if(osl_keys->pressed.circle){oslPlaySound(select, 2); break;}
		if(menuChoice > 5) menuChoice = 1;
        if(menuChoice < 1) menuChoice = 5;
        
        if(menuChoice == BUY1){
		    placeSelector(selector, 19,116);
		    cost = 100;
		    if(osl_keys->pressed.cross && player.money >= cost){oslPlaySound(bought, 7); player.money -= cost; player.lives++;}    
              else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);                     
		}
        
        else if(menuChoice == BUY3){
			placeSelector(selector, 19, 148);
			cost = 250;
		    if(osl_keys->pressed.cross && player.money >= cost){oslPlaySound(bought, 7); player.money -= cost; player.lives+=3;}       
              else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);                  
		}	
		
		else if(menuChoice == BUY9){
			placeSelector(selector, 20, 177);
			cost = 500;
		    if(osl_keys->pressed.cross && player.money >= cost){oslPlaySound(bought, 7); player.money -= cost; player.lives+=9;}  
              else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);                       
		}
		  
		else if(menuChoice == BUY15){
			placeSelector(selector, 20, 205);
			cost = 890;
		    if(osl_keys->pressed.cross && player.money >= cost){oslPlaySound(bought, 7); player.money -= cost; player.lives+=15;}  
            else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);                       
		}
		
		else if(menuChoice == BACK){
			placeSelector(selector, 20, 232);
			if(osl_keys->pressed.cross){oslPlaySound(select, 2); break;}
		}
		
        oslStartDrawing();
        oslClearScreen(BLACK);
        oslDrawImage(background);
        oslDrawImage(selector);
        
        //display player money
        oslSetTextColor(WHITE); oslPrintf_xy(250, 20, "Player money left: $%lld", player.money);
        
        oslEndDrawing();
        oslSyncFrame();
    }
    
    //free memory
    if(selector != NULL) {oslDeleteImage(selector); selector = NULL;}
    if(background != NULL){oslDeleteImage(background); background = NULL;}
    
    return;
}

void MENU::UpgradeCharacter()
{
    cost = 99999;
    menuChoice = 1;
    selector = oslLoadImageFilePNG((char*)"img/data/selector2.png", OSL_IN_RAM, OSL_PF_5551);
    background = oslLoadImageFilePNG((char*)"img/data/customize5.png", OSL_IN_RAM, OSL_PF_5551);
    
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
		else if(osl_keys->pressed.circle){oslPlaySound(select, 2); break;}
		if(menuChoice > 5) menuChoice = 1;
        if(menuChoice < 1) menuChoice = 5;
        
        if(menuChoice == UPGRADE_HEALTH){
		    placeSelector(selector, 19,116);
		    if(osl_keys->pressed.cross) {oslPlaySound(bought, 2);}   
            else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);                        
		}
        
        else if(menuChoice == UPGRADE_ATTACK){
			placeSelector(selector, 19, 148);
			if(osl_keys->pressed.cross){oslPlaySound(bought, 2);}
			else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);     
		}	
		
		else if(menuChoice == UPGRADE_JUMP_HEIGHT){
			placeSelector(selector, 20, 177);
			if(osl_keys->pressed.cross){oslPlaySound(bought, 2);}
			else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);     
		}
		  
		else if(menuChoice == UPGRADE_MAX_POWER){
			placeSelector(selector, 20, 205);
			if(osl_keys->pressed.cross){oslPlaySound(bought, 2);}
			else if(osl_keys->pressed.cross && player.money < cost)oslPlaySound(error, 7);     
		}
		
		else if(menuChoice == BACK){
			placeSelector(selector, 20, 232);
			if(osl_keys->pressed.cross){oslPlaySound(bought, 2); break;}  
		}
		
        oslStartDrawing();
        oslClearScreen(BLACK);
        oslDrawImage(background);
        oslDrawImage(selector);
        
        //display player money
        oslSetTextColor(WHITE); oslPrintf_xy(250, 20, "Player money left: $%lld", player.money);
        
        oslEndDrawing();
        oslSyncFrame();
    }
    
    //free memory
    if(selector != NULL) {oslDeleteImage(selector); selector = NULL;}
    if(background != NULL){oslDeleteImage(background); background = NULL;}
    
    return;
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
        
        if(osl_keys->pressed.circle)    {oslPlaySound(select, 2); break;}
        
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
    if(selector != NULL){oslDeleteImage(selector); selector = NULL;}
    return;
}
