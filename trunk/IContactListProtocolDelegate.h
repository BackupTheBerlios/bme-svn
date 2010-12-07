/*
 *  IContactListProtocolDelegate.h
 *  Bme
 *
 *  Created by Tim De Jong on 05-05-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef I_CONTACT_LIST_PROTOCOL_DELEGATE_H
#define I_CONTACT_LIST_PROTOCOL_DELEGATE_H

#include "Contact.h"
#include "Status.h"

class IContactListProtocolDelegate
{
public:
	typedef enum DefaultContactListType
	{
		K_ALLOW_LIST = 0,
		K_BLOCK_LIST
	}
	DefaultContactListType;
	
public:
	IContactListProtocolDelegate() {};
	virtual ~IContactListProtocolDelegate() {};
	
	virtual void SyncListStarted() = 0;
	virtual void SyncListEnded() = 0;
	virtual void SetInformUserUponListChange(bool informUser) = 0;
	virtual void SetDefaultContactList(DefaultContactListType contactListType) = 0;
	
	virtual void ContactFound(Contact* contact) = 0;
	virtual void GroupFound(std::string groupId, std::string groupName) = 0;
	virtual void ContactStatusChanged(std::string passport, Status* status) = 0;
	virtual void ContactPersonalMessageFound(std::string message) = 0;
	
	virtual void ContactPhoneNumberFound(PhoneNumberType phoneType, std::string phoneNumber) = 0;
	virtual void ContactBlogSettingFound(bool hasBlog) = 0;
	virtual void ContactCanPageSettingFound(bool canBePaged) = 0;
	virtual void ContactMSNDirectCapableSettingFound(bool msnDirectCapable) = 0;
		
	
};

#endif
