/*
 * Multiplayer functions and globals ~V@ughn 
 * -----------------------------------------
 * ->These functions are used for playing online or adhoc games with friends!
      -a class method was not approached due to certain static linkage problems
         and it just made life a whole lot easier keeping it simple and placing
         it all in a couple functions.
 */ 
#define ADDRESS "www.google.it"

static char message[100] = "";

static char buffer[100] = "";

int InitOnlineGame();

int InitAdhocGame();

int connectAPCallback(int state);

int connectToAP(int config);

void doClient();

void doServer();

void clientConnected(struct remotePsp *aPsp);

void serverConnected(struct remotePsp *aPsp);

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
//MULTIPLAYER function definitions://///////////////////////////////////////////////////////////////////////////

int InitAdhocGame()
{
    IMAGE * image = oslLoadImageFilePNG((char*)"img/data/lx1.png", OSL_IN_RAM, OSL_PF_5551);
    
    //clear screen
    oslStartDrawing();
    oslSetBkColor(RGBA(0,0,0,0)); 
    oslClearScreen(BLACK);
    oslEndDrawing();
    oslSyncFrame();
    
    while(1)
    {
        oslStartDrawing();
        oslDrawImage(image);
	    oslSetTextColor(RED);
	    
		if (oslIsWlanPowerOn()){
			oslDrawString(10, 10, "Press [] to start a server");
			oslDrawString(10, 35, "Press X to start a client");
		}
		else oslDrawString(10, 10, "Please turn on the wlan switch");
			
        oslDrawString(10, 55, "Press O to quit");

        oslEndDrawing();
        
        oslEndDrawing();
        oslSyncFrame();

        oslReadKeys();
        if (osl_keys->released.cross && oslIsWlanPowerOn())       doClient();
        else if (osl_keys->released.square && oslIsWlanPowerOn()) doServer();
        else if (osl_keys->released.circle)                       break;
    }
    
    return 0;
}

int InitOnlineGame()
{
    int enabled = 0;
    int selectedConfig = 0;
    
    oslNetInit();
    
    if (!oslIsWlanPowerOn())
        sprintf(message, "Please turn on the WLAN.");
    
    //Get connections list:
    struct oslNetConfig configs[OSL_MAX_NET_CONFIGS];
    int numconfigs = oslGetNetConfigs(configs);
    if (!numconfigs){
        sprintf(message, "No configuration found!");
        enabled = 0;
    }
    
    while(1)
    {
		oslStartDrawing();
	
        if (enabled){
            sprintf(buffer, "Press X to connect to %s.", configs[selectedConfig].name);
    		oslDrawString(30, 50, buffer);
    		oslDrawString(30, 80, "Press UP and DOWN to change settings.");
        }
        
        oslDrawString(30, 150, "Press O to quit.");
		oslDrawString(30, 200, message);

		oslEndDrawing();
        oslEndFrame();
        oslSyncFrame();

        oslReadKeys();
        if (osl_keys->released.circle) break;

        if (osl_keys->released.cross){connectToAP(selectedConfig + 1);}
        
        else if (osl_keys->released.up){if (++selectedConfig >= numconfigs)selectedConfig = numconfigs - 1;}
        
        else if (osl_keys->released.down){if (--selectedConfig < 0)selectedConfig = 0;}
    }
    
    oslNetTerm();
    
    return 1;
}


int connectAPCallback(int state)
{
    oslStartDrawing();
    oslDrawString(30, 200, "Connecting to AP...");
    sprintf(buffer, "State: %i", state);
    oslDrawString(30, 230, buffer);
    oslEndDrawing();
    oslEndFrame();
    oslSyncFrame();

    return 0;
}


int connectToAP(int config)
{
    oslStartDrawing();
    oslDrawString(30, 200, "Connecting to AP...");
    oslEndDrawing();
    oslEndFrame();
    oslSyncFrame();

    int result = oslConnectToAP(config, 30, connectAPCallback);
    if (!result){
        char ip[30] = "";
        char resolvedIP[30] = "";

        oslStartDrawing();
        oslGetIPaddress(ip);
        sprintf(buffer, "IP address: %s", ip);
        oslDrawString(30, 170, buffer);

        sprintf(buffer, "Resolving %s", ADDRESS);
        oslDrawString(30, 200, buffer);
        oslEndDrawing();
        oslEndFrame();
        oslSyncFrame();

        result = oslResolveAddress((char*)ADDRESS, resolvedIP);

        oslStartDrawing();
        oslGetIPaddress(ip);
        if (!result)
            sprintf(buffer, "Resolved IP address: %s", ip);
        else
            sprintf(buffer, "Error resolving address!");
        oslDrawString(30, 230, buffer);
        oslEndDrawing();
        oslEndFrame();
        oslSyncFrame();
		sceKernelDelayThread(3*1000000);
    }else{
        oslStartDrawing();
        sprintf(buffer, "Error connecting to AP!");
        oslDrawString(30, 200, buffer);
        oslEndDrawing();
        oslEndFrame();
        oslSyncFrame();
		sceKernelDelayThread(3*1000000);
    }
    oslDisconnectFromAP();
    return 0;
}

//Connects to a psp:
void doClient()
{
    int skip = 0;
	int quit = 0;
	int i = 0;
	int current = 0;
	
	IMAGE * image = oslLoadImageFilePNG((char*)"img/data/lx1.png", OSL_IN_RAM, OSL_PF_5551);
	
	oslStartDrawing();
    oslDrawImage(image);
    oslEndDrawing();
    oslSyncFrame();

	int init = oslAdhocInit((char*)"ULUS99999");
	if (init)
	{
		char message[100] = "";
		sprintf(message, "adhocInit error: %i", init);
		oslMessageBox(message, "Debug",  oslMake3Buttons(OSL_KEY_CROSS, OSL_MB_OK , 0, 0, 0, 0));
		for(int i = 0; i < 50; i++){}
		return;
	}

    while(!osl_quit && !quit){
        if (!skip){
            oslStartDrawing();

			u8 *macAddress = oslAdhocGetMacAddress();
	        oslPrintf_xy(10, 10, "Current state: %s", oslAdhocGetState() == ADHOC_INIT ? "OK" : "KO");
	        oslPrintf_xy(10, 25, "Your MAC address: %02X:%02X:%02X:%02X:%02X:%02X", macAddress[0], macAddress[1], macAddress[2], macAddress[3], macAddress[4], macAddress[5]);
	
			if (oslAdhocGetRemotePspCount())
				oslPrintf_xy(10, 40, "Press X to request a connection");
			oslPrintf_xy(10, 55, "Press O to abort");
			for (i=0; i < oslAdhocGetRemotePspCount(); i++)
			{
				oslDrawString(10, 100 + 15 * i, oslAdhocGetPspByIndex(i)->name);
			}
            oslEndDrawing();
        }
        oslEndFrame();
        skip = oslSyncFrame();

		oslReadKeys();
		if (osl_keys->released.down)
		{
			if (++current >= oslAdhocGetRemotePspCount())
				current = 0;
		}
		else if (osl_keys->released.up)
		{
			if (--current < 0)
				current = oslAdhocGetRemotePspCount() - 1;
		}
		else if (osl_keys->released.cross && oslAdhocGetRemotePspCount())
		{
			//Request a connection:
			int ret = oslAdhocRequestConnection(oslAdhocGetPspByIndex(current), 30, NULL);
			if (ret == OSL_ADHOC_ACCEPTED || ret == OSL_ADHOC_ESTABLISHED)
			{
				clientConnected(oslAdhocGetPspByIndex(current));
			}
		}
		else if (osl_keys->released.circle)
		{
			quit = 1;
		}
	}
	oslAdhocTerm();
}

				
//Waits for a connection from a psp:
void doServer()
{
    IMAGE * image = oslLoadImageFilePNG((char*)"img/data/lx1.png", OSL_IN_RAM, OSL_PF_5551);
    
    oslStartDrawing();
    oslDrawImage(image);
    oslEndDrawing();
    oslSyncFrame();
    
    int skip = 0;
	int quit = 0;
	char message[100] = "";
	int dialog = OSL_DIALOG_NONE;
	int connected = 0;

	int init = oslAdhocInit((char*)"ULUS99999");
	if (init)
	{
		snprintf(message, sizeof(message), "adhocInit error: %i", init);
		oslMessageBox(message, "Debug",  oslMake3Buttons(OSL_KEY_CROSS, OSL_MB_OK , 0, 0, 0, 0));
		for(int i = 0; i < 50; i++){}
		return;
	}

    while(!osl_quit && !quit){
		struct remotePsp *reqPsp = oslAdhocGetConnectionRequest();

        if (!skip){
            oslStartDrawing();

			u8 *macAddress = oslAdhocGetMacAddress();
	        oslPrintf_xy(10, 15, "Current state: %s", oslAdhocGetState() == ADHOC_INIT ? "OK" : "KO");
	        oslPrintf_xy(10, 25, "Your MAC address: %02X:%02X:%02X:%02X:%02X:%02X", macAddress[0], macAddress[1], macAddress[2], macAddress[3], macAddress[4], macAddress[5]);
	        
			oslPrintf_xy(10, 35, "Press O to abort");
			if (reqPsp == NULL)
			{
				oslPrintf_xy(10, 65, "Waiting for a connection request...");
			}
			else
			{
				snprintf(message, sizeof(message), "Accept request from psp : %s", reqPsp->name);
				oslDrawString(10, 100, message);
				if (oslGetDialogType() == OSL_DIALOG_NONE)
					oslInitMessageDialog(message, 1);
			}

            dialog = oslGetDialogType();
            if (dialog){
                oslDrawDialog();
                if (oslGetDialogStatus() == PSP_UTILITY_DIALOG_NONE){
                    if (dialog == OSL_DIALOG_MESSAGE){
                        int button = oslGetDialogButtonPressed();
                        if (button == PSP_UTILITY_MSGDIALOG_RESULT_YES)
						{
							oslAdhocAcceptConnection(reqPsp);
							connected = 1;
						}
                        else if (button == PSP_UTILITY_MSGDIALOG_RESULT_NO)
						{
							oslAdhocRejectConnection(reqPsp);
						}
                    }
                    oslEndDialog();
                }
			}

            oslEndDrawing();
        }
        oslEndFrame();
        skip = oslSyncFrame();

		if (connected)
			serverConnected(reqPsp);

		oslReadKeys();
		if (dialog == OSL_DIALOG_NONE)
		{
			if (osl_keys->released.circle)
			{
				quit = 1;
			}
		}
	}
	oslAdhocTerm();
}