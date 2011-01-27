/*
 *  ConversationManager.cpp
 *  Bme
 *
 *  Created by Tim De Jong on 06-05-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */

#include "ConversationManager.h"
#include "IConversationProtocol.h"

ConversationManager::ConversationManager(User* user, IConversationManagerProtocol *conversationProtocol)
						:	IConversationManagerProtocolDelegate(),
							m_user(user),
							m_conversationManagerProtocol(conversationProtocol)
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

void ConversationManager::SetUser(User* user)
{
	m_user = user;
}

std::vector<Conversation*> ConversationManager::ActiveConversations()
{
	return m_conversations;
}

void ConversationManager::UserConversationStarted(Contact* withContact, IConversationProtocol* conversationProtocol)
{
	Conversation* conversation = new Conversation(conversationProtocol);
	m_conversations.push_back(conversation);
	conversationProtocol->StartSession(m_user->Passport());
	//inform UI
}

void ConversationManager::InvitedToConversation(std::string invitedByPassport, IConversationProtocol* conversationProtocol)
{
	Conversation* conversation = new Conversation(conversationProtocol);
	m_conversations.push_back(conversation);
	conversationProtocol->AnswerInvitation(m_user->Passport());
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