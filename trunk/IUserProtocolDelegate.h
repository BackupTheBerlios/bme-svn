/*
 *  IUserProtocolDelegate.h
 *  Bme
 *
 *  Created by Tim De Jong on 05-05-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef I_USER_PROTOCOL_DELEGATE_H
#define I_USER_PROTOCOL_DELEGATE_H

#include "Status.h"

class IUserProtocolDelegate
{
public:
	IUserProtocolDelegate() {};
	virtual ~IUserProtocolDelegate() {};
	
	virtual void LoggedInWithStatus(Status* status) = 0;
	
	virtual void UsernameFound(std::string username) = 0;
	virtual void PhoneNumberFound(PhoneNumberType phoneType, std::string phoneNumber) = 0;
	virtual void BlogSettingFound(bool hasBlog) = 0;
	virtual void CanPageSettingFound(bool canBePaged) = 0;
	virtual void MSNDirectCapableSettingFound(bool msnDirectCapable) = 0;
	virtual void HasMobileDeviceEnabledSettingFound(bool mobileEnabled) = 0;
};

#endif
