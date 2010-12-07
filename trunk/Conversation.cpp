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