/*
 *  ContactList.cpp
 *  Bme
 *
 *  Created by Tim De Jong on 19-02-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */

#include "ContactList.h"

ContactList::ContactList(IContactListProtocol* contactListProtocol)
				:	IContactListProtocolDelegate(),
					UIEventProvider(),
					m_contactListProtocol(contactListProtocol),
					m_informUserUponContactAdd(true)
{
	m_contactListProtocol->SetContactListProtocolDelegate(this);
}

ContactList::~ContactList()
{
	delete m_contactListProtocol;
	//delete all the contacts
	typedef std::vector<Contact*>::iterator VI;
	for (VI c = m_contacts.begin(); c != m_contacts.end(); ++c)
	{
		Contact* contact = (*c);
		delete contact;
	}	
}

std::vector<Contact*> ContactList::GetAllContacts()
{
	return m_contacts;
}

Contact* ContactList::GetContact(uint32_t contactIndex)
{
	return m_contacts[contactIndex];
}

uint32_t ContactList::Count()
{
	return m_contacts.size();
}

std::vector<Contact*> ContactList::GetContactsForList(std::string contactListType)
{
	return m_contactLists[contactListType];
}

void ContactList::SetInformUserUponAddContact(bool informUser)
{
	m_informUserUponContactAdd = informUser;
}

bool ContactList::InformUserUponAddContact()
{
	return m_informUserUponContactAdd;
}

void ContactList::SyncListStarted()
{
	//inform UI about the contact that has been added
	std::vector<IUIListener*> m_uiContactListListeners = this->GetAllListeners();
	for (UI c = m_uiContactListListeners.begin(); c != m_uiContactListListeners.end(); ++c) 
	{
		IUIContactListListener* uiContactListener = (IUIContactListListener*)*c;
		uiContactListener->SyncListStarted();	
	}
}

void ContactList::SyncListEnded()
{
	//inform UI about the contact that has been added
	std::vector<IUIListener*> m_uiContactListListeners = this->GetAllListeners();
	for (UI c = m_uiContactListListeners.begin(); c != m_uiContactListListeners.end(); ++c) 
	{
		IUIContactListListener* uiContactListener = (IUIContactListListener*)*c;
		uiContactListener->SyncListEnded();	
	}
}

void ContactList::SetInformUserUponListChange(bool informUser)
{
	this->SetInformUserUponAddContact(informUser);	
}

void ContactList::SetDefaultContactList(DefaultContactListType contactListType)
{
	m_defaultContactListType = contactListType;
}

void ContactList::ContactFound(Contact* contact)
{
	m_contacts.push_back(contact);
	m_contactPassports[contact->Passport()] = contact;
	//inform UI about the contact that has been added
	std::vector<IUIListener*> m_uiContactListListeners = this->GetAllListeners();
	for (UI c = m_uiContactListListeners.begin(); c != m_uiContactListListeners.end(); ++c) 
	{
		IUIContactListListener* uiContactListener = (IUIContactListListener*)*c;
		uiContactListener->ContactAdded(contact);	
	}
}

void ContactList::GroupFound(std::string groupId, std::string groupName)
{
	m_groups[groupId] = groupName;
	//inform UI about the group that has been added
	std::vector<IUIListener*> m_uiContactListListeners = this->GetAllListeners();
	for (UI c = m_uiContactListListeners.begin(); c != m_uiContactListListeners.end(); ++c) 
	{
		IUIContactListListener* uiContactListener = (IUIContactListListener*)*c;
		uiContactListener->GroupAdded(groupId, groupName);	
	}	
}

void ContactList::ContactStatusChanged(std::string passport, Status* status)
{
	Contact *contact = m_contactPassports[passport];								
	if (contact)
	{
		contact->SetStatus(status);		
		//inform UI about the contact status has been changed
		std::vector<IUIListener*> m_uiContactListListeners = this->GetAllListeners();
		for (UI c = m_uiContactListListeners.begin(); c != m_uiContactListListeners.end(); ++c) 
		{
			IUIContactListListener* uiContactListener = (IUIContactListListener*)*c;
			uiContactListener->ContactStatusChanged(contact);	
		}	
	}	
}

void ContactList::ContactPersonalMessageFound(std::string message)
{
	//retrieve contact added last
	Contact *contact = m_contacts.back();
	contact->SetPersonalMessage(message);
}

void ContactList::ContactPhoneNumberFound(PhoneNumberType phoneType, std::string phoneNumber)
{
	//retrieve contact added last
	Contact *contact = m_contacts.back();
	contact->AddPhoneNumber(phoneType, phoneNumber);
}

void ContactList::ContactBlogSettingFound(bool hasBlog)
{
	//retrieve contact added last
	Contact *contact = m_contacts.back();
	contact->SetHasBlog(hasBlog);
}

void ContactList::ContactCanPageSettingFound(bool canBePaged)
{
	//retrieve contact added last
	Contact *contact = m_contacts.back();
	contact->SetCanBePaged(canBePaged);
}

void ContactList::ContactMSNDirectCapableSettingFound(bool msnDirectCapable)
{
	//retrieve contact added last
	Contact *contact = m_contacts.back();
	contact->SetMsnDirectCapable(msnDirectCapable);
}

/** ====sorter example =====

//TODO: create a sorter class that makes it possible to sort on a combination of values 
 
 int comparefunc(const void *arg1, const void *arg2);
 
 
 
 int main(void) {
 
 MyDate dates[MAXDATES];
 
 // Set up some initial date values here
 
 
 
 // Now sort them                                      
 
 qsort(dates, MAXDATES, sizeof(MyDate), comparefunc);
 
 
 
 return 0;
 
 }
 
 
 
 int comparefunc(const void *arg1, const void *arg2) {
 
 const MyDate *date1 = (MyDate *)arg1;
 
 const MyDate *date2 = (MyDate *)arg2;
 
 
 
 if (date1->year < date2->year)
 
 return -1;
 
 else if (date1->year > date2->year)
 
 return 1;
 
 else {
 
 if (date1->month < date2->month)
 
 return -1;
 
 else if (date1->month > date2->month)
 
 return 1;
 
 else {
 
 if (date1->day < date2->day)
 
 return -1;
 
 else if (date1->day > date2->day)
 
 return 1;
 
 }
 
 }
 
 return 0;
}
 
*/ 
