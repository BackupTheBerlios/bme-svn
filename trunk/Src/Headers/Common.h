/*****************************************************************
 * Copyright (c) 2005 Tim de Jong								 *
 *							       								 *
 * All rights reserved.											 *
 * Distributed under the terms of the MIT License.               *
 *****************************************************************/
#ifndef COMMON_H
#define COMMON_H

#include <be/app/Message.h>
#include <be/support/String.h>
#include <be/interface/Bitmap.h>
#include <be/storage/File.h>
#include <be/translation/TranslatorRoster.h>
#include <be/xml/BContent.h> 
#include "Contact.h"

namespace Common
{
	BString				decodeURL(BString encoded);
	BString				encodeURL(BString toEncode);
	long				StringHash(BString string);
	
	BBitmap*			ConvertBitmap(const unsigned char *rgbaBitmap, uint32 bitmapWidth, uint32 bitmapHeight);	
	
	BDocument			parseXMLString(BString xmlString);
	
	uint32				FindTranslatorConstant(BTranslatorRoster *roster, const char *mime);
	
	status_t 			WritePeopleData(BString filename, Contact *contact);
	status_t 			WritePeopleData(BString filename, Contact *contact, BString groupName);
};

#endif
