/*
 *  ConversationManager.cpp
 *  Bme
 *
 *  Created by Tim De Jong on 06-05-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */

#include "ConversationManager.h"

ConversationManager::ConversationManager(IConversationManagerProtocol *conversationProtocol)
						:	m_conversationManagerProtocol(conversationProtocol)
{	
	m_conversationManagerProtocol->SetConversationManagerProtocolDelegate(this);
}

ConversationManager::~ConversationManager()
{
}

void ConversationManager::StartConversation(Contact* contact)
{
	m_conversationManagerProtocol->StartConversation(contact);
}

void ConversationManager::EndConversation(Conversation* conversation)
{
	m_conversationManagerProtocol->EndConversation(conversation);
}

std::vector<Conversation*> ConversationManager::ActiveConversations()
{
	return m_conversations;
}

void ConversationManager::ConversationStarted(Conversation* conversation, bool startedByUser)
{
	m_conversations.push_back(conversation);
	//inform UI
}

void ConversationManager::ConversationEnded(Conversation* conversation)
{
	//TODO: check if this works!
	typedef std::vector<Conversation*>::iterator CI;
	//loop through the available conversations and remove the one that has ended
	for (CI c = m_conversations.begin(); c != m_conversations.end(); ++c)
	{
		if (*c == conversation)
		{
			m_conversations.erase(c);
			delete conversation;
		}
	}
	//inform UI
}