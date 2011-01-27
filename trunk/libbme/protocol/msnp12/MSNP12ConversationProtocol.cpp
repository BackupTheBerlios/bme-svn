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
	m_sbServerConnection->Close();
}

void MSNP12ConversationProtocol::StartSession(std::string userPassport)
{
	ProtocolMessage* startSessionMessage = new ProtocolMessage(SwitchboardMessages::K_SB_USR_COMMAND);
	startSessionMessage->AddParam(userPassport);
	startSessionMessage->AddParam(this->AuthenticationString());
	
	SendCommandMessageTrId(startSessionMessage);
}

void MSNP12ConversationProtocol::EndSession()
{
	//Inform the switchboard server that the user wants to leave the session
	//the switchboard server will close the connection upon receiving this message
	ProtocolMessage* endSessionMessage = new ProtocolMessage(SwitchboardMessages::K_LEAVE_SB_SESSION);
	SendCommandMessage(endSessionMessage);	
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

bool MSNP12ConversationProtocol::IsHandlerForMessage(ProtocolMessage* message)
{
	std::string command = message->CommandType();
	return (command == SwitchboardMessages::K_SB_USR_COMMAND ||
			command == SwitchboardMessages::K_ANSWER_SB_SESSION	||
			command == SwitchboardMessages::K_PRINCIPALS_IN_SESSION	||	
			command == SwitchboardMessages::K_INVITE_PRINCIPAL ||	
			command == SwitchboardMessages::K_PRINCIPAL_JOINED ||			
			command == SwitchboardMessages::K_PRINCIPAL_LEFT ||						
			command == SwitchboardMessages::K_SWITCHBOARD_MESSAGE
			);
}

void MSNP12ConversationProtocol::HandleMessage(ProtocolMessage* message)
{
	std::string command = message->CommandType();
	if (command == SwitchboardMessages::K_SB_USR_COMMAND)
	{
		this->HandleUSRMessage(message);
	}
	else if (command == SwitchboardMessages::K_ANSWER_SB_SESSION)
	{
		this->HandleANSMessage(message);
	}
	else if (command == SwitchboardMessages::K_PRINCIPALS_IN_SESSION)
	{
		this->HandleIROMessage(message);
	}
	else if (command == SwitchboardMessages::K_INVITE_PRINCIPAL)
	{
		this->HandleCALMessage(message);
	}
	else if (command == SwitchboardMessages::K_PRINCIPAL_JOINED)
	{
		this->HandleJOIMessage(message);
	}
	else if (command == SwitchboardMessages::K_PRINCIPAL_LEFT)
	{
		this->HandleBYEMessage(message);
	}
	else if (command == SwitchboardMessages::K_SWITCHBOARD_MESSAGE)
	{
		this->HandleMSGMessage(message);
	}	
}

void MSNP12ConversationProtocol::HandleUSRMessage(ProtocolMessage* message)
{
	std::string okMessage = message->GetParam(0);
	if (okMessage == "OK")
	{
		this->Delegate()->ConversationStarted();
	}
}

void MSNP12ConversationProtocol::HandleANSMessage(ProtocolMessage* message)
{
	std::string okMessage = message->GetParam(0);
	if (okMessage == "OK")
	{
		this->Delegate()->JoinedExistingConversation();
	}
}

void MSNP12ConversationProtocol::HandleIROMessage(ProtocolMessage* message)
{
	uint32_t participantNumber = atoi(message->GetParam(0).c_str());
	uint32_t totalNumberOfParticipants = atoi(message->GetParam(1).c_str());
	std::string participantPassport = message->GetParam(2);
	this->Delegate()->ContactAlreadyInConversation(participantNumber, totalNumberOfParticipants, participantPassport);	
}

void MSNP12ConversationProtocol::HandleCALMessage(ProtocolMessage* message)
{
}

void MSNP12ConversationProtocol::HandleJOIMessage(ProtocolMessage* message)
{
	std::string participantPassport = message->GetParam(0);
	this->Delegate()->ContactJoinedConversation(participantPassport);
}

void MSNP12ConversationProtocol::HandleBYEMessage(ProtocolMessage* message)
{
	//Two types of BYE message are available
	//BYE example@passport.com\r\n -> participant chose to close the session
	//BYE example@passport.com 1\r\n -> closed due to idleness
	
	std::string participantPassport = message->GetParam(0);
	if (message->ParamCount() > 1)
	{
		this->Delegate()->IdleConversationClosed();
	}
	else 
	{
		this->Delegate()->ContactLeftConversation(participantPassport);
	}
}

void MSNP12ConversationProtocol::HandleMSGMessage(ProtocolMessage* message)
{
}


