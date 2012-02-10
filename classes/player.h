class PLAYER : public STATS
{
    public:
          PLAYER();
          ~PLAYER();
          
          //specifics
          int manip;
          bool initialBoot;
          short manipulate;
          short position;
          short march;
          
          //manipulators
          long long money;
          long maxHealth;
          short facing;
          int facingLeft;
          int facingRight;
          
          //stats
          short lives;
          
          //true false variables
          bool quit;
          bool powerActivated;
          bool toggle;
          
          //PLAYER methods
          inline void ReadKeys();
          
          inline void SpriteAnimate();
          
          inline void Handle();
          
          void SpawnLevel(const int levelReached);
          
          void SetUp(const int changeId);
    
    private:
          int sy;
          int manip2;
          int manip3;
          int manipGlow;
        
}player;

inline void PLAYER::Handle()
{
    //keep player in the screen
    if(image->x > 440) image->x = 440;
    if(image->x < -10) image->x = -10;
    
    //add player power
    manip3++;
    if(manip3 > 800){
    if(power <= player.maxPower)power++;
    if(power > player.maxPower) power = player.maxPower;
    }
    
    //handle power level
    if(powerActivated){
        if(manip2 > (200 + (2 * maxPower))) {manip2 = 0; powerActivated = false;} 
        manip2++;
    }
    
    //if the player's power level is ready make player glow
    if(power >= (maxPower/2)){
        manipGlow++;
        if(manipGlow < 15)      {oslSetAlpha(OSL_FX_ADD, 500); oslDrawImage(image); oslSetAlpha(OSL_FX_RGBA, 500);}
        else if(manipGlow > 15) oslDrawImage(image);
        if(manip > 30) manipGlow = 0;
    }
    
    //else draw normally
    else oslDrawImage(image);
        
    //gravity
    image->y+=sy;
    if(image->y > (GROUND - image->stretchY)) image->y = (GROUND - image->stretchY);
    if(image->y != (GROUND - image->stretchY)){touchingGround = false; sy++;}
    else touchingGround = true;
    
    //handle player health and lives
    if(player.health <= 0){
        oslPlaySound(groan, 7); 
        lives--; player.image->y = 20; 
        image->x = 240; 
        health = SetHealth(id);
    }
    if(lives < 0) quit = true;
    
    return;
}

inline void PLAYER::ReadKeys()
{
    oslReadKeys();
    
    //pausing
    if(osl_keys->pressed.start)pauseGame();
    
    //toggle onscreen text
    if(osl_keys->pressed.select) {if(toggle)toggle = false; else toggle = true;}
    
    //punching/attacking
    else if(osl_keys->pressed.square)
    {    
        if(facing == facingRight) position = ATTACKING_RIGHT;
        if(facing == facingLeft)  position = ATTACKING_LEFT;
        
        attacking = true;
        guarding = false;
        SpriteAnimate();
    }
    
    //guarding/shielding
    else if(osl_keys->held.triangle)
    {
        if(facing == facingRight) position = GUARDING_RIGHT;
        if(facing == facingLeft)  position = GUARDING_LEFT;
        
        guarding = true;
        attacking = false;
        SpriteAnimate();
    }
    
    //movement
    else if(osl_keys->held.left)
    {
        if(touchingGround){position = LEFT; SpriteAnimate();}
        facing = facingLeft; 
        image->x-=3; 
        if(powerActivated)image->x-=3;
    }
    
    //movement
    else if(osl_keys->held.right)
    { 
        if(player.touchingGround){position = RIGHT; SpriteAnimate();}
        facing = facingRight; 
        image->x+=3; 
        if(powerActivated)image->x+=3;
    }
        
    //sprite animation
    else if (!osl_keys->held.value) {
        guarding = false;
        attacking = false;
        
        if(facing == facingRight)     position = STILL_RIGHT; 
        else if(facing == facingLeft) position = STILL_LEFT; 
        
        SpriteAnimate();
    }
    
    //jumping
    
    if(touchingGround && osl_keys->pressed.cross) 
    {
        position = JUMPING;
        touchingGround = false;
        attacking = false;
        guarding = false;
        sy -= jumpHeight;
        if(powerActivated)sy -= jumpHeight;
        SpriteAnimate();
    }
    
    if(osl_keys->pressed.R && powerActivated == false)
    {
        if(player.power >= (player.maxPower/2))
        {
            player.powerActivated = true;
            oslPlaySound(powerUp, 2);
            
            for(int i = 0; i < 50; i++){
                oslStartDrawing();
                oslSetAlpha(OSL_FX_ADD, 400); oslDrawImage(level); oslSetAlpha(OSL_FX_RGBA, 400);
                oslSetAlpha(OSL_FX_ADD, 800); oslDrawImage(player.image); oslSetAlpha(OSL_FX_RGBA, 500);
                oslEndDrawing();
                oslSyncFrame();
            }
            
            power = 0;
            manip2 = 0;
         }
         
         else oslPlaySound(error, 2);
    }
    
    return;
}

inline void PLAYER::SpriteAnimate()
{	
    //Moves the sprite in the row that it is in
    manipulate++; if(manipulate > 9) {march++; manipulate = 0;}
    
    oslSetImageTileSize(player.image,(march * 53),position,53,53);
    
    if (march == 3) march = 0;
}

void PLAYER::SetUp(const int changeId)
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

void PLAYER::SpawnLevel(const int levelReached)
{
    if(level != NULL){oslDeleteImage(level); level = NULL;}
    if(level != NULL) oslFatalError("ERROR! FAILED TO DELETE LEVEL FROM MEMORY!!");
    
    if(levelReached <= 0) oslFatalError("ERROR! LEVEL REACHED IS EQUAL TO ZERO?!!");
    if(levelReached == 1) level = oslLoadImageFile((char*)"img/data/lx1.png", OSL_IN_RAM, OSL_PF_5551);
    else oslFatalError("ERROR NO MORE MAPS TO LOAD! CANNOT CONTINUE!!");

    return;
}

PLAYER::PLAYER()
{
    initialBoot = true;
    manip = 0;
    position = STILL_RIGHT;
    sy = 0;
    money = 0;
    lives = 1;
    health = 100;
    attack = 10;
    power = 1;
    alive = true;
    touchingGround = false;
    image = NULL;
    attacking = false;
    guarding = false;
    quit = false;
    facing = facingRight;
    powerActivated = false;
    manip3 = 0;
    facingLeft = 0;
    facingRight = 1;
    manipGlow = 0;
    toggle = false;
    
    return;
}

PLAYER::~PLAYER()
{
    if(image != NULL) {oslDeleteImage(image); image = NULL;}   
    quit = true;
    
    return;
}
