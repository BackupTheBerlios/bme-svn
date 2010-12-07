/*
 *  XMLDocument.cpp
 *  BmeApp
 *
 *  Created by Tim De Jong on 26-08-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */

#include "XMLDocument.h"

XMLDocument::XMLDocument()
				: XMLNode(XMLDocumentKind)
{
}

XMLDocument::XMLDocument(string xmlString)
				: XMLNode(XMLDocumentKind)
{
}

XMLDocument::XMLDocument(XMLElement* root)
				: XMLNode(XMLDocumentKind)
{
	this->SetRootElement(root);
}

XMLDocument::~XMLDocument()
{
	delete m_rootElement;
}

string XMLDocument::Version()
{
	return m_version;
}

void XMLDocument::SetVersion(string version)
{
	m_version = version;
}

XMLElement* XMLDocument::RootElement()
{
	return m_rootElement;
}

void XMLDocument::SetRootElement(XMLNode* root)
{
	if (root->Kind() == XMLElementKind)
	{
		m_rootElement = (XMLElement*)root;
	}
}

void XMLDocument::AddChild(XMLNode* child)
{
	m_children.push_back(child);
}

void XMLDocument::InsertChildAtIndex(XMLNode* child, size_t index)
{
	m_children.insert(m_children.begin() + index, child);
}

void XMLDocument::InsertChildrenAtIndex(vector<XMLNode*> children, size_t index)
{
	m_children.insert(m_children.begin() + index, children.begin(), children.end());
}

void XMLDocument::RemoveChildAtIndex(size_t index)
{
	m_children.erase(m_children.begin() + index);
}

void XMLDocument::ReplaceChildAtIndex(size_t index, XMLNode* node)
{
	XMLNode* oldNode  = m_children[index];
	m_children[index] = node;
	delete oldNode;
}

void XMLDocument::SetChildren(vector<XMLNode*> children)
{
	m_children = children;
}
