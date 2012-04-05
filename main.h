typedef OSL_IMAGE IMAGE;
typedef OSL_SOUND SOUND;
typedef OSL_FONT FONT;

#define GROUND 234
#define LAST_LEVEL 8

/*Wait; will pause the screen for 3 seconds*/
#define Wait() sceKernelDelayThread(3000000);

/*Wait; will pause the screen for 0.5 seconds*/
#define hWait() sceKernelDelayThread(500000);

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

/******************** 
 * global Variables *
 ********************/
int totalNum = 0;

int attackLevel = 0;
float attackManip = 1;

int healthLevel = 0;
float healthManip = 1;

int jumpLevel = 0;
float jumpManip = 1;

int powerLevel = 0;
float powerManip = 1;

SOUND *menu_music, *scream, *punch1, *punch2, *hard_punch, *soft_punch, *confuse, 
*stun, *smashFist, *jump, *groan, *groan2;
FONT * ltn;

/**
 * (very simple function.... decided to just place it here)
 * @param image - source image
 * @param x - x position for source image to be drawn
 * @param y - y position for source image to be drawn
 */
inline void placeSelector(OSL_IMAGE * image, int x, int y)
{ image->x = x; image->y = y; }

/**
 * Shows my custom logo (mandatory for any mod of this game)
 */
void VAUGHN_LOGO( void );

/**
 * Pauses the game and allows access to menu
 */
void PauseGame( void );

/**
 * Simple collision test... self explanatory code
 */
int collision(OSL_IMAGE *img1,float img1posX, float img1posY, OSL_IMAGE *img2, float img2posX, float img2posY );

/**
 * Main function of entire game
 *@param MODE - if 1 game mode = SOLO, if 2 game mode = BOSS 
 */
int MAIN_GAME(const int MODE);


/**
 * Epic Sathe game engine
 * (for documentation read each file within engine)
 * ~made by V@ughn
 */
int SaveGame();

int LoadGame();

#include "engine\stats.h"

#include "engine\multiplayer.h"

#include "engine\object.h"

#include "engine\item.h"

#include "engine\menu.h"

#include "engine\controller.h"

#include "engine\io.h"