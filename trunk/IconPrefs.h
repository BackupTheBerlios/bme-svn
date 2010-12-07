/*
 *  IconPrefs.h
 *  BmeApp
 *
 *  Created by Tim De Jong on 30-08-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef ICON_PREFS_H
#define ICON_PREFS_H

#include <string>
#include <vector>
#include "XMLDocument.h"
#include "XMLNode.h"

class IconPrefs
{
public:
	IconPrefs(std::string prefsPath);
	virtual ~IconPrefs();
	
	std::string				Name();
	std::vector<XMLNode*>	GetStatusNodes();
	std::vector<XMLNode*>	GetEmoticonNodes();
	
private:
	XMLDocument*			m_xmlDocument;
	std::string				m_name;
	std::vector<XMLNode*>	m_statusNodes;
	std::vector<XMLNode*>	m_emoticonNodes;
};

#endif

