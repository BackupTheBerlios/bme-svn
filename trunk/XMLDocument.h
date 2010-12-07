/*
 *  XMLDocument.h
 *  BmeApp
 *
 *  Created by Tim De Jong on 26-08-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef XML_DOCUMENT_H
#define XML_DOCUMENT_H

#include <string>
#include <vector>
#include "XMLNode.h"
#include "XMLElement.h"

using namespace std;

class XMLDocument : public XMLNode
{
private:	
	XMLDocument(string xmlString);
	
public:
	XMLDocument();
	XMLDocument(XMLElement* root);
	virtual ~XMLDocument();
	
	virtual	string			Version();
	virtual void			SetVersion(string version);
	
	virtual XMLElement*		RootElement();
	virtual void			SetRootElement(XMLNode* root);
	
	virtual void			AddChild(XMLNode* child);
	virtual void			InsertChildAtIndex(XMLNode* child, size_t index);
	virtual void			InsertChildrenAtIndex(vector<XMLNode*> children, size_t index);
	virtual void			RemoveChildAtIndex(size_t index);
	virtual void			ReplaceChildAtIndex(size_t index, XMLNode* node);
	virtual void			SetChildren(vector<XMLNode*> children);
		
private:
	string					m_version;
	XMLElement*				m_rootElement;
};

#endif