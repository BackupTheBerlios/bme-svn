/*
 *  XMLElement.cpp
 *  BmeApp
 *
 *  Created by Tim De Jong on 26-08-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */

#include "XMLElement.h"

XMLElement::XMLElement()
			:	XMLNode(XMLElementKind)
{
}

XMLElement::XMLElement(string name)
			:	XMLNode(XMLElementKind)
{
	this->SetName(name);
}

XMLElement::XMLElement(string name, string stringValue)
			:	XMLNode(XMLElementKind)
{
	this->SetName(name);
	this->SetStringValue(stringValue);
}

XMLElement::~XMLElement()
{
}

vector<XMLElement*> XMLElement::ElementsForName(string name)
{
}

void XMLElement::AddAttribute(XMLNode* attribute)
{
	m_attributes[attribute->Name()] = attribute;
}

XMLNode* XMLElement::AttributeForName(string name)
{
	return m_attributes[name];
}

vector<XMLNode*> XMLElement::Attributes()
{
	vector<XMLNode*>attributes;
	typedef map<string, XMLNode*>::const_iterator AI;
	
	for (AI attr = m_attributes.begin(); attr != m_attributes.end(); ++attr)
	{
		attributes.push_back((*attr).second);
	}
	
	return attributes;
}

void XMLElement::RemoveAttributeForName(string attrName)
{
}

void XMLElement::SetAttributes(vector<XMLNode*> attributes)
{
}

void XMLElement::AddNamespace(XMLNode* aNamespace)
{
}

vector<XMLNode*> XMLElement::Namespaces()
{
}

XMLNode* XMLElement::NamespaceForPrefix(string name)
{
	return NULL;
}

void XMLElement::RemoveNamespaceForPrefix(string name)
{
}

XMLNode* XMLElement::ResolveNamespaceForName(string name)
{
	return NULL;
}

string XMLElement::ResolvePrefixForNamespaceURI(string namespaceURI)
{
	return "";
}

void XMLElement::SetNamespaces(vector<XMLNode*> namespaces)
{
}

void XMLElement::AddChild(XMLNode* child)
{
	m_children.push_back(child);
}

void XMLElement::InsertChildAtIndex(XMLNode* child, size_t index)
{
	m_children.insert(m_children.begin() + index, child);
}

void XMLElement::InsertChildrenAtIndex(vector<XMLNode*> children, size_t index)
{
	m_children.insert(m_children.begin() + index, children.begin(), children.end());
}

void XMLElement::RemoveChildAtIndex(size_t index)
{
	m_children.erase(m_children.begin() + index);
}

void XMLElement::ReplaceChildAtIndex(size_t index, XMLNode* node)
{
	XMLNode* oldNode  = m_children[index];
	m_children[index] = node;
	delete oldNode;
}

void XMLElement::SetChildren(vector<XMLNode*> children)
{
	m_children = children;
}
