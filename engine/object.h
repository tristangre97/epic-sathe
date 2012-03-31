/** 
 * class OBJECT : public STATS ~V@ughn
 * ------------------------------------
 * ->container for many different types of objects:
 *  
 * @UpdatePlayer(int MODE, struct remotePsp *aPsp) - updates player
 * @UpdateEnemy()  - updates enemies
 * @SetUp(const int changeId) -sets up player stats
 * @UpdateFriend(IMAGE * image) -updates a buddy
 * @Reward(const int id, long long &money)-adds player money, resets enemy, and plays death sound
 * @SetUpEnemy(const int changeId, int x, int y) - sets up enemy stats
 *      
 */

class OBJECT : public STATS {
    public:
          OBJECT();
          ~OBJECT();
          
          //properites
          long long money;
          long maxHealth;
          int facingLeft;
          int facingRight;
          int speed;
          int special;
          int waitToAttack;
          short lives;
          short facing;
          bool quit;
          bool powerActivated;
          bool toggle;
          bool initialBoot;
          
          //methods
          virtual void UpdatePlayer(int MODE, struct remotePsp *aPsp);
          virtual void SetUp(const int changeId);
          
          //multiplayer methods
          virtual void UpdateFriend(IMAGE * image);
          
          //ENEMY methods
          virtual void Reward(const int id, long long &money);
          virtual void SetUpEnemy(const int changeId, int x, int y);  
		  virtual void UpdateEnemy();
    
    private:
          int sy;
          int manip;
          int manip2;
          int manip3;
          int manipGlow;

}player, spawn, enemy[MAX_ENEMIES];

/* effect macros */
#define BLOWN_BACK_RIGHT 893
#define BLOWN_BACK_LEFT 793
#define NOTHING 0

/* sprite positions */
#define STILL_RIGHT 0
#define GUARDING_RIGHT 54
#define RIGHT 108
#define LEFT 162
#define ATTACKING_RIGHT 216
#define ATTACKING_LEFT 270
#define JUMPING 324
#define GUARDING_LEFT 378
#define STILL_LEFT 432

/**
 * class BOSS : public OBJECT ~V@ughn
 * ----------------------------------
 * ->subclass of class OBJECT
 * ->used to create bosses
 *
 */
class BOSS : public OBJECT {
    public:
        const char * line1;
        const char * line2;
        const char * line3;
        const char * playerLine1;
        const char * playerLine2;
        const char * playerLine3;
        
    private:
}boss;

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
//OBJECT methods://///////////////////////////////////////////////////////////////////////////

void OBJECT::UpdatePlayer(int MODE, struct remotePsp *aPsp)
{
    SpriteAnimate();
    
    if(image->x > 440) image->x = 440;
    if(image->x < -10) image->x = -10;
        
    //gravity
    if(image->y != (GROUND - image->stretchY)){touchingGround = false; sy++;}
    if(image->y > (GROUND - image->stretchY)){image->y = (GROUND - image->stretchY); sy = 0;}
    else if(image->y == (GROUND - image->stretchY)) touchingGround = true;
    image->y+=sy;
    
    //handle power
    if(powerActivated){
        manip2++;
        if(manip2 >= 15){power--; manip2 = 0;}
        if(power <= 0){powerActivated = false; power = maxPower;}
    }
    
    //handle player health and lives
    if(health <= 0){
        lives--; image->y = 20; 
        image->x = 240; 
        health = SetHealth(id);
    }
    if(lives < 0) quit = true;
    
    /* read player input */
    oslReadKeys();
    
    if(MODE == 1){
        
        //allow termination of adhoc game
	    if (osl_keys->released.select){}
		
	    else if (osl_keys->released.left)
		  {}
    }
	
    //pausing
    if(osl_keys->pressed.start)PauseGame();
    
    //toggle onscreen text
    if(osl_keys->pressed.select) {if(toggle)toggle = false; else toggle = true;}
    
	//jumping
    if(touchingGround && osl_keys->pressed.cross) 
    {
        touchingGround = false;
		position = JUMPING;
        if(powerActivated)sy -= (jumpHeight * 2);
		else sy -= jumpHeight;
		oslPlaySound(jump, 5);
    }

    //punching/attacking
    else if(osl_keys->pressed.square)
    {   
        if(facing == facingRight && touchingGround) position = ATTACKING_RIGHT;
        if(facing == facingLeft && touchingGround)  position = ATTACKING_LEFT;
        
        attacking = true;
        guarding = false;
    }
    
    //guarding/shielding
    else if(osl_keys->held.triangle)
    {  
        if(facing == facingRight && touchingGround) position = GUARDING_RIGHT;
        if(facing == facingLeft && touchingGround)  position = GUARDING_LEFT;
        
        guarding = true;
        attacking = false;
    }
    
    //movement
    else if(osl_keys->held.left)
    {
        if(touchingGround){
            position = LEFT; 
        }
        facing = facingLeft; 
        image->x-=speed;
        if(powerActivated)image->x-=speed;
    }
    
    //movement
    else if(osl_keys->held.right)
    { 
        if(touchingGround){
            position = RIGHT; 
        }
        facing = facingRight; 
        image->x+=speed; 
        if(powerActivated)image->x+=speed;
    }
        
    //sprite animation
    else if (!osl_keys->held.value) {
        guarding = false;
        attacking = false;
        
        if(facing == facingLeft  && touchingGround) position = STILL_LEFT; 
        if(facing == facingRight  && touchingGround) position = STILL_RIGHT;
		if(!touchingGround) position = JUMPING;
    }
    
    return;
}

inline void OBJECT::UpdateFriend(IMAGE * image)
{
    
    return;
}

inline void OBJECT::UpdateEnemy()
{
    SpriteAnimate();
    
    if(image->x > 440)   image->x = 440;
    if(image->x < -10)   image->x = -10;
    
    //gravity
    image->y+=sy;
    if(image->y > (GROUND - image->stretchY)) image->y = (GROUND - image->stretchY);
    if(image->y != (GROUND - image->stretchY)){touchingGround = false; sy++;}
    else touchingGround = true;
    
    //show enemy  and enemy health
    oslSetTextColor(0xFF0000FF);
    oslPrintf_xy(image->x, image->y - 10, "HP: %lld", health);
    
    //check for collisions
    int colliding = collision(player.image,player.image->x, player.image->y,image, image->x,image->y);
    
    //special effects
    if(special == BLOWN_BACK_RIGHT){if(image->x < 440)image->x+=5; if(image->y >50)image->y-=10;if(image->x >= 440) special = NOTHING;}
    else if(special == BLOWN_BACK_LEFT){if(image->x > 0)image->x-=5; if(image->y >50)image->y-=10;if(image->x <= 0) special = NOTHING;}
      
    //player attack
    if(player.attacking && colliding)
    {

        //subtract health
        if(player.powerActivated == false)  health -= player.attack; 
        if(player.powerActivated == true)   health -= (player.attack * 2);
        
        //randomly play a punch sound
        int random_number; srand((unsigned)time(0)); random_number = (rand()%4)+1;
        if(random_number == 1 || random_number == 3){oslStopSound(punch1); oslPlaySound(punch1, 2);}
        if(random_number == 3 || random_number == 4){oslStopSound(punch2); oslPlaySound(punch2, 3);}
        
        //now apply effect
        if(player.facing == player.facingLeft) special = BLOWN_BACK_LEFT;
        if(player.facing == player.facingRight) special = BLOWN_BACK_RIGHT;
        
        //communicate
        player.attacking = false;
    }
    
    //some basic movement AI
    if(attacking == false)
    { 
      if(player.image->x > image->x && colliding != 1) {
            image->x += 2; 
            position = RIGHT;
      }
      if(player.image->x < image->x && colliding != 1) {
            image->x -= 2; 
            position = LEFT;
      }
    }
    
    //some basic attacking AI
    if(waitToAttack < 600) {waitToAttack++; attacking = false;}
    else if(waitToAttack >= 600 && colliding)
    {
        attacking = true;

        if(position == RIGHT) position = ATTACKING_RIGHT;
        if(position == LEFT)  position = ATTACKING_LEFT;
        
        if(player.guarding == false)player.health -= attack;
        
        //randomly play a punch sound
        int random_number; srand((unsigned)time(0)); random_number = (rand()%4)+1;
        if(random_number == 1 || random_number == 3){oslStopSound(punch1); oslPlaySound(punch1, 4);}
        if(random_number == 3 || random_number == 4){oslStopSound(punch2); oslPlaySound(punch2, 5);}
        
        //communicate
        attacking = false;
        waitToAttack = 0; //reset
    }
    
    return;
}


void OBJECT::SetUp(const int changeId)
{
    id = changeId;
    attack =     SetAttack(id);
    health =     SetHealth(id);
    maxHealth =  health;
    maxPower =   SetPower(id);
    jumpHeight = SetJumpHeight(id);
    if(image != NULL){oslDeleteImage(image); image = NULL;}
    image = SetImage(id);
    image->x = 240;
    image->y = 50;
    oslSetImageTileSize(image,(1 * 53),STILL_LEFT,53,53);
    
    return;
}

void OBJECT::Reward(const int id, long long &money)
{
    int moneyEarned = 0;
    
    if(id == DUDE)              moneyEarned = 20;
    else if(id == SATHE_NORMAL) moneyEarned = 25;
    else if(id == REPUBLIKEN)   moneyEarned = 5;
    else if(id == ORRE)         moneyEarned = 25;
    else if(id == BARON)        moneyEarned = 30;
    else if(id == BLADE)        moneyEarned = 35;
    else if(id == RYAN)         moneyEarned = 40;
    else if(id == EARTH)        moneyEarned = 40;
    else if(id == ATLANTIS)     moneyEarned = 38;
    else if(id == VEXUS)        moneyEarned = 55;
    else if(id == ZAMUS_NORMAL) moneyEarned = 40;
    else if(id == SUPER_SATHE)  moneyEarned = 69;
    else if(id == GENAMI)       moneyEarned = 80;
    else if(id == ORPHEUS)      moneyEarned = 110;
    else if(id == SATHIMUS)     moneyEarned = 150;
    else if(id == WEAK_KROM)    moneyEarned = 160;
    else if(id == WEAK_WRAITH)  moneyEarned = 170;
    else if(id == WRAITH)       moneyEarned = 200;
    else if(id == KRITH)        moneyEarned = 190;
    else if(id == ULTRA_SATHE)  moneyEarned = 200;
    else if(id == ULTRA_ZAMUS)  moneyEarned = 220;
    else if(id == KROM)         moneyEarned = 260;
    else if(id == SATHIS)       moneyEarned = 300;
    else if(id == PHALEM)       moneyEarned = 400;
    else if(id == FOURTH_ELDER) moneyEarned = 350;
    else if(id == FIFTH_ELDER)  moneyEarned = 410;
    else if(id == SIXTH_ELDER)  moneyEarned = 440;
    else if(id == ELDER_SATHE)  moneyEarned = 500;
    else if(id == ETHAS)        moneyEarned = 600;
    else oslWarning("ERROR! INVALID PARAMETER PASSED TO Reward()!");
    
	//add player money
	money += moneyEarned;

	//play death sound
	oslStopSound(groan); 
	oslStopSound(groan2);
	srand((unsigned)time(0)); 
	int ran = (rand()%4)+1;
	if(ran == 2)oslPlaySound(groan, 6);
	else oslPlaySound(groan2, 6); 

    //reset enemy
	alive = false;
	totalNum--;
    
    return;
}


void OBJECT::SetUpEnemy(const int changeId, int x, int y)
{
	short index = -1;

	//first look for the next enemy that can be used
	for(int i = 0; i < MAX_ENEMIES; i++){
		if(!enemy[i].alive) {index = i; break;}
	}

	//if no slots ready tell the player and exit function to avoid errors
	if(index == -1 || index > MAX_ENEMIES){oslWarning("ERROR! Unable to create enemy (no slots ready)."); return;}

	//set stats for that specific enemy
    enemy[index].id = changeId;
    enemy[index].attack =    enemy[index].SetAttack(enemy[index].id);
    enemy[index].health =    enemy[index].SetHealth(enemy[index].id);
    enemy[index].maxHealth = enemy[index].health;
    enemy[index].maxPower =  enemy[index].SetPower(enemy[index].id);
    enemy[index].jumpHeight =enemy[index].SetJumpHeight(enemy[index].id);
	enemy[index].waitToAttack = 0;

	//set image for enemy
    if(enemy[index].image != NULL){oslDeleteImage(enemy[index].image);}
    enemy[index].image = enemy[index].SetImage(enemy[index].id);
    enemy[index].image->x = x;
    enemy[index].image->y = y;
    
	//put enemy into the game
	enemy[index].alive = true;
    totalNum++;
    
    return;
}

OBJECT::OBJECT()
{
    manip3 = 0;
    facingLeft = 0;
    facingRight = 1;
    manipGlow = 0;
    manip2 = 0;
    speed = 3;
    manip = 0;

    position = STILL_RIGHT;
	facing = facingRight;

    alive = false;
    touchingGround = false;
    attacking = false;
    guarding = false;
    quit = false;
	powerActivated = false;
    initialBoot = true;
    toggle = false;

    return;
}

OBJECT::~OBJECT()
{
    if(image != NULL) {oslDeleteImage(image); image = NULL;}   
    quit = true;
    
    return;
}
