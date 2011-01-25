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
#include "Conversation.h"

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
			//XFR 15 SB 207.46.108.37:1863 CKI 17262740.1050826919.32308\r\n
			if (!m_contactsForConversations.empty())
			{
				//get the first contact in the queue to start a conversation with
				Contact* contact = m_contactsForConversations.front();
				m_contactsForConversations.pop();
				//retrieve switchboard server address, port
				std::string address = message->GetParam(1);
				//split address in an ip-address and a port part
				size_t colonPos = address.find(":");
				if (colonPos != std::string::npos)
				{				
					std::string ipString = address.substr(0, colonPos - 1);
					std::string portString = address.substr(colonPos + 1, address.size() - colonPos);
					int32_t port = atoi(portString.c_str());
				
					//check the authentication type is CKI
					std::string cki = message->GetParam(2);
					if (cki == "CKI")
					{
						std::string authenticationString = message->GetParam(3);
						//connect to the requested switchboard connection
						
						//m_conversationManagerDelegate->UserConversationStarted(contact, IConversationProtocol* conversation);
					}
				}
			}
			else 
			{
				//unexpected error: more switchboard connections than waiting contacts
			}		
		}
	}
	else if (command == NotificationMessages::K_INVITED_FOR_SWITCHBOARD)
	{	
		//RNG 11752013 207.46.108.38:1863 CKI 849102291.520491113 example@passport.com Example%20Name\r\n
		std::string switchboardId = message->GetParam(0);
		//someone invited us for a conversation
		std::string invitedByPassport = message->GetParam(5);
		//m_conversationManagerDelegate->InvitedToConversation(invitedByPassport, IConversationProtocol* conversation)
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