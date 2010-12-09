/*
 *  BmeClient.h
 *  Bme
 *
 *  Created by Tim De Jong on 04-05-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef BME_CLIENT_H
#define BME_CLIENT_H

#include <string>
#include "User.h"
#include "Protocol.h"
#include "ContactList.h"
#include "ConversationManager.h"
#include "Conversation.h"
#include "Preferences.h"

/** Main Entrypoint for all graphical clients
 */
class BmeClient
{
private:
	static Preferences* s_preferences;

public:
	static Preferences* GetPreferences();

private:	
	BmeClient(Protocol* protocol);
	
public:
	virtual ~BmeClient();
	//singleton method
	static BmeClient* ConnectWithUserDetails(std::string username, std::string password, std::string protocolVersion);//IUIBmeClientListener?

public:	
	User* GetUser();
	ContactList* GetContactList();
	ConversationManager* GetConversationManager();
	
	//client prefs?
	
private:
	Protocol* m_protocol;
	User* m_user;
	ContactList* m_contactList;
	ConversationManager* m_conversationManager;
};

#endif
