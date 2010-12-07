/*
 *  ConversationItem.cpp
 *  Bme
 *
 *  Created by Tim De Jong on 04-05-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */

#include "ConversationItem.h"

ConversationItem::ConversationItem()
{
}

ConversationItem::~ConversationItem()
{
}

void ConversationItem::SetText(std::string text)
{
	m_itemText = text;
}

std::string ConversationItem::Text()
{
	return m_itemText;
}