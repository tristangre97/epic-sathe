class ENEMY
{
    public:
           ENEMY();
           ~ENEMY();
           
           //manipulators
           short id;
           int jumpHeight;
           int maxPower;
           int special;
           int waitToAttack;
           
           //statistics
           int health;
           int maxHealth;
           int attack;
           long long power;
           
           //true false variables
           bool guarding;
           bool alive;
           bool touchingGround;
           bool attacking;
           
           //others
           short march;
           short position;
           short manipulate;
           int sy;
           
           //image
           OSL_IMAGE * image;
           
           //quick setup methods
           void SetUpSlot1(const int id, int x, int y);
           
           void SetUpSlot2(const int id, int x, int y);
           
           void SetUpSlot3(const int id, int x, int y);
           
           void SetUpSlot4(const int id, int x, int y);
           
           void SetUpSlot5(const int id, int x, int y);
           
           void SetUpSlot6(const int id, int x, int y);
           
           void SetUpSlot7(const int id, int x, int y);
           
           void SetUpSlot8(const int id, int x, int y);
           
           void SetUpSlot9(const int id, int x, int y);
           
           void SetUpSlot10(const int id, int x, int y);
           
           //ENEMY methods
           
           void Reward(const int id);
           
           OSL_IMAGE * SetImage(const short id);
           
           int SetHealth(const short id);
           
           int SetAttack(const short id);
           
           short SetJumpHeight(const short id);
           
           long long SetPower(const short id);
           
           inline void SpriteAnimate(OSL_IMAGE * image, short &manipulate, short &march, short &position);
           
           inline void Handle(OSL_IMAGE * image, int &health, int &attack, long long &power, long long maxPower, bool &touchingGround, bool &attacking, int &sy, short &position, int &special);
    
    private:
        
}enemy1, enemy2, enemy3, enemy4, enemy5, enemy6, enemy7, enemy8, enemy9, enemy10, spawn;

inline void ENEMY::Handle(OSL_IMAGE * image, int &health, int &attack, long long &power, long long maxPower, bool &touchingGround, bool &attacking, int &sy, short &position, int &special)
{
    //keep enemy in the screen
    if(image->x > 450)   image->x = 450;
    if(image->x < -10)   image->x = -10;
    
    //add player power
    if(power < maxPower)power++;
    
    //gravity
    image->y+=sy;
    if(image->y > GROUND) image->y = GROUND;
    if(image->y != GROUND){touchingGround = false; sy++;}
    else touchingGround = true;
    
    //show enemy health
    oslSetTextColor(RED);
    oslPrintf_xy(image->x, image->y - 4, "HP: %d", health);
    
    //check for collisions
    int colliding = collision(player.image,player.image->x, player.image->y,image, image->x,image->y);
    
    if(player.attacking && colliding)
    {
        //subtract health
        health -= player.attack; 
        
        //randomly play a punch sound
        int random_number; srand((unsigned)time(0)); random_number = (rand()%4)+1;
        if(random_number == 1 || random_number == 3){oslStopSound(punch1); oslPlaySound(punch1, 2);}
        if(random_number == 3 || random_number == 4){oslStopSound(punch2); oslPlaySound(punch2, 3);}
        
        //now apply effect
        if(player.facing == player.left) special = BLOWN_BACK_LEFT;
        if(player.facing == player.right) special = BLOWN_BACK_RIGHT;
        
        //communicate
        player.attacking = false;
    }
    
    //some basic movement AI
    if(attacking == false)
    {
      if(special == BLOWN_BACK_RIGHT){if(image->x < 440)image->x+=5; if(image->y >50)image->y-=10;if(image->x >= 440) special = NOTHING;}
      else if(special == BLOWN_BACK_LEFT){if(image->x > 0)image->x-=5; if(image->y >50)image->y-=10;if(image->x <= 0) special = NOTHING;}
      else if(player.image->x > image->x && colliding != 1) {image->x += 2; position = RIGHT;}
      else if(player.image->x < image->x && colliding != 1) {image->x -= 2; position = LEFT;}
      else if(player.image->x == image->x){
          if(position == RIGHT)position = STILL_RIGHT;
          if(position == LEFT) position = STILL_LEFT;
      }
    }
    
    //some basic attacking AI
    if(waitToAttack < 2000) {waitToAttack++; attacking = false;}
    else if(waitToAttack >= 1000 && colliding)
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

void ENEMY::Reward(const int id)
{
    int moneyEarned = 0;
    
    if(id == DUDE)              moneyEarned = 5;
    else if(id == SATHE_NORMAL) moneyEarned = 10;
    else if(id == REPUBLIKEN)   moneyEarned = 1;
    else if(id == ORRE)         moneyEarned = 8;
    else if(id == BARON)        moneyEarned = 10;
    else if(id == BLADE)        moneyEarned = 10;
    else if(id == RYAN)         moneyEarned = 15;
    else if(id == EARTH)        moneyEarned = 20;
    else if(id == ATLANTIS)     moneyEarned = 9;
    else if(id == VEXUS)        moneyEarned = 10;
    else if(id == ZAMUS_NORMAL) moneyEarned = 10;
    else if(id == SUPER_SATHE)  moneyEarned = 15;
    else if(id == GENAMI)       moneyEarned = 20;
    else if(id == ORPHEUS)      moneyEarned = 24;
    else if(id == SATHIMUS)     moneyEarned = 27;
    else if(id == WEAK_KROM)    moneyEarned = 30;
    else if(id == WEAK_WRAITH)  moneyEarned = 35;
    else if(id == WRAITH)       moneyEarned = 40;
    else if(id == KRITH)        moneyEarned = 60;
    else if(id == ULTRA_SATHE)  moneyEarned = 100;
    else if(id == ULTRA_ZAMUS)  moneyEarned = 100;
    else if(id == KROM)         moneyEarned = 110;
    else if(id == SATHIS)       moneyEarned = 150;
    else if(id == PHALEM)       moneyEarned = 150;
    else if(id == FOURTH_ELDER) moneyEarned = 160;
    else if(id == FIFTH_ELDER)  moneyEarned = 180;
    else if(id == SIXTH_ELDER)  moneyEarned = 200;
    else if(id == ELDER_SATHE)  moneyEarned = 300;
    else if(id == ETHAS)        moneyEarned = 360;
    else oslFatalError("ERROR! INVALID PARAMETER PASSED TO Reward()!");
    
    player.money += moneyEarned;
    
    return;
}

inline void ENEMY::SpriteAnimate(OSL_IMAGE * image, short &manipulate, short &march, short &position)
{	
    //Moves the sprite in the row that it is in
    manipulate++; if(manipulate > 10) {march++; manipulate = 0;}
    
    oslSetImageTileSize(image,(march * 53),position,53,76);
    
    if (march == 3) march = 0;

    oslDrawImage(image);
}

void ENEMY::SetUpSlot1(const int id, int x, int y)
{
    enemy1.attack =    enemy1.SetAttack(id);
    enemy1.health =    enemy1.SetHealth(id);
    enemy1.maxHealth = enemy1.health;
    enemy1.maxPower =  enemy1.SetPower(id);
    enemy1.jumpHeight =enemy1.SetJumpHeight(id);
    enemy1.alive = true;
    if(enemy1.image != NULL){oslDeleteImage(enemy1.image); enemy1.image = NULL;}
    enemy1.image = enemy1.SetImage(id);
    enemy1.image->x = x;
    enemy1.image->y = y;
    
    totalNum++;
    
    return;
}

void ENEMY::SetUpSlot2(const int id, int x, int y)
{
    enemy2.attack =    enemy2.SetAttack(id);
    enemy2.health =    enemy2.SetHealth(id);
    enemy2.maxHealth = enemy2.health;
    enemy2.maxPower =  enemy2.SetPower(id);
    enemy2.jumpHeight =enemy2.SetJumpHeight(id);
    enemy2.alive = true;
    if(enemy2.image != NULL){oslDeleteImage(enemy2.image); enemy2.image = NULL;}
    enemy2.image = enemy2.SetImage(enemy2.id);
    enemy2.image->x = x;
    enemy2.image->y = y;
    
    totalNum++;
       
    return;
}

void ENEMY::SetUpSlot3(const int id, int x, int y)
{
    enemy3.attack =    enemy3.SetAttack(id);
    enemy3.health =    enemy3.SetHealth(id);
    enemy3.maxHealth = enemy3.health;
    enemy3.maxPower =  enemy3.SetPower(id);
    enemy3.jumpHeight =enemy3.SetJumpHeight(id);
    enemy3.alive = true;
    if(enemy3.image != NULL){oslDeleteImage(enemy3.image); enemy3.image = NULL;}
    enemy3.image = enemy3.SetImage(id);
    enemy3.image->x = x;
    enemy3.image->y = y;
    
    totalNum++;
    
    return;
}

void ENEMY::SetUpSlot4(const int id, int x, int y)
{
    enemy4.attack =    enemy4.SetAttack(id);
    enemy4.health =    enemy4.SetHealth(id);
    enemy4.maxHealth = enemy4.health;
    enemy4.maxPower =  enemy4.SetPower(id);
    enemy4.jumpHeight =enemy4.SetJumpHeight(id);
    enemy4.alive = true;
    if(enemy4.image != NULL){oslDeleteImage(enemy4.image); enemy4.image = NULL;}
    enemy4.image = enemy1.SetImage(id);
    enemy4.image->x = x;
    enemy4.image->y = y;
    
    totalNum++;
    
    return;
}

void ENEMY::SetUpSlot5(const int id, int x, int y)
{
    enemy5.attack =    enemy5.SetAttack(id);
    enemy5.health =    enemy5.SetHealth(id);
    enemy5.maxHealth = enemy5.health;
    enemy5.maxPower =  enemy5.SetPower(id);
    enemy5.jumpHeight =enemy5.SetJumpHeight(id);
    enemy5.alive = true;
    if(enemy5.image != NULL){oslDeleteImage(enemy5.image); enemy5.image = NULL;}
    enemy5.image = enemy1.SetImage(id);
    enemy5.image->x = x;
    enemy5.image->y = y;
    
    totalNum++;
    
    return;
}

void ENEMY::SetUpSlot6(const int id, int x, int y)
{
    enemy6.attack =    enemy6.SetAttack(id);
    enemy6.health =    enemy6.SetHealth(id);
    enemy6.maxHealth = enemy6.health;
    enemy6.maxPower =  enemy6.SetPower(id);
    enemy6.jumpHeight =enemy6.SetJumpHeight(id);
    enemy6.alive = true;
    if(enemy6.image != NULL){oslDeleteImage(enemy6.image); enemy6.image = NULL;}
    enemy6.image = enemy6.SetImage(id);
    enemy6.image->x = x;
    enemy6.image->y = y;
    
    totalNum++;
    
    return;
}

void ENEMY::SetUpSlot7(const int id, int x, int y)
{
    enemy7.attack =    enemy7.SetAttack(id);
    enemy7.health =    enemy7.SetHealth(id);
    enemy7.maxHealth = enemy7.health;
    enemy7.maxPower =  enemy7.SetPower(id);
    enemy7.jumpHeight =enemy7.SetJumpHeight(id);
    enemy7.alive = true;
    if(enemy7.image != NULL){oslDeleteImage(enemy7.image); enemy7.image = NULL;}
    enemy7.image = enemy7.SetImage(id);
    enemy7.image->x = x;
    enemy7.image->y = y;
    
    totalNum++;
    
    return;
}

void ENEMY::SetUpSlot8(const int id, int x, int y)
{
    enemy8.attack =    enemy8.SetAttack(id);
    enemy8.health =    enemy8.SetHealth(id);
    enemy8.maxHealth = enemy8.health;
    enemy8.maxPower =  enemy8.SetPower(id);
    enemy8.jumpHeight =enemy8.SetJumpHeight(id);
    enemy8.alive = true;
    if(enemy8.image != NULL){oslDeleteImage(enemy8.image); enemy8.image = NULL;}
    enemy8.image = enemy8.SetImage(id);
    enemy8.image->x = x;
    enemy8.image->y = y;
    
    totalNum++;
    
    return;
}

void ENEMY::SetUpSlot9(const int id, int x, int y)
{
    enemy9.attack =    enemy9.SetAttack(id);
    enemy9.health =    enemy9.SetHealth(id);
    enemy9.maxHealth = enemy9.health;
    enemy9.maxPower =  enemy9.SetPower(id);
    enemy9.jumpHeight =enemy9.SetJumpHeight(id);
    enemy9.alive = true;
    if(enemy9.image != NULL){oslDeleteImage(enemy9.image); enemy9.image = NULL;}
    enemy9.image = enemy9.SetImage(id);
    enemy9.image->x = x;
    enemy9.image->y = y;
    
    totalNum++;
    
    return;
}

void ENEMY::SetUpSlot10(const int id, int x, int y)
{
    enemy10.attack =    enemy10.SetAttack(id);
    enemy10.health =    enemy10.SetHealth(id);
    enemy10.maxHealth = enemy10.health;
    enemy10.maxPower =  enemy10.SetPower(id);
    enemy10.jumpHeight =enemy10.SetJumpHeight(id);
    enemy10.alive = true;
    if(enemy10.image != NULL){oslDeleteImage(enemy10.image); enemy10.image = NULL;}
    enemy10.image = enemy10.SetImage(id);
    enemy10.image->x = x;
    enemy10.image->y = y;
    
    totalNum++;
    
    return;
}

short ENEMY::SetJumpHeight(const short id)
{   
    short height = 5;
    
    if(id == DUDE)              height = 10;
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

int ENEMY::SetHealth(const short id)
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

int ENEMY::SetAttack(const short id)
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

long long ENEMY::SetPower(const short id)
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

OSL_IMAGE * ENEMY::SetImage(const short id)
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

ENEMY::ENEMY()
{
    health = 1;
    alive = false;
    image = NULL;
    guarding = false;
    attacking = false;
    id = 1;
    attack = 1;
    power = 1;
    waitToAttack = 0;
    
    return;
}

ENEMY::~ENEMY()
{
    if(image != NULL){oslDeleteImage(image); image = NULL;}
    
    return;
}
