//
//  ContactListController.m
//  Bme
//
//  Created by Tim De Jong on 09-07-10.
//  Copyright 2010 ThinkPractice. All rights reserved.
//

#import "ContactListController.h"
#import "Sorter.h"
#import "Contact.h"
#import <iostream>

@implementation ContactListController

@synthesize contactList, contactListListener, tableView, contactListAvailable;

-(id)initWithContactList:(ContactList*)cList
{
	self = [super init];
	
	if (self)
	{
		self.contactList = cList;
		self.contactListListener = new MacUIContactListListener(self);
		self.contactList->AddUIListener(self.contactListListener);
	}
	return self;
}

-(void)sortList
{
	Sorter sorter;
	//sorter.AddCompareKey(K_ON_FORWARD_LIST_KEY, true);
	sorter.AddCompareKey(K_ONLINE_STATUS_KEY, false);
	sorter.AddCompareKey(K_PASSPORT_KEY,true);	
	contactList->Sort(sorter);
}

-(void)setContactList:(ContactList *)cList
{
	contactList = cList;
	self.contactListListener = new MacUIContactListListener(self);
	self.contactList->AddUIListener(self.contactListListener);
}

- (NSInteger)numberOfRowsInTableView:(NSTableView *)aTableView
{	
	if (contactListAvailable)
	{
		NSInteger numberOfContacts = self.contactList->Count(); 
		return numberOfContacts;
	}
	else 
	{
		return 0;
	}

}

-(id)tableView:(NSTableView *)aTableView objectValueForTableColumn:(NSTableColumn *)aTableColumn row:(NSInteger)rowIndex
{
	NSString* title = [aTableColumn identifier];
	
	Contact* contact = self.contactList->GetContact(rowIndex);
	if ([title isEqualToString:@"passport"])
	{
		std::string passport = contact->Passport();
		NSString* contactPassport = [NSString stringWithCString:passport.c_str() encoding:NSUTF8StringEncoding];
		return contactPassport;
	}
	else if ([title isEqualToString:@"FL"])
	{
		NSNumber* number = [NSNumber numberWithBool:contact->IsOnForwardList()];
		return number;
	}
	else if ([title isEqualToString:@"AL"])
	{
		NSNumber* number = [NSNumber numberWithBool:contact->IsOnAllowList()];
		return number;
	}
	else if ([title isEqualToString:@"RL"])
	{
		NSNumber* number = [NSNumber numberWithBool:contact->IsOnReverseList()];
		return number;
	}
	else if ([title isEqualToString:@"BL"])
	{
		NSNumber* number = [NSNumber numberWithBool:contact->IsBlocked()];
		return number;
	}	
}

-(void)dealloc
{
	delete contactList;
	[tableView release];
	[super dealloc];
}

@end

MacUIContactListListener::MacUIContactListListener(ContactListController* contactListController)
							:	IUIContactListListener(),
								m_contactListController(contactListController)		
{
}

MacUIContactListListener::~MacUIContactListListener()
{
}

void MacUIContactListListener::SyncListStarted()
{
}

void MacUIContactListListener::SyncListEnded()
{
	NSLog(@"SyncListEnded()");
	//list synching has finished, sort the list with contacts
	[m_contactListController sortList];
	m_contactListController.contactListAvailable = YES;
	[m_contactListController.tableView reloadData];	
}

void MacUIContactListListener::ContactAdded(Contact* contact)
{
	NSLog(@"Contact Added: %s ", contact->FriendlyName().c_str());
}

void MacUIContactListListener::ContactStatusChanged(Contact* contact)
{
	//list synching has finished, sort the list with contacts
	[m_contactListController sortList];
}

void MacUIContactListListener::GroupAdded(std::string groupId, std::string groupName)
{
	NSLog(@"Group Added, groupId = %s,groupName= %s",groupId.c_str(), groupName.c_str());
}