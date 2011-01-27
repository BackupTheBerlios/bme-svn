/*
 *  BmeClient.cpp
 *  Bme
 *
 *  Created by Tim De Jong on 04-05-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */

#include "BmeClient.h"

Preferences* BmeClient::s_preferences = NULL;

Preferences* BmeClient::GetPreferences()
{
	if (!s_preferences)
	{
		s_preferences = new Preferences();
	}
	return s_preferences;
}

BmeClient::BmeClient(Protocol* protocol)
			:	m_protocol(protocol)
{
	m_user = m_protocol->GetUser();
	m_contactList = m_protocol->GetContactList();
	m_conversationManager = m_protocol->GetConversationManager(m_user);
}

BmeClient::~BmeClient()
{
	delete m_protocol;
	delete m_user;
	delete m_contactList;
	delete m_conversationManager;
}

BmeClient* BmeClient::ConnectWithUserDetails(std::string username, std::string password, std::string protocolVersion)
{
	Protocol* bmeProtocol = Protocol::GetBmeProtocol(protocolVersion);
	bmeProtocol->Login(username, password);
	return new BmeClient(bmeProtocol);
}

User* BmeClient::GetUser()
{
	return m_user;
}

ContactList* BmeClient::GetContactList()
{
	return m_contactList;
}

ConversationManager* BmeClient::GetConversationManager()
{
	return m_conversationManager;
}