/*
 *  IconPrefs.cpp
 *  BmeApp
 *
 *  Created by Tim De Jong on 30-08-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#include "IconPrefs.h"
#include "PlatformSpecific.h"
#include <iostream>

IconPrefs::IconPrefs(std::string prefsPath)
{
	m_xmlDocument = PlatformSpecific::GetXMLDocumentFromFile(prefsPath);
	XMLNode* rootElement = m_xmlDocument->RootElement();
	
	cout << rootElement->Name() << endl;
	
	typedef std::vector<XMLNode*>::const_iterator XI;
	vector<XMLNode*> children = rootElement->Children();
	for (XI c = children.begin(); c != children.end(); ++c)
	{
		XMLNode* child = *c;
		if (child->Name() == "name")
		{
			m_name = child->StringValue();
		}
		else if (child->Name() == "statusses")
		{
			vector<XMLNode*> statusChildren = child->Children();
			for (XI c3 = statusChildren.begin(); c3 != statusChildren.end();++c3)
			{
				XMLNode* statusChild = *c3;
				if (statusChild->Name() == "status")
				{
					m_statusNodes.push_back(statusChild);
				}
			}
		}
		else if (child->Name() == "emoticons")
		{
			vector<XMLNode*> emoticonChildren = child->Children();
			for (XI c3 = emoticonChildren.begin(); c3 != emoticonChildren.end();++c3)
			{
				XMLNode* emoticonChild = *c3;
				if (emoticonChild->Name() == "status")
				{
					m_statusNodes.push_back(emoticonChild);
				}
			}
		}	
		
	}
}

IconPrefs::~IconPrefs()
{
	delete m_xmlDocument;
}

std::string	IconPrefs::Name()
{
	return m_name;
}

vector<XMLNode*> IconPrefs::GetStatusNodes()
{
	return m_statusNodes;
}

vector<XMLNode*> IconPrefs::GetEmoticonNodes()
{
	return m_emoticonNodes;
}