/*
 *  ConversationItem.h
 *  Bme
 *
 *  Created by Tim De Jong on 04-05-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef CONVERSATION_ITEM_H
#define CONVERSATION_ITEM_H

#include <string>

class ConversationItem
{
public:
	ConversationItem();
	virtual ~ConversationItem();
	
	void SetText(std::string text);
	std::string Text();
	
private:
	std::string m_itemText;
	bool m_acknowledged;
};

#endif
