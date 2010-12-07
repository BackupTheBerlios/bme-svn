/*
 *  PlatformSpecific.h
 *  Bme
 *
 *  Created by Tim De Jong on 25-04-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef PLATFORM_SPECIFIC_H
#define PLATFORM_SPECIFIC_H

#include <string>
#include "Image.h"
#include "IThread.h"
#include "IRunnable.h"
#include "IConnectionManager.h"
#include "IImageManager.h"
#include "ICrypto.h"
#include "XMLDocument.h"
#include "XMLNode.h"
#include "XMLElement.h"
#include "IPathManager.h"

//TODO: check if this code does not leak!
/**
	Makes all platform specific code available via standardised interfaces. Each platform should
	implement this interface to return platform specific implementations of these interfaces.
*/
class PlatformSpecific
{
public:
	static void Init();
	static void Cleanup();
	
	static IConnectionManager* GetConnectionManager();
	static IImageManager* GetImageManager();	
	static ICrypto* GetCrypto();
	
	static IThread*	GetThread(IRunnable* runnable);
	static IPathManager* GetPathManager();
	
	static XMLDocument* GetXMLDocumentFromString(std::string xmlString);
	static XMLDocument* GetXMLDocumentFromFile(std::string filename);
	
private:
	static XMLNode* TraverseTree(void* startNode, XMLDocument* document);
	
private:
	static IConnectionManager* s_connectionManager;
	static IImageManager* s_imageManager;
	static ICrypto* s_crypto;
	static IPathManager* s_pathManager;
};


#endif