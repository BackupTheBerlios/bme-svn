/*
 *  MSNP12Protocol.cpp
 *  Bme
 *
 *  Created by Tim De Jong on 17-06-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */

#include "MSNP12Protocol.h"
#include "ProtocolConstants.h"
#include "ProtocolMessage.h"
#include "PlatformSpecific.h"
#include "MSNP12PingHandler.h"
#include "MSNP12ConversationManagerProtocol.h"

MSNP12Protocol::MSNP12Protocol()
					:	Protocol(),
						m_isAuthenticating(false)
{
	m_userProtocol = new MSNP12UserProtocol();
	m_contactListProtocol = new MSNP12ContactListProtocol();
	m_conversationManagerProtocol = new MSNP12ConversationManagerProtocol();
	m_connection = new NSServerConnection(PlatformSpecific::GetConnectionManager());
	m_connection->AddServerConnectionListener(this);
}

MSNP12Protocol::~MSNP12Protocol()
{
	delete m_connection;
}

std::string MSNP12Protocol::Version()
{
	return "MSPN12";
}

void MSNP12Protocol::Login(std::string username, std::string password)
{
	//set the username and password for the user
	m_userProtocol->SetLoginDetails(username, password);
	m_userProtocol->SetProtocolDelegate(this);
	m_contactListProtocol->SetProtocolDelegate(this);
}

void MSNP12Protocol::DidConnect()
{
	//start the login sequence
	bool successful = false;	
	if (m_connection->GetConnection()->IsConnected() && !m_isAuthenticating)
	{
		//add the protocolhandles to the NSServerConnection
		m_connection->AddMessageHandler(m_userProtocol);		
		ProtocolMessage* message = new ProtocolMessage(NotificationMessages::K_PROTOCOLS_SUPPORTED);
		message->SetTrId(ProtocolMessage::CurrentTrId());
		message->AddParam(ProtocolConstants::K_PROTOCOL_VERSION);				
		message->AddParam("CVR0");
		m_connection->SendCommandMessage(message);
		successful = true;
		//sometimes the didconnect is called twice? this prevents from sending the authentication message twice
		m_isAuthenticating = true;
	}	
}

IUserProtocol* MSNP12Protocol::GetUserProtocol()
{
	return m_userProtocol;
}

IContactListProtocol* MSNP12Protocol::GetContactListProtocol()
{
	return m_contactListProtocol;
}

IConversationManagerProtocol* MSNP12Protocol::GetConversationManagerProtocol()
{
	return m_conversationManagerProtocol;
}

void MSNP12Protocol::AuthenticationCompleted()
{
	//add PingHandler to NSServerConnection
	m_connection->AddMessageHandler(new MSNP12PingHandler());	
		
	//synchronise lists, need some info here???
	m_connection->AddMessageHandler(m_contactListProtocol);
	m_contactListProtocol->SyncList();
	
	m_userProtocol->SendInitialPresence();
	
	m_isAuthenticating = false;
	//call delegate here, to show that user logged in, show in interface!
	//m_userProtocolDelegate->LoggedInWithStatus(m_initialStatus);
}

void MSNP12Protocol::SyncListEnded()
{
//	m_userProtocol->SendInitialPresence();
}
