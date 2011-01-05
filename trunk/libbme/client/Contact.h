/*
 *  Contact.h
 *  Bme
 *
 *  Created by Tim De Jong on 19-02-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 * All rights reserved.											 *
 * Distributed under the terms of the MIT License.               *
 *****************************************************************/
#ifndef CONTACT_H
#define CONTACT_H

//#include "IXMLFlattenable.h"
#include <vector>
#include <map>
#include <string>
#include "Status.h"
#include "KeyValueCollection.h"

class Contact : public KeyValueCollection
{
public:
	Contact();//IContactProtocol?
	Contact(std::string passport, std::string friendlyName, std::string guid, int32_t partOfLists, Status *status);
	virtual				~Contact();
	
	//inherited from IXMLFlattenable
	//BString				XMLFlatten();
	//void				XMLUnflatten(xmlDocPtr xmlDocument);
	
	void						SetPassport(std::string passport);
	std::string					Passport();
	
	void						SetFriendlyName(std::string friendlyName);
	std::string					FriendlyName();
	
	void						SetGUID(std::string guid);
	std::string					GUID();
	
	void						AddGroup(std::string groupId);
	bool						RemoveGroup(std::string groupId);
	std::vector<std::string>	Groups();
	
	void						SetPartOfLists(int32_t partOfLists);
	int32_t						PartOfLists();
	
	void						SetStatus(Status *status);
	Status*						GetStatus();
	
	bool						IsOnForwardList();
	bool						IsOnReverseList();
	bool						IsOnAllowList();
	bool						IsBlocked();				
	bool						IsOnline();
	
	bool						HasPersonalMessage();
	void						SetPersonalMessage(std::string personalMessage);
	std::string					PersonalMessage();
	
	//bitmap image, phone numbers, etc.
	virtual void AddPhoneNumber(PhoneNumberType phoneNumberType, std::string number);
	virtual std::map<PhoneNumberType, std::string> PhoneNumbers();
	virtual std::string GetPhoneNumber(PhoneNumberType numberType);
	
	virtual void SetHasBlog(bool hasBlog);
	virtual bool HasBlog();
	
	virtual void SetCanBePaged(bool canBePaged);
	virtual bool CanBePaged();
	
	virtual void SetMsnDirectCapable(bool msnDirectCapable);
	virtual bool MsnDirectCapable();	
	
private:
	std::string			m_passport,
						m_friendlyName,
						m_guid,
						m_personalMessage
						;		
	
	bool				m_hasPersonalMessage;
	int32_t				m_partOfLists;
	
	Status				*m_status;	
	std::vector<std::string> m_groups;
	
	std::map<PhoneNumberType, std::string> m_phoneNumbers;
	bool				m_hasBlog,
						m_canBePaged,
						m_msnDirectCapable
						;
};

#endif

