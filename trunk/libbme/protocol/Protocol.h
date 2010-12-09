/*
 *  Protocol.h
 *  Bme
 *
 *  Created by Tim De Jong on 04-05-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>
#include "ProtocolConstants.h"
#include "User.h"
#include "ContactList.h"
#include "ConversationManager.h"
#include "IUserProtocol.h"
#include "IContactListProtocol.h"
#include "IConversationManagerProtocol.h"

class Protocol
{
public:	
	static Protocol* GetBmeProtocol(std::string protocolVersion);

public:
	Protocol();
	virtual ~Protocol();
	
	virtual std::string Version() = 0;
	virtual void Login(std::string passport, std::string password) = 0;
		
	virtual User* GetUser();
	virtual ContactList* GetContactList();
	virtual ConversationManager* GetConversationManager();	
	
protected:
	//the classes to interact with the different parts of the protocol
	virtual IUserProtocol* GetUserProtocol() = 0;
	virtual IContactListProtocol* GetContactListProtocol() = 0;//a ProtocolHandler of some kind...
	virtual IConversationManagerProtocol* GetConversationManagerProtocol() = 0;
};

#endif
