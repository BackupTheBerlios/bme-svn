//
//  main.m
//  BmeApp
//
//  Created by Tim De Jong on 15-07-10.
//  Copyright 2010 ThinkPractice. All rights reserved.
//

#import <Cocoa/Cocoa.h>

int main(int argc, char *argv[])
{
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
	int returnCode = NSApplicationMain(argc,  (const char **) argv);
	[pool release];
	
	return returnCode; 
}
