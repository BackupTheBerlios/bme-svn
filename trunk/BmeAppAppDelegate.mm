//
//  BmeAppAppDelegate.m
//  BmeApp
//
//  Created by Tim De Jong on 15-07-10.
//  Copyright 2010 ThinkPractice. All rights reserved.
//

#import "BmeAppAppDelegate.h"
#include "ProtocolConstants.h"
#include "PlatformSpecific.h"

@implementation BmeAppAppDelegate

@synthesize window, loginView, contactListView, contactListController;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification 
{
	// Insert code here to initialize your application 
	PlatformSpecific::Init();
	
	bmeClient = BmeClient::ConnectWithUserDetails("obelmiks@hotmail.com", "tim2839", ProtocolConstants::K_PROTOCOL_VERSION);	
	[contactListController setContactList:bmeClient->GetContactList()];
	
	//[loginView setHidden:NO];
}

- (void)applicationWillTerminate:(NSNotification *)notification
{
	[contactListController release];
	delete bmeClient;
	PlatformSpecific::Cleanup();
}

-(IBAction)loginAction:(id)sender
{
	//[loginView setHidden:YES];
	[loginView setHidden:NO];
}

@end
