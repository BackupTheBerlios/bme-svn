/*
 *  Conversation.cpp
 *  Bme
 *
 *  Created by Tim De Jong on 19-02-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */

#include "Conversation.h"
#include "IConversationProtocol.h"

Conversation::Conversation(IConversationProtocol* conversationProtocol)
					:	m_conversationProtocol(conversationProtocol)

{
	m_conversationProtocol->SetConversationProtocolDelegate(this);
}

Conversation::~Conversation()
{
	delete m_conversationProtocol;
	//delete all the conversation items for this Conversation
	typedef std::vector<ConversationItem*>::iterator CI;
	for (CI c = m_conversationItems.begin(); c != m_conversationItems.end(); ++c)
	{
		ConversationItem* convItem = *c;
		delete convItem;
	}
}

void Conversation::Close()
{
	m_conversationProtocol->EndSession();
}

void Conversation::AddContact(Contact* contact)
{
	m_conversationProtocol->InviteContactToSession(contact->Passport());
}

void Conversation::AddConversationItem(ConversationItem* conversationItem)
{
	//add the conversation item (message) to this conversation
	m_conversationItems.push_back(conversationItem);
	//send the conversation item to the server
	//m_conversationProtocol->
}

//IConversationProtocolDelegate methods
void Conversation::ConversationStarted()
{
}

void Conversation::ContactJoinedConversation(std::string participantPassport)
{
}

void Conversation::RingingContact(std::string contactPassport)
{
}

void Conversation::ContactLeftConversation(std::string participantPassport)
{
}

void Conversation::IdleConversationClosed()
{
}

void Conversation::JoinedExistingConversation()
{
}

void Conversation::ContactAlreadyInConversation(uint32_t participantNumber, uint32_t totalNumberOfParticipants, std::string participantPassport)
{
}
