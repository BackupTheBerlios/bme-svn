/*
 *  Contact.cpp
 *  Bme
 *
 *  Created by Tim De Jong on 19-02-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 *	All rights reserved.										  
 *	Distributed under the terms of the MIT License.               
 *****************************************************************/
#ifndef CONTACT_H
#include "Contact.h"
#endif

#include "ProtocolConstants.h"

Contact::Contact()
			:		KeyValueCollection(),
					m_hasPersonalMessage(false)
{
}

Contact::Contact(std::string passport, std::string friendlyName, std::string guid, int32_t partOfLists, Status *status)
			:	KeyValueCollection(),
				m_passport(passport),
				m_friendlyName(friendlyName),
				m_guid(guid),
				m_hasPersonalMessage(false),
				m_partOfLists(partOfLists),
				m_status(status)
{
}

Contact::~Contact()
{
}

void Contact::SetPassport(std::string passport)
{
	m_passport = passport;
}

std::string Contact::Passport()
{
	return m_passport;
}

void Contact::SetFriendlyName(std::string friendlyName)
{
	m_friendlyName = friendlyName;
}

std::string Contact::FriendlyName()
{
	return m_friendlyName;
}

void Contact::SetGUID(std::string guid)
{
	m_guid = guid;
}

std::string Contact::GUID()
{
	return m_guid;
}

void Contact::AddGroup(std::string groupId)
{
	m_groups.push_back(groupId);
}

bool Contact::RemoveGroup(std::string groupId)
{
	typedef std::vector<std::string>::iterator I;
	for (I p = m_groups.begin(); p != m_groups.end(); ++p) 
	{
		if (*p == groupId)
		{
			m_groups.erase(p);
			return true;
		}
	}
	return false;
}

std::vector<std::string> Contact::Groups()
{
	return m_groups;
}

void Contact::SetPartOfLists(int32_t partOfLists)
{
	m_partOfLists = partOfLists;
}

int32_t Contact::PartOfLists()
{
	return m_partOfLists;
}

void Contact::SetStatus(Status *status)
{
	m_status = status;
}

Status* Contact::GetStatus()
{
	return m_status;
}

bool Contact::IsOnForwardList()
{
	//find out if this contact is part of the forward list
	return ((m_partOfLists & ContactListTypes::K_FORWARD_LIST) == 1);
}

bool Contact::IsOnReverseList()
{
	//find out if this contact has you on their forward list
	return ((m_partOfLists & ContactListTypes::K_REVERSE_LIST) == 1);
}

bool Contact::IsOnAllowList()
{
	//find out if this contact has you on their allow list
	return ((m_partOfLists & ContactListTypes::K_ALLOW_LIST) == 1);
}

bool Contact::IsBlocked()
{
	//find out if this contact is part of the blocked list
	return ((m_partOfLists & ContactListTypes::K_BLOCK_LIST) == 1);
}

bool Contact::IsOnline()
{
	return (m_status->GetAbbreviation() != Statusses::K_OFFLINE);
}

bool Contact::HasPersonalMessage()
{	
	return m_hasPersonalMessage;
}

void Contact::SetPersonalMessage(std::string personalMessage)
{
	m_hasPersonalMessage = true;
	m_personalMessage = personalMessage;
}

std::string Contact::PersonalMessage()
{
	return m_personalMessage;
}

void Contact::AddPhoneNumber(PhoneNumberType phoneNumberType, std::string number)
{
	m_phoneNumbers[phoneNumberType] = number;
}

std::map<PhoneNumberType, std::string> Contact::PhoneNumbers()
{
	return m_phoneNumbers;
}

std::string Contact::GetPhoneNumber(PhoneNumberType numberType)
{
	return m_phoneNumbers[numberType];
}

void Contact::SetHasBlog(bool hasBlog)
{
	m_hasBlog = hasBlog;
}

bool Contact::HasBlog()
{
	return m_hasBlog;
}

void Contact::SetCanBePaged(bool canBePaged)
{
	m_canBePaged = canBePaged;
}

bool Contact::CanBePaged()
{
	return m_canBePaged;
}

void Contact::SetMsnDirectCapable(bool msnDirectCapable)
{
	m_msnDirectCapable = msnDirectCapable;
}

bool Contact::MsnDirectCapable()
{
	return m_msnDirectCapable;
}
