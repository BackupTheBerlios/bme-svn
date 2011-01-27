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
