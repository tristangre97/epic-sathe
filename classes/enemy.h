class ENEMY : public STATS
{
    public:
           ENEMY();
           ~ENEMY();
           
           //manipulators
           int special;
           int waitToAttack;
           
           //others
           short march;
           short position;
           short manipulate;
           int sy;
           
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
           
           inline void Handle(OSL_IMAGE * image, long long &health, long long &attack, long long &power, long long maxPower, bool &touchingGround, bool &attacking, int &sy, short &position, int &special);
    
    private:
        
}enemy1, enemy2, enemy3, enemy4, enemy5, enemy6, enemy7, enemy8, enemy9, enemy10, spawn;

inline void ENEMY::Handle(OSL_IMAGE * image, long long &health, long long &attack, long long &power, long long maxPower, bool &touchingGround, bool &attacking, int &sy, short &position, int &special)
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
    oslPrintf_xy(image->x, image->y - 4, "HP: %lld", health);
    
    //check for collisions
    int colliding = collision(player.image,player.image->x, player.image->y,image, image->x,image->y);
    
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
    enemy1.attack =    assign.SetAttack(id);
    enemy1.health =    assign.SetHealth(id);
    enemy1.maxHealth = enemy1.health;
    enemy1.maxPower =  assign.SetPower(id);
    enemy1.jumpHeight =assign.SetJumpHeight(id);
    enemy1.alive = true;
    if(enemy1.image != NULL){oslDeleteImage(enemy1.image); enemy1.image = NULL;}
    enemy1.image = assign.SetImage(id);
    enemy1.image->x = x;
    enemy1.image->y = y;
    
    totalNum++;
    
    return;
}

void ENEMY::SetUpSlot2(const int id, int x, int y)
{
    enemy2.attack =    assign.SetAttack(id);
    enemy2.health =    assign.SetHealth(id);
    enemy2.maxHealth = enemy2.health;
    enemy2.maxPower =  assign.SetPower(id);
    enemy2.jumpHeight =assign.SetJumpHeight(id);
    enemy2.alive = true;
    if(enemy2.image != NULL){oslDeleteImage(enemy2.image); enemy2.image = NULL;}
    enemy2.image = assign.SetImage(enemy2.id);
    enemy2.image->x = x;
    enemy2.image->y = y;
    
    totalNum++;
       
    return;
}

void ENEMY::SetUpSlot3(const int id, int x, int y)
{
    enemy3.attack =    assign.SetAttack(id);
    enemy3.health =    assign.SetHealth(id);
    enemy3.maxHealth = enemy3.health;
    enemy3.maxPower =  assign.SetPower(id);
    enemy3.jumpHeight =assign.SetJumpHeight(id);
    enemy3.alive = true;
    if(enemy3.image != NULL){oslDeleteImage(enemy3.image); enemy3.image = NULL;}
    enemy3.image = assign.SetImage(id);
    enemy3.image->x = x;
    enemy3.image->y = y;
    
    totalNum++;
    
    return;
}

void ENEMY::SetUpSlot4(const int id, int x, int y)
{
    enemy4.attack =    assign.SetAttack(id);
    enemy4.health =    assign.SetHealth(id);
    enemy4.maxHealth = assign.health;
    enemy4.maxPower =  assign.SetPower(id);
    enemy4.jumpHeight =assign.SetJumpHeight(id);
    enemy4.alive = true;
    if(enemy4.image != NULL){oslDeleteImage(enemy4.image); enemy4.image = NULL;}
    enemy4.image = assign.SetImage(id);
    enemy4.image->x = x;
    enemy4.image->y = y;
    
    totalNum++;
    
    return;
}

void ENEMY::SetUpSlot5(const int id, int x, int y)
{
    enemy5.attack =    assign.SetAttack(id);
    enemy5.health =    assign.SetHealth(id);
    enemy5.maxHealth = enemy5.health;
    enemy5.maxPower =  assign.SetPower(id);
    enemy5.jumpHeight =assign.SetJumpHeight(id);
    enemy5.alive = true;
    if(enemy5.image != NULL){oslDeleteImage(enemy5.image); enemy5.image = NULL;}
    enemy5.image = assign.SetImage(id);
    enemy5.image->x = x;
    enemy5.image->y = y;
    
    totalNum++;
    
    return;
}

void ENEMY::SetUpSlot6(const int id, int x, int y)
{
    enemy6.attack =    assign.SetAttack(id);
    enemy6.health =    assign.SetHealth(id);
    enemy6.maxHealth = enemy6.health;
    enemy6.maxPower =  assign.SetPower(id);
    enemy6.jumpHeight =assign.SetJumpHeight(id);
    enemy6.alive = true;
    if(enemy6.image != NULL){oslDeleteImage(enemy6.image); enemy6.image = NULL;}
    enemy6.image = assign.SetImage(id);
    enemy6.image->x = x;
    enemy6.image->y = y;
    
    totalNum++;
    
    return;
}

void ENEMY::SetUpSlot7(const int id, int x, int y)
{
    enemy7.attack =    assign.SetAttack(id);
    enemy7.health =    assign.SetHealth(id);
    enemy7.maxHealth = enemy7.health;
    enemy7.maxPower =  assign.SetPower(id);
    enemy7.jumpHeight =assign.SetJumpHeight(id);
    enemy7.alive = true;
    if(enemy7.image != NULL){oslDeleteImage(enemy7.image); enemy7.image = NULL;}
    enemy7.image = assign.SetImage(id);
    enemy7.image->x = x;
    enemy7.image->y = y;
    
    totalNum++;
    
    return;
}

void ENEMY::SetUpSlot8(const int id, int x, int y)
{
    enemy8.attack =    assign.SetAttack(id);
    enemy8.health =    assign.SetHealth(id);
    enemy8.maxHealth = enemy8.health;
    enemy8.maxPower =  assign.SetPower(id);
    enemy8.jumpHeight =assign.SetJumpHeight(id);
    enemy8.alive = true;
    if(enemy8.image != NULL){oslDeleteImage(enemy8.image); enemy8.image = NULL;}
    enemy8.image = assign.SetImage(id);
    enemy8.image->x = x;
    enemy8.image->y = y;
    
    totalNum++;
    
    return;
}

void ENEMY::SetUpSlot9(const int id, int x, int y)
{
    enemy9.attack =    assign.SetAttack(id);
    enemy9.health =    assign.SetHealth(id);
    enemy9.maxHealth = enemy9.health;
    enemy9.maxPower =  assign.SetPower(id);
    enemy9.jumpHeight =assign.SetJumpHeight(id);
    enemy9.alive = true;
    if(enemy9.image != NULL){oslDeleteImage(enemy9.image); enemy9.image = NULL;}
    enemy9.image = assign.SetImage(id);
    enemy9.image->x = x;
    enemy9.image->y = y;
    
    totalNum++;
    
    return;
}

void ENEMY::SetUpSlot10(const int id, int x, int y)
{
    enemy10.attack =    assign.SetAttack(id);
    enemy10.health =    assign.SetHealth(id);
    enemy10.maxHealth = enemy10.health;
    enemy10.maxPower =  assign.SetPower(id);
    enemy10.jumpHeight =assign.SetJumpHeight(id);
    enemy10.alive = true;
    if(enemy10.image != NULL){oslDeleteImage(enemy10.image); enemy10.image = NULL;}
    enemy10.image = assign.SetImage(id);
    enemy10.image->x = x;
    enemy10.image->y = y;
    
    totalNum++;
    
    return;
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
