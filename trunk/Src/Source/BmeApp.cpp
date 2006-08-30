/*****************************************************************
 * Copyright (c) 2005 Tim de Jong								 *
 *							       								 *
 * All rights reserved.											 *
 * Distributed under the terms of the MIT License.               *
 *****************************************************************/
#ifndef BME_APP_H
#include "BmeApp.h"
#endif

#include <be/app/Messenger.h>
#include <be/app/Roster.h>
#include <be/storage/AppFileInfo.h>
#include <be/storage/FindDirectory.h>
#include <be/storage/AppFileInfo.h>
#include <be/storage/File.h>
#include <be/interface/Alert.h>
#include "constants.h"
#include "ProtocolConstants.h"
#include "Preferences.h"
#include "Statusses.h"
#include "MainWindow.h"

/**	Constructor
 */
BmeApp::BmeApp()
		:	BApplication("application/x-vnd.Be-Messeng-er")			
{	
	//construct user settings dir
	find_directory(B_USER_SETTINGS_DIRECTORY,&m_prefsPath);
	m_prefsPath.Append(K_BME_SETTINGS_PATH);
	m_prefsPath.Append("Bme");		
	//load app's preferences
	LoadPreferences(m_prefsPath.Path());
	//find app dir
	app_info appInfo;
	be_app->GetAppInfo(&appInfo);
	BPath appDir(&appInfo.ref);	
	//load statusses
	BPath iconPrefsPath;
	appDir.GetParent(&iconPrefsPath);	
	iconPrefsPath.Append(K_STANDARD_ICON_PATH);
	iconPrefsPath.Append("iconprefs.txt");
	LoadStatusses(iconPrefsPath);
	//get window dimensions
	prefsLock.Lock();
	if (preferences.FindRect(K_MAIN_WINDOW_RECT,&m_mainWindowFrame) != B_OK)
	{
		m_mainWindowFrame = BRect(100,100,400,500);
	}
	//add standard client id, if not found
	int64 id;
	id = ClientIdentification::K_MSNC4;
			 
		preferences.ReplaceInt64(K_CLIENT_ID,id);
		
	/*if (preferences.FindInt64(K_CLIENT_ID,id) != B_OK)
	{		
		id = ClientIdentification::K_MSNC1 + ClientIdentification::K_MSNC2 +
			 ClientIdentification::K_MSNC3 + ClientIdentification::K_MSNC4;
			 
		preferences.AddInt64(K_CLIENT_ID,id);
	}*/	
	prefsLock.Unlock();
	//start the protocol looper
	m_protocolLooper = new ProtocolLooper();
	m_protocolLooper->Run();
	//construct app's main window
	MainWindow *mainWindow = new MainWindow(m_mainWindowFrame, m_protocolLooper);	
	mainWindow->Show();	
}

/**	Destructor
 */
BmeApp::~BmeApp()
{		
	//save app's preferences
	SavePreferences(m_prefsPath.Path());
	//clean up statusses
	DeleteStatusses();
}

/**	Hook function: handles received messages.
	@param message, the current message from the message queue to handle 
 */
void BmeApp::MessageReceived(BMessage* message)
{
	switch(message->what)
	{
		//if soundplay or CL-amp wants to set current track playing
		case InterfaceMessages::K_USER_SET_PERSONAL_MSG:
		{
			BMessenger msgr(m_protocolLooper);
			msgr.SendMessage(message);
		}
		break;
		default:
			BApplication::MessageReceived(message);
		break;
	}
}

/**	Hook function: called when user requests about information.
 */
void BmeApp::AboutRequested()
{	
	//get application version, from SimplyVorbis code!
	app_info ai;
	version_info vi;
	be_app->GetAppInfo(&ai);
	BFile file(&ai.ref,B_READ_ONLY);
	BAppFileInfo appinfo(&file);
	appinfo.GetVersionInfo(&vi,B_APP_VERSION_KIND);

	BString variety;
	switch(vi.variety)
	{
		case 0:
			variety = "d";
			break;
		case 1:
			variety = "a";
			break;
		case 2:
			variety = "b";
			break;
		case 3:
			variety = "g";
			break;
		case 4:
			variety = "rc";
			break;
		default:
			variety = "Final";
			break;
	}
	
	char version[64];
	if(variety!="Final")
		sprintf(version,"%s %lu.%lu %s%lu","v",vi.major,
			vi.middle,variety.String(),vi.internal);
	else
		sprintf(version,"%s %lu.%lu","v",vi.major,vi.middle);
	
	BString bmeVersion = "Bme ";
	bmeVersion << version << "\n\n" << AppConstants::K_ABOUT_TEXT;	
	BAlert *alert = new BAlert("Info", bmeVersion.String(), "OK");
	alert->Go(NULL);
}

/**	Main function: creates a BmeApp object and runs it. Starts the application.
	@return 0, if execution was stopped correctly.
 */
int main()
{	
	BmeApp bme;
	bme.Run();

	return 0;
}
