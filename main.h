#include <oslib/oslib.h>

/*Wait; will pause the screen for 3 seconds*/
#define Wait sceKernelDelayThread(3000000);

/*Wait; will pause the screen for 0.5 seconds*/
#define hWait sceKernelDelayThread(500000);

/* normal psp calls */
PSP_MODULE_INFO("Epic Sathe", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);
PSP_HEAP_SIZE_KB(-1024);

/* menu macros */
#define SHOW_MAIN_MENU 1
#define SHOW_SECOND_MENU 2
#define EXIT 0

typedef OSL_IMAGE IMAGE;
typedef OSL_SOUND SOUND;
typedef OSL_FONT FONT;

/* global OSL_SOUND and OSL_IMAGE variables */
SOUND *menu_music, *select, *scream, *groan, *punch1, *punch2, *hard_punch, *soft_punch, *confuse,
*stun, *smashFist, *battle1, *battle2, *battle3, *battle4, *groan2, *bought, *battle5, *error,
*nextLevelSound;

IMAGE *level, *cloud1, *cloud2, *cloud3, *cloud4, *cloud5, *cloud6, *cloud7, *cloud8;

/* define our color set for easy use */
enum colors {
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


/************************* GLOBALS ********************************/
//keeps track of the level the player is on
int currentLevel = 1;
int currentBossLevel = 1;
int trackLevel = currentBossLevel;

//checks to see if the level was loaded already
int spawned = 0;
int totalNum = 0;
/************************* GLOBALS ********************************/


/* very simple function.... decided to just place it here */
inline void placeSelector(OSL_IMAGE * image, int x, int y)
{ image->x = x; image->y = y; }

int collision(OSL_IMAGE *img1,float img1posX, float img1posY, OSL_IMAGE *img2, float img2posX, float img2posY );

void HANDLE_GAME();

void PauseGame( void );

void AnimatePowerUp();

int BOSS_MODE();

int MAIN_GAME(const int MODE);

void VAUGHN_LOGO( void );

#include "engine/stats.h"

/* had to define here due to linking problems... messy fix I know */
class Multiplayer : public STATS {
    public:
        Multiplayer();
        ~Multiplayer();

        int InitOnlineGame();
        int InitAdhocGame();
        
    private:
        
}online;

#include "engine/player.h"

#include "engine/io.h"

#include "engine/enemy.h"

#include "engine/menu.h"

#include "engine/level.h"

#include "engine/multiplayer.h"

#include "engine/item.h"
