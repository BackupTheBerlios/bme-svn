//
//  ContactListController.h
//  Bme
//
//  Created by Tim De Jong on 09-07-10.
//  Copyright 2010 ThinkPractice. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <AppKit/AppKit.h>
#import "ContactList.h"
#import "IUIContactListListener.h"

class MacUIContactListListener;

@interface ContactListController : NSObject <NSTableViewDataSource>
{
	ContactList* contactList;
	MacUIContactListListener* contactListListener;
	NSTableView* tableView;
	BOOL contactListAvailable;
}

@property (nonatomic, assign) ContactList* contactList;
@property (nonatomic, assign) MacUIContactListListener* contactListListener;
@property (nonatomic, retain) IBOutlet NSTableView* tableView;
@property BOOL contactListAvailable;

-(id)initWithContactList:(ContactList*)contactList;
-(void)sortList;

@end

class MacUIContactListListener : public IUIContactListListener 
{
public:
	MacUIContactListListener(ContactListController* contactListController);
	virtual ~MacUIContactListListener();

public:	
	virtual void SyncListStarted();
	virtual void SyncListEnded();
	
	virtual void ContactAdded(Contact* contact);
	virtual void ContactStatusChanged(Contact* contact);
	virtual void GroupAdded(std::string groupId, std::string groupName);

private:
	ContactListController* m_contactListController;
};