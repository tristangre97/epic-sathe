#include <pspkernel.h>
#include <oslib/oslib.h>

/*Wait; will pause the screen for 3 seconds*/
#define Wait sceKernelDelayThread(3000000);

/*Wait; will pause the screen for 0.5 seconds*/
#define hWait sceKernelDelayThread(500000);

/* sprite positions */
#define STILL_RIGHT 0
#define GUARDING_RIGHT 76
#define RIGHT 152
#define LEFT 228
#define ATTACKING_RIGHT 304
#define ATTACKING_LEFT 380
#define JUMPING 456
#define GUARDING_LEFT 532
#define STILL_LEFT 546

/* normal psp calls */
PSP_MODULE_INFO("Epic Sathe", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);
PSP_HEAP_SIZE_KB(-2024);

/* menu macros */
#define SHOW_MAIN_MENU 1
#define SHOW_SECOND_MENU 2
#define EXIT 0

/* effect macros */
#define BLOWN_BACK_RIGHT 893
#define BLOWN_BACK_LEFT 793
#define NOTHING 0

/* define fighter ID's */
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

/* other macros */
#define GROUND 160
#define LAST_LEVEL 8

/* global OSL_SOUND and OSL_IMAGE variables */
OSL_SOUND *menu_music, *select, *scream, *groan, *punch1, *punch2, *hard_punch, *soft_punch, *confuse,
*stun, *powerup, *smashFist, *battle1, *battle2, *battle3, *battle4, *groan2, *bought, *battle5, *error,
*powerUp;

OSL_IMAGE *level, *cloud1, *cloud2, *cloud3, *cloud4, *cloud5, *cloud6, *cloud7, *cloud8;

/* define our color set for easy use */
enum colors 
{
    RED          = 0xFF0000FF,
	GREEN        = 0xFF00FF00,
	BLUE         = 0xFFFF0000,
	WHITE        = 0xFFFFFFFF,
	LIGHTGRAY    = 0xFFBFBFBF,
	GRAY         = 0xFF7F7F7F,
	DARKGRAY     = 0xFF3F3F3F,		
	BLACK        = 0xFF000000,
	AZURE        = 0xFFFF7F00,
    VIOLET       = 0xFFFF007F,
    ROSE         = 0xFF7F00FF,
    ORANGE       = 0xFF007FFF,
    CHARTREUSE   = 0xFF00FF7F,
    SPRING_GREEN = 0xFF7FFF00,
    CYAN         = 0xFFFFFF00,
    MAGENTA      = 0xFFFF00FF,
    YELLOW       = 0xFF00FFFF,
};

//keeps track of the level the player is on
int currentLevel = 1;

//checks to see if the level was loaded already
int spawned = 0;
int totalNum = 0;
        
/* very simple function.... decided to just place it here */
inline void placeSelector(OSL_IMAGE * image, int x, int y)
{
    image->x = x;
    image->y = y;
}

int collision(OSL_IMAGE *img1,float img1posX, float img1posY, OSL_IMAGE *img2, float img2posX, float img2posY );

void pauseGame( void );

void HANDLE_GAME();

int MAIN_GAME();

void VAUGHN_LOGO( void );

#include "classes/stats.h"

#include "classes/player.h"

#include "classes/enemy.h"

#include "classes/multiplayer.h"

#include "classes/menu.h"

#include "classes/level.h"


