/**
 * I/O functions and globals ~V@ughn 
 * -----------------------------------------
 * ->It did not make sense to make a class with only two methods so all of the saving and loading
 *     has been squeezed into two simple functions 
 * ->Relies on class CONTROLLER to save and load data
 * ->saves player stats
 * ->loads player stats
 */
int SaveGame();
 
int LoadGame();

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
//I/O function definitions:////////////////////////////////////////////////////////////////////////////
int SaveGame()
{
    #define SUCCESS 1
    #define ERROR 0
    
    oslStartDrawing();
    oslClearScreen(BLACK);
    oslSetTextColor(WHITE);
    oslPrintf_xy(5, 5, "SAVING STATS...");
    oslEndDrawing();
    oslSyncFrame();
    hWait();
    
    //prepare file for writing
    FILE * saveFile, *saveSoloLevel, *saveBossLevel, *saveMoney;
    saveFile = fopen("define/save1", "w");
    saveSoloLevel = fopen("define/save2", "w");
    saveBossLevel = fopen("define/save3", "w");
    saveMoney = fopen("define/save4", "w");
    
    //write player data while also encrypting it with a key
    //fprintf(saveFile, KEY);
    fprintf(saveFile, "%d", player.id);
    
    //write player solo level
    fprintf(saveSoloLevel, "%d", use.currentLevel);
    
    //write player boss level
    fprintf(saveBossLevel, "%d", use.currentBossLevel);
    
    //write player money
    fprintf(saveMoney, "%lld", player.money);
    
    //close save file
    fclose(saveFile);
    fclose(saveSoloLevel);
    fclose(saveBossLevel);
    fclose(saveMoney);

    return SUCCESS;
}

int LoadGame()
{
    oslStartDrawing();
    oslClearScreen(BLACK);
    oslSetTextColor(WHITE);
    oslPrintf_xy(5, 5, "LOADING STATS...");
    oslEndDrawing();
    oslSyncFrame();
    hWait();
    
    #define SUCCESS 1
    #define ERROR 0
    
    //prepare file for loading
    FILE * loadFile, *loadSoloLevel, *loadBossLevel, *loadMoney;
    long long size, size2, size3, size4;
    char * buffer, *buffer2, *buffer3, *buffer4;
    loadFile = fopen("define/save1", "r");
    loadSoloLevel = fopen("define/save2", "r");
    loadBossLevel = fopen("define/save3", "r");
    loadMoney = fopen("define/save4", "r");
    
    //if the file was not found exit
    if(!loadFile || !loadSoloLevel || !loadBossLevel || !loadMoney){
        fclose(loadFile);
        fclose(loadSoloLevel);
        fclose(loadBossLevel);
        fclose(loadMoney);
        return ERROR;
    }
    
    //set up file for reading
	fseek(loadFile , 0 , SEEK_END);
	size = ftell(loadFile);
	rewind(loadFile);
	buffer = (char*) malloc(size+1);
	
	//set up file for reading
	fseek(loadSoloLevel , 0 , SEEK_END);
	size2 = ftell(loadSoloLevel);
	rewind(loadSoloLevel);
	buffer2 = (char*) malloc(size2+1);
	
	//set up file for reading
	fseek(loadBossLevel , 0 , SEEK_END);
	size3 = ftell(loadBossLevel);
	rewind(loadBossLevel);
	buffer3 = (char*) malloc(size3+1);
	
	//set up file for reading
	fseek(loadMoney , 0 , SEEK_END);
	size4 = ftell(loadMoney);
	rewind(loadMoney);
	buffer4 = (char*) malloc(size4+1);
	
	//if the data is corrupt or not there exit
	if(!buffer || !buffer2 || !buffer3 || !buffer4) {
        fclose(loadFile);
        fclose(loadSoloLevel);
        fclose(loadBossLevel);
        fclose(loadMoney);
        return ERROR;
    }
	 
	//read data and place it into buffer
	fread(buffer, 1, size, loadFile);
	buffer[size] = '\0'; // Add NULL terminator.
	
	//read data and place it into buffer
	fread(buffer2, 1, size2, loadSoloLevel);
	buffer2[size2] = '\0'; // Add NULL terminator.
	
	//read data and place it into buffer
	fread(buffer3, 1, size3, loadBossLevel);
	buffer3[size3] = '\0'; // Add NULL terminator.
	
	//read data and place it into buffer
	fread(buffer4, 1, size4, loadMoney);
	buffer4[size4] = '\0'; // Add NULL terminator.
	
	//now close the file 
	fclose(loadFile);
	fclose(loadSoloLevel);
    fclose(loadBossLevel);
    fclose(loadMoney);
	
	/* all of the data from the file is now stored into
	   char * buffer... we can now manipulate it
	*/
	
	//apply values
	player.id = atoi(buffer);
	use.currentLevel = atoi(buffer2);
	use.currentBossLevel = atoi(buffer3);
	player.money = atoi(buffer4);
	
	oslStartDrawing();
    oslClearScreen(BLACK);
    oslSetTextColor(WHITE);
    oslPrintf_xy(5, 5, "STATS loaded!");
    oslEndDrawing();
    oslSyncFrame();
    hWait();
    
	if(player.initialBoot){player.initialBoot = false;}
    player.SetUp(player.id); 
    
    return SUCCESS;
}
  