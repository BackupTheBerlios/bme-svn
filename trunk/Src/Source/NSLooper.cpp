/*****************************************************************
 * Copyright (c) 2005 Tim de Jong								 *
 *							       								 *
 * All rights reserved.											 *
 * Distributed under the terms of the MIT License.               *
 *****************************************************************/
#ifndef NS_LOOPER_H
#include "NSLooper.h"
#endif

#include <be/app/MessageQueue.h>
#include <be/app/Handler.h>
#include <be/app/Messenger.h>
#include <iostream>
#include "constants.h"
#include "ProtocolConstants.h"
//handler classes
#include "AuthenticationHandler.h"
#include "ContactListHandler.h"
#include "ErrorHandler.h"
#include "UserInfoHandler.h"
#include "NSUIFilter.h"
#include "UIHandler.h"
#include "MessageFields.h"

/**	Constructor
	Connects to the Dispatch server which directs to a 
	Notification server, to which subsequently will be connected.
 */
NSLooper::NSLooper(BLooper *owner)
			:	ServerLooper(owner)
{		
	AddHandler(new AuthenticationHandler());
	AddHandler(new ContactListHandler());	
	AddHandler(new ErrorHandler());
	AddHandler(new UserInfoHandler());
	//add UIHandler
	UIHandler *uiHandler = new UIHandler(owner);
	uiHandler->AddFilter(new NSUIFilter());
	AddHandler(uiHandler);
}

NSLooper::~NSLooper()
{	
	//delete sbloopers!!!
	typedef map<BString,SBLooper*>::const_iterator CI;
	for (CI p = sbLoopers.begin(); p != sbLoopers.end();++p)
	{
		delete (*p).second;
	}
}

void NSLooper::MessageReceived(BMessage *message)
{
	switch(message->what)
	{
		case InterfaceMessages::K_CONNECT_SB_MSG:
		{
			BString sbAddress;
			message->FindString(K_SB_ADDRESS,&sbAddress);
			//CHECK IF MORE THAN ONE SB_LOOPERS ARE NECESSARY!!!!
			if (sbLoopers[sbAddress] == NULL)
			{
				//connection to sbLooper doesn't exist yet
				int32 sbPort;
				message->FindInt32(K_SB_PORT,&sbPort);
			
				BString authString;
				message->FindString(K_AUTHENTICATION_STRING,&authString);
			
				SBLooper *sbLooper = new SBLooper(this,sbAddress,sbPort,authString);			
				sbLoopers[sbAddress] = sbLooper;
				sbLooper->Run();
			}
			else
			{
				//connection does exist, what to do here?
			}
		}
		break;
		default:
		{			
			ServerLooper::MessageReceived(message);
		}
		break;
	}
}

void NSLooper::init()
{
	m_currentTrID = 1;
}
