/*
 *  ContactList.h
 *  Bme
 *
 *  Created by Tim De Jong on 19-02-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef CONTACT_LIST_H
#define CONTACT_LIST_H

#include <map>
#include <vector>
#include "Contact.h"
#include "IContactListProtocolDelegate.h"
#include "IContactListProtocol.h"
#include "IUIContactListListener.h"
#include "UIEventProvider.h"
#include "Sorter.h"

class ContactList : public IContactListProtocolDelegate, public UIEventProvider
{
public:
	ContactList(IContactListProtocol* contactListProtocol);
	virtual ~ContactList();
	
	void AddContact(Contact* contact);
	bool RemoveContact(Contact* contact);
		
	virtual std::vector<Contact*> GetAllContacts();
	virtual Contact* GetContact(uint32_t contactIndex);
	uint32_t Count();
	
	virtual void Sort(Sorter sorter);	
	virtual std::vector<Contact*> GetContactsForList(std::string contactListType);
	virtual std::vector<Contact*> GetSortedContactList(Sorter sorter);
	
	virtual void SetInformUserUponAddContact(bool informUser);
	virtual bool InformUserUponAddContact();

public:
	virtual void SyncListStarted();
	virtual void SyncListEnded();
	virtual void SetInformUserUponListChange(bool informUser);
	virtual void SetDefaultContactList(DefaultContactListType contactListType);
	
	virtual void ContactFound(Contact* contact);
	virtual void GroupFound(std::string groupId, std::string groupName);
	virtual void ContactStatusChanged(std::string passport, Status* status);
	virtual void ContactPersonalMessageFound(std::string message);
	
	virtual void ContactPhoneNumberFound(PhoneNumberType phoneType, std::string phoneNumber);
	virtual void ContactBlogSettingFound(bool hasBlog);
	virtual void ContactCanPageSettingFound(bool canBePaged);
	virtual void ContactMSNDirectCapableSettingFound(bool msnDirectCapable);
		
private:
	IContactListProtocol* m_contactListProtocol;

private:
	typedef std::vector<Contact*> ContactListType;
	
	ContactListType m_contacts;
	std::map<std::string, Contact*> m_contactPassports;
	std::map<std::string, ContactListType> m_contactLists;
	std::map<std::string, std::string> m_groups;
	
	bool m_informUserUponContactAdd;
	DefaultContactListType m_defaultContactListType;
};

#endif
