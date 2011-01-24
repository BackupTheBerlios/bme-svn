/*
 *  MSNP12ConversationManagerProtocol.cpp
 *  BmeApp
 *
 *  Created by Tim De Jong on 24-01-11.
 *  Copyright 2011 ThinkPractice. All rights reserved.
 *
 */

#include "MSNP12ConversationManagerProtocol.h"
#include "ProtocolConstants.h"

MSNP12ConversationManagerProtocol::MSNP12ConversationManagerProtocol()
									:	IConversationManagerProtocol()
{
}

MSNP12ConversationManagerProtocol::~MSNP12ConversationManagerProtocol()
{
}

void MSNP12ConversationManagerProtocol::StartConversation(Contact* contact)
{
	//add the contact to a queue which is used when the switchboard connection becomes available
	m_contactsForConversations.push(contact);
	//request a connection to a switchboard server
	ProtocolMessage* startConversationMessage = new ProtocolMessage(NotificationMessages::K_REQUEST_SWITCHBOARD_SESSION);
	startConversationMessage->AddParam("SB");
	SendCommandMessageTrId(startConversationMessage);
}

void MSNP12ConversationManagerProtocol::EndConversation(Conversation* conversation)
{
}

bool MSNP12ConversationManagerProtocol::IsHandlerForMessage(ProtocolMessage* message)
{
	std::string command = message->CommandType();
	
	if (command == NotificationMessages::K_REQUEST_SWITCHBOARD_SESSION)
	{
		//check if this XFR command is a redirection for the notification server or a switchboard specific message
		std::string nsString = message->GetParam(0);
		if (nsString == "SB")
		{
			//we only handle messages for the switchboard server here
			return true;
		}
		else
		{
			return false;
		}
	}	
	
	return	(command == NotificationMessages::K_INVITED_FOR_SWITCHBOARD);			 
}

void MSNP12ConversationManagerProtocol::HandleMessage(ProtocolMessage* message)
{
	std::string command = message->CommandType();
	if (command == NotificationMessages::K_REQUEST_SWITCHBOARD_SESSION)
	{
		//check if this XFR command is a redirection for the notification server or a switchboard specific message
		std::string nsString = message->GetParam(0);
		if (nsString == "SB")
		{
			if (!m_contactsForConversations.empty())
			{
				//get the first contact in the queue to start a conversation with
				Contact* contact = m_contactsForConversations.front();
				m_contactsForConversations.pop();
				//retrieve switchboard server address, port
				
				//connect to the requested switchboard connection
			}
			else 
			{
				//unexpected error: more switchboard connections than waiting contacts
			}		
		}
	}
	else if (command == NotificationMessages::K_INVITED_FOR_SWITCHBOARD)
	{	
		//someone invited us for a conversation
	}	
}

void MSNP12ConversationManagerProtocol::SetConversationManagerProtocolDelegate(IConversationManagerProtocolDelegate* converationManagerProtocolDelegate)
{
	m_conversationManagerDelegate = converationManagerProtocolDelegate;
}

IConversationManagerProtocolDelegate* MSNP12ConversationManagerProtocol::Delegate()
{
	return m_conversationManagerDelegate;
}