/*
 *  MacPlatform.cpp
 *  Bme
 *
 *  Created by Tim De Jong on 25-04-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#import "PlatformSpecific.h"

#include "MacConnectionManager.h"
#include "MacThread.h"
#include "MacImageManager.h"
#include "MacCrypto.h"
#include "MacPathManager.h"

//mac specific implementation
static NSAutoreleasePool *s_pool = nil;
//static singleton variables
IConnectionManager*  PlatformSpecific::s_connectionManager = NULL;
IImageManager* PlatformSpecific::s_imageManager = NULL;
ICrypto* PlatformSpecific::s_crypto = NULL;
IPathManager* PlatformSpecific::s_pathManager = NULL;

void PlatformSpecific::Init()
{
	//create NSAutoReleasePool here
	s_pool = [[NSAutoreleasePool alloc] init];	
}

void PlatformSpecific::Cleanup()
{	
	[s_pool release];
}

IConnectionManager* PlatformSpecific::GetConnectionManager()
{
	if (!s_connectionManager)
	{
		s_connectionManager = new MacConnectionManager();
	}
	return s_connectionManager; 
}

IImageManager* PlatformSpecific::GetImageManager()
{
	if (!s_imageManager)
	{
		s_imageManager = new MacImageManager();
	}	
	return s_imageManager;
}

ICrypto* PlatformSpecific::GetCrypto()
{
	if (!s_crypto)
	{
		s_crypto = new MacCrypto();
	}
	return s_crypto;
}

IThread* PlatformSpecific::GetThread(IRunnable* runnable)
{
	MacThread* thread = new MacThread(runnable);
	return thread;
}

IPathManager* PlatformSpecific::GetPathManager()
{
	if (!s_pathManager)
	{
		s_pathManager = new MacPathManager();
	}
	return s_pathManager;
}

static std::string ConvertToCString(NSString* macString)  
{
	const char* str = [macString cStringUsingEncoding:NSASCIIStringEncoding];
	if (str)
	{
		std::string cString(str); 
		return cString;
	}
	return "";
}

XMLDocument* PlatformSpecific::GetXMLDocumentFromString(std::string xmlString)
{	
	//prepare and parse the xml string
	NSString* xmlStr = [[NSString alloc] initWithCString:xmlString.c_str() encoding:NSUTF8StringEncoding];
	NSError *error = nil;
	NSXMLDocument* xmlDoc = [[NSXMLDocument alloc] initWithXMLString:xmlStr options:NSXMLDocumentTidyXML error:&error];
	[xmlStr release];
	//set the properties for the document
	XMLDocument* document = new XMLDocument();
	
	string version(ConvertToCString([xmlDoc version]));
	document->SetVersion(version);
	document->SetName(ConvertToCString([xmlDoc name]));
	document->SetIndex([xmlDoc index]);
	document->SetLevel([xmlDoc level]);
	document->SetXMLString(ConvertToCString([xmlDoc XMLString]));
	//traverse tree and create our a tree with our own objects
	XMLNode* rootNode = PlatformSpecific::TraverseTree([xmlDoc rootElement], document);
	document->SetRootElement(rootNode);
	
	[xmlDoc release];
	return document;
}

XMLDocument* PlatformSpecific::GetXMLDocumentFromFile(std::string filename)
{
	NSString* path = [[NSString alloc] initWithCString:filename.c_str() encoding:NSUTF8StringEncoding];
	
	NSError* error = nil;
	NSString* xmlText = [[NSString alloc] initWithContentsOfFile:path encoding:NSUTF8StringEncoding error:&error];
	[path release];
	
	XMLDocument* document = NULL;
	if (!error)
	{
		const char* xmlString = [xmlText cStringUsingEncoding:NSASCIIStringEncoding];
		if (xmlString)
		{
			document = PlatformSpecific::GetXMLDocumentFromString(xmlString);	
		}
	}
	[xmlText release];
	return document;
}

XMLNode* PlatformSpecific::TraverseTree(void* stNode, XMLDocument* document)
{
	NSXMLNode* startNode = (NSXMLNode*)stNode;
	
	XMLNode* node = NULL;	
	if ([startNode kind] == NSXMLElementKind)
	{
		node = new XMLElement();
	}
	else
	{
		node = new XMLNode();
	}
	//set node properties
	node->SetIndex([startNode index]);
	node->SetKind((XMLNode::XMLNodeKind)[startNode kind]);
	node->SetLevel([startNode level]);
	node->SetName(ConvertToCString([startNode name]));
	node->SetStringValue(ConvertToCString([startNode stringValue]));
	node->SetRootDocument(document);	
	node->SetXMLString(ConvertToCString([startNode XMLString]));
	
	//traverse node children
	NSArray* children = [startNode children];
	for (NSXMLNode* child in children)
	{
		XMLNode* childNode = TraverseTree(child,document);
		if (childNode->Kind() == XMLNode::XMLAttributeKind)
		{
			XMLElement* elementNode = dynamic_cast<XMLElement*>(node);
			if (elementNode)
			{
				elementNode->AddAttribute(childNode);
			}
		}
		else if (childNode->Kind() == XMLNode::XMLNamespaceKind) 
		{
			XMLElement* elementNode = dynamic_cast<XMLElement*>(node);
			if (elementNode)
			{
				elementNode->AddNamespace(childNode);
			}
		}
		else 
		{
			node->AddChild(childNode);
		}
		childNode->SetParent(node);		
	}
	
	return node;
}


									
