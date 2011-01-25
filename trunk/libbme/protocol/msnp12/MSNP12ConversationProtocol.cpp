/*
 *  MSNP12ConversationProtocol.cpp
 *  BmeApp
 *
 *  Created by Tim De Jong on 25-01-11.
 *  Copyright 2011 ThinkPractice. All rights reserved.
 *
 */

#include "MSNP12ConversationProtocol.h"
#include "ProtocolConstants.h"

MSNP12ConversationProtocol::MSNP12ConversationProtocol(SBServerConnection* sbServerConnection)
								:	IConversationProtocol(),
									m_sbServerConnection(sbServerConnection)
{
	//make this class a protocol handler for the messages received on the switchboard session
	m_sbServerConnection->AddMessageHandler(this);
}

MSNP12ConversationProtocol::~MSNP12ConversationProtocol()
{
	m_sbServerConnection->Close();//TODO: move somewhere else?
}

bool MSNP12ConversationProtocol::IsHandlerForMessage(ProtocolMessage* message)
{
	return false;
}

void MSNP12ConversationProtocol::HandleMessage(ProtocolMessage* message)
{
}

void MSNP12ConversationProtocol::StartSession(std::string userPassport)
{
	ProtocolMessage* startSessionMessage = new ProtocolMessage(SwitchboardMessages::K_SB_USR_COMMAND);
	startSessionMessage->AddParam(userPassport);
	startSessionMessage->AddParam(this->AuthenticationString());
	
	SendCommandMessageTrId(startSessionMessage);
}

void MSNP12ConversationProtocol::AnswerInvitation(std::string userPassport)
{
	ProtocolMessage* answerInvitationMessage = new ProtocolMessage(SwitchboardMessages::K_ANSWER_SB_SESSION);
	answerInvitationMessage->AddParam(userPassport);
	answerInvitationMessage->AddParam(this->AuthenticationString());
	answerInvitationMessage->AddParam(this->SwitchBoardId());
	
	SendCommandMessageTrId(answerInvitationMessage);
}

void MSNP12ConversationProtocol::SetAuthenticationString(std::string authenticationString)
{
	m_authenticationString = authenticationString;
}

std::string MSNP12ConversationProtocol::AuthenticationString()
{
	return m_authenticationString;
}

void MSNP12ConversationProtocol::SetSwitchBoardId(std::string switchBoardId)
{
	m_switchBoardId = switchBoardId;
}

std::string MSNP12ConversationProtocol::SwitchBoardId()
{
	return m_switchBoardId;
}

void MSNP12ConversationProtocol::SetConversationProtocolDelegate(IConversationProtocolDelegate* conversationProtocolDelegate)
{
	m_conversationProtocolDelegate = conversationProtocolDelegate;
}

IConversationProtocolDelegate* MSNP12ConversationProtocol::Delegate()
{
	return m_conversationProtocolDelegate;
}