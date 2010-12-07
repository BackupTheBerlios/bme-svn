//
//  BmeAppAppDelegate.h
//  BmeApp
//
//  Created by Tim De Jong on 15-07-10.
//  Copyright 2010 ThinkPractice. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#include "ContactListController.h"
#include "BmeClient.h"

@interface BmeAppAppDelegate : NSObject <NSApplicationDelegate> 
{
    NSWindow *window;
	NSView* loginView;
	NSView* contactListView;
	
	ContactListController *contactListController;
	BmeClient* bmeClient;
}

@property (assign) IBOutlet NSWindow *window;
@property (assign) IBOutlet NSView* loginView;
@property (assign) IBOutlet NSView* contactListView;
@property (nonatomic,retain) IBOutlet ContactListController* contactListController;

-(IBAction)loginAction:(id)sender;

@end
