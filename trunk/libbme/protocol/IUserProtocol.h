/*
 *  IUserProtocol.h
 *  Bme
 *
 *  Created by Tim De Jong on 05-05-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef I_USER_PROTOCOL_H
#define I_USER_PROTOCOL_H

#include <string>

#include "IUserProtocolDelegate.h"
#include "Status.h"

class IUserProtocol
{
public:
	IUserProtocol() {};
	virtual ~IUserProtocol() {};
	
	virtual void SetInitialStatus(Status* status) = 0;
	virtual void SetStatus(Status* status) = 0;
	virtual void SetDisplayName(std::string displayName) = 0;
	virtual void SetPersonalMessage(std::string personalMessage) = 0;
	virtual void SetMusicPlaying(std::string musicPlaying) = 0;
	
	virtual void AddPhoneNumber(PhoneNumberType phoneType, std::string phoneNumber) = 0;
	
public:
	virtual void SetUserProtocolDelegate(IUserProtocolDelegate* userProtocolDelegate) = 0;
	virtual IUserProtocolDelegate* Delegate() = 0;
};

#endif
