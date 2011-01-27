/*
 *  IConversationProtocolDelegate.h
 *  Bme
 *
 *  Created by Tim De Jong on 05-05-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef I_CONVERSATION_PROTOCOL_H
#define I_CONVERSATION_PROTOCOL_H

#include <string>
#include <stdint.h>

class IConversationProtocolDelegate
{
public:
	IConversationProtocolDelegate() {};
	virtual ~IConversationProtocolDelegate() {};
	
	virtual void ConversationStarted() = 0;
	virtual void ContactJoinedConversation(std::string participantPassport) = 0;
	
	virtual void RingingContact(std::string contactPassport) = 0;
	virtual void ContactLeftConversation(std::string participantPassport) = 0;
	virtual void IdleConversationClosed() = 0;
	
	virtual void JoinedExistingConversation() = 0;
	virtual void ContactAlreadyInConversation(uint32_t participantNumber, uint32_t totalNumberOfParticipants, std::string participantPassport) = 0;
};

#endif
