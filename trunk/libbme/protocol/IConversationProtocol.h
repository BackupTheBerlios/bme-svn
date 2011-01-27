/*
 *  IConversationProtocol.h
 *  Bme
 *
 *  Created by Tim De Jong on 05-05-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef I_CONTACT_LIST_PROTOCOL_H
#define I_CONTACT_LIST_PROTOCOL_H

//#include "IConversationProtocolDelegate.h"

class IConversationProtocolDelegate;

class IConversationProtocol
{
public:
	IConversationProtocol() {};
	virtual ~IConversationProtocol() {};
	
	virtual void StartSession(std::string userPassport) = 0;
	virtual void EndSession() = 0;
	virtual void AnswerInvitation(std::string userPassport) = 0;
	virtual void InviteContactToSession(std::string contactPassport) = 0;
	
	virtual void SetConversationProtocolDelegate(IConversationProtocolDelegate* conversationProtocolDelegate) = 0;
	virtual IConversationProtocolDelegate* Delegate() = 0;
};

#endif

