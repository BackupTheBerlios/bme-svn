/*
 *  IContactListProtocol.h
 *  Bme
 *
 *  Created by Tim De Jong on 05-05-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef I_CONTACT_LIST_PROTOCOL_H
#define I_CONTACT_LIST_PROTOCOL_H

#include"IContactListProtocolDelegate.h"

class IContactListProtocol
{
public:
	IContactListProtocol() {};
	virtual ~IContactListProtocol() {};
	
	virtual void SetContactListProtocolDelegate(IContactListProtocolDelegate* userProtocolDelegate) = 0;
	virtual IContactListProtocolDelegate* Delegate() = 0;
};

#endif

