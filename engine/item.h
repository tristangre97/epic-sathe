/**
 * class ITEM ~V@ughn
 * ------------------
 * ->contains data to create an in-battle collectable item
 *    -independant class, relies on nothing but itself
 *      
 */
class ITEM  
{
    public:
        ITEM();
        ~ITEM();
        
        //properites
        IMAGE * image;
        SOUND * collected;
        SOUND * missed;
        bool active;
        long long stall;
        
        //behaviors
        virtual inline void SpriteAnimate();
        virtual void UpdateItem(IMAGE * level);
    
    private:
        int manipulate;
        int position;
        int march;
};

#define WAIT_TIME 1000

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
//ITEM methods://///////////////////////////////////////////////////////////////////////////

void ITEM::UpdateItem(IMAGE * level)
{
    if(!image || !collected) oslFatalError("ERROR! ITEM properties are equal to NULL!");
    
    if(active)
    {
        SpriteAnimate();
        
        //move powerup image downwards and rotate
        image->y++;
        image->angle += 3;
        
        //check for collisions
        int colliding = collision(player.image,player.image->x, player.image->y,image, image->x,image->y);
        
        //if player grabbed item
        if(colliding)
        {
            //play sound effect and reset item
            oslPlaySound(collected, 6);
            active = false;
            
            //powerup animation effect
            player.powerActivated = true;
            for(int i = 0; i < 50; i++){
                oslStartDrawing();
                oslSetAlpha(OSL_FX_ADD, (200 + i)); 
                oslDrawImage(level);
                oslEndDrawing();
                oslSyncFrame();
            }
         
             //reset position
            image->y = -5;
            srand((unsigned)time(0));
            image->x = (rand()%150)+220;
            
            //reset stall
            stall = 0;
        }
        
        //if player failed to grab item
        if(image->y >= 280){
            //play sound effect and reset item
            oslPlaySound(missed, 6);
            active = false;
            
            //reset position
            image->y = -5;
            srand((unsigned)time(0));
            image->x = (rand()%150)+220;
            
            //reset stall
            stall = 0;
        }
            
     }
     
     else
     {
        stall++;
        if(stall >= WAIT_TIME)
            active = true;
            
        //reset position
        image->y = -5;
        srand((unsigned)time(0));
        image->x = (rand()%300)+250;
     }
            
    return;
}

inline void ITEM::SpriteAnimate()
{	
    //Moves the sprite in the row that it is in
    manipulate++; if(manipulate > 10) {march++; manipulate = 0;}
    
    oslSetImageTileSize(image,(march * 23),position,25,23);
    
    oslSetAlpha(OSL_FX_ADD, 400);
    oslDrawImage(image);
    
    if (march == 4) march = 0;
    
    
}


ITEM::ITEM()
{
    position = 0;
    march = 0;
    manipulate = 0;
    stall = 0;
    active = false;
}

ITEM::~ITEM()
{
    
    return;
}