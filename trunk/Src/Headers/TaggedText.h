/*****************************************************************
 * Copyright (c) 2005 Tim de Jong								 *
 *							       								 *
 * All rights reserved.											 *
 * Distributed under the terms of the MIT License.               *
 *****************************************************************/
 
#ifndef TAGGED_TEXT_H
#define TAGGED_TEXT_H

#include <be/support/String.h>
#include <be/support/List.h>


#ifndef EMOTICON_H
#include "Emoticon.h"
#endif

/**	Tag structure to represent emoticons within the text
 */
struct Tag
{
	int32				m_start,
						m_end,
						m_type;
						
	Emoticon			*m_emoticon;
};

/**	This class represents text and the emoticons in this text
	@author Tim de Jong	
 */
class TaggedText
{
	public:
		TaggedText();
		TaggedText(BString& txt, BList& tagList);
		
		BString				getText();
		BList&				getTags();
	
	public:
		enum {	K_EMOTICON =				0,
				K_USER_EMOTICON =			1,
				K_WEB_ADDRESS =				2};
		
	private:
		//private variables
		BString				m_text;
		BList				m_tags;		
};

#endif

