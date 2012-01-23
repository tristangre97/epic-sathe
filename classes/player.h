class PLAYER
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
          short id;
          short jumpHeight;
          long long money;
          long maxHealth;
          short facing;
          static const int left = 0;
          static const int right = 1;
          
          //stats
          long long health;
          long long attack;
          long long power;
          long long maxPower;
          short lives;
          
          //true false variables
          bool guarding;
          bool attacking;
          bool alive;
          bool touchingGround;
          bool quit;
          
          //image
          OSL_IMAGE * image;
          
          //PLAYER methods
          inline void ReadKeys(OSL_IMAGE * image);
          
          inline void SpriteAnimate( void );
          
          inline void Handle(OSL_IMAGE * image);
          
          void SpawnLevel(const int levelReached);
          
          OSL_IMAGE * SetImage(const short id);
          
          int SetHealth(const short id);
          
          int SetAttack(const short id);
          
          short SetJumpHeight(const short id);
          
          long long SetPower(const short id);
          
          void SetUp(const int id);
    
    private:
          int sy;
        
}player;

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

inline void PLAYER::Handle(OSL_IMAGE * image)
{
    //keep player in the screen
    if(image->x > 450) image->x = 450;
    if(image->x < -10) image->x = -10;
    
    //add player power
    if(player.power < player.maxPower)player.power++;
    
    //gravity
    image->y+=sy;
    if(image->y > GROUND) image->y = GROUND;
    if(image->y != GROUND){touchingGround = false; sy++;}
    else touchingGround = true;
    
    if(player.health <= 0){oslPlaySound(groan, 7); player.lives--; player.image->y = 100; player.image->x = 240; player.health = player.SetHealth(id);}
    if(player.health <= 0 && player.lives <= 0) player.quit = true;
    
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
        if(player.facing == right)       player.position = ATTACKING_RIGHT;
        else if(player.position == left) player.position = ATTACKING_LEFT;
        
        player.attacking = true;
        player.guarding = false;
        SpriteAnimate();
    }
    
    //guarding/shielding
    else if(osl_keys->held.triangle)
    {
        if(player.facing == right) player.position = GUARDING_RIGHT;
        if(player.facing == left)  player.position = GUARDING_LEFT;
        
        player.guarding = true;
        player.attacking = false;
        SpriteAnimate();
    }
    
    //movement
    else if(osl_keys->held.left)
    {
        if(player.touchingGround){player.position = LEFT; SpriteAnimate();}
        player.facing = left; 
        image->x-=3; 
    }
    
    //movement
    else if(osl_keys->held.right)
    { 
        if(player.touchingGround){player.position = RIGHT; SpriteAnimate();}
        player.facing = right; 
        image->x+=3; 
    }
    
    //sprite animation
    else if (!osl_keys->held.value) {
        player.guarding = false;
        player.attacking = false;
        
        if(player.facing == right)     player.position = STILL_RIGHT; 
        else if(player.facing == left) player.position = STILL_LEFT; 
        
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
        SpriteAnimate();
    }
    
    return;
}

inline void PLAYER::SpriteAnimate( void )
{	
    //Moves the sprite in the row that it is in
    player.manipulate++; if(player.manipulate > 9) {player.march++; player.manipulate = 0;}
    
    oslSetImageTileSize(player.image,(player.march * 53),player.position,53,76);
    
    if (player.march == 3) player.march = 0;
}

short PLAYER::SetJumpHeight(const short id)
{   
    short height = 5;
    
    if(id == DUDE)              height = 20;
    else if(id == SATHE_NORMAL) height = 12;
    else if(id == REPUBLIKEN)   height = 8;
    else if(id == ORRE)         height = 12;
    else if(id == BARON)        height = 12;
    else if(id == BLADE)        height = 12;
    else if(id == RYAN)         height = 12;
    else if(id == EARTH)        height = 12;
    else if(id == ATLANTIS)     height = 12;
    else if(id == VEXUS)        height = 13;
    else if(id == ZAMUS_NORMAL) height = 13;
    else if(id == SUPER_SATHE)  height = 13;
    else if(id == GENAMI)       height = 13;
    else if(id == ORPHEUS)      height = 13;
    else if(id == SATHIMUS)     height = 18;
    else if(id == WEAK_KROM)    height = 18;
    else if(id == WEAK_WRAITH)  height = 12;
    else if(id == WRAITH)       height = 12;
    else if(id == KRITH)        height = 17;
    else if(id == ULTRA_SATHE)  height = 17;
    else if(id == ULTRA_ZAMUS)  height = 14;
    else if(id == KROM)         height = 14;
    else if(id == SATHIS)       height = 14;
    else if(id == PHALEM)       height = 14;
    else if(id == FOURTH_ELDER) height = 14;
    else if(id == FIFTH_ELDER)  height = 14;
    else if(id == SIXTH_ELDER)  height = 14;
    else if(id == ELDER_SATHE)  height = 14;
    else if(id == ETHAS)        height = 16;
    else oslFatalError("ERROR! INVALID PARAMETER PASSED TO SetJumpHeight()!");
    
    return height;
}

int PLAYER::SetHealth(const short id)
{
    int health = 0;
    
    if(id == DUDE)              health = 100;
    else if(id == SATHE_NORMAL) health = 125;
    else if(id == REPUBLIKEN)   health = 50;
    else if(id == ORRE)         health = 110;
    else if(id == BARON)        health = 108;
    else if(id == BLADE)        health = 120;
    else if(id == RYAN)         health = 114;
    else if(id == EARTH)        health = 124;
    else if(id == ATLANTIS)     health = 98;
    else if(id == VEXUS)        health = 117;
    else if(id == ZAMUS_NORMAL) health = 130;
    else if(id == SUPER_SATHE)  health = 150;
    else if(id == GENAMI)       health = 210;
    else if(id == ORPHEUS)      health = 119;
    else if(id == SATHIMUS)     health = 198;
    else if(id == WEAK_KROM)    health = 209;
    else if(id == WEAK_WRAITH)  health = 210;
    else if(id == WRAITH)       health = 223;
    else if(id == KRITH)        health = 250;
    else if(id == ULTRA_SATHE)  health = 300;
    else if(id == ULTRA_ZAMUS)  health = 280;
    else if(id == KROM)         health = 310;
    else if(id == SATHIS)       health = 327;
    else if(id == PHALEM)       health = 278;
    else if(id == FOURTH_ELDER) health = 400;
    else if(id == FIFTH_ELDER)  health = 500;
    else if(id == SIXTH_ELDER)  health = 800;
    else if(id == ELDER_SATHE)  health = 99999;
    else if(id == ETHAS)        health = 100000;
    else oslFatalError("ERROR! INVALID PARAMETER PASSED TO SetHealth()!");
    
    return health;
}

int PLAYER::SetAttack(const short id)
{
    int attack = 0;
    
    if(id == DUDE)              attack = 10;
    else if(id == SATHE_NORMAL) attack = 25;
    else if(id == REPUBLIKEN)   attack = 2;
    else if(id == ORRE)         attack = 13;
    else if(id == BARON)        attack = 16;
    else if(id == BLADE)        attack = 23;
    else if(id == RYAN)         attack = 28;
    else if(id == EARTH)        attack = 32;
    else if(id == ATLANTIS)     attack = 26;
    else if(id == VEXUS)        attack = 34;
    else if(id == ZAMUS_NORMAL) attack = 30;
    else if(id == SUPER_SATHE)  attack = 80;
    else if(id == GENAMI)       attack = 72;
    else if(id == ORPHEUS)      attack = 180;
    else if(id == SATHIMUS)     attack = 250;
    else if(id == WEAK_KROM)    attack = 300;
    else if(id == WEAK_WRAITH)  attack = 500;
    else if(id == WRAITH)       attack = 1000;
    else if(id == KRITH)        attack = 2200;
    else if(id == ULTRA_SATHE)  attack = 2400;
    else if(id == ULTRA_ZAMUS)  attack = 1700;
    else if(id == KROM)         attack = 8000;
    else if(id == SATHIS)       attack = 8700;
    else if(id == PHALEM)       attack = 8800;
    else if(id == FOURTH_ELDER) attack = 10000;
    else if(id == FIFTH_ELDER)  attack = 15000;
    else if(id == SIXTH_ELDER)  attack = 50000;
    else if(id == ELDER_SATHE)  attack = 9999999;
    else if(id == ETHAS)        attack = 8999999;
    else oslFatalError("ERROR! INVALID PARAMETER PASSED TO SetAttack()!");
    
    return attack;
}

long long PLAYER::SetPower(const short id)
{
    long long power = 0;
    
    if(id == DUDE)              power = 1;
    else if(id == SATHE_NORMAL) power = 4;
    else if(id == REPUBLIKEN)   power = 2;
    else if(id == ORRE)         power = 3;
    else if(id == BARON)        power = 3;
    else if(id == BLADE)        power = 4;
    else if(id == RYAN)         power = 6;
    else if(id == EARTH)        power = 8;
    else if(id == ATLANTIS)     power = 6;
    else if(id == VEXUS)        power = 9;
    else if(id == ZAMUS_NORMAL) power = 10;
    else if(id == SUPER_SATHE)  power = 25;
    else if(id == GENAMI)       power = 60;
    else if(id == ORPHEUS)      power = 200;
    else if(id == SATHIMUS)     power = 500;
    else if(id == WEAK_KROM)    power = 2000;
    else if(id == WEAK_WRAITH)  power = 2500;
    else if(id == WRAITH)       power = 10000;
    else if(id == KRITH)        power = 15000;
    else if(id == ULTRA_SATHE)  power = 50000;
    else if(id == ULTRA_ZAMUS)  power = 60000;
    else if(id == KROM)         power = 790000;
    else if(id == SATHIS)       power = 780000;
    else if(id == PHALEM)       power = 800000;
    else if(id == FOURTH_ELDER) power = 1000000;
    else if(id == FIFTH_ELDER)  power = 10000000;
    else if(id == SIXTH_ELDER)  power = 100000000;
    else if(id == ELDER_SATHE)  power = 999999999;
    else if(id == ETHAS)        power = 99999999;
    else oslFatalError("ERROR! INVALID PARAMETER PASSED TO SetPower()!");
    
    return power;
}

OSL_IMAGE * PLAYER::SetImage(const short id)
{
    OSL_IMAGE * image = NULL;
    
    if(id == -1)                     image = oslLoadImageFilePNG((char*)"img/data/xf1.png", OSL_IN_RAM, OSL_PF_5551);
    else if(id == DUDE)              image = oslLoadImageFilePNG((char*)"img/fighters/dude.png", OSL_IN_RAM, OSL_PF_5551);
    else if(id == SATHE_NORMAL) image = oslLoadImageFilePNG((char*)"img/fighters/sathe_normal.png", OSL_IN_RAM, OSL_PF_5551);
    else if(id == REPUBLIKEN)   image = oslLoadImageFilePNG((char*)"img/fighters/REPUBLIKEN.png", OSL_IN_RAM, OSL_PF_5551);
    else if(id == ORRE)         image = oslLoadImageFilePNG((char*)"img/fighters/orre.png", OSL_IN_RAM, OSL_PF_5551);
    else if(id == BARON)        image = oslLoadImageFilePNG((char*)"img/fighters/baron.png", OSL_IN_RAM, OSL_PF_5551);
    else if(id == BLADE)        image = oslLoadImageFilePNG((char*)"img/fighters/blade.png", OSL_IN_RAM, OSL_PF_5551);
    else if(id == RYAN)         image = oslLoadImageFilePNG((char*)"img/fighters/ryan.png", OSL_IN_RAM, OSL_PF_5551);
    else if(id == EARTH)        image = oslLoadImageFilePNG((char*)"img/fighters/earth.png", OSL_IN_RAM, OSL_PF_5551);
    else if(id == ATLANTIS)     image = oslLoadImageFilePNG((char*)"img/fighters/atlantis.png", OSL_IN_RAM, OSL_PF_5551);
    else if(id == VEXUS)        image = oslLoadImageFilePNG((char*)"img/fighters/dude.png", OSL_IN_RAM, OSL_PF_5551);
    else if(id == ZAMUS_NORMAL) image = oslLoadImageFilePNG((char*)"img/fighters/dude.png", OSL_IN_RAM, OSL_PF_5551);
    else if(id == SUPER_SATHE)  image = oslLoadImageFilePNG((char*)"img/fighters/dude.png", OSL_IN_RAM, OSL_PF_5551);
    else if(id == GENAMI)       image = oslLoadImageFilePNG((char*)"img/fighters/dude.png", OSL_IN_RAM, OSL_PF_5551);
    else if(id == ORPHEUS)      image = oslLoadImageFilePNG((char*)"img/fighters/dude.png", OSL_IN_RAM, OSL_PF_5551);
    else if(id == SATHIMUS)     image = oslLoadImageFilePNG((char*)"img/fighters/dude.png", OSL_IN_RAM, OSL_PF_5551);
    else if(id == WEAK_KROM)    image = oslLoadImageFilePNG((char*)"img/fighters/dude.png", OSL_IN_RAM, OSL_PF_5551);
    else if(id == WEAK_WRAITH)  image = oslLoadImageFilePNG((char*)"img/fighters/dude.png", OSL_IN_RAM, OSL_PF_5551);
    else if(id == WRAITH)       image = oslLoadImageFilePNG((char*)"img/fighters/dude.png", OSL_IN_RAM, OSL_PF_5551);
    else if(id == KRITH)        image = oslLoadImageFilePNG((char*)"img/fighters/dude.png", OSL_IN_RAM, OSL_PF_5551);
    else if(id == ULTRA_SATHE)  image = oslLoadImageFilePNG((char*)"img/fighters/dude.png", OSL_IN_RAM, OSL_PF_5551);
    else if(id == ULTRA_ZAMUS)  image = oslLoadImageFilePNG((char*)"img/fighters/dude.png", OSL_IN_RAM, OSL_PF_5551);
    else if(id == KROM)         image = oslLoadImageFilePNG((char*)"img/fighters/dude.png", OSL_IN_RAM, OSL_PF_5551);
    else if(id == SATHIS)       image = oslLoadImageFilePNG((char*)"img/fighters/dude.png", OSL_IN_RAM, OSL_PF_5551);
    else if(id == PHALEM)       image = oslLoadImageFilePNG((char*)"img/fighters/dude.png", OSL_IN_RAM, OSL_PF_5551);
    else if(id == FOURTH_ELDER) image = oslLoadImageFilePNG((char*)"img/fighters/dude.png", OSL_IN_RAM, OSL_PF_5551);
    else if(id == FIFTH_ELDER)  image = oslLoadImageFilePNG((char*)"img/fighters/dude.png", OSL_IN_RAM, OSL_PF_5551);
    else if(id == SIXTH_ELDER)  image = oslLoadImageFilePNG((char*)"img/fighters/dude.png", OSL_IN_RAM, OSL_PF_5551);
    else if(id == ELDER_SATHE)  image = oslLoadImageFilePNG((char*)"img/fighters/dude.png", OSL_IN_RAM, OSL_PF_5551);
    else if(id == ETHAS)        image = oslLoadImageFilePNG((char*)"img/fighters/dude.png", OSL_IN_RAM, OSL_PF_5551);
    else oslFatalError("ERROR! INVALID PARAMETER PASSED TO OSL_IMAGE * loadImage(const short id)!!");

    return image;
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
    
    return;
}

PLAYER::~PLAYER()
{
    if(player.image != NULL) {oslDeleteImage(player.image); player.image = NULL;}   
    player.quit = true;
    
    return;
}
