/*
 *  Conversation.h
 *  Bme
 *
 *  Created by Tim De Jong on 19-02-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef CONVERSATION_H
#define CONVERSATION_H

#include "IConversationProtocolDelegate.h"

#include "ConversationItem.h"
#include "IUIConversationListener.h"
#include "Contact.h"

class IConversationProtocol;

class Conversation : public IConversationProtocolDelegate
{
public:
	Conversation(IConversationProtocol* conversationProtocol);
	virtual ~Conversation();
	
	void AddContact(Contact* contact);
	void AddConversationItem(ConversationItem* conversationItem);
		
	//UIListeners
	void AddUIListener(IUIConversationListener* uiConversationListener);
	bool RemoveUIListener(IUIConversationListener* uiConversationListener);

private:
	IConversationProtocol* m_conversationProtocol;
};

#endif