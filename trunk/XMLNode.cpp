/*
 *  XMLNode.cpp
 *  BmeApp
 *
 *  Created by Tim De Jong on 26-08-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */

#include "XMLNode.h"

XMLNode::XMLNode()
			:	m_xmlNodeKind(XMLInvalidKind)
{
}

XMLNode::XMLNode(XMLNodeKind xmlNodeKind)
			:	m_xmlNodeKind(xmlNodeKind)
{
}

XMLNode::~XMLNode()
{
	typedef vector<XMLNode*>::iterator NI;
	//delete all of the node's children
	for (NI n = m_children.begin(); n != m_children.end(); ++n)
	{
		XMLNode* node = *n;
		delete node;
	}
}

size_t XMLNode::Index()
{
	return m_index;
}

XMLNode::XMLNodeKind XMLNode::Kind()
{
	return m_xmlNodeKind;
}

size_t XMLNode::Level()
{
	return m_level;
}

void XMLNode::SetName(std::string name)
{
	m_name = name;
}

string XMLNode::Name()
{
	return m_name;
}

void XMLNode::SetStringValue(std::string value)
{
	m_stringValue = value;
}

string XMLNode::StringValue()
{
	return m_stringValue;
}

XMLDocument* XMLNode::RootDocument()
{
	return m_rootDocument;
}

XMLNode* XMLNode::Parent()
{
	return m_parent;
}

void XMLNode::AddChild(XMLNode* child)
{
	m_children.push_back(child);
}

XMLNode* XMLNode::ChildAtIndex(size_t index)
{
	if (index < ChildCount())
	{
		return m_children[index];
	}
	return NULL;
}

size_t XMLNode::ChildCount()
{
	return m_children.size();
}

vector<XMLNode*> XMLNode::Children()
{
	return m_children;
}

XMLNode* XMLNode::NextNode()
{
	return m_nextNode;
}

XMLNode* XMLNode::NextSibling()
{
	XMLNode* parent = this->Parent();
	if (parent)
	{
		return parent->ChildAtIndex(this->Index() + 1);
	}
	return NULL;
}

XMLNode* XMLNode::PreviousNode()
{
	return m_previousNode;
}

XMLNode* XMLNode::PreviousSibling()
{
	XMLNode* parent = this->Parent();
	if (parent)
	{
		return parent->ChildAtIndex(this->Index() - 1);
	}
	return NULL;
}

string XMLNode::XMLString()
{
	return m_xmlString;
}

void XMLNode::SetIndex(size_t index)
{
	m_index = index;
}

void XMLNode::SetKind(XMLNodeKind kind)
{
	m_xmlNodeKind = kind;
}

void XMLNode::SetLevel(size_t level)
{
	m_level = level;
}

void XMLNode::SetRootDocument(XMLDocument* rootDocument)
{
	m_rootDocument = rootDocument;
}

void XMLNode::SetParent(XMLNode* parent)
{
	m_parent = parent;
}

void  XMLNode::SetNextNode(XMLNode* nextNode)
{
	m_nextNode = nextNode;
}

void  XMLNode::SetPreviousNode(XMLNode* previousNode)
{
	m_previousNode = previousNode;
}

void XMLNode::SetXMLString(string xmlString)
{
	m_xmlString = xmlString;
}

