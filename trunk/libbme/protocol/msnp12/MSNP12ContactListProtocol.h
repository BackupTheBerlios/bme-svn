/*
 *  MSNP12ContactListProtocol.h
 *  Bme
 *
 *  Created by Tim De Jong on 06-07-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef MSNP12_CONTACT_LIST_HANDLER_H
#define MSNP12_CONTACT_LIST_HANDLER_H

#include "ProtocolHandler.h"
#include "IContactListProtocol.h"

class MSNP12ContactListProtocol : public ProtocolHandler, public IContactListProtocol 
{
public:
	MSNP12ContactListProtocol();
	virtual ~MSNP12ContactListProtocol();

	virtual void SyncList();
	
public:
	virtual bool IsHandlerForMessage(ProtocolMessage* message);
	virtual void HandleMessage(ProtocolMessage* message);
	
public:
	virtual void SetContactListProtocolDelegate(IContactListProtocolDelegate* userProtocolDelegate);
	virtual IContactListProtocolDelegate* Delegate();

private:
	IContactListProtocolDelegate* m_contactListProtocolDelegate;
	
private:
	uint32_t	m_numContacts,
				m_contactsAdded,
				m_numGroups,
				m_groupsAdded
				;
};

#endif


