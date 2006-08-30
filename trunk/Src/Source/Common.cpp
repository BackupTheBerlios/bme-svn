/*****************************************************************
 * Copyright (c) 2005 Tim de Jong								 *
 *							       								 *
 * All rights reserved.											 *
 * Distributed under the terms of the MIT License.               *
 *****************************************************************/
#ifndef COMMON_H
#include "Common.h"
#endif

//CLEAN THIS UP LATER!
#include <be/storage/NodeInfo.h>
#include <be/xml/BParser.h>
#include <iostream>
#include <stdio.h>
#include "PeopleDefs.h"

BString Common::decodeURL(BString encoded)
{
	BString decoded = encoded;
	int index = decoded.FindFirst ('%', 0);
  	while (index != B_ERROR)
  	{
   		char buf[3], c;
   		decoded.Remove(index,1);
   		decoded.MoveInto(buf,index,2);
   		buf[2] = '\0';
   		sscanf(buf, "%x", &c);
   		decoded.Insert(c,1,index);
   		index = decoded.FindFirst('%', index + 1);
	}
  	return decoded;
}

BString Common::encodeURL(BString toEncode)
{
  	const char* rptr;
  	char* wptr;
  	char* retval;

  	wptr = retval = new char[toEncode.Length()*3];
  	rptr = toEncode.String();
//áéíóú%20(@#$%25&/?¿¡!ñÑ<>)%20{^|¬°;,~\}%20[àèìòù]
//(áéíóú)@{àèìòù}#[ºª\|~¬æ®†¥ //∫ø //π∑∂ ƒ©™£ //≤≈ ¢√ßµ…ñÑ]
  	while(1)
  	{
    	if(*rptr=='\0')
    	{ 
    		*wptr='\0'; break; 
    	}
//    	if(!(isalpha(*rptr) || isdigit(*rptr))){
    	if((*rptr==' ') || (*rptr == '%'))
    	{
      		sprintf(wptr, "%%%2x", (uint8)(*rptr));
      		rptr++;
      		wptr+=3;
      		continue;
    	}
    	*wptr=*rptr;
    	wptr++;
    	rptr++;
  	}
  	BString encodedString(retval);
  	return encodedString;
}

//djb2 hash algorithm
long Common::StringHash(BString string)
{	
	unsigned long hash = 5381;
    for (int i = 0; i < string.CountChars(); i++)
   	{
    	int c = string[i];
    	hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}
    return hash;
}

BBitmap* Common::ConvertBitmap(const unsigned char *rgbaBitmap, uint32 bitmapWidth, uint32 bitmapHeight)
{
	BBitmap* bitmap = new BBitmap(BRect(0.0, 0.0, bitmapWidth - 1.0, bitmapHeight - 1.0), 0, B_RGBA32);
	
	if (bitmap && bitmap->IsValid()) 
	{
    	memcpy(bitmap->Bits(), rgbaBitmap, bitmap->BitsLength());
	}
	return bitmap;	
}

BDocument Common::parseXMLString(BString xmlString)
{	
	char* xmlChars = xmlString.LockBuffer(xmlString.Length());
	BDocument document;
	if (ParseXML(&document,xmlChars, xmlString.Length()) == B_OK)
	{
	}	
	xmlString.UnlockBuffer();	
	//return parsed document to process stringdata
	return document;
}

uint32 Common::FindTranslatorConstant(BTranslatorRoster *roster, const char *mime)
{
	translator_id *translators;
	int32 num_translators;
  
	roster->GetAllTranslators(&translators, &num_translators);

	for (int32 i=0;i<num_translators;i++) 
	{
		const translation_format *fmts;
     	int32 num_fmts;

     	roster->GetOutputFormats(translators[i], &fmts, &num_fmts);

     	for (int32 j = 0;j < num_fmts; j++) 
     	{
        	if (!strcasecmp(fmts[j].MIME, mime))
           	{
              	return fmts[j].type;
            }
     	}
  	}
  	return 0;
}

status_t Common::WritePeopleData(BString filename, Contact *contact)
{	
	return WritePeopleData(filename, contact, "Ungrouped");	
}

status_t Common::WritePeopleData(BString filename, Contact *contact, BString groupName)
{	
	BFile file(filename.String(), B_CREATE_FILE | B_WRITE_ONLY);
	//set file mime type to people file mime
	BNodeInfo fileInfo(&file);
	fileInfo.SetType(K_PERSON_FILE_TYPE);
	//check if file is opened ok! 
	status_t err = file.InitCheck();
	if (err == B_OK)
	{
		BString contactName;
		file.WriteAttr(K_PERSON_NAME, B_STRING_TYPE, 0, contactName.String(), contactName.Length() + 1);
		
		BString nickName = contact->FriendlyName();
		file.WriteAttr(K_PERSON_NICKNAME, B_STRING_TYPE, 0, nickName.String(), nickName.Length() + 1); 
		
		BString email = contact->Passport();
		file.WriteAttr(K_PERSON_EMAIL, B_STRING_TYPE, 0, email.String(), email.Length() + 1); 
		file.WriteAttr(K_PERSON_MSN, B_STRING_TYPE, 0, email.String(), email.Length() + 1);
		
		/*file.WriteAttr(K_PERSON_HOME_PHONE, B_STRING_TYPE, 0, fHomePhone.String(), fHomePhone.Length()+1); 
		file.WriteAttr(K_PERSON_WORK_PHONE, B_STRING_TYPE, 0, fWorkPhone.String(), fWorkPhone.Length()+1); 
		file.WriteAttr(K_PERSON_CELL_PHONE, B_STRING_TYPE, 0, fCellPhone.String(), fCellPhone.Length()+1); */
		
		if(groupName.Length() > 0 && groupName.ICompare("Ungrouped") != 0)
		{
			file.WriteAttr(K_PERSON_GROUP, B_STRING_TYPE, 0, groupName.String(), groupName.Length() + 1);
		}
		else
		{
			file.WriteAttr(K_PERSON_GROUP, B_STRING_TYPE, 0, "", 1);
		}
	}
	return err;
}
