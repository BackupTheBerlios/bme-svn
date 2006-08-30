/*****************************************************************
 * Copyright (c) 2005 Tim de Jong								 *
 *							       								 *
 * All rights reserved.											 *
 * Distributed under the terms of the MIT License.               *
 *****************************************************************/
#ifndef PROTOCOL_LOOPER_H
#include "ProtocolLooper.h"
#endif

#include <be/storage/Path.h>
#include <be/storage/Directory.h>
#include <be/storage/Entry.h>
#include <be/storage/File.h>
#include <be/storage/FindDirectory.h>
#include <iostream>
#include "constants.h"
#include "ProtocolConstants.h"
#include "UIHandler.h"
#include "MainWindowUIFilter.h"
#include "ProtocolHandler.h"

#include "ChatWindow.h"

/**	Constructor
 */
ProtocolLooper::ProtocolLooper()
					:	BLooper(),
						m_nsLooper(new NSLooper(this))
{	
	m_nsLooper->Run();
	//add handlers for different kind of messages
	AddHandler(new ProtocolHandler(m_nsLooper));	
	
	BRect chatFrame(100.0f,100.0f,400.0f,500.0f);
	ChatWindow *chatWindow = new ChatWindow(chatFrame, "Chatting with");
	chatWindow->Show();
}

/**	Destructor
 */
ProtocolLooper::~ProtocolLooper()
{	
	//quit nsLooper
	//m_nsLooper->Lock();
	//m_nsLooper->Quit();	
}

void ProtocolLooper::MessageReceived(BMessage *message)
{
	int32 noHandlers = CountHandlers();
	if (noHandlers > 1)
	{
		//make sure the message won't be send to the looper main handler again!
		for (int32 i = 1; i < noHandlers; i++)
		{
			BHandler *handler = HandlerAt(i);
			BMessenger msgr(handler);
			msgr.SendMessage(message);
		}
	}
}

//FIX THIS: so that setOwner can be called multiple times without faulty behaviour
void ProtocolLooper::setOwner(BLooper *owner)
{
cout << "setOwner Only call this method once!!!" << endl;	
	m_owner = owner;
	if (Lock())
	{
		UIHandler *mainWindowUIHandler = new UIHandler(m_owner);
		mainWindowUIHandler->AddFilter(new MainWindowUIFilter());
		AddHandler(mainWindowUIHandler);
		Unlock();
	}
}

BLooper* ProtocolLooper::getOwner()
{
	return m_owner;
}

bool ProtocolLooper::QuitRequested()
{
	cout << "ProtocolLooper::QuitRequested()" << endl;
	
	return BLooper::QuitRequested();
}
