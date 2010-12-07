/*
 *  Protocol.cpp
 *  Bme
 *
 *  Created by Tim De Jong on 06-05-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#include "Protocol.h"
#include "User.h"
#include "MSNP12Protocol.h"

Protocol::Protocol()
{
}

Protocol::~Protocol()
{
}

Protocol* Protocol::GetBmeProtocol(std::string protocolVersion)
{
	if (protocolVersion == ProtocolConstants::K_PROTOCOL_VERSION)
	{
		//current MSNP12
		return new MSNP12Protocol();
	}
	return NULL;
}

User* Protocol::GetUser()
{
	return new User(this->GetUserProtocol());
}

ContactList* Protocol::GetContactList()
{
	return new ContactList(this->GetContactListProtocol());
}

ConversationManager* Protocol::GetConversationManager()
{
	return new ConversationManager(this->GetConversationManagerProtocol());
}