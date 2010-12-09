/*
 *  MSNP12AuthenticationProtocol.h
 *  Bme
 *
 *  Created by Tim De Jong on 23-06-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef MSNP12_AUTHENTICATION_PROTOCOL_H
#define MSNP12_AUTHENTICATION_PROTOCOL_H

#include "ProtocolHandler.h"
#include "IUserProtocol.h"
#include "Status.h"
#include "HTTPFormatter.h"

class MSNP12UserProtocol : public ProtocolHandler, public IUserProtocol
{
public:
	MSNP12UserProtocol();
	MSNP12UserProtocol(std::string username, std::string password);
	virtual ~MSNP12UserProtocol();
	
	virtual bool IsHandlerForMessage(ProtocolMessage* message);
	virtual void HandleMessage(ProtocolMessage* message);
	virtual void StartLogin(std::string username, std::string password);
	virtual void Logout();
	virtual void SetLoginDetails(std::string username, std::string password);
	virtual void SendInitialPresence();
	
public:
	virtual void SetInitialStatus(Status* status);
	virtual void SetStatus(Status* status);
	virtual void SetDisplayName(std::string displayName);
	virtual void SetPersonalMessage(std::string personalMessage);
	virtual void SetMusicPlaying(std::string musicPlaying);
	virtual void AddPhoneNumber(PhoneNumberType phoneType, std::string phoneNumber);
	
public:
	virtual void SetUserProtocolDelegate(IUserProtocolDelegate* userProtocolDelegate);
	virtual IUserProtocolDelegate* Delegate();	
	
private:
	std::string	TweenerAuthenticate(std::string challenge);
	bool		SSLSend(std::string host, HTTPFormatter *send, HTTPFormatter **recv);
	
private:
	std::string	m_username,
				m_password
				;
	Status*		m_initialStatus
				;	
	IUserProtocolDelegate* m_userProtocolDelegate;
};

#endif