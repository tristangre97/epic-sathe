/** 
 * class STATS ~V@ughn
 * -------------------
 * ->Super class of class BOSS and class OBJECT
 *
 * @SpriteAnimate()    - animates sprites
 * @SetImage(...)      - sets image
 * @SetHealth(...)     - sets health
 * @SetAttack(...)     - sets attack power
 * @SetJumpHeight(...) - sets jump height
 * @SetPower(...)      - sets power level
 *      
 */
class STATS 
{
    public:
        //properties
        short id;
        short xp;
        
        int jumpHeight;
        int maxHealth;
        
        long long health;
        long long attack;
        long long power;
        long long maxPower;
        
        bool guarding;
        bool alive;
        bool touchingGround;
        bool attacking;
        
        short manipulate;
        short position;
        short march;
          
        //image
        IMAGE * image;
          
        //methods
        virtual inline void SpriteAnimate();
        virtual IMAGE * SetImage(const short id);
        virtual int SetHealth(const short id, float manipulate);
        virtual int SetAttack(const short id, float manipulate);
        virtual short SetJumpHeight(const short id, float manipulate);
        virtual long long SetPower(const short id, float manipulate);
        
        STATS();
        ~STATS();
        
};

/* define fighter ID's */
#define MDUDE -1
#define DUDE 0
#define SATHE_NORMAL 1
#define REPUBLIKEN 2
#define ORRE 3
#define BARON 4
#define BLADE 5
#define RYAN 6
#define EARTH 7
#define ATLANTIS 8
#define VEXUS 9
#define ZAMUS_NORMAL 10
#define SUPER_SATHE 11
#define GENAMI 12
#define ORPHEUS 13
#define SATHIMUS 14
#define WEAK_KROM 15
#define WEAK_WRAITH 16
#define WRAITH 17
#define KRITH 18
#define ULTRA_SATHE 19
#define ULTRA_ZAMUS 20
#define KROM 21
#define SATHIS 22
#define PHALEM 23
#define FOURTH_ELDER 24
#define FIFTH_ELDER 25
#define SIXTH_ELDER 26
#define ELDER_SATHE 27
#define ETHAS 28

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
//STATS methods://///////////////////////////////////////////////////////////////////////////

inline void STATS::SpriteAnimate()
{	
    //Moves the sprite in the row that it is in
    manipulate++; if(manipulate > 10) {march++; manipulate = 0;}
    
    oslSetImageTileSize(image,(march * 53),position,53,53);
    
    if (march == 3) march = 0;
    
    if(image != NULL) oslDrawImage(image);
	else oslWarning("ERROR! Image is equal to NULL! Found in SpriteAnimate() function!");
}

short STATS::SetJumpHeight(const short id, float manipulate = 1)
{   
    short height = 5;
    
    if(id == DUDE)              height = 17 * manipulate;
    else if(id == SATHE_NORMAL) height = 15 * manipulate;
    else if(id == REPUBLIKEN)   height = 8 * manipulate;
    else if(id == ORRE)         height = 12 * manipulate;
    else if(id == BARON)        height = 12 * manipulate;
    else if(id == BLADE)        height = 12 * manipulate;
    else if(id == RYAN)         height = 12 * manipulate;
    else if(id == EARTH)        height = 12 * manipulate;
    else if(id == ATLANTIS)     height = 12 * manipulate;
    else if(id == VEXUS)        height = 22 * manipulate;
    else if(id == ZAMUS_NORMAL) height = 13 * manipulate;
    else if(id == SUPER_SATHE)  height = 13 * manipulate;
    else if(id == GENAMI)       height = 13 * manipulate;
    else if(id == ORPHEUS)      height = 13 * manipulate;
    else if(id == SATHIMUS)     height = 18 * manipulate;
    else if(id == WEAK_KROM)    height = 18 * manipulate;
    else if(id == WEAK_WRAITH)  height = 12 * manipulate;
    else if(id == WRAITH)       height = 12 * manipulate;
    else if(id == KRITH)        height = 17 * manipulate;
    else if(id == ULTRA_SATHE)  height = 17 * manipulate;
    else if(id == ULTRA_ZAMUS)  height = 14 * manipulate;
    else if(id == KROM)         height = 14 * manipulate;
    else if(id == SATHIS)       height = 14 * manipulate;
    else if(id == PHALEM)       height = 14 * manipulate;
    else if(id == FOURTH_ELDER) height = 14 * manipulate;
    else if(id == FIFTH_ELDER)  height = 14 * manipulate;
    else if(id == SIXTH_ELDER)  height = 14 * manipulate;
    else if(id == ELDER_SATHE)  height = 14 * manipulate;
    else if(id == ETHAS)        height = 16 * manipulate;
    else oslFatalError("ERROR! INVALID PARAMETER PASSED TO SetJumpHeight()!");
    
    return height;
}

int STATS::SetHealth(const short id, float manipulate = 1)
{
    int health = 0;
    
    if(id == DUDE)              health = 100 * manipulate;
    else if(id == SATHE_NORMAL) health = 125 * manipulate;
    else if(id == REPUBLIKEN)   health = 50 * manipulate;
    else if(id == ORRE)         health = 110 * manipulate;
    else if(id == BARON)        health = 108 * manipulate;
    else if(id == BLADE)        health = 120 * manipulate;
    else if(id == RYAN)         health = 114 * manipulate;
    else if(id == EARTH)        health = 124 * manipulate;
    else if(id == ATLANTIS)     health = 98 * manipulate;
    else if(id == VEXUS)        health = 117 * manipulate;
    else if(id == ZAMUS_NORMAL) health = 130 * manipulate;
    else if(id == SUPER_SATHE)  health = 150 * manipulate;
    else if(id == GENAMI)       health = 210 * manipulate;
    else if(id == ORPHEUS)      health = 119 * manipulate;
    else if(id == SATHIMUS)     health = 198 * manipulate;
    else if(id == WEAK_KROM)    health = 209 * manipulate;
    else if(id == WEAK_WRAITH)  health = 210 * manipulate;
    else if(id == WRAITH)       health = 223 * manipulate;
    else if(id == KRITH)        health = 250 * manipulate;
    else if(id == ULTRA_SATHE)  health = 300 * manipulate;
    else if(id == ULTRA_ZAMUS)  health = 280 * manipulate;
    else if(id == KROM)         health = 310 * manipulate;
    else if(id == SATHIS)       health = 327 * manipulate;
    else if(id == PHALEM)       health = 278 * manipulate;
    else if(id == FOURTH_ELDER) health = 400 * manipulate;
    else if(id == FIFTH_ELDER)  health = 500 * manipulate;
    else if(id == SIXTH_ELDER)  health = 800 * manipulate;
    else if(id == ELDER_SATHE)  health = 99999 * manipulate;
    else if(id == ETHAS)        health = 100000 * manipulate;
    else oslFatalError("ERROR! INVALID PARAMETER PASSED TO SetHealth()!");
    
    return health;
}

int STATS::SetAttack(const short id, float manipulate = 1)
{
    int attack = 0;
    
    if(id == DUDE)              attack = 10 * manipulate;
    else if(id == SATHE_NORMAL) attack = 25 * manipulate;
    else if(id == REPUBLIKEN)   attack = 2 * manipulate;
    else if(id == ORRE)         attack = 13 * manipulate;
    else if(id == BARON)        attack = 16 * manipulate;
    else if(id == BLADE)        attack = 27 * manipulate;
    else if(id == RYAN)         attack = 30 * manipulate;
    else if(id == EARTH)        attack = 34 * manipulate;
    else if(id == ATLANTIS)     attack = 35 * manipulate;
    else if(id == VEXUS)        attack = 42 * manipulate;
    else if(id == ZAMUS_NORMAL) attack = 34 * manipulate;
    else if(id == SUPER_SATHE)  attack = 80 * manipulate;
    else if(id == GENAMI)       attack = 72 * manipulate;
    else if(id == ORPHEUS)      attack = 180 * manipulate;
    else if(id == SATHIMUS)     attack = 250 * manipulate;
    else if(id == WEAK_KROM)    attack = 300 * manipulate;
    else if(id == WEAK_WRAITH)  attack = 500 * manipulate;
    else if(id == WRAITH)       attack = 1000 * manipulate;
    else if(id == KRITH)        attack = 2200 * manipulate;
    else if(id == ULTRA_SATHE)  attack = 2400 * manipulate;
    else if(id == ULTRA_ZAMUS)  attack = 1700 * manipulate;
    else if(id == KROM)         attack = 8000 * manipulate;
    else if(id == SATHIS)       attack = 8700 * manipulate;
    else if(id == PHALEM)       attack = 8800 * manipulate;
    else if(id == FOURTH_ELDER) attack = 10000 * manipulate;
    else if(id == FIFTH_ELDER)  attack = 15000 * manipulate;
    else if(id == SIXTH_ELDER)  attack = 50000 * manipulate;
    else if(id == ELDER_SATHE)  attack = 9999999 * manipulate;
    else if(id == ETHAS)        attack = 8999999 * manipulate;
    else oslFatalError("ERROR! INVALID PARAMETER PASSED TO SetAttack()!");
    
    return attack;
}

long long STATS::SetPower(const short id, float manipulate = 1)
{
    long long power = 0;
    
    if(id == DUDE)              power = 2 * manipulate;
    else if(id == SATHE_NORMAL) power = 4 * manipulate;
    else if(id == REPUBLIKEN)   power = 2 * manipulate;
    else if(id == ORRE)         power = 3 * manipulate;
    else if(id == BARON)        power = 3 * manipulate;
    else if(id == BLADE)        power = 4 * manipulate;
    else if(id == RYAN)         power = 6 * manipulate;
    else if(id == EARTH)        power = 8 * manipulate;
    else if(id == ATLANTIS)     power = 6 * manipulate;
    else if(id == VEXUS)        power = 9 * manipulate;
    else if(id == ZAMUS_NORMAL) power = 10 * manipulate;
    else if(id == SUPER_SATHE)  power = 25 * manipulate;
    else if(id == GENAMI)       power = 60 * manipulate;
    else if(id == ORPHEUS)      power = 200 * manipulate;
    else if(id == SATHIMUS)     power = 500 * manipulate;
    else if(id == WEAK_KROM)    power = 2000 * manipulate;
    else if(id == WEAK_WRAITH)  power = 2500 * manipulate;
    else if(id == WRAITH)       power = 10000 * manipulate;
    else if(id == KRITH)        power = 15000 * manipulate;
    else if(id == ULTRA_SATHE)  power = 50000 * manipulate;
    else if(id == ULTRA_ZAMUS)  power = 60000 * manipulate;
    else if(id == KROM)         power = 790000 * manipulate;
    else if(id == SATHIS)       power = 780000 * manipulate;
    else if(id == PHALEM)       power = 800000 * manipulate;
    else if(id == FOURTH_ELDER) power = 1000000 * manipulate;
    else if(id == FIFTH_ELDER)  power = 10000000 * manipulate;
    else if(id == SIXTH_ELDER)  power = 100000000 * manipulate;
    else if(id == ELDER_SATHE)  power = 999999999 * manipulate;
    else if(id == ETHAS)        power = 99999999 * manipulate;
    else oslFatalError("ERROR! INVALID PARAMETER PASSED TO SetPower()!");
    
    return power;
}

IMAGE * STATS::SetImage(const short id)
{
    IMAGE * image = NULL;
    
    if(id == MDUDE)              image = oslLoadImageFilePNG((char*)"img/fighters/Mdude.png", OSL_IN_RAM, OSL_PF_5551);
    else if(id == DUDE)         image = oslLoadImageFilePNG((char*)"img/fighters/dude.png", OSL_IN_RAM, OSL_PF_5551);
    else if(id == SATHE_NORMAL) image = oslLoadImageFilePNG((char*)"img/fighters/sathe_normal.png", OSL_IN_RAM, OSL_PF_5551);
    else if(id == REPUBLIKEN)   image = oslLoadImageFilePNG((char*)"img/fighters/REPUBLIKEN.png", OSL_IN_RAM, OSL_PF_5551);
    else if(id == ORRE)         image = oslLoadImageFilePNG((char*)"img/fighters/orre.png", OSL_IN_RAM, OSL_PF_5551);
    else if(id == BARON)        image = oslLoadImageFilePNG((char*)"img/fighters/baron.png", OSL_IN_RAM, OSL_PF_5551);
    else if(id == BLADE)        image = oslLoadImageFilePNG((char*)"img/fighters/blade.png", OSL_IN_RAM, OSL_PF_5551);
    else if(id == RYAN)         image = oslLoadImageFilePNG((char*)"img/fighters/ryan.png", OSL_IN_RAM, OSL_PF_5551);
    else if(id == EARTH)        image = oslLoadImageFilePNG((char*)"img/fighters/earth.png", OSL_IN_RAM, OSL_PF_5551);
    else if(id == ATLANTIS)     image = oslLoadImageFilePNG((char*)"img/fighters/atlantis.png", OSL_IN_RAM, OSL_PF_5551);
    else if(id == VEXUS)        image = oslLoadImageFilePNG((char*)"img/fighters/vexus.png", OSL_IN_RAM, OSL_PF_5551);
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
    
    if(!image) oslFatalError("ERROR! Image is equal to NULL!");
    
    return image;
}

STATS::STATS()
{
  return;
}

STATS::~STATS()
{
  return;
}
