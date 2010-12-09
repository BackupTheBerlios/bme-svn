/*
 *  User.cpp
 *  Bme
 *
 *  Created by Tim De Jong on 19-02-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */

#include "User.h"
#include "IUserProtocol.h"

User::User(IUserProtocol* userProtocol)
		:	IUserProtocolDelegate(),
			UIEventProvider(),
			m_userProtocol(userProtocol)
{
	m_userProtocol->SetUserProtocolDelegate(this);
}

User::~User()
{
	delete m_userProtocol;
}

std::string User::Name()
{
	return m_username;
}

void User::SetName(std::string username)
{
	m_userProtocol->SetDisplayName(username);
}

std::map<PhoneNumberType, std::string> User::PhoneNumbers()
{
	return m_phoneNumbers;
}

std::string User::GetPhoneNumber(PhoneNumberType numberType)
{
	return m_phoneNumbers[numberType];
}

bool User::HasBlog()
{
	return m_hasBlog;
}

bool User::CanBePaged()
{
	return m_canBePaged;	
}

bool User::MsnDirectCapable()
{
	return m_msnDirectCapable;
}

bool User::HasMobileDeviceEnabled()
{
	return m_mobileEnabled;
}

void User::LoggedInWithStatus(Status* status)
{
	//setting the status for the user
	m_userStatus = status;
	//TODO: update send to UI?
}

void User::UsernameFound(std::string username)
{
	m_username = username;
	//inform all listeners about the user name being found
	std::vector<IUIListener*> m_uiUserListeners = this->GetAllListeners();
	for (UI ul = m_uiUserListeners.begin(); ul != m_uiUserListeners.end(); ++ul)
	{
		IUIUserListener* listener = (IUIUserListener*)*ul;
		listener->UsernameFound(username);
	}
}

void User::PhoneNumberFound(PhoneNumberType phoneType, std::string phoneNumber)
{
	m_phoneNumbers[phoneType] = phoneNumber;
}

void User::BlogSettingFound(bool hasBlog)
{
	m_hasBlog = hasBlog;
}

void User::CanPageSettingFound(bool canBePaged)
{
	m_canBePaged = canBePaged;
}

void User::MSNDirectCapableSettingFound(bool msnDirectCapable)
{
	m_msnDirectCapable = msnDirectCapable;
}

void User::HasMobileDeviceEnabledSettingFound(bool mobileEnabled)
{
	m_mobileEnabled = mobileEnabled;
}
