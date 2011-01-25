/*
 *  ConversationManager.h
 *  Bme
 *
 *  Created by Tim De Jong on 06-05-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef CONVERSATION_MANAGER_H
#define CONVERSATION_MANAGER_H

#include <vector>
#include "Contact.h"
#include "Conversation.h"
#include "IConversationManagerProtocol.h"
#include "IConversationManagerProtocolDelegate.h"

class ConversationManager : public IConversationManagerProtocolDelegate
{
public:
	ConversationManager(IConversationManagerProtocol *conversationProtocol);
	virtual ~ConversationManager();
	
	void StartConversation(Contact* contact);
	void EndConversation(Conversation* conversation);
	
	std::vector<Conversation*> ActiveConversations();
	//IConversationManagerProtocolDelegate methods
	void UserConversationStarted(Contact* withContact, IConversationProtocol* conversationProtocol);
	void InvitedToConversation(std::string invitedByPassport, IConversationProtocol* conversationProtocol);
	void ConversationEnded(Conversation* conversation);
	
private:
	IConversationManagerProtocol* m_conversationManagerProtocol;
	std::vector<Conversation*> m_conversations;
};

#endif