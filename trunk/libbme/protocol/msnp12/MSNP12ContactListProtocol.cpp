/*
 *  MSNP12ContactListProtocol.cpp
 *  Bme
 *
 *  Created by Tim De Jong on 06-07-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */

#include "MSNP12ContactListProtocol.h"
#include "Contact.h"
#include "Common.h"
#include "PlatformSpecific.h"
#include "XMLDocument.h"
#include <iostream>

MSNP12ContactListProtocol::MSNP12ContactListProtocol()
							:	ProtocolHandler(),
								IContactListProtocol()
{
}

MSNP12ContactListProtocol::~MSNP12ContactListProtocol()
{
}

void MSNP12ContactListProtocol::SyncList()
{
	//send initial SYN message
	ProtocolMessage* synMessage = new ProtocolMessage(NotificationMessages::K_SYNCHRONISE_LIST);
	synMessage->AddParam("0");
	synMessage->AddParam("0");
	
	//m_contactsAdded = 0;
	//m_groupsAdded = 0;			
	SendCommandMessageTrId(synMessage);
	
	//inform the contact list the sync message has been sent
	m_contactListProtocolDelegate->SyncListStarted();
}

bool MSNP12ContactListProtocol::IsHandlerForMessage(ProtocolMessage* message)
{
	std::string command = message->CommandType();
	return	(command == NotificationMessages::K_ADD_BEHAVIOUR_MSG) ||
			(command == NotificationMessages::K_DEFAULT_CONTACT_LIST_MSG) ||
			(command == NotificationMessages::K_CONTACT_LIST_MSG) ||
			(command == NotificationMessages::K_GROUP_LIST_MSG) ||
			(command == NotificationMessages::K_CHANGE_STATUS) ||
			(command == NotificationMessages::K_SYNCHRONISE_LIST) ||
			(command == NotificationMessages::K_PRINCIPAL_INITIAL_PRESENCE) ||
			(command == NotificationMessages::K_CONTACT_PERSONAL_MSG) ||
			(command == NotificationMessages::K_CONTACT_PHONE_NUMBERS)
			;
}

void MSNP12ContactListProtocol::HandleMessage(ProtocolMessage* message)
{
	std::string command = message->CommandType();
	//CHANGED IN MSNP11!!!!
	if (command == NotificationMessages::K_SYNCHRONISE_LIST)
	{
		std::string firstTimeStamp = message->GetParam(0);
		std::string	secondTimeStamp = message->GetParam(1);
			
		if (firstTimeStamp != secondTimeStamp)
		{
			//we should update our contactlist	
			std::string numContacts = message->GetParam(2);
			m_numContacts = atoi(numContacts.c_str());		
								
			std::string numGroups = message->GetParam(3);
			m_numGroups = atoi(numGroups.c_str());
		}
		else
		{
			//if we don't have to synchronise the list and are using the cached contact list instead
			//be sure to set the m_contactsAdded and m_groupsAdded to the number of contacts and groups
			//available. In that way the initial status message will always be sent, and always after
			//the syn message
			m_contactsAdded = m_numContacts;
			m_groupsAdded = m_numGroups;
		}		
	}
	else if (command == NotificationMessages::K_CONTACT_LIST_MSG)
	{		
		Contact *newContact = new Contact();
		
		for (int i = 0; i < message->ParamCount(); i++)
		{
			std::string temp = message->GetParam(i);
				
			if (temp.find("N=") != std::string::npos)
			{						
				temp = temp.substr(2);	
				newContact->SetPassport(temp);
			}
			else if (temp.find("F=") != std::string::npos)
			{
				temp = temp.substr(2);
				std::string friendlyName = temp;
				friendlyName = Common::decodeURL(friendlyName);
				newContact->SetFriendlyName(friendlyName);
			}
			else if (temp.find("C=") != std::string::npos)
			{
				temp = temp.substr(2);
				newContact->SetGUID(temp);
			}
			else if (i == 4)
			{
				//only in this order!!! 
				//parse groupID's
				std::string groupId;
				int32_t startIndex = 0;
				size_t commaIndex = std::string::npos;
				do
				{
					commaIndex = temp.find(",",startIndex);
					if (commaIndex != std::string::npos)
					{
						//get one of the groupID's
						groupId = temp.substr(startIndex, commaIndex-startIndex);		
						//add group to grouplist of contact
						newContact->AddGroup(groupId);
						cout << "GroupID 1= " << groupId << endl;								
						groupId = "";
						//start searching at position past the previous found comma
						startIndex = commaIndex + 1;
					}
					else
					{
						//get one of the groupID's
						//temp.CopyInto(groupID,0, temp.CountChars());		
						groupId = temp;
						//add group to grouplist of contact
						newContact->AddGroup(groupId);
						cout << "GroupID 2= " << groupId << endl;
						groupId = "";								
						break;
					}							
				}
				while (commaIndex <= temp.size());					
			}
			else
			{ 
				int32_t partOfLists = atoi(temp.c_str());
				newContact->SetPartOfLists(partOfLists);
			}
		}		
		//set initial status for the contact to offline
		newContact->SetStatus(Status::GetStatusForAbbreviation(Statusses::K_OFFLINE));
		//inform the contact list that a new contact has been found
		m_contactListProtocolDelegate->ContactFound(newContact);
		m_contactsAdded++;
		//see if we're done synchronizing the lists
		if (m_contactsAdded == m_numContacts)
		{
			m_contactListProtocolDelegate->SyncListEnded();
			this->ProtocolDelegate()->SyncListEnded();
		}
	}
	else if (command == NotificationMessages::K_GROUP_LIST_MSG)
	{
		std::string groupName = message->GetParam(0);
		std::string	groupId = message->GetParam(1);					
									
		m_contactListProtocolDelegate->GroupFound(groupId, groupName);	
		m_groupsAdded++;
	}			
	else if (
			 (command == NotificationMessages::K_PRINCIPAL_INITIAL_PRESENCE) ||
			 (command == NotificationMessages::K_PRINCIPAL_STATUS)
			 )
	{				
		std::string temp = message->GetParam(0);
		//find status
		Status *status = Status::GetStatusForAbbreviation(temp); 
		if (status)
		{
			//find contactID if available
			std::string contactPassport = message->GetParam(1);
			m_contactListProtocolDelegate->ContactStatusChanged(contactPassport, status);				
		}		
	}
	else if (command == NotificationMessages::K_ADD_BEHAVIOUR_MSG)
	{
		std::string value = message->GetParam(0);
		if (value == AddBehaviour::K_INFORM_USER)
		{
			m_contactListProtocolDelegate->SetInformUserUponListChange(true);
		}
		else if (value == AddBehaviour::K_ADD_IMMEDIATELY) 
		{
			m_contactListProtocolDelegate->SetInformUserUponListChange(false);
		}		
	}
	else if (command == NotificationMessages::K_DEFAULT_CONTACT_LIST_MSG)
	{
		std::string value = message->GetParam(0);
		if (value == DefaultContactListTypes::K_DEFAULT_ALLOWED)
		{
			m_contactListProtocolDelegate->SetDefaultContactList(IContactListProtocolDelegate::K_ALLOW_LIST);
		}
		else if (value == DefaultContactListTypes::K_DEFAULT_BLOCKED)
		{
			m_contactListProtocolDelegate->SetDefaultContactList(IContactListProtocolDelegate::K_BLOCK_LIST);
		}
	}	
	else if (command == NotificationMessages::K_PRINCIPAL_STATUS)
	{
	}
	else if (command == NotificationMessages::K_ADD_PRINCIPAL)
	{
	}
	else if (command == NotificationMessages::K_REMOVE_PRINCIPAL)
	{
	}
	else if (command == NotificationMessages::K_RENAME_PRINCIPAL)
	{
		//see if still works!!!
	}
	else if (command == NotificationMessages::K_CONTACT_PERSONAL_MSG)
	{
		//buddy sent a personal message
		std::string principalPassport = message->GetParam(0);			
		//get the message
		std::string payload = message->PayloadString();		
		XMLDocument* personalMessageXML = PlatformSpecific::GetXMLDocumentFromString(payload);
		//find and set the personal message
		vector<XMLNode*> children = personalMessageXML->RootElement()->Children();
		for (int i = 0; i < children.size(); i++)
		{
			XMLNode* child = children[i];
			if (child->Name() == "PSM") 
			{
				std::string personalMessage = child->StringValue();
				m_contactListProtocolDelegate->ContactPersonalMessageFound(personalMessage);
				break;
			}
		}
		
	}
	else if (command == NotificationMessages::K_CONTACT_PHONE_NUMBERS)
	{
		std::string subCommand = message->GetParam(0);
		
		if (subCommand == SettingTypes::K_HOME_PHONE_NUMBER)
		{
			std::string phoneNumber = Common::decodeURL(message->GetParam(1));
			m_contactListProtocolDelegate->ContactPhoneNumberFound(K_HOME_PHONE_NUMBER, phoneNumber);			
		}
		else if (subCommand == SettingTypes::K_WORK_PHONE_NUMBER)
		{
			std::string phoneNumber = Common::decodeURL(message->GetParam(1));
			m_contactListProtocolDelegate->ContactPhoneNumberFound(K_WORK_PHONE_NUMBER, phoneNumber);			
		}
		else if (subCommand == SettingTypes::K_MOBILE_PHONE_NUMBER)
		{
			std::string phoneNumber = Common::decodeURL(message->GetParam(1));
			m_contactListProtocolDelegate->ContactPhoneNumberFound(K_MOBILE_PHONE_NUMBER, phoneNumber);			
		}
		else if (subCommand == SettingTypes::K_HAS_MSN_SPACE_BLOG)
		{
			bool hasBlog = atoi(message->GetParam(1).c_str());
			m_contactListProtocolDelegate->ContactBlogSettingFound(hasBlog);	
		}
		else if (subCommand == SettingTypes::K_CAN_PAGE_MOBILE) 
		{
			std::string value = Common::decodeURL(message->GetParam(1));
			if (value == "Y")
			{
				m_contactListProtocolDelegate->ContactCanPageSettingFound(true);
			}
		}
		else if (subCommand == SettingTypes::K_CAN_DIRECT_PAGE_MOBILE)
		{
			std::string value = Common::decodeURL(message->GetParam(1));
			if (value == "2")
			{
				m_contactListProtocolDelegate->ContactMSNDirectCapableSettingFound(true);
			}
			else 
			{
				m_contactListProtocolDelegate->ContactMSNDirectCapableSettingFound(false);
			}
			
		}		
	}	
}

void MSNP12ContactListProtocol::SetContactListProtocolDelegate(IContactListProtocolDelegate* userProtocolDelegate)
{
	m_contactListProtocolDelegate = userProtocolDelegate;
}

IContactListProtocolDelegate* MSNP12ContactListProtocol::Delegate()
{
	return m_contactListProtocolDelegate;
}