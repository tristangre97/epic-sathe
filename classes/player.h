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
          
          //PLAYER methods
          inline void ReadKeys(OSL_IMAGE * image);
          
          inline void SpriteAnimate( void );
          
          inline void Handle(OSL_IMAGE * image);
          
          void SpawnLevel(const int levelReached);
          
          void SetUp(const int id);
    
    private:
          int sy;
          int manip2;
          int manip3;
          int manipGlow;
        
}player;

inline void PLAYER::Handle(OSL_IMAGE * image)
{
    //keep player in the screen
    if(image->x > 450) image->x = 450;
    if(image->x < -10) image->x = -10;
    
    //add player power
    manip3++;
    if(manip3 > 800){
    if(player.power <= player.maxPower)player.power++;
    if(player.power > player.maxPower) player.power = player.maxPower;
    }
    
    //handle power level
    if(player.powerActivated){
        if(manip2 > (200 + (2 * player.maxPower))) {manip2 = 0; player.powerActivated = false;} 
        manip2++;
    }
    
    //if the player's power level is ready make player glow
    if(player.power >= (player.maxPower/2)){
        manipGlow++;
        if(manipGlow < 15)      {oslSetAlpha(OSL_FX_ADD, 200); oslDrawImage(player.image); oslSetAlpha(OSL_FX_RGBA, 200);}
        else if(manipGlow > 15) oslDrawImage(player.image);
        if(manip > 30) manipGlow = 0;
    }
    
    //else draw normally
    else oslDrawImage(player.image);
        
    //gravity
    image->y+=sy;
    if(image->y > GROUND) image->y = GROUND;
    if(image->y != GROUND){touchingGround = false; sy++;}
    else touchingGround = true;
    
    //handle player health and lives
    if(player.health <= 0){
        oslPlaySound(groan, 7); 
        player.lives--; player.image->y = 20; 
        player.image->x = 240; 
        player.health = player.SetHealth(id);
    }
    if(player.lives < 0) player.quit = true;
    
    return;
}

inline void PLAYER::ReadKeys(OSL_IMAGE * image)
{
    oslReadKeys();
    
    //pausing
    if(osl_keys->pressed.start)pauseGame();
    
    //punching/attacking
    else if(osl_keys->pressed.square)
    {    
        if(player.facing == facingRight)       player.position = ATTACKING_RIGHT;
        if(player.facing == facingLeft)      player.position = ATTACKING_LEFT;
        
        player.attacking = true;
        player.guarding = false;
        SpriteAnimate();
    }
    
    //guarding/shielding
    else if(osl_keys->held.triangle)
    {
        if(player.facing == facingRight) player.position = GUARDING_RIGHT;
        if(player.facing == facingLeft)  player.position = GUARDING_LEFT;
        
        player.guarding = true;
        player.attacking = false;
        SpriteAnimate();
    }
    
    //movement
    else if(osl_keys->held.left)
    {
        if(player.touchingGround){player.position = LEFT; SpriteAnimate();}
        player.facing = facingLeft; 
        player.image->x-=3; 
        if(player.powerActivated)player.image->x-=3;
    }
    
    //movement
    else if(osl_keys->held.right)
    { 
        if(player.touchingGround){player.position = RIGHT; SpriteAnimate();}
        player.facing = facingRight; 
        player.image->x+=3; 
        if(player.powerActivated)player.image->x+=3;
    }
        
    //sprite animation
    else if (!osl_keys->held.value) {
        player.guarding = false;
        player.attacking = false;
        
        if(player.facing == facingRight)     player.position = STILL_RIGHT; 
        else if(player.facing == facingLeft) player.position = 608; 
        
        SpriteAnimate();
    }
    
    //jumping
    
    if(player.touchingGround && osl_keys->pressed.cross) 
    {
        player.position = JUMPING;
        player.touchingGround = false;
        player.attacking = false;
        player.guarding = false;
        sy -= jumpHeight;
        if(player.powerActivated)sy -= jumpHeight;
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
                oslSetAlpha(OSL_FX_ADD, 500); oslDrawImage(level); oslSetAlpha(OSL_FX_RGBA, 500);
                oslDrawImage(player.image);
                oslEndDrawing();
                oslSyncFrame();
            }
            
            player.power = 0;
            manip2 = 0;
         }
         
         else oslPlaySound(error, 2);
    }
    
    return;
}

inline void PLAYER::SpriteAnimate( void )
{	
    //Moves the sprite in the row that it is in
    player.manipulate++; if(player.manipulate > 9) {player.march++; player.manipulate = 0;}
    
    oslSetImageTileSize(player.image,(player.march * 53),player.position,53,75);
    
    if (player.march == 3) player.march = 0;
}

void PLAYER::SetUp(const int id)
{
    player.id = id;
    player.attack =     player.SetAttack(id);
    player.health =     player.SetHealth(id);
    player.maxHealth =  player.health;
    player.maxPower =   player.SetPower(id);
    player.jumpHeight = player.SetJumpHeight(id);
    if(player.image != NULL){oslDeleteImage(player.image); player.image = NULL;}
    player.image = player.SetImage(id);
    player.image->x = 240;
    player.image->y = 50;
    oslSetImageTileSize(player.image,(1 * 53),STILL_LEFT,53,76);
    
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
    player.initialBoot = true;
    player.manip = 0;
    player.position = STILL_RIGHT;
    player.sy = 0;
    player.money = 0;
    player.lives = 1;
    player.health = 100;
    player.attack = 10;
    player.power = 1;
    player.alive = true;
    player.touchingGround = false;
    player.image = NULL;
    player.attacking = false;
    player.guarding = false;
    player.quit = false;
    player.facing = facingRight;
    player.powerActivated = false;
    player.manip3 = 0;
    player.facingLeft = 0;
    player.facingRight = 1;
    player.manipGlow = 0;
    
    return;
}

PLAYER::~PLAYER()
{
    if(player.image != NULL) {oslDeleteImage(player.image); player.image = NULL;}   
    player.quit = true;
    
    return;
}
