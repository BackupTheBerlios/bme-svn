/*
 *  XMLElement.h
 *  BmeApp
 *
 *	Created by Tim De Jong on 26-08-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef XML_ELEMENT_H
#define XML_ELEMENT_H

#include <string>
#include <vector>
#include <map>
#include "XMLNode.h"

using namespace std;

class XMLElement : public XMLNode
{
public:
	XMLElement();
	XMLElement(string name);
	XMLElement(string name, string stringValue);
	virtual ~XMLElement();
	
	vector<XMLElement*>			ElementsForName(string name);
	
	virtual void				AddChild(XMLNode* child);
	virtual void				InsertChildAtIndex(XMLNode* child, size_t index);
	virtual void				InsertChildrenAtIndex(vector<XMLNode*> children, size_t index);
	virtual void				RemoveChildAtIndex(size_t index);
	virtual void				ReplaceChildAtIndex(size_t index, XMLNode* node);
	virtual void				SetChildren(vector<XMLNode*> children);
	
	virtual void				AddAttribute(XMLNode* attribute);
	virtual XMLNode*			AttributeForName(string name);
	virtual vector<XMLNode*>	Attributes();
	virtual void				RemoveAttributeForName(string attrName);
	virtual void				SetAttributes(vector<XMLNode*> attributes);
	
	virtual void				AddNamespace(XMLNode* aNamespace);
	virtual vector<XMLNode*>	Namespaces();
	virtual XMLNode*			NamespaceForPrefix(string name);
	virtual void				RemoveNamespaceForPrefix(string name);
	virtual XMLNode*			ResolveNamespaceForName(string name);
	virtual string				ResolvePrefixForNamespaceURI(string namespaceURI);
	virtual void				SetNamespaces(vector<XMLNode*> namespaces);
	
private:
	map<string, XMLNode*>		m_attributes;
	vector<XMLNode*>			m_namespaces
								;
};

#endif
