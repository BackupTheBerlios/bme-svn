/*
 *  User.h
 *  Bme
 *
 *  Created by Tim De Jong on 19-02-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef USER_H
#define USER_H

#include <string.h>
#include <map>
#include "IUserProtocolDelegate.h"
#include "IUserProtocol.h"
#include "IUIUserListener.h"
#include "UIEventProvider.h"
#include "Status.h"

class User : public IUserProtocolDelegate, public UIEventProvider
{
public:
	User(IUserProtocol* userProtocol);
	virtual ~User();
	
	virtual std::string Name();
	virtual void SetName(std::string username);
	
	virtual std::map<PhoneNumberType, std::string> PhoneNumbers();
	virtual std::string GetPhoneNumber(PhoneNumberType numberType);
	
	virtual bool HasBlog();
	virtual bool CanBePaged();
	virtual bool MsnDirectCapable();
	virtual bool HasMobileDeviceEnabled();
		
public:
	virtual void LoggedInWithStatus(Status* status);
	
	virtual void UsernameFound(std::string username);
	virtual void PhoneNumberFound(PhoneNumberType phoneType, std::string phoneNumber);
	virtual void BlogSettingFound(bool hasBlog);
	virtual void CanPageSettingFound(bool canBePaged);
	virtual void MSNDirectCapableSettingFound(bool msnDirectCapable);
	virtual void HasMobileDeviceEnabledSettingFound(bool mobileEnabled);
	
private:
	IUserProtocol*	m_userProtocol;
	Status*			m_userStatus;
	
	std::string		m_passport,
					m_username
					;
	
	bool			m_hasBlog,
					m_canBePaged,
					m_msnDirectCapable,
					m_mobileEnabled
					;
	
	std::map<PhoneNumberType, std::string> m_phoneNumbers;
};

#endif